#ifndef COMMANDS_FLAG
#define COMMANDS_FLAG

/****************************************************************************** 
  ------------------------------- Includes -------------------------------
******************************************************************************/

#include "_7_StateMachine.h"


/****************************************************************************** 
  ------------------------------- Constants -------------------------------
******************************************************************************/

#define COMMAND_CHARACTER   '$'
#define PARAM_CHAR          '/' //The parameter character

#define PARAM_STRING_BUFFER_SIZE  100

typedef enum{
  CMD_START,
  CMD_STOP,
  CMD_SLEEP,
  CMD_ACK,
  CMD_STARTM1,
  CMD_SLEEP_DEBUG,
  CMD_DEBUG,
  CMD_STARTM2,
  NUMBER_OF_COMMANDS
}command_enum;


extern char* CMD[NUMBER_OF_COMMANDS];
extern char param_str[PARAM_STRING_BUFFER_SIZE];


/****************************************************************************** 
  ------------------------------- Functions -------------------------------
******************************************************************************/
void InitCMD();
void ExecuteCommand(int cmd);
int VerifyCommand(char* data);
void SaveParamString(char* data, int len);

#endif
