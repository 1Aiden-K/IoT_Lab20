/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/aiden/Desktop/IoT-Engineering/VisualStudioCodeProjects/IoT_Lab20/src/IoT_Lab20.ino"
/*
 * Project IoT_Lab20
 * Description:
 * Author:
 * Date:
 */

#include "MQTT.h"

void setup();
void loop();
#line 10 "c:/Users/aiden/Desktop/IoT-Engineering/VisualStudioCodeProjects/IoT_Lab20/src/IoT_Lab20.ino"
SYSTEM_THREAD(ENABLED);

enum State
{
  NORTH,
  EAST
};
State currentRoadState = NORTH;
State pastRoadState = EAST;

void callback(char *topic, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;

  if (String(p) == "NORTH")
  {
    currentRoadState = NORTH;
  }
  else if (String(p) == "EAST")
  {
    currentRoadState = EAST;
  }

  switch (currentRoadState)
  {
  case NORTH:
    client.publish("interstateLight/east", "YELLOW");
    delay(5000);
    client.publish("interstateLight/east", "RED");
    client.publish("interstateLight/north", "GREEN");
    break;
  case EAST:
    client.publish("interstateLight/north", "YELLOW");
    delay(5000);
    client.publish("interstateLight/north", "RED");
    client.publish("interstateLight/east", "GREEN");
    break;
  }
}

void setup()
{
}

void loop()
{
  if (client.isConnected())
  {
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
    client.subscribe("interstateSensors");
    client.publish("interstateLight/east", "RED");
    client.publish("interstateLight/north", "GREEN");
  }
}