#include <Arduino.h>

String sectionHeader() {
    String p = "";
    p += "<head>\n";
	p += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
	p += "<title>wordClock</title>\n";
	p += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
	p += "body{margin-top: 50px; background-color: black; color: white;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
	p += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    p += "</style>\n";
    p += "</head>\n";
 return p;
}
String pageSetup(String sDate, String sTime, String sBrightness, String sBrightnessReduced, String sColor){
  String p = "<!DOCTYPE html>\n";
  p += "<html>\n";
  p += sectionHeader();

  p += "<body>\n";
  p += "<h1>Serveur web de la wordClock</h1>\n";
  // dateTime
  p += "<form action=\"/dateTime\">\n";
  p += "<label for=\"dateTime\">Entrer la date et l'heure actuelle:</label>\n";
  p += "<input type=\"datetime-local\" id=\"dateTime\" name=\"dateTime\" min=\"2023-01-01T00:00\" value=\""+sDate+"T"+sTime+"\">\n";
  p += "<input type=\"submit\">\n";
  p += "</form><BR>\n";
  // Brightness normal
  p += "<form action=\"/brightness\">\n";
  p += "<label for=\"brightness\">R&#233;gler la luminosit&#233; des leds [10..200]:</label>\n";
  p += "<input type=\"number\" id=\"brightness\" name=\"brightness\" min=\"10\" max=\"200\" step=\"5\" value=\""+sBrightness+"\">\n";
  p += "<input type=\"submit\">\n";
  p += "</form><BR>\n";
  // Brightness reduced
  p += "<form action=\"/brightnessReduced\">\n";
  p += "<label for=\"brightnessReduced\">R&#233;gler la luminosit&#233; r&#233;duite des leds [10..200]:</label>\n";
  p += "<input type=\"number\" id=\"brightnessReduced\" name=\"brightnessReduced\" min=\"10\" max=\"200\" step=\"5\" value=\""+sBrightnessReduced+"\">\n";
  p += "<input type=\"submit\">\n";
  p += "</form><BR>\n";
  // color
  p += "<form action=\"/color\">\n";
  p += "<label for=\"color\">Choisir la couleur d'affichage:</label>\n";
  p += "<input type=\"color\" id=\"color\" name=\"color\" value=\""+sColor+"\">\n";
  /*
  p += "<select name=\"color\" id=\"color\">\n";
  p += "<option value=\"white\">Blanc</option>\n";
  p += "<option value=\"blue\">Bleu</option>\n";
  p += "<option value=\"red\">Rouge</option>\n";
  p += "<option value=\"green\">Vert</option>\n";
  p += "</select>\n";
  */
  p += "<input type=\"submit\">\n";
  p += "</form>\n";

  p += "</body>\n";
  p += "</html>\n";
 return p;
}
/*
String SendHTML(uint8_t led1stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Serveur web de la wordClock</h1>\n";
  ptr += "<h3>L'heure actuelle est ";
  ptr += getTimeDay();
  ptr += ".";
  ptr += getTimeMonth();
  ptr += ".";
  ptr += getTimeYear();
  ptr += " ";
  ptr += getTimeHour();
  ptr += ":";
  ptr += getTimeMinute();
  ptr += ":";
  ptr += getTimeSecond();
  ptr += "\n";
  
   if(led1stat) {
    ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";
  } else {
    ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";
  }

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
*/