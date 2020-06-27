#include <Wire.h>
#include <SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
SSD1306 display(0x3c, D4, D3);//SDA,SCL

char *ssid = "U+NetE334";
char *password = "";
String APIKEY = ""; // Enter your API key
String CityID = "1835848"; // Seoul, KR

WiFiClient client;
char servername[]="api.openweathermap.org";
String result;

int counter = 60;

String weatherDescription ="";
String weatherLocation = "";
float Temperature;
float Humidity;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println();

  WiFi.begin(ssid,password);

  // Wait for the Wi-Fi connection
  int i=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connection established!");

  display.init();
  display.flipScreenVertically();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(counter == 60) //Get new data every 10 minutes
    {
      counter = 0;
      getWeatherData();
    }else
    {
      counter++;
      displayConditions(weatherLocation,weatherDescription,Temperature,Humidity);
      delay(5000);
    }
}

void getWeatherData() //client function to send/receive GET request data.
{
  if (client.connect(servername, 80)) {  //starts client connection, checks for connection
    client.println("GET /data/2.5/weather?id="+CityID+"&units=metric&APPID="+APIKEY);
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  } 
  else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }
 
  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
      result = result+c;
    }
 
  client.stop(); //stop client
  result.replace('[', ' ');
  result.replace(']', ' ');
  Serial.println(result);
 
  char jsonArray [result.length()+1];
  result.toCharArray(jsonArray,sizeof(jsonArray));
  jsonArray[result.length() + 1] = '\0';
   
  StaticJsonBuffer<1024> json_buf;
  JsonObject &root = json_buf.parseObject(jsonArray);
  if (!root.success())
  {
    Serial.println("parseObject() failed");
  }
   
  String location = root["name"];
  float temperature = root["main"]["temp"];
  float humidity = root["main"]["humidity"];
  String weather = root["weather"]["main"];
  String description = root["weather"]["description"];
   
  weatherLocation = location;
  weatherDescription = weather;
  Temperature = temperature;
  Humidity = humidity;
}

void displayConditions(String location, String weatherDescription, float Temperature,float Humidity)
{  
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(22, 10, "City: " + location);
  display.drawString(52, 20, "Weather: " + weatherDescription);
  display.drawString(77, 30, "Temperature: " + String(Temperature));
  display.drawString(82, 40, "Humidity: "+ String(Humidity));  
  display.display();
}
