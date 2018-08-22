#ifndef SERIAL_FLAG
#define SERIAL_FLAG

/****************************************************************************** 
  ------------------------------- Includes -------------------------------
******************************************************************************/

#include <Arduino.h>
#include <RFduinoGZLL.h>
#include "_3_GZLL.h"
#include "_5_EnergyManagement.h"
#include "_90_Commands.h"
#include "_7_StateMachine.h"

/****************************************************************************** 
  ------------------------------- Constants -------------------------------
******************************************************************************/

#define RX_PIN        2
#define TX_PIN        3 
#define WAKE_PIN      4
#define LED1          5


#define BAUD          9600 //With wireless communication 9600 seems to be the maximum

#define BUFFER_SIZE   200

#define DOUBLE_ID         ' '
#define INT_ID            'd'
#define STRING_ID         's'  
#define ERROR_CHARACTER   'X'


extern unsigned long SerialIdleTime;

#define   SERIAL_IDLE_TIMEOUT   500 //ms
#define   LED_BLINK_TIME   10 //ms


/****************************************************************************** 
  ------------------------------- Structures -------------------------------
******************************************************************************/

typedef struct BufferStruct{
  char data[BUFFER_SIZE];
  int head;
  
}buffer_struct;


/****************************************************************************** 
  ------------------------------- Functions -------------------------------
******************************************************************************/

void InitSerial();
void serialEvent(void);
void BlinkLed(unsigned ms);

#endif
