
#ifndef PAGE_SCHEDULESETTINGS_H
#define PAGE_SCHEDULESETTINGS_H

const char PAGE_ScheduleSettings[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s btn--orange">&#9664;</a>&nbsp;&nbsp;<strong>Schedule Settings</strong>
<hr>
<form "action="" method="get">
<b><i>SOOTHING COLORS<b></i>
<table style="border:none;margin-left:10px">
  <tr>
    <td align="right"><label for="soothingcolorsd">default</label></td>
    <td colspan="6"><input type="checkbox" id="soothingcolorsd" name="soothingcolorsd" onclick="if(this.checked) document.getElementById('soothingcolorsu').checked=false; document.getElementById('soothingcolorsd').checked=true;"></td>
  </tr>
  <tr>
    <td align="right"><label for="soothingcolorsu">user</label></td>
	<td><input type="checkbox" id="soothingcolorsu" name="soothingcolorsu" onclick="if(this.checked) document.getElementById('soothingcolorsd').checked=false; document.getElementById('soothingcolorsu').checked=true;"></td>
    <td><input id="scolor1" name="scolor1" type="color" value="#530031" style="width:40px"></td>
    <td><input id="scolor2" name="scolor2" type="color" value="#842742" style="width:40px"></td>
    <td><input id="scolor3" name="scolor3" type="color" value="#b32424" style="width:40px"></td>
    <td><input id="scolor4" name="scolor4" type="color" value="#ff7100" style="width:40px"></td>
    <td><input id="scolor5" name="scolor5" type="color" value="#ff9900" style="width:40px"></td>
  </tr>
 <tr>
    <td align="right"><label for="soothingcolorstest">test</label></td>
    <td colspan="6"><input type="checkbox" id="soothingcolorstest" name="soothingcolorstest" onclick="if(this.checked) document.getElementById('refreshingcolorstest').checked=false; document.getElementById('hourcolortest').checked=false;"></td>
  </tr>
</table>
<p></p>
<b><i>REFRESHING COLORS<b></i>
<table style="border:none;margin-left:10px">
  <tr>
    <td align="right"><label for="refreshingcolorsd">default</label></td>
    <td colspan="6"><input type="checkbox" id="refreshingcolorsd" name="refreshingcolorsd" onclick="if(this.checked) document.getElementById('refreshingcolorsu').checked=false; document.getElementById('refreshingcolorsd').checked=true;"></td>
  </tr>
  <tr>
    <td align="right"><label for="refreshingcolorsu">user</label></td>
	<td><input type="checkbox" id="refreshingcolorsu" name="refreshingcolorsu" onclick="if(this.checked) document.getElementById('refreshingcolorsd').checked=false; document.getElementById('refreshingcolorsu').checked=true;"></td>
    <td><input id="rcolor1" name="rcolor1" type="color" value="#84f63a" style="width:40px"></td>
    <td><input id="rcolor2" name="rcolor2" type="color" value="#69ef88" style="width:40px"></td>
    <td><input id="rcolor3" name="rcolor3" type="color" value="#f53f16" style="width:40px"></td>
    <td><input id="rcolor4" name="rcolor4" type="color" value="#3ea1e2" style="width:40px"></td>
    <td><input id="rcolor5" name="rcolor5" type="color" value="#edf079" style="width:40px"></td>
  </tr>
 <tr>
    <td align="right"><label for="refreshingcolorstest">test</label></td>
    <td colspan="6"><input type="checkbox" id="refreshingcolorstest" name="refreshingcolorstest" onclick="if(this.checked) document.getElementById('soothingcolorstest').checked=false; document.getElementById('hourcolortest').checked=false;"></td>
  </tr>
</table>
<p></p>
<b><i>DELAYS (minutes)<b></i>
<table style="border:none;margin-left:10px">
  <tr>
    <td><label for="sunset_delay">Past Sunset Twilight: </label><input type="text" id="sunset_delay" name="sunset_delay" maxlength="6" style="width:5em;border:none" value="60"></td>
  </tr>
  <tr>
    <td><label for="wakeup_delay">Past Wake Up Alarm: </label><input type="text" id="wakeup_delay" name="wakeup_delay" maxlength="6" style="width:5em;border:none" value="60"></td>
  </tr>
</table>
<p></p>
<b><i>WAKE UP ALARM<b></i>
<table style="border:none;margin-left:10px">
  <tr>
    <td><label for="alarm_hour">Hour: </label><input type="text" id="alarm_hour" name="alarm_hour" maxlength="2" style="width:1.5em;border:none" value="7"></td>
    <td><label for="alarm_minute">Minute:</label><input type="text" id="alarm_minute" name="alarm_minute" maxlength="2" style="width:1.5em;border:none" value="45"></td>
  </tr>
  </table>
<table style="text-align:center;border:none;margin-left:10px">
  <tr>
	<td><input type="checkbox" id="wd_mo" name="wd_mo"></td>
	<td><input type="checkbox" id="wd_tu" name="wd_tu"></td>
	<td><input type="checkbox" id="wd_we" name="wd_we"></td>
	<td><input type="checkbox" id="wd_th" name="wd_th"></td>
	<td><input type="checkbox" id="wd_fr" name="wd_fr"></td>
	<td><input type="checkbox" id="wd_sa" name="wd_sa"></td>
	<td><input type="checkbox" id="wd_su" name="wd_su"></td>
  </tr>
  <tr>
    <td style="width:2.2em"><label for="wd_mo">Mon</label></td>
    <td style="width:2.2em"><label for="wd_tu">Tue</label></td>	
    <td style="width:2.2em"><label for="wd_we">Wed</label></td>	
    <td style="width:2.2em"><label for="wd_th">Thu</label></td>	
    <td style="width:2.2em"><label for="wd_fr">Fri</label></td>
    <td style="width:2.2em"><label for="wd_sa">Sat</label></td>
    <td style="width:2.2em"><label for="wd_su">Sun</label></td>
  </tr>
</table>
<p></p>
<b><i>NIGHT HOUR COLOR<b></i>
<table style="text-align:center;border:none;margin-left:10px">
    <tr>
    <td><label for="hcolor1">0-1</label></td>
    <td><label for="hcolor2">1-2</label></td>	
    <td><label for="hcolor3">2-3</label></td>	
    <td><label for="hcolor4">3-4</label></td>	
    <td><label for="hcolor5">4-5</label></td>
    <td><label for="hcolor6">5-6</label></td>
    <td><label for="hcolor7">6-7</label></td>
  </tr>
  <tr>
    <td><input id="hcolor1" name="hcolor1" type="color" value="#FF0000" style="width:38px"></td>
    <td><input id="hcolor2" name="hcolor2" type="color" value="#FF7F00" style="width:38px"></td>
    <td><input id="hcolor3" name="hcolor3" type="color" value="#FFFF00" style="width:38px"></td>
    <td><input id="hcolor4" name="hcolor4" type="color" value="#00FF00" style="width:38px"></td>
    <td><input id="hcolor5" name="hcolor5" type="color" value="#0000FF" style="width:38px"></td>
	<td><input id="hcolor6" name="hcolor6" type="color" value="#4B0082" style="width:38px"></td>
	<td><input id="hcolor7" name="hcolor7" type="color" value="#9400D3" style="width:38px"></td>
  </tr>
 <tr>
    <td align="right"><label for="hourcolortest">test</label></td>
    <td colspan="6" align="left"><input type="checkbox" id="hourcolortest" name="hourcolortest" onclick="if(this.checked) document.getElementById('refreshingcolorstest').checked=false; document.getElementById('soothingcolorstest').checked=false;"></td>
  </tr>
  <tr>
</table>
  <p></p>
<b><i>STOP...<b></i>
<table>
<tr>
    <td align="right"><label for="stopsoothing">soothing</label></td>
    <td><input type="checkbox" id="stopsoothing" name="stopsoothing"></td>
    <td align="right"><label for="stoprefreshing">refreshing</label></td>
    <td><input type="checkbox" id="stoprefreshing" name="stoprefreshing"></td>
    <td align="right"><label for="stophourcolor">hour color</label></td>
    <td><input type="checkbox" id="stophourcolor" name="stophourcolor"></td>
  </tr>
  </tr>
    <tr>
  <td colspan="6"><p></p></td>
  </tr>
    <tr>
    <td colspan="6" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--orange" value="Save"</td>
  </tr>
</table>
</form>
<script>
  
window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/schedulevalues");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====";

int IsBitSet(byte b, int pos)
{
   return (b & (1 << pos)) != 0;
}

void send_schedule_settings_html()
{
	Serial.println("************************************");
	Serial.println(server.args());

	  if (server.args() > 0 )  // Save Settings
	  {
	    config.weekday = 0;
	    TestSoothingColors = false;
		TestRefreshingColors = false;
		TestHourColor = false;
		StopSoothing = false;
		StopRefreshing = false;
		StopHourColor = false;
	    for ( uint8_t i = 0; i < server.args(); i++ ) {
	      if (server.argName(i) == "soothingcolorsd") config.soothingcolors = 0;
	      if (server.argName(i) == "soothingcolorsu") config.soothingcolors = 1;
	      if (server.argName(i) == "refreshingcolorsd") config.refreshingcolors = 0;
	      if (server.argName(i) == "refreshingcolorsu") config.refreshingcolors = 1;
	      if (server.argName(i) == "soothingcolorstest") TestSoothingColors = true;
	      if (server.argName(i) == "refreshingcolorstest") TestRefreshingColors = true;
	      if (server.argName(i) == "hourcolortest") TestHourColor = true;
	      if (server.argName(i) == "scolor1") config.scolor1 =  server.arg(i);
	      if (server.argName(i) == "scolor2") config.scolor2 =  server.arg(i);
	      if (server.argName(i) == "scolor3") config.scolor3 =  server.arg(i);
	      if (server.argName(i) == "scolor4") config.scolor4 =  server.arg(i);
	      if (server.argName(i) == "scolor5") config.scolor5 =  server.arg(i);
	      if (server.argName(i) == "rcolor1") config.rcolor1 =  server.arg(i);
	      if (server.argName(i) == "rcolor2") config.rcolor2 =  server.arg(i);
	      if (server.argName(i) == "rcolor3") config.rcolor3 =  server.arg(i);
	      if (server.argName(i) == "rcolor4") config.rcolor4 =  server.arg(i);
	      if (server.argName(i) == "rcolor5") config.rcolor5 =  server.arg(i);
	      if (server.argName(i) == "sunset_delay") config.sunset_delay =  server.arg(i);
	      if (server.argName(i) == "wakeup_delay") config.wakeup_delay =  server.arg(i);
	      if (server.argName(i) == "alarm_hour") config.alarm_hour =  server.arg(i);
	      if (server.argName(i) == "alarm_minute") config.alarm_minute =  server.arg(i);
	      if (server.argName(i) == "wd_su") config.weekday += 1;
	      if (server.argName(i) == "wd_mo") config.weekday += 2;
	      if (server.argName(i) == "wd_tu") config.weekday += 4;
	      if (server.argName(i) == "wd_we") config.weekday += 8;
	      if (server.argName(i) == "wd_th") config.weekday += 16;
	      if (server.argName(i) == "wd_fr") config.weekday += 32;
	      if (server.argName(i) == "wd_sa") config.weekday += 64;
	      if (server.argName(i) == "hcolor1") config.hcolor1 =  server.arg(i);
	      if (server.argName(i) == "hcolor2") config.hcolor2 =  server.arg(i);
	      if (server.argName(i) == "hcolor3") config.hcolor3 =  server.arg(i);
	      if (server.argName(i) == "hcolor4") config.hcolor4 =  server.arg(i);
	      if (server.argName(i) == "hcolor5") config.hcolor5 =  server.arg(i);
	      if (server.argName(i) == "hcolor6") config.hcolor6 =  server.arg(i);
	      if (server.argName(i) == "hcolor7") config.hcolor7 =  server.arg(i);
	      if (server.argName(i) == "stopsoothing") StopSoothing = true;
	      if (server.argName(i) == "stoprefreshing") StopRefreshing = true;
	      if (server.argName(i) == "stophourcolor") StopHourColor = true;
	    }
	    WriteConfig();
	  }
	  server.send_P ( 200, "text/html", PAGE_ScheduleSettings );
	  Serial.println(__FUNCTION__);
}

void send_schedule_settings_values_html()
{
  String values ="";
  values += "soothingcolorsd|" +  (String) (config.soothingcolors ? "" : "checked") + "|chk\n";
  values += "soothingcolorsu|" +  (String) (config.soothingcolors ? "checked" : "") + "|chk\n";
  values += "refreshingcolorsd|" +  (String) (config.refreshingcolors ? "" : "checked") + "|chk\n";
  values += "refreshingcolorsu|" +  (String) (config.refreshingcolors ? "checked" : "") + "|chk\n";
  values += "soothingcolorstest|" +  (String) (TestSoothingColors ? "checked" : "") + "|chk\n";
  values += "refreshingcolorstest|" +  (String) (TestRefreshingColors ? "checked" : "") + "|chk\n";
  values += "hourcolortest|" +  (String) (TestHourColor ? "checked" : "") + "|chk\n";
  values += "scolor1|" + (String) config.scolor1 + "|input\n";
  values += "scolor2|" + (String) config.scolor2 + "|input\n";
  values += "scolor3|" + (String) config.scolor3 + "|input\n";
  values += "scolor4|" + (String) config.scolor4 + "|input\n";
  values += "scolor5|" + (String) config.scolor5 + "|input\n";
  values += "rcolor1|" + (String) config.rcolor1 + "|input\n";
  values += "rcolor2|" + (String) config.rcolor2 + "|input\n";
  values += "rcolor3|" + (String) config.rcolor3 + "|input\n";
  values += "rcolor4|" + (String) config.rcolor4 + "|input\n";
  values += "rcolor5|" + (String) config.rcolor5 + "|input\n";
  values += "sunset_delay|" + (String) config.sunset_delay + "|input\n";
  values += "wakeup_delay|" + (String) config.wakeup_delay + "|input\n";
  values += "alarm_hour|" + (String) config.alarm_hour + "|input\n";
  values += "alarm_minute|" + (String) config.alarm_minute + "|input\n";
  values += "wd_su|" +  (String) (IsBitSet(config.weekday,0) ? "checked" : "") + "|chk\n";
  values += "wd_mo|" +  (String) (IsBitSet(config.weekday,1) ? "checked" : "") + "|chk\n";
  values += "wd_tu|" +  (String) (IsBitSet(config.weekday,2) ? "checked" : "") + "|chk\n";
  values += "wd_we|" +  (String) (IsBitSet(config.weekday,3) ? "checked" : "") + "|chk\n";
  values += "wd_th|" +  (String) (IsBitSet(config.weekday,4) ? "checked" : "") + "|chk\n";
  values += "wd_fr|" +  (String) (IsBitSet(config.weekday,5) ? "checked" : "") + "|chk\n";
  values += "wd_sa|" +  (String) (IsBitSet(config.weekday,6) ? "checked" : "") + "|chk\n";
  values += "hcolor1|" + (String) config.hcolor1 + "|input\n";
  values += "hcolor2|" + (String) config.hcolor2 + "|input\n";
  values += "hcolor3|" + (String) config.hcolor3 + "|input\n";
  values += "hcolor4|" + (String) config.hcolor4 + "|input\n";
  values += "hcolor5|" + (String) config.hcolor5 + "|input\n";
  values += "hcolor6|" + (String) config.hcolor6 + "|input\n";
  values += "hcolor7|" + (String) config.hcolor7 + "|input\n";
  values += "stopsoothing|" +  (String) (StopSoothing ? "checked" : "") + "|chk\n";
  values += "stoprefreshing|" +  (String) (StopRefreshing ? "checked" : "") + "|chk\n";
  values += "stophourcolor|" +  (String) (StopHourColor ? "checked" : "") + "|chk\n";
  Serial.println("soothing");
  Serial.println(config.soothingcolors);
  Serial.println("refreshing");
  Serial.println(config.refreshingcolors);
  Serial.println("weekday");
  Serial.println(config.weekday);
  Serial.println("-----------------");
  Serial.println(TestSoothingColors);
  Serial.println(TestRefreshingColors);
  Serial.println(TestHourColor);
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
  schedule_init();
  user_color_init();
  AdminTimeOutCounter=0;

}



#endif /* PAGE_SCHEDULESETTINGS_H */
