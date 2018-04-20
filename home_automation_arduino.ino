   //SIMPLE AND CHEAP HOME AUTOMATION SYSTEM USING ARDUINO MKR1000 BY ROOTSAID
   //Simple Arduino Code for building a home automation system that can control electrical appliances 
   //such as lights, fans, gates etc suing our mobile phone from anywhere around the world. 
   //Complete Project Tutorial on - :  http://rootsaid.com/home-automation-using-arduino/


#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "your_essid"; 
char pass[] = "your_password";
int keyIndex = 0;      
int ledpin = 6;
bool val = true;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);  
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
   
  
  Serial.print("Start Serial ");
  pinMode(ledpin, OUTPUT); 
  Serial.print("WiFi101 shield: ");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("NOT PRESENT");
    return; // don't continue
  }
  Serial.println("DETECTED");
  
  while ( status != WL_CONNECTED) {
    digitalWrite(ledpin, LOW);
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                
    digitalWrite(ledpin, HIGH);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();                          
  printWifiStatus();                      
  digitalWrite(ledpin, HIGH);
}
void loop() {
  WiFiClient client = server.available();  

  if (client) {                           
    Serial.println("new client");       
    String currentLine = "";              
    while (client.connected()) 
    {       
      if (client.available()) 
      {           
        char c = client.read();          
        Serial.write(c);                 
        if (c == '\n') 
        {                 

            if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("www.rootsaid.com<br>");
            client.print("https://www.youtube.com/c/rootsaid<br>");
            client.print("<br>");
            client.print("<h1>Home Automation using Arduino<br>");
            client.print("<br>");
            client.print("<h1>Click <a href=\"/device1on\">here</a> Turn Device 1 ON<br>");
            client.print("Click <a href=\"/device1off\">here</a> Turn Device 1 OFF<br>");
            client.print("Click <a href=\"/device2on\">here</a> Turn Device 2 ON<br>");
            client.print("Click <a href=\"/device2off\">here</a> Turn Device 2 OFF<br>");
            client.print("Click <a href=\"/device3on\">here</a> Turn Device 3 ON<br>");
            client.print("Click <a href=\"/device3off\">here</a> Turn Device 3 OFF<br>");
            client.print("Click <a href=\"/device4on\">here</a> Turn Device 4 ON<br>");
            client.print("Click <a href=\"/device4off\">here</a> Turn Device 4 OFF<br></h1>");

            client.println();
            break;
          }
          else {   
            currentLine = "";
          }
        }
        else if (c != '\r') {   
          currentLine += c;   
        }

  
if(currentLine.endsWith("GET /device1on"))
    {
       digitalWrite(0, HIGH); 
    }
    else if(currentLine.endsWith("GET /device1off"))
    {
       digitalWrite(0, LOW); 
    }
    else if(currentLine.endsWith("GET /device2on"))
    {
       digitalWrite(1, HIGH); 
    }
    else if(currentLine.endsWith("GET /device2off"))
    {
       digitalWrite(1, LOW); 
    }
    else if(currentLine.endsWith("GET /device3on"))
    {
       digitalWrite(2, HIGH); 
    }
    else if(currentLine.endsWith("GET /device3off"))
    {
       digitalWrite(2, LOW); 
    }
    else if(currentLine.endsWith("GET /device4on"))
    {
       digitalWrite(3, HIGH); 
    }
    else if(currentLine.endsWith("GET /device4off"))
    {
       digitalWrite(3, LOW); 
    }
    else
    {
     Serial.println("Invalid"); 
    }
      }
    }

    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() 
{

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
 
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
 
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

