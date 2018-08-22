#include "_90_Commands.h"

/****************************************************************************** 
  ------------------------------- Variables -------------------------------
******************************************************************************/

char* CMD[NUMBER_OF_COMMANDS];
char param_str[PARAM_STRING_BUFFER_SIZE];


/****************************************************************************** 
  ------------------------------- Functions -------------------------------
******************************************************************************/
/*************************************************** 
Initializes the command strings
***************************************************/
void InitCMD(){
   CMD[CMD_START]       =   "$START$";
   CMD[CMD_STOP]        =   "$STOP$";
   CMD[CMD_SLEEP]       =   "$SLEEP$";
   CMD[CMD_ACK]         =   "$ACK$";
   CMD[CMD_STARTM1]     =   "$STARTM1$";
   CMD[CMD_SLEEP_DEBUG] =   "$SLEEP_DEBUG$";
   CMD[CMD_DEBUG]       =   "$DEBUG$";
   CMD[CMD_STARTM2]     =   "$STARTM2$";
}


/*************************************************** 
Executes the given command
***************************************************/
void ExecuteCommand(int cmd){

  switch(cmd){
    
    case CMD_START:{
      event = START_EVENT;
      break;
    }

    case CMD_STOP:{
      event = STOP_EVENT;
      break;
    }

    case CMD_SLEEP:{
      event = SLEEP_EVENT;
      break;
    }

    case CMD_STARTM1:{
      event = STARTM1_EVENT;
      break;
    }

     case CMD_STARTM2:{
      event = STARTM2_EVENT;
      break;
    }

     case CMD_SLEEP_DEBUG:{
      event = SLEEP_DEBUG_EVENT;
      break;
    }

    case CMD_DEBUG:{
      event = DEBUG_EVENT;
      break;
    }

    default: event = STOP_EVENT; break;
    
  }
  
}


/*************************************************** 
Verifies the command string
***************************************************/
int VerifyCommand(char* data){
  for(int i=0; i<NUMBER_OF_COMMANDS; ++i){
    if(strcmp(data, CMD[i])==0) return i;
  }
  return -1;
}


/*************************************************** 
Saves the parameters string for future use
***************************************************/
void SaveParamString(char* data, int len){
  for(int i=0; i<len; ++i){
    param_str[i] = data[i];
  }
}

