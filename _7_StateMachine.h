#ifndef STATEMACHINE_FLAG
#define STATEMACHINE_FLAG

/****************************************************************************** 
  ------------------------------- Includes -------------------------------
******************************************************************************/


#include "_3_GZLL.h"
#include "_90_Commands.h"


/****************************************************************************** 
  ------------------------------- Globals -------------------------------
******************************************************************************/

typedef enum{
  IDLE_STATE,
  RECEIVE_N_SEND_STATE,
  SHUTOFF_STATE,
  WAITING_FOR_PARAMS_STATE,
  DEBUG_STATE,
  MAX_STATES
}state_enum;

typedef enum{
  NO_EVENT,
  START_EVENT,
  STOP_EVENT,
  SLEEP_EVENT,
  SERIAL_TIMEOUT_EVENT,
  WAKE_UP_EVENT,
  STARTM1_EVENT,
  STARTM2_EVENT,
  SLEEP_DEBUG_EVENT,
  PARAMS_EVENT,
  TIMEOUT_EVENT,
  DEBUG_EVENT,
  MAX_EVENTS
}event_enum;

extern state_enum (*state_table[MAX_STATES][MAX_EVENTS])(void);
extern state_enum state;
extern state_enum next_state;
extern event_enum event;

#define   WAITING_FOR_PARAMS_STATE_TIMEOUT    10000 //ms
#define   DELAY_BEFORE_SENDING_COMMAND        1 //MS

extern unsigned parametric_active;

/****************************************************************************** 
  ------------------------------- Functions -------------------------------
******************************************************************************/

state_enum No_Event_Handler(void);
state_enum Start_Event_Handler(void);
state_enum Stop_Event_Handler(void);
state_enum Error_Event_Handler(void);
state_enum Sleep_Event_Handler(void);
state_enum Serial_Timeout_Event_Handler(void);

void Timeout(state_enum state);

state_enum Wake_Up_Event_Handler(void);
state_enum StartM1_Event_Handler(void);
state_enum StartM2_Event_Handler(void);
state_enum Sleep_Debug_Event_Handler(void);

state_enum Params_Event_Handler(void);
state_enum Timeout_Event_Handler(void);

state_enum Debug_Event_Handler(void);
state_enum EndDebug_Event_Handler(void);



#endif
