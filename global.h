#ifndef GLOBAL_H
#define GLOBAL_H


ESP8266WebServer server(80);							// The Webserver
boolean firstStart = true;								// On firststart = true, NTP will try to get a valid time
boolean ntp_response_ok = false;
boolean manual_time_set = false;
boolean TestSoothingColors = false;
boolean TestRefreshingColors = false;
boolean TestHourColor = false;
boolean StopSoothing = false;
boolean StopRefreshing = false;
boolean StopHourColor = false;
int HourColorTestStep = 0;
String chipID;
int WIFI_connected = false;
bool CFG_saved = false;
int AdminTimeOutCounter = 0;							// Counter for Disabling the AdminMode
WiFiUDP UDPNTPClient;											// NTP Client
volatile unsigned long UnixTimestamp = 0;	// GLOBALTIME  ( Will be set by NTP)
int cNTP_Update = 0;											// Counter for Updating the time via NTP
Ticker tkSecond;												  // Second - Timer for Updating Datetime Structure
//custom declarations

bool date_ok = false;
long absoluteActualTime, actualTime;
long  customWatchdog;                     // WatchDog to detect main loop blocking. There is a builtin WatchDog to the chip firmare not related to this one


struct strConfig {
  boolean dhcp;                         // 1 Byte - EEPROM 16
  boolean isDayLightSaving;             // 1 Byte - EEPROM 17
  long Update_Time_Via_NTP_Every;       // 4 Byte - EEPROM 18
  long timeZone;                        // 4 Byte - EEPROM 22
  byte  IP[4];                          // 4 Byte - EEPROM 32
  byte  Netmask[4];                     // 4 Byte - EEPROM 36
  byte  Gateway[4];                     // 4 Byte - EEPROM 40
  String ssid;                          // up to 32 Byte - EEPROM 64
  String password;                      // up to 32 Byte - EEPROM 96
  String ntpServerName;                 // up to 32 Byte - EEPROM 128
  String DeviceName;                    // up to 32 Byte - EEPROM 160
  // Application Settings here... from EEPROM 192 up to 511 (0 - 511)
  String latitude;
  String longitude;
  String sunrise;
  String sunset;
  String twilight;
  boolean soothingcolors;
  boolean refreshingcolors;
  String sunset_delay;
  String wakeup_delay;
  String alarm_hour;
  String alarm_minute;
  byte weekday;
  String scolor1;
  String scolor2;
  String scolor3;
  String scolor4;
  String scolor5;
  String rcolor1;
  String rcolor2;
  String rcolor3;
  String rcolor4;
  String rcolor5;
  String hcolor1;
  String hcolor2;
  String hcolor3;
  String hcolor4;
  String hcolor5;
  String hcolor6;
  String hcolor7;
} config;


//  Auxiliar function to handle EEPROM

void EEPROMWritelong(int address, long value){
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);

  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

long EEPROMReadlong(long address){
  //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);

  //Return the recomposed long by using bitshift.
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

// Check the Values is between 0-255
boolean checkRange(String Value){
  if (Value.toInt() < 0 || Value.toInt() > 255)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void WriteStringToEEPROM(int beginaddress, String string){
  char  charBuf[string.length() + 1];
  string.toCharArray(charBuf, string.length() + 1);
  for (int t =  0; t < sizeof(charBuf); t++)
  {
    EEPROM.write(beginaddress + t, charBuf[t]);
  }
}

String  ReadStringFromEEPROM(int beginaddress){
  volatile byte counter = 0;
  char rChar;
  String retString = "";
  while (1)
  {
    rChar = EEPROM.read(beginaddress + counter);
    if (rChar == 0) break;
    if (counter > 31) break;
    counter++;
    retString.concat(rChar);

  }
  return retString;
}


/*
**
** CONFIGURATION HANDLING
**
*/
void ConfigureWifi(){
  Serial.println("Configuring Wifi");
  WiFi.begin (config.ssid.c_str(), config.password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    delay(500);
  }
  if (!config.dhcp)
  {
    WiFi.config(IPAddress(config.IP[0], config.IP[1], config.IP[2], config.IP[3] ),  IPAddress(config.Gateway[0], config.Gateway[1], config.Gateway[2], config.Gateway[3] ) , IPAddress(config.Netmask[0], config.Netmask[1], config.Netmask[2], config.Netmask[3] ));
  }
}


void WriteConfig(){

  Serial.println("Writing Config");
  EEPROM.write(0, 'C');
  EEPROM.write(1, 'F');
  EEPROM.write(2, 'G');

  EEPROM.write(16, config.dhcp);
  EEPROM.write(17, config.isDayLightSaving);

  EEPROMWritelong(18, config.Update_Time_Via_NTP_Every); // 4 Byte
  EEPROMWritelong(22, config.timeZone); // 4 Byte

  EEPROM.write(32, config.IP[0]);
  EEPROM.write(33, config.IP[1]);
  EEPROM.write(34, config.IP[2]);
  EEPROM.write(35, config.IP[3]);

  EEPROM.write(36, config.Netmask[0]);
  EEPROM.write(37, config.Netmask[1]);
  EEPROM.write(38, config.Netmask[2]);
  EEPROM.write(39, config.Netmask[3]);

  EEPROM.write(40, config.Gateway[0]);
  EEPROM.write(41, config.Gateway[1]);
  EEPROM.write(42, config.Gateway[2]);
  EEPROM.write(43, config.Gateway[3]);

  WriteStringToEEPROM(64, config.ssid);
  WriteStringToEEPROM(96, config.password);
  WriteStringToEEPROM(128, config.ntpServerName);
  WriteStringToEEPROM(160, config.DeviceName);
  // Application Settings here... from EEPROM 192 up to 511 (0 - 511)
  WriteStringToEEPROM(192, config.latitude);
  WriteStringToEEPROM(202, config.longitude);
  WriteStringToEEPROM(212, config.sunrise);
  WriteStringToEEPROM(222, config.sunset);
  WriteStringToEEPROM(232, config.twilight);
  EEPROM.write(242, config.soothingcolors);
  EEPROM.write(243, config.refreshingcolors);
  WriteStringToEEPROM(244, config.sunset_delay);
  WriteStringToEEPROM(249, config.wakeup_delay);
  WriteStringToEEPROM(254, config.alarm_hour);
  WriteStringToEEPROM(259, config.alarm_minute);
  EEPROM.write(264, config.weekday);
  WriteStringToEEPROM(265, config.scolor1);
  WriteStringToEEPROM(275, config.scolor2);
  WriteStringToEEPROM(285, config.scolor3);
  WriteStringToEEPROM(295, config.scolor4);
  WriteStringToEEPROM(305, config.scolor5);
  WriteStringToEEPROM(315, config.rcolor1);
  WriteStringToEEPROM(325, config.rcolor2);
  WriteStringToEEPROM(335, config.rcolor3);
  WriteStringToEEPROM(345, config.rcolor4);
  WriteStringToEEPROM(355, config.rcolor5);
  WriteStringToEEPROM(365, config.hcolor1);
  WriteStringToEEPROM(375, config.hcolor2);
  WriteStringToEEPROM(385, config.hcolor3);
  WriteStringToEEPROM(395, config.hcolor4);
  WriteStringToEEPROM(405, config.hcolor5);
  WriteStringToEEPROM(415, config.hcolor6);
  WriteStringToEEPROM(425, config.hcolor7);
  EEPROM.commit();
}

boolean ReadConfig(){
  Serial.println("Reading Configuration");
  if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F'  && EEPROM.read(2) == 'G' )
  {
    Serial.println("Configuration Found!");
    config.dhcp = 	EEPROM.read(16);
    config.isDayLightSaving = EEPROM.read(17);
    config.Update_Time_Via_NTP_Every = EEPROMReadlong(18); // 4 Byte
    config.timeZone = EEPROMReadlong(22); // 4 Byte
    config.IP[0] = EEPROM.read(32);
    config.IP[1] = EEPROM.read(33);
    config.IP[2] = EEPROM.read(34);
    config.IP[3] = EEPROM.read(35);
    config.Netmask[0] = EEPROM.read(36);
    config.Netmask[1] = EEPROM.read(37);
    config.Netmask[2] = EEPROM.read(38);
    config.Netmask[3] = EEPROM.read(39);
    config.Gateway[0] = EEPROM.read(40);
    config.Gateway[1] = EEPROM.read(41);
    config.Gateway[2] = EEPROM.read(42);
    config.Gateway[3] = EEPROM.read(43);
    config.ssid = ReadStringFromEEPROM(64);
    config.password = ReadStringFromEEPROM(96);
    config.ntpServerName = ReadStringFromEEPROM(128);
    config.DeviceName = ReadStringFromEEPROM(160);
    // Application parameters here ... from EEPROM 192 to 511
    config.latitude = ReadStringFromEEPROM(192);
    config.longitude = ReadStringFromEEPROM(202);
    config.sunrise = ReadStringFromEEPROM(212);
    config.sunset = ReadStringFromEEPROM(222);
    config.twilight = ReadStringFromEEPROM(232);
    config.soothingcolors = EEPROM.read(242);
    config.refreshingcolors = EEPROM.read(243);
    config.sunset_delay = ReadStringFromEEPROM(244);
    config.wakeup_delay = ReadStringFromEEPROM(249);
    config.alarm_hour = ReadStringFromEEPROM(254);
    config.alarm_minute = ReadStringFromEEPROM(259);
    config.weekday = EEPROM.read(264);
    config.scolor1 = ReadStringFromEEPROM(265);
    config.scolor2 = ReadStringFromEEPROM(275);
    config.scolor3 = ReadStringFromEEPROM(285);
    config.scolor4 = ReadStringFromEEPROM(295);
    config.scolor5 = ReadStringFromEEPROM(305);
    config.rcolor1 = ReadStringFromEEPROM(315);
    config.rcolor2 = ReadStringFromEEPROM(325);
    config.rcolor3 = ReadStringFromEEPROM(335);
    config.rcolor4 = ReadStringFromEEPROM(345);
    config.rcolor5 = ReadStringFromEEPROM(355);
    config.hcolor1 = ReadStringFromEEPROM(365);
    config.hcolor2 = ReadStringFromEEPROM(375);
    config.hcolor3 = ReadStringFromEEPROM(385);
    config.hcolor4 = ReadStringFromEEPROM(395);
    config.hcolor5 = ReadStringFromEEPROM(405);
    config.hcolor6 = ReadStringFromEEPROM(415);
    config.hcolor7 = ReadStringFromEEPROM(425);
    return true;
  }
  else
  {
    Serial.println("Configuration NOT FOUND!!!!");
    return false;
  }
}


void printConfig(){

  Serial.println("Printing Config");

  Serial.printf("DHCP:%d\n", config.dhcp);
  Serial.printf("DayLight:%d\n", config.isDayLightSaving);

  Serial.printf("NTP update every %ld sec\n", config.Update_Time_Via_NTP_Every); // 4 Byte
  Serial.printf("Timezone %ld\n", config.timeZone); // 4 Byte

  Serial.printf("IP:%d.%d.%d.%d\n", config.IP[0],config.IP[1],config.IP[2],config.IP[3]);
  Serial.printf("Mask:%d.%d.%d.%d\n", config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3]);
  Serial.printf("Gateway:%d.%d.%d.%d\n", config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3]);

  Serial.printf("SSID:%s\n", config.ssid.c_str());
  Serial.printf("PWD:%s\n", config.password.c_str());
  Serial.printf("ntp ServerName:%s\n", config.ntpServerName.c_str());
  Serial.printf("Device Name:%s\n", config.DeviceName.c_str());

  Serial.printf("Latitude:%s\n", config.latitude.c_str());
  Serial.printf("Longitude:%s\n", config.longitude.c_str());

  Serial.printf("Sunrise:%s\n", config.sunrise.c_str());
  Serial.printf("Sunset:%s\n", config.sunset.c_str());
  Serial.printf("Twilight:%s\n", config.twilight.c_str());

  Serial.printf("scolor1:%s\n", config.scolor1.c_str());
  Serial.printf("rcolor1:%s\n", config.rcolor1.c_str());
  Serial.printf("hcolor1:%s\n", config.hcolor1.c_str());

    // Application Settings here... from EEPROM 192 up to 511 (0 - 511)

}



String GetMacAddress(){
  uint8_t mac[6];
  char macStr[18] = {0};
  WiFi.macAddress(mac);
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],  mac[1], mac[2], mac[3], mac[4], mac[5]);
  return  String(macStr);
}

String GetAPMacAddress(){
  uint8_t mac[6];
  char macStr[18] = {0};
  WiFi.softAPmacAddress(mac);
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],  mac[1], mac[2], mac[3], mac[4], mac[5]);
  return  String(macStr);
}

// convert a single hex digit character to its integer value (from https://code.google.com/p/avr-netino/)
unsigned char h2int(char c){
  if (c >= '0' && c <= '9') {
    return ((unsigned char)c - '0');
  }
  if (c >= 'a' && c <= 'f') {
    return ((unsigned char)c - 'a' + 10);
  }
  if (c >= 'A' && c <= 'F') {
    return ((unsigned char)c - 'A' + 10);
  }
  return (0);
}

String urldecode(String input) // (based on https://code.google.com/p/avr-netino/)
{
  char c;
  String ret = "";

  for (byte t = 0; t < input.length(); t++)
  {
    c = input[t];
    if (c == '+') c = ' ';
    if (c == '%') {


      t++;
      c = input[t];
      t++;
      c = (h2int(c) << 4) | h2int(input[t]);
    }

    ret.concat(c);
  }
  return ret;

}

#endif
