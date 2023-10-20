#define WIFI_NAME "(*********)"
#define WIFI_PASSWORD "**********"
#define DEVICE_ID 3
#define DEVICE_NAME "FanControl"
#define TOKEN "**************************"

//Define pin for the relay that corresponds to button on remote
int LightRelayPin = 5;
int LowRelayPin = 4;
int MedRelayPin = 0;
int HighRelayPin = 2;
int FanRelayPin = 14;

#include <RemoteMe.h>
#include <RemoteMeSocketConnector.h>
#include <ESP8266WiFi.h>

RemoteMe& remoteMe = RemoteMe::getInstance(TOKEN, DEVICE_ID);

void onLightChange(String s) 
{
  
  if(s.equals("On") || s.equals("on"))
  {
    digitalWrite(LightRelayPin, LOW);
    delay(200);
  
    digitalWrite(LightRelayPin, HIGH);
  }
  else if(s.equals("Off") || s.equals("off"))
  {
    digitalWrite(LightRelayPin, LOW);
    delay(200);
  
    digitalWrite(LightRelayPin, HIGH);
  }
}
////////////////////////////////////////////////////////////////////////////
void onSpeedChange(String m) 
{
  if(m.equals("High") || m.equals("high"))
  {
    digitalWrite(HighRelayPin, LOW);
    delay(200);
  
    digitalWrite(HighRelayPin, HIGH);
  }

  else if(m.equals("Medium") || m.equals("medium"))
  {
    digitalWrite(MedRelayPin, LOW);
    delay(200);
  
    digitalWrite(MedRelayPin, HIGH);
  }

  else if(m.equals("Low") || m.equals("low"))
  {
    digitalWrite(LowRelayPin, LOW);
    delay(200);
  
    digitalWrite(LowRelayPin, HIGH);
  }

  else if(m.equals("Off") || m.equals("off"))
  {
    digitalWrite(FanRelayPin, LOW);
    delay(200);
  
    digitalWrite(FanRelayPin, HIGH);
  }
}

void setup() 
{
  pinMode(LightRelayPin, OUTPUT);
  digitalWrite(LightRelayPin, HIGH);
  pinMode(LowRelayPin, OUTPUT);
  digitalWrite(LowRelayPin, HIGH);
  pinMode(MedRelayPin, OUTPUT);
  digitalWrite(MedRelayPin, HIGH);
  pinMode(HighRelayPin, OUTPUT);
  digitalWrite(HighRelayPin, HIGH);
  pinMode(FanRelayPin, OUTPUT);
  digitalWrite(FanRelayPin, HIGH);
  
  //Serial.begin(9600);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  //Wait for Wifi to connect
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
  }

  //When Light value changes in remoteMe, trigger onLightChange
  remoteMe.getVariables()->observeText("Light", onLightChange);
  //When Speed value changes in remoteMe, trigger onSpeedChange
  remoteMe.getVariables()->observeText("Speed", onSpeedChange);

  remoteMe.setConnector(new RemoteMeSocketConnector());
  remoteMe.sendRegisterDeviceMessage(DEVICE_NAME);
}


void loop() 
{
  //Keep checking for updates
  remoteMe.loop();
}
