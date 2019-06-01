#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "JSON.h"
#include "index.h"

#define AP_SSID "NodeMCU" //this will be the network name
#define LED_ESP 16
#define LED_NODE 2

IPAddress apIP(42, 42, 42, 42);  // Defining a static IP address: local & gateway   
IPAddress apSubnet(255, 255, 255, 0); // subnet FF FF FF 00

ESP8266WebServer server(80);

void handleRoot();
void handleNotFound();
void handleUpdate();

void setup() {
    pinMode (LED_ESP, OUTPUT);
    pinMode (LED_NODE, OUTPUT);
    digitalWrite (LED_ESP, LOW);
    digitalWrite (LED_NODE, LOW);
    delay(1000);

    Serial.begin(115200);
    Serial.println("Configuring WiFi access point...");

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(apIP, apIP, apSubnet);

    boolean result = WiFi.softAP(AP_SSID);
    if(result) {
        Serial.printf("Done!\nSSID: %s\nPW: \nIP: %s\n", AP_SSID, apIP.toString().c_str());
    } else {
        Serial.println("Error! Something went wrong...");
    }

    server.on("/",      handleRoot);
    server.on("/update", handleUpdate);
    server.onNotFound(  handleNotFound);

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
//Serial.printf("Number of connected devices (stations) = %d\n", WiFi.softAPgetStationNum());
}

void handleRoot() {
    String html = MAIN_page;
    Serial.print("HTML");
    server.send(200, "text/html", html);
}

void handleNotFound() {
    String message = "File Not Found\n\n";
    server.send(404, "text/plain", message );
}

void handleUpdate() {
    StaticJsonBuffer<512> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(server.arg("values"));

    Serial.println(server.arg("values"));

    if (!root.success()) {
        Serial.println("parseObject() failed");
    }    

    const char* sensor = root["sensor"];

    digitalWrite(LED_ESP, (root["LED1"]["checked"] ? LOW : HIGH));
    digitalWrite(LED_NODE, (root["LED2"]["checked"] ? LOW : HIGH));

    server.send(200, "text/plane", server.arg("values")); //Send web page
}
