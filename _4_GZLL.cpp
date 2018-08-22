#include "_3_GZLL.h"

/****************************************************************************** 
  ------------------------------- Variables -------------------------------
******************************************************************************/


device_t role = DEVICE_ROLE;



/****************************************************************************** 
  ------------------------------- Static Functions -------------------------------
******************************************************************************/


/*************************************************** 
There seems to be one excessive character when receiving the command.
This functions corrects it.
***************************************************/
static void CorrectCommand(char* data, int len){
  data[len] = '\0';
}

/****************************************************************************** 
  ------------------------------- Functions -------------------------------
******************************************************************************/

/*************************************************** 
Initializes the GZLL protocol
***************************************************/
void InitGZLL(){
  RFduinoGZLL.begin(role);
  pinMode(LED2, OUTPUT);
}


/*************************************************** 
Receives data from Host
***************************************************/
void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{

  if(len > 0){

    switch(data[0]){
      
      case COMMAND_CHARACTER:{
        CorrectCommand(data,len);
        int cmd = VerifyCommand(data);
        ExecuteCommand(cmd);
        break;
      }

      case PARAM_CHAR:{
        CorrectCommand(data,len);
        SaveParamString(data, len);
        event = PARAMS_EVENT;
        break;
      }

      default: break;
    }
    

  }
}


/*************************************************** 
Sends host a 0 byte payload to receive the binary_state. 
Also pings the MCU when not receiving serial data.
***************************************************/
void Ping(){
  
  char temp[20];
  snprintf(temp, 20, "sDEVICE State: %d\r\n", state);
  
 // request the binary_state from the Host (send a 0 byte payload)
  RFduinoGZLL.sendToHost(temp);
  delay(5);
  if(state == DEBUG_STATE)  DeepSleepDelay(DEBUG_PING_INTERVAL);
  else                      DeepSleepDelay(PING_INTERVAL);

  delay(5);
  
}








