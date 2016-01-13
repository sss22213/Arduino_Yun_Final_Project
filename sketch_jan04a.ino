//Include library
#include <dht.h>
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
extern "C" {
#include <core.h>
}
//Declare
YunServer server;
dht DHT;
#define dht_dpin A1

//Global variable
int t1 = 0, t2 = 0;
extern int timer;
float Tempature = 0;
float Humidity = 0;
//Object

int DHT11()
{

  //Declare Sensor
  DHT.read11(dht_dpin);

  //Display information and Read Sensor
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Humidity = DHT.humidity;
  Serial.print("% ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Tempature = DHT.temperature;
  Serial.println("C ");
  return 0;
}
int WebServer()
{
  YunClient client = server.accept();  // Get clients coming from server
  if (client)                          // Is there a new client?
  {
    String request = client.readString();
    request.trim();

    //Request
    if (request == "Humidity") {
      client.println(Humidity);
    }
    if (request == "Temperature") {
      client.println(Tempature);
    }
    client.stop();
  }
  return 0;
}
void setup() {
  // put your setup code here, to run once
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  OS_Start();
  TASK_Create(DHT11, 1, 20);
  TASK_Create(WebServer, 0, 2);
}

void loop() {
  t2 = millis();
  // put your main code here, to run repeatedly:
  if (t2 - t1 > 10)
  {
    timer++;
    //Serial.println(timer);
    TASK_Excute();
    t1 = t2;
  }

}
