#include <RFduinoGZLL.h>
#include <stdio.h>
#include "_1_Serial.h"
#include "_3_GZLL.h"
#include "_7_StateMachine.h"


void setup()
{
  InitCMD();
  InitSerial();
  InitGZLL();
}


void loop()
{

 Timeout(state);
  
  if( (event >= 0) && (event < MAX_EVENTS) ){
    next_state = state_table[state][event]();
    state = next_state;
  }


}




