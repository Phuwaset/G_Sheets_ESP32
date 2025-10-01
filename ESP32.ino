#include "WiFi.h"
#include <HTTPClient.h>
#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7 * 3600;  // GMT+7
const int   daylightOffset_sec = 0;

// WiFi credentials
const char* ssid = "X50s._Phu";       
const char* password = "p0000000";    

String GOOGLE_SCRIPT_ID = "AKfycbzOGNR0gp5gx7bJjJ0La_mOHqB2YWkKLfGu-o3AX_TINraMI5IvniB71nmP4WlMjwZZrA";  
// form App Script_WebApp

const int ANALOG_PIN = 34;   

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect WiFi
  Serial.print("Connecting to WiFi: ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // Init NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("Failed to obtain time");
      return;
    }

    
    char timeStringBuff[50];
    strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);
    String timeString(timeStringBuff);
    timeString.replace(" ", "_");

    
    int analogValue = analogRead(ANALOG_PIN);

    
    int tempValue = random(20, 35); 

    Serial.print("Date: "); Serial.print(timeString);
    Serial.print(" | Analog: "); Serial.print(analogValue);
    Serial.print(" | Temp: "); Serial.println(tempValue);

    
    String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID +
                      "/exec?date=" + timeString +
                      "&analog=" + String(analogValue) +
                      "&temp=" + String(tempValue);

    HTTPClient http;
    http.begin(urlFinal.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Payload: " + payload);
    } else {
      Serial.println("Error in sending request");
    }
    http.end();
  }

  delay(5000); 
}
