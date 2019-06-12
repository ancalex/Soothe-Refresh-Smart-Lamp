#define FASTLED_INTERRUPT_RETRY_COUNT 0
#include "FastLED.h"

/*
 * * ESP8266 template with phone config web page
 * based on BVB_WebConfig_OTA_V7 from Andreas Spiess https://github.com/SensorsIot/Internet-of-Things-with-ESP8266
 *
 */

#define DATA_PIN    2
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    30
#define DENSITY     40
CRGB leds[NUM_LEDS];
//#define FRAMES_PER_SECOND  30
uint8 fullbrightness = 120;
uint8 brightness = 1;
CRGBPalette16 gPal;
uint32_t xscale = 20;
uint32_t yscale = 3;
uint8_t index1 = 0;

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <Ticker.h>
#include <EEPROM.h>
#include "global.h"
#include "NTP.h"
#include "GeoLocation.h"
#include "SunCalculator.h"
#include "MainFunctions.h"

// Include STYLE and Script "Pages"
#include "Page_Script.js.h"
#include "Page_Style.css.h"

// Include HTML "Pages"
#include "Page_ScheduleSettings.h"
#include "Page_Admin.h"
#include "Page_NTPSettings.h"
#include "Page_Information.h"
#include "Page_NetworkConfiguration.h"
#include "Page_SetTime.h"
#include "Page_GeoLocation.h"

extern "C" {
#include "user_interface.h"
}

void setup() {

	Serial.begin(115200);

	//**** Network Config load
	EEPROM.begin(512); // define an EEPROM space of 512Bytes to store data
	CFG_saved = ReadConfig();

	//  Connect to WiFi acess point or start as Acess point
	if (CFG_saved)  //if no configuration yet saved, load defaults
	{
		// Connect the ESP8266 to local WIFI network in Station mode
		Serial.println("Booting");
		//printConfig();
		WiFi.mode(WIFI_STA);
		WiFi.begin(config.ssid.c_str(), config.password.c_str());
		WIFI_connected = WiFi.waitForConnectResult();
		if (WIFI_connected != WL_CONNECTED)
			Serial.println("Connection Failed! activating the AP mode...");

		Serial.print("Wifi ip:");
		Serial.println(WiFi.localIP());
	}

	if ((WIFI_connected != WL_CONNECTED) or !CFG_saved) {
		// DEFAULT CONFIG
		Serial.println("Setting AP mode default parameters");
		config.ssid = "S&R_SMART_LAMP-" + String(ESP.getChipId(), HEX); // SSID of access point
		config.password = "";   // password of access point
		config.dhcp = true;
		config.IP[0] = 192;
		config.IP[1] = 168;
		config.IP[2] = 1;
		config.IP[3] = 100;
		config.Netmask[0] = 255;
		config.Netmask[1] = 255;
		config.Netmask[2] = 255;
		config.Netmask[3] = 0;
		config.Gateway[0] = 192;
		config.Gateway[1] = 168;
		config.Gateway[2] = 1;
		config.Gateway[3] = 254;
		config.DeviceName = "S&R_SMART_LAMP";
		config.ntpServerName = "0.ro.pool.ntp.org"; // to be adjusted to PT ntp.ist.utl.pt
		config.Update_Time_Via_NTP_Every = 3;
		config.timeZone = 20;
		config.isDayLightSaving = true;
		aplication_configs();
		//WriteConfig();
		WiFi.mode(WIFI_AP);
		WiFi.softAP(config.ssid.c_str(),"admin1234");
		Serial.print("Wifi ip:");
		Serial.println(WiFi.softAPIP());
	}

	// Start HTTP Server for configuration
	server.on("/", []() {
		Serial.println("admin.html");
		server.send_P ( 200, "text/html", PAGE_AdminMainPage); // const char top of page
	});

	server.on("/favicon.ico", []() {
		Serial.println("favicon.ico");
		server.send( 200, "text/html", "" );
	});
	server.on("/schedule.html", send_schedule_settings_html);
	server.on("/geolocation.html", send_geolocation_html);
	// Network config
	server.on("/config.html", send_network_configuration_html);
	// Info Page
	server.on("/info.html", []() {
		Serial.println("info.html");
		server.send_P ( 200, "text/html", PAGE_Information );
	});
	server.on("/ntp.html", send_NTP_configuration_html);
	server.on("/time.html", send_Time_Set_html);
	server.on("/style.css", []() {
		Serial.println("style.css");
		server.send_P ( 200, "text/plain", PAGE_Style_css );
	});
	server.on("/microajax.js", []() {
		Serial.println("microajax.js");
		server.send_P ( 200, "text/plain", PAGE_microajax_js );
	});
	server.on("/admin/values", send_network_configuration_values_html);
	server.on("/admin/connectionstate", send_connection_state_values_html);
	server.on("/admin/infovalues", send_information_values_html);
	server.on("/admin/ntpvalues", send_NTP_configuration_values_html);
	server.on("/admin/timevalues", send_Time_Set_values_html);
	server.on("/admin/schedulevalues", send_schedule_settings_values_html);
	server.on("/admin/geolocationvalues", send_geolocation_values_html);
	server.on("/admin/geolocationresults", send_geolocation_results_html);
	server.onNotFound([]() {
		Serial.println("Page Not Found");
		server.send ( 400, "text/html", "Page not Found" );
	});
	server.begin();
	Serial.println("HTTP server started");

	printConfig();

	// start internal time update ISR
	tkSecond.attach(1, ISRsecondTick);

	// tell FastLED about the LED strip configuration
	FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
	    						//.setCorrection(TypicalLEDStrip) // cpt-city palettes have different color balance
	    						.setDither(fullbrightness < 255);
	FastLED.setBrightness(fullbrightness);

	Serial.println("FastLed Setup done");

	// start internal time update ISR
	tkSecond.attach(1, ISRsecondTick);
	//GeoLocation();
}

// the loop function runs over and over again forever
void loop() {
	server.handleClient();

	if (config.Update_Time_Via_NTP_Every > 0) {
		if (cNTP_Update > 5 && firstStart) {
			getNTPtime();
            delay(1500); //wait for DateTime
			schedule_init();
			user_color_init();
			cNTP_Update = 0;
			firstStart = false;
		}
		else if (cNTP_Update > (config.Update_Time_Via_NTP_Every * 60)) {
			getNTPtime();
			cNTP_Update = 0;
		}
	}
	//  feed de DOG :)
	customWatchdog = millis();

	//============================
	if (WIFI_connected != WL_CONNECTED and manual_time_set == false) {
		config.Update_Time_Via_NTP_Every = 0;
		//display_animation_no_wifi();
		softtwinkles();
	} else if (ntp_response_ok == false and manual_time_set == false) {
		config.Update_Time_Via_NTP_Every = 1;
		//display_animation_no_ntp();
		pride();
	} else if (ntp_response_ok == true or manual_time_set == true) {
		schedule();
	}
	FastLED.show();
}

void schedule() {
	if (actualTime == 0) {
		schedule_init();
		user_color_init();
		delay(1000);
	}
	if ((actualTime > start_soothing_time) and (actualTime < stop_soothing_time) and (StopSoothing == false)) {
		currentMillis = millis();
		if (config.soothingcolors == 0) {
			gPal = Sunset_Real_gp;
		} else {
			gPal = soothing_userdefined_gp;
		}
		FastLED.setBrightness(brightness);
		ColorWaves(leds, NUM_LEDS, gPal);
		if (currentMillis - startMillis >= soothing_step) {
			Serial.println("soothing-step");
			Serial.println(soothing_step);
			Serial.println(twilight);
			Serial.println(brightness);
			if (brightness <= fullbrightness) {
				brightness += 1;
			}
			startMillis = currentMillis;
		}
	}
	else if ((actualTime > start_refreshing_time) and (actualTime < stop_refreshing_time) and (StopRefreshing == false) and (IsBitSet(config.weekday, DayOfTheWeek(DateTime.year, DateTime.month, DateTime.day)))) {
		currentMillis = millis();
		if (config.refreshingcolors == 0) {
			gPal = bhw3_21_gp;
		} else {
			gPal = refreshing_userdefined_gp;
		}
		FastLED.setBrightness(brightness);
		ColorWaves(leds, NUM_LEDS, gPal);
		if (currentMillis - startMillis >= refreshing_step) {
			Serial.println("refreshing-step");
			Serial.println(refreshing_step);
			Serial.println(twilight);
			Serial.println(brightness);
			if (brightness <= fullbrightness) {
				brightness += 1;
			}
			startMillis = currentMillis;
		}
	}
	else if ((actualTime >= 1) and actualTime <= (7*3600) and (StopHourColor == false) and (DateTime.year != 1970))  {
		brightness = 4;
		FastLED.setBrightness(brightness);
		int n = int(actualTime/3600);
		hourcolors_switch (n);
		gPal = hour_color_init ();
		ColorWaves(leds, NUM_LEDS, gPal);
	}
	else if (TestSoothingColors == true) {
		if (config.soothingcolors == 0) {
			gPal = Sunset_Real_gp;
		} else {
			gPal = soothing_userdefined_gp;
		}
		FastLED.setBrightness(fullbrightness);
		ColorWaves(leds, NUM_LEDS, gPal);
	}
	else if (TestRefreshingColors == true) {
		if (config.refreshingcolors == 0) {
			gPal = bhw3_21_gp;
		} else {
			gPal = refreshing_userdefined_gp;
		}
		FastLED.setBrightness(fullbrightness);
		ColorWaves(leds, NUM_LEDS, gPal);
	}
	else if (TestHourColor == true) {
		brightness = 4;
		FastLED.setBrightness(brightness);
		hourcolors_switch (HourColorTestStep);
		gPal = hour_color_init ();
		//ColorWaves(leds, NUM_LEDS, gPal);
        inoise8_fire();
		currentMillis = millis();
		if (currentMillis - startMillis >= 3000) {
			if (HourColorTestStep < 6) {
				HourColorTestStep += 1;
			}
			else {
				HourColorTestStep = 0;
			}
			startMillis = currentMillis;
		}
	}
	else {
		startMillis = millis();
		HourColorTestStep = 0;
		brightness = 4;
		clear_leds();
	}

}

