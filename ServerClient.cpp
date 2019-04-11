#include "Global.h"
StaticJsonDocument<400> doc;

void setupServerClient(void){
        setSyncProvider(getServerValues);
        setSyncInterval(5*60*60);
}

time_t getServerValues() {
        WiFiClient client;
        HTTPClient http;
        time_t currentTime =0;
        for(int i=0; i<5&&currentTime==0; i++) {
                Serial.println("Starting Sync");
                if (http.begin(client, "http://home.vitoesposito.com:62522/embedded.html")) {
                        int httpCode = http.GET();
                        if (httpCode ==HTTP_CODE_OK) {
                                String payload = http.getString();
                                Serial.println(payload);

                                auto error = deserializeJson(doc, payload);
                                if (error) {
                                        Serial.print(F("deserializeJson failed  "));
                                        Serial.println(error.c_str());
                                        http.end();
                                        continue;
                                }
                                currentTime=doc["Time"];



                        } else {
                                Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
                        }
                        http.end();
                } else {
                        Serial.printf("[HTTP} Unable to connect\n");
                }
        }
        setSyncInterval(12*60*60);
        return currentTime; // return 0 if unable to get the time
}

void printTimeLocal(){
        time_t time = now();
        Serial.print("Local: ");
        if(hour(time)<10) {
                Serial.print(" ");
        }
        Serial.print(hour(time));
        Serial.print(":");
        if(minute(time)<10) {
                Serial.print("0");
        }
        Serial.print(minute(time));
        Serial.print(":");
        if(second(time)<10) {
                Serial.print("0");
        }
        Serial.print(second(time));
        Serial.println();
}


int getMinuteCount(void){
        time_t time = now();
        return (hour(time)*60)+minute(time);
}
