#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

int color_array[3];
CRGBPalette16 soothing_userdefined_gp;
CRGBPalette16 refreshing_userdefined_gp;

long start_soothing_time;
long stop_soothing_time;
unsigned long soothing_step;
long start_refreshing_time;
long stop_refreshing_time;
unsigned long refreshing_step;
unsigned long startMillis;
unsigned long currentMillis;

//soothing default color palette
// Gradient palette "Sunset_Real_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Real.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.
DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
    0, 120,  0,  0,
   22, 179, 22,  0,
   51, 255,104,  0,
   85, 167, 22, 18,
  135, 100,  0,103,
  198,  16,  0,130,
  255,   0,  0,160};

//refreshing default color palette
// Gradient palette "bhw3_21_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_21.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.
DEFINE_GRADIENT_PALETTE( bhw3_21_gp ) {
    0,   1, 40, 98,
   48,   1, 65, 68,
   76,   2,161, 96,
  104,   0, 81, 25,
  130,  65,182, 82,
  153,   0, 86,170,
  181,  17,207,182,
  204,  17,207,182,
  255,   1, 23, 46};

void aplication_configs() {
	config.latitude = "";
	config.longitude = "";
	config.sunrise = "";
	config.sunset = "";
	config.twilight = "";
	config.soothingcolors = 0;
	config.refreshingcolors = 0;
	config.sunset_delay = "120";
	config.wakeup_delay = "30";
	config.alarm_hour = "6";
	config.alarm_minute = "45";
	config.weekday = 62;
	config.scolor1 = "#530031";
	config.scolor2 = "#842742";
	config.scolor3 = "#b32424";
	config.scolor4 = "#ff7100";
	config.scolor5 = "#ff9900";
	config.rcolor1 = "#84f63a";
	config.rcolor2 = "#69ef88";
	config.rcolor3 = "#f53f16";
	config.rcolor4 = "#3ea1e2";
	config.rcolor5 = "#edf079";
	config.hcolor1 = "#FF0000"; //red   from fastled rainbow color palette
	config.hcolor2 = "#AB5500"; //orange
	config.hcolor3 = "#ABAB00"; //yellow
	config.hcolor4 = "#00FF00"; //green
	config.hcolor5 = "#00AB55"; //aqua
	config.hcolor6 = "#0000FF"; //blue
	config.hcolor7 = "#5500AB"; //purple
}

void HEX2RGB(String hex_value) {
int number = (int) strtol( &hex_value[1], NULL, 16);
color_array[0] = number >> 16;
color_array[1] = number >> 8 & 0xFF;
color_array[2] = number & 0xFF;
}

void hourcolors_switch (int n) {
	switch(n) {
	case 0: {
		HEX2RGB(config.hcolor1);
	}
	break;
	case 1: {
		HEX2RGB(config.hcolor2);
	}
	break;
	case 2: {
		HEX2RGB(config.hcolor3);
	}
	break;
	case 3: {
		HEX2RGB(config.hcolor4);
	}
	break;
	case 4: {
		HEX2RGB(config.hcolor5);
	}
	break;
	case 5: {
		HEX2RGB(config.hcolor6);
	}
	break;
	case 6: {
		HEX2RGB(config.hcolor7);
	}
	break;
	}
}

void schedule_init () {
	sunRiseSet ();
	config.sunrise = string_rise;
	config.sunset = string_set;
	config.twilight = string_twilight;
	Serial.println("--------------");
	Serial.println(string_rise);
	Serial.println(string_set);
	Serial.println(string_twilight);
	soothing_step = (twilight*3600*1000)/fullbrightness;
	start_soothing_time = set*3600; // - int(soothing_step/1000)
	stop_soothing_time = start_soothing_time + (twilight*3600) + config.sunset_delay.toInt()*60;
	Serial.println("--------------");
	Serial.println(soothing_step);
	Serial.println(start_soothing_time);
	Serial.println(stop_soothing_time);
	if (stop_soothing_time >= 86399) { //one second before midnight
		stop_soothing_time = 86399;
	}
	refreshing_step = (5*60*1000)/fullbrightness;
	start_refreshing_time = config.alarm_hour.toInt()*3600 + config.alarm_minute.toInt()*60 - 5*60; // 5 minutes before wake up
	stop_refreshing_time = start_refreshing_time + 5*60 + config.wakeup_delay.toInt()*60;
	Serial.println("--------------");
	Serial.println(refreshing_step);
	Serial.println(start_refreshing_time);
	Serial.println(stop_refreshing_time);
}

void user_color_init () {
	//soothing user defined palette
	uint8_t palette1[20];
	HEX2RGB(config.scolor1);
	palette1[0] = 0;  // anchor of first color - must be zero
	palette1[1] = color_array[0];
	palette1[2] = color_array[1];
	palette1[3] = color_array[2];
	HEX2RGB(config.scolor2);
	//palette1[4] = 63;
	palette1[4] = random8(39,87);
	palette1[5] = color_array[0];
	palette1[6] = color_array[1];
	palette1[7] = color_array[2];
	HEX2RGB(config.scolor3);
	//palette1[8] = 127;
	palette1[8] = random8(103,151);
	palette1[9] = color_array[0];
	palette1[10] = color_array[1];
	palette1[11] = color_array[2];
	HEX2RGB(config.scolor4);
	//palette1[12] = 191;
	palette1[12] = random8(167,215);
	palette1[13] = color_array[0];
	palette1[14] = color_array[1];
	palette1[15] = color_array[2];
	HEX2RGB(config.scolor5);
	palette1[16] = 255; // anchor of last color - must be 255
	palette1[17] = color_array[0];
	palette1[18] = color_array[1];
	palette1[19] = color_array[2];
	soothing_userdefined_gp = palette1;

	//refreshing user defined palette
	uint8_t palette2[20];
	HEX2RGB(config.rcolor1);
	palette2[0] = 0;  // anchor of first color - must be zero
	palette2[1] = color_array[0];
	palette2[2] = color_array[1];
	palette2[3] = color_array[2];
	HEX2RGB(config.rcolor2);
	//palette2[4] = 63;
	palette2[4] = random8(39,87);
	palette2[5] = color_array[0];
	palette2[6] = color_array[1];
	palette2[7] = color_array[2];
	HEX2RGB(config.rcolor3);
	//palette2[8] = 127;
	palette2[8] = random8(103,151);
	palette2[9] = color_array[0];
	palette2[10] = color_array[1];
	palette2[11] = color_array[2];
	HEX2RGB(config.rcolor4);
	//palette2[12] = 191;
	palette2[12] = random8(167,215);
	palette2[13] = color_array[0];
	palette2[14] = color_array[1];
	palette2[15] = color_array[2];
	HEX2RGB(config.rcolor5);
	palette2[16] = 255; // anchor of last color - must be 255
	palette2[17] = color_array[0];
	palette2[18] = color_array[1];
	palette2[19] = color_array[2];
	refreshing_userdefined_gp = palette2;
}

CRGBPalette16 hour_color_init () {
	uint8_t palette[12];
	palette[0] = 0;
	palette[1] = 0;
	palette[2] = 0;
	palette[3] = 0;
	palette[4] = 127;
	palette[5] = color_array[0];
	palette[6] = color_array[1];
	palette[7] = color_array[2];
	palette[8] = 255;
	palette[9] = 0;
	palette[10] = 0;
	palette[11] = 0;
	return palette;
}

void clear_leds () {
	fill_solid( leds, NUM_LEDS, CRGB(0,0,0));
	FastLED.setBrightness(0);
}

// code from https://gist.github.com/kriegsman/8281905786e8b2632aeb
void ColorWaves( CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette)
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 300, 1500);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;

  for( uint16_t i = 0 ; i < numleds; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    uint16_t h16_128 = hue16 >> 7;
    if( h16_128 & 0x100) {
      hue8 = 255 - (h16_128 >> 1);
    } else {
      hue8 = h16_128 >> 1;
    }

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    uint8_t index = hue8;
    //index = triwave8( index);
    index = scale8( index, 240);

    CRGB newcolor = ColorFromPalette( palette, index, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (numleds-1) - pixelnumber;

    nblend( ledarray[pixelnumber], newcolor, 128);
  }
}
// code from https://github.com/atuline/FastLED-Demos/blob/master/inoise8_fire/inoise8_fire.ino
void inoise8_fire() {
  for(int i = 0; i < NUM_LEDS; i++) {
    index1 = inoise8(i*xscale,millis()*yscale*NUM_LEDS/255);                                           // X location is constant, but we move along the Y at the rate of millis()
    leds[i] = ColorFromPalette(gPal, _min(i*(index1)>>6, 255), i*255/NUM_LEDS, LINEARBLEND);            // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }                                                                                                   // The higher the value of i => the higher up the palette index (see palette definition).
                                                                                                      // Also, the higher the value of i => the brighter the LED.
}

// code from https://gist.github.com/kriegsman/964de772d64c502760e5
void pride()
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;

  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    CRGB newcolor = CHSV( hue8, sat8, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;

    nblend( leds[pixelnumber], newcolor, 64);
  }
}

//code from https://gist.github.com/kriegsman/99082f66a726bdff7776
const CRGB lightcolor(8,5,1);

void softtwinkles() {
  for( int i = 0; i < NUM_LEDS; i++) {
    if( !leds[i]) continue; // skip black pixels
    if( leds[i].r & 1) { // is red odd?
      leds[i] -= lightcolor; // darken if red is odd
    } else {
      leds[i] += lightcolor; // brighten if red is even
    }
  }

  // Randomly choose a pixel, and if it's black, 'bump' it up a little.
  // Since it will now have an EVEN red component, it will start getting
  // brighter over time.
  if( random8() < DENSITY) {
    int j = random16(NUM_LEDS);
    if( !leds[j] ) leds[j] = lightcolor;
  }
}


#endif /* MAINFUNCTIONS_H_*/
