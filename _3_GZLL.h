#ifndef GZLL_FLAG
#define GZLL_FLAG


/****************************************************************************** 
  ------------------------------- Includes -------------------------------
******************************************************************************/


#include <RFduinoGZLL.h>
#include <Arduino.h>
#include "_1_Serial.h"
#include "_5_EnergyManagement.h"
#include "_7_StateMachine.h"
#include "_90_Commands.h"


/****************************************************************************** 
  ------------------------------- Globals -------------------------------
******************************************************************************/

#define DEVICE_ROLE DEVICE0

//The time needed between receiving 2 commands from HOST
#define PING_INTERVAL       2000 //[ms]
#define DEBUG_PING_INTERVAL 500 //[ms]
#define PARAMETRIC_START_PING_INTERVAL  500 //[ms]

#define MAX_PING_INTERVAL_MULTIPLIER  20

#define LED2                6

//#define FORMAT_CHECK //If this is defined each incoming data goes through a format check

/****************************************************************************** 
  ------------------------------- Functions -------------------------------
******************************************************************************/

void InitGZLL();
void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len);
void Ping();

#endif
