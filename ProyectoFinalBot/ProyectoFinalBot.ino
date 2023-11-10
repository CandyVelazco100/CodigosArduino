#include <ESP8266WiFi.h>
#include <DHT.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

//config red y thingspeak
const char* ssid = "Velasco";
const char* pass = "6861001267";
const char* server = "api.thingspeak.com";
String thingSpeakApiKey = "49J12S0SZZWTIO85";

//config terminales
#define DHTTYPE DHT11 
#define DHTPIN D1
#define Temp D2
#define Hum D3

//Config dht11
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

//config telegram
#define ID_Chat "5124160750"
#define token_Bot "Tu_token"
#define BOTtoken "6208820307:AAFuu-h8mKe6CMihxDPVovBtPrbdyFMu4x8"
WiFiClientSecure clientt;
UniversalTelegramBot bot(BOTtoken, clientt);
int botRequestDelay = 1000;  
unsigned long lastTimeBotRan;
String mensaje = "";

void handleNewMessages(int numNewMessages, float tempera, float humed ) {
  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    
    if (from_name == "") from_name = "Guest";
    if (text == "/temperatura") {      
      String temp = "Temperatura: ";
      temp += float(tempera);
      temp +=" *C\n";
      bot.sendMessage(chat_id,temp, "");
    }
  
    if (text == "/humedad") {   
      String temp = "Humedad: ";
      temp += float(humed);
      temp += " %";
      bot.sendMessage(chat_id,temp, "");
    }
    
    if (text == "/start") {
      String welcome = "Bievenid@ " + from_name + ".\n";
      welcome += "/temperatura : Temperatura actual\n";
      welcome += "/humedad : Humedad actual\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}

void connectToWiFi() {
  Serial.println("Conectandose a ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
}

void setup() {
  pinMode(Temp, OUTPUT);
  pinMode(Hum, OUTPUT);
  Serial.begin(115200); 
  dht.begin();
  clientt.setInsecure();    
  WiFi.mode(WIFI_STA);    
  WiFi.disconnect();
  delay(100);
  connectToWiFi(); 
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("¡Error al leer del sensor DHT!");
    return;
  }

  if (millis() > lastTimeBotRan + botRequestDelay) {      
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);      
    while (numNewMessages) {              
      handleNewMessages(numNewMessages, t, h);        
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);     
    }  
    lastTimeBotRan = millis();    
  }

  if (client.connect(server, 80)) { 
    String postStr = thingSpeakApiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + thingSpeakApiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("\nTemperatura: ");
    Serial.print(t);
    Serial.print("C\n");
    Serial.print("Humedad: ");
    Serial.print(h);
    Serial.print("%\n");
    Serial.println("Enviando a ThingSpeak");
     client.stop();

    if (t >= 40.00) {
      digitalWrite(Temp, HIGH);
      mensaje = "¡Alerta de temperatura alta! \nTemperatura: " +String(t) + "°C";
      bot.sendMessage(ID_Chat, mensaje, "");
    } else if(t <= 25.00){
      digitalWrite(Temp, HIGH);
      mensaje = "¡Alerta de temperatura baja! \nTemperatura: " +String(t) + "°C";
      bot.sendMessage(ID_Chat, mensaje, "");      
    }else{
      digitalWrite(Temp, LOW);
    }
    
    if (h >= 50.00) {
      digitalWrite(Hum, HIGH);
      mensaje = "¡Alerta de humedad alta! \nHumedad: " +String(h) + "°%";
      bot.sendMessage(ID_Chat, mensaje, "");       
    } else {
      digitalWrite(Hum, LOW);
    }
    delay(16000);
  }
  
}