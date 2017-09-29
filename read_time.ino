#include <ESP8266WiFi.h>

const char* ssid = "";
const char* password = "";
String dated;
String tm;
int flag=0;

void setup() {
  Serial.begin(115200); 
  Serial.println(); 
  pinMode(D0, OUTPUT);
  digitalWrite(D0, 1);
  initWifi();
}

void loop() {
  Serial.println(getTime());
  Serial.println("your Date : ");
  //digitalWrite(D0, 0);
  tm=dated.substring(17,19);
  if((tm == "04") && (flag==0))
  {
    digitalWrite(D0, 0);
    flag=1;
    delay(30000);
    digitalWrite(D0, 1);
    }
   else if((tm == "12") && (flag==1))
   {
    digitalWrite(D0, 0);
    flag=0;
    delay(30000);
    digitalWrite(D0, 1);
    }
  //Serial.print(dated.substring(17,19));
  delay(50000);
}
  
String getTime() {
  WiFiClient client;
  while (!!!client.connect("google.com", 80)) {
    Serial.println("connection failed, retrying...");
  }

  client.print("HEAD / HTTP/1.1\r\n\r\n");
 
  while(!!!client.available()) {
     yield();
  }

  while(client.available()){
    if (client.read() == '\n') {    
      if (client.read() == 'D') {    
        if (client.read() == 'a') {    
          if (client.read() == 't') {    
            if (client.read() == 'e') {    
              if (client.read() == ':') {    
                client.read();
                String theDate = client.readStringUntil('\r');
                client.stop();
                dated="";
                dated=theDate;
                return theDate;
              }
            }
          }
        }
      }
    }
  }
}

void initWifi() {
   Serial.print("Connecting to ");
   Serial.print(ssid);
   
      WiFi.begin(ssid, password);
  

   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
  Serial.print("\nWiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
}
