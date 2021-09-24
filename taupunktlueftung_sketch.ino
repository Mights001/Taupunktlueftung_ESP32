
#include <DHTesp.h>
#include <WiFiManager.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <ArduinoJson.h>
#include "index_html.h"


struct Taupunkt {
        float temp = 0;
        float dampf = 0; 
        
    };

 

//Pin für Relay Lüfter 
int relay = 12;

 // Fühler DHT11

DHTesp Aussen;
TaskHandle_t tempTaskHandle = NULL;
int Aussenpin = 17;

DHTesp Raum;
int RaumPin = 16;

//Json 
StaticJsonDocument<1024> jsonDocument;
char buffer[1024];

//Bool Hand Auto
bool varhand, varautomatik;
int luefterein;
//Taupunktvariablen
float DiffTautemp;
Taupunkt TAussen, TRaum;

//Sensor Objecte 
TempAndHumidity lastAussen;
TempAndHumidity lastRaum;


//Webserver Initialisieren 
WebServer server(80);
const char* host = "esp32";
float Diff = 3.0;       // Minimale Taupunktdifferenz für Start Lüfter
float starthumi = 55.0; // Unter dieser Innenfeuchtigkeit wird nicht gelüftet
float MinTemp = 10.0;   // Unter dieser Innentemperatur wird nicht gelüftet





//Setup
void setup() {
  
// Initialize temperature sensor Aussen
Aussen.setup(Aussenpin, DHTesp::DHT22);
  // Initialize temperature sensor Raum 
Raum.setup(RaumPin, DHTesp::DHT22);
  
 WiFiManager manager;    

    bool success = manager.autoConnect("ESP32_AP","password");
 
    if(!success) {
        Serial.println("Failed to connect");
    } 
    else {
        Serial.println("Connected");
    }


Serial.begin(115200);
pinMode(relay, OUTPUT); // Setzt den Digitalpin 12 als Outputpin


  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }

  
setup_routing(); 

}

  
void loop() {


lastAussen = Aussen.getTempAndHumidity();
lastRaum = Raum.getTempAndHumidity();

//Serial.print(lastAussen.temperature);

TAussen = Taupunktberechnung(lastAussen.temperature, lastAussen.humidity);
TRaum = Taupunktberechnung(lastRaum.temperature, lastRaum.humidity);

 

DiffTautemp =  TRaum.temp - TAussen.temp; 

if(!varhand){

        if (DiffTautemp > Diff && lastRaum.humidity > starthumi && lastRaum.temperature > MinTemp){
        digitalWrite(relay, HIGH);
        luefterein = 1;
           
        }else{
        
          digitalWrite(relay, LOW);
          luefterein = 0;
          
         }
}else{
  //Hand schalte Lüfter ein 
digitalWrite(relay, HIGH);
    luefterein = 1;
  
}
 
delay(100);
 
 server.handleClient();  
}



void setup_routing() {
  server.on("/temperature", getTemperature);
  server.on("/pressure", getPressure);
  server.on("/humidity", getHumidity);
  server.on("/env", getEnv);
  server.on("/", sendhtmlindex);
  server.on("/hand", hand);
  
  // Send a GET request to <ESP_IP>/get?diff=<inputMessage>
  server.on("/get", HTTP_GET, []() {
    
    if( server.hasArg("diff")) {
    
    String argument = server.arg("diff");
    
    Diff = argument.toFloat(); 
    server.send(200, "text/html", index_html);
    Serial.println(argument);
    }

    if( server.hasArg("starthumi")) {
    
    String argument = server.arg("starthumi");
    
    starthumi = argument.toFloat(); 
    server.send(200, "text/html", index_html);
    Serial.println(argument);
    }

    if( server.hasArg("MinTemp")) {
    
    String argument = server.arg("MinTemp");
    
    MinTemp = argument.toFloat(); 
    server.send(200, "text/html", index_html);
    Serial.println(argument);
    }

  });

  server.on("/firmware", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", firmwarepage);
  });



    /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });

  // start server
  server.begin();
}

void getTemperature() {
    Serial.println("Get temperature");
  create_json("temperature", lastAussen.temperature, "°C");
  server.send(200, "application/json", buffer);
}
 
void getHumidity() {
  Serial.println("Get humidity");
  create_json("humidity", lastAussen.humidity, "%");
  server.send(200, "application/json", buffer);
}
 
void getPressure() {
  Serial.println("Get pressure");
  create_json("pressure", 0, "mBar");
  server.send(200, "application/json", buffer);
}
 
void getEnv() {
  Serial.println("Get env");
  jsonDocument.clear(); // Clear json buffer
  add_json_object("Luftfeuchte Aussen", lastAussen.humidity, "%");
  add_json_object("Aussentemperatur", lastAussen.temperature, "°C");
  add_json_object("Luftfeuchte Innen", lastRaum.humidity, "%");
  add_json_object("Innentemperatur", lastRaum.temperature, "°C");
  add_json_object("Taupunktdifferenz", DiffTautemp, "°C");
  add_json_object("Taupunktaussen", TAussen.temp, "°C");
  add_json_object("Taupunktinnen", TRaum.temp, "°C");
  add_json_object("Diff Einstellung", Diff, "°C");
  add_json_object("Start Luftfeuchte", starthumi, "%");
  add_json_object("Min Innentemperatur", MinTemp, "°C");  
  add_json_object("Luefter ein ", luefterein, "Bool");
  serializeJson(jsonDocument, buffer);
  server.send(200, "application/json", buffer);
}

void create_json(char *tag, float value, char *unit) {  
  jsonDocument.clear();
  jsonDocument["type"] = tag;
  jsonDocument["value"] = value;
  jsonDocument["unit"] = unit;
  serializeJson(jsonDocument, buffer);  
}
 
void add_json_object(char *tag, float value, char *unit) {
  JsonObject obj = jsonDocument.createNestedObject();
  obj["type"] = tag;
  obj["value"] = value;
  obj["unit"] = unit; 
}

void sendhtmlindex() {
  Serial.println("Index");
  server.send(200, "text/html", index_html);
}

void hand(){
   if( server.hasArg("hand")) {
    
    if(server.arg("hand") == "true"){
      varhand = true;      
      };
      if(server.arg("hand") == "false"){
      varhand = false;      
      };
    server.send(200, "text/html", index_html);
    Serial.println(varhand);
    }
  
  }

Taupunkt Taupunktberechnung(float temp, float hummi){


    float t, f, z1, es, e, z2, z3, dru ,tau, feu;
    float ai = 7.45;
    float bi = 235.0;
    Taupunkt intern;
    
    t = temp;
    f = hummi; 
    t = t * 1;
    f = f * 1;
    z1 = (ai * t) / ( bi +  t);
    es = 6.1 * exp(( z1 * 2.3025851));
    e =  es *  f / 100;
    z2 =  e / 6.1;
    z3 = 0.434292289 * log( z2);
    dru = ( e * 100) / 100;
    
    //dru = floor( dru) / 100;
    intern.temp = ((235 *  z3) / (7.45 -  z3) * 100) /100 ;
    
    //tau = floor( tau) / 100;
    intern.dampf = ((216.7 *  e) / (273.15 +  t) * 100) /100 ;
    //feu = round( feu) / 100;

    return intern;
}
