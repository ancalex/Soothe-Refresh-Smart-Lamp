#ifndef PAGE_GEOLOCATION_H
#define PAGE_GEOLOCATION_H

const char PAGE_GeoLocation[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s btn--orange">&#9664;</a>&nbsp;&nbsp;<strong>GeoLocation et al</strong>
<hr>
<form action="" method="get">
<b><i>LOCATION</b></i>
<table style="border:none;margin-left:10px">
  <tr>
    <td><label for="latitude">Latitude: </label><input type="text" id="latitude" name="latitude" maxlength="12" style="width:5em;border:none" value="0"></td>
    <td><label for="longitude">Longitude: </label><input type="text" id="longitude" name="longitude" maxlength="12" style="width:5em;border:none" value="0"></td>
  </tr>
  <tr>
    <td colspan="2"><i><input type="text" id="location_info" name="location_info" style="border:none;width:20em;font-size:11pt;" value="" disabled></i></td>
  </tr>
</table>
<p></p>
<b><i>SUN CALCULATOR<b></i>
<table style="border:none;margin-left:10px">
  <tr>
    <td><label for="sunrise">Sunrise: </label><input type="text" id="sunrise" name="sunrise" maxlength="6" style="width:5.5em;border:none" value="0"></td>
    <td><label for="sunset">Sunset: </label><input type="text" id="sunset" name="sunset" maxlength="6" style="width:6em;border:none" value="0"></td>
  </tr>
  <tr>
    <td colspan="2"><label for="twilight">Twilight: </label><input type="text" id="twilight" name="twilight" maxlength="6" style="width:5em;border:none" value="0"></td>
  </tr>
  <tr>
    <td align="center"><a href="javascript:SetResults()" id="locate" style="width:130px" class="btn btn--m btn--orange">Locate</a></td></td>
    <td align="center"><input type="submit" style="width:150px" class="btn btn--m btn--orange" value="Save"></td>
  </tr>
</table>
</form>
<script>

function SetResults()
{
	setValues("/admin/geolocationresults");
    document.getElementById("location_info").style.display = "block";
}

window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/geolocationvalues");
        document.getElementById("location_info").style.display = "none";
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

</script>
)=====";

void send_geolocation_html()
{
	if (server.args() > 0 )  // Save Settings
	{
		for ( uint8_t i = 0; i < server.args(); i++ ) {
			if (server.argName(i) == "latitude") config.latitude = server.arg(i);
			if (server.argName(i) == "longitude") config.longitude =  server.arg(i);
		}
		//longitude=config.longitude.toFloat();
		//latitude=config.latitude.toFloat();
		if ((ntp_response_ok == true or manual_time_set == true) and (config.latitude.toFloat() != 0 and config.longitude.toFloat() != 0)) {
			schedule_init();
			WriteConfig();
		}

	}
	server.send_P ( 200, "text/html", PAGE_GeoLocation );
	Serial.println(__FUNCTION__);
}

void send_geolocation_values_html()
{
	String values ="";
	values += "latitude|" +  config.latitude + "|input\n";
	values += "longitude|" + config.longitude + "|input\n";
	values += "location_info||input\n";
	values += "sunrise|" +  config.sunrise + "|input\n";
	values += "sunset|" +  config.sunset + "|input\n";
	values += "twilight|" +  config.twilight + "|input\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__);
	AdminTimeOutCounter=0;
}

void send_geolocation_results_html()
{
	GeoLocation();
	String values ="";
	values += "longitude|" + (String) longitude + "|input\n";
	values += "latitude|" +  (String) latitude + "|input\n";
	values += "location_info|" +  (String) city + ", " + (String) region + ", " + (String) country + "|input\n";
	values += "sunrise||input\n";
	values += "sunset||input\n";
	values += "twilight||input\n";
	Serial.println(values);
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__);
}

#endif /* PAGE_GEOLOCATION_H */
