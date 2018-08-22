#include "_1_Serial.h"

/****************************************************************************** 
  ------------------------------- Variables -------------------------------
******************************************************************************/


buffer_struct Buffer;

char commandchar = 0;
int commandchar_isfree = true; 

unsigned long SerialIdleTime = 0;
unsigned long LedBlinkTime = 0;

int LedState = 0;

unsigned cmd_char_counter = 0;

/****************************************************************************** 
  ----------------------------- Static Functions -----------------------------
******************************************************************************/

static void ResetBuffer(buffer_struct *buffstr){
  buffstr->head = 0;
}


static void InitBuffer(buffer_struct buffstr){
  buffstr.head = 0;
}


/*************************************************** 
Checks if a character is a number or not
***************************************************/
static int isNum(char ch){
  int temp = ch - '0';
  if(temp<0 || temp>9) return false;
  return true;
}


/*************************************************** 
Checks if a number is a double or not
If not then it replaces the characters with X
***************************************************/
static void DataFormatCheck_DOUBLE(buffer_struct *Buffer){
  int wrong_format = false;

  if(Buffer->data[0] != DOUBLE_ID) wrong_format = true;

  for(int i = 1; i<(Buffer->head); ++i){
    char c = Buffer->data[i];
    if(!isNum(c) && (c != '.') && (c != '\n') && (c != '\r') ) Buffer->data[i] = ERROR_CHARACTER;
  }

  if(wrong_format){
    for(int i = 1; i<(Buffer->head); ++i){
      if( (Buffer->data[i] != '\n') && (Buffer->data[i] != '\r') ){
        Buffer->data[i] = 'X';
      }
    }
  }
}


/*************************************************** 
Checks if a number is an integer or not.
If not then it replaces the characters with X
***************************************************/
static void DataFormatCheck_INT(buffer_struct *Buffer){
  int wrong_format = false;

  //If there is no format type character at the beginning it is wrong
  if(Buffer->data[0] != INT_ID) wrong_format = true;
  
  for(int i = 1; i<(Buffer->head); ++i){
    char c = Buffer->data[i];
    if(!isNum(c) && (c != '-') && (c != '\n') && (c != '\r') ) Buffer->data[i] = ERROR_CHARACTER;
  }

  if(wrong_format){
    for(int i = 1; i<(Buffer->head); ++i){
      if( (Buffer->data[i] != '\n') && (Buffer->data[i] != '\r') ){
        Buffer->data[i] = 'X';
      }
    }
  }
  
}


/*************************************************** 
Checks if a number is a string
If not then it replaces the characters with X
***************************************************/
static void DataFormatCheck_STRING(buffer_struct *Buffer){
  int wrong_format = false;

  if(Buffer->data[0] != STRING_ID) wrong_format = true;

  if(wrong_format){
    for(int i = 1; i<(Buffer->head); ++i){
      if( (Buffer->data[i] != '\n') && (Buffer->data[i] != '\r') ){
        Buffer->data[i] = 'X';
      }
    }
  }
  
}


/*************************************************** 
Stores the characters and sends them
***************************************************/
static void SendBuffer(buffer_struct *Buffer, char datatype){

#ifdef FORMAT_CHECK
    switch(datatype){
      case DOUBLE_ID: DataFormatCheck_DOUBLE(Buffer); break;
      case INT_ID:    DataFormatCheck_INT(Buffer);    break;
      case STRING_ID: DataFormatCheck_STRING(Buffer); break;
      default: break;
    }
#endif
  
  RFduinoGZLL.sendToHost(Buffer->data, Buffer->head);
  
  ResetBuffer(Buffer);
  
  commandchar = 0;
  commandchar_isfree = true; //The next data may arrive
}



/*************************************************** 
Stores the characters and sends them
***************************************************/
static void StoreAndSendData(char ch, char datatype){
  if(ch != 0){
    Buffer.data[Buffer.head] = ch;
    Buffer.head++;
    
    if(Buffer.head >= BUFFER_SIZE) ResetBuffer(&Buffer);
    
    if(ch == '\n' || ch == '\0'){
      Buffer.data[Buffer.head] = '\r';
      Buffer.head++;
      SendBuffer(&Buffer, datatype);
    }
    
  }
}


/*************************************************** 
Sets up the command character
***************************************************/
static void SetCommandChar(char ch){
  
  if(commandchar_isfree){
    
    switch(ch){
      case DOUBLE_ID:         commandchar = DOUBLE_ID;  commandchar_isfree = false;   break;
      case INT_ID:            commandchar = INT_ID;     commandchar_isfree = false;   break;
      case STRING_ID:         commandchar = STRING_ID;  commandchar_isfree = false;   break;
      case COMMAND_CHARACTER: commandchar = COMMAND_CHARACTER; commandchar_isfree = false; break;
      default: break;
    }
    
  
  }
  
}



/*************************************************** 
Stores the command string
***************************************************/
static void GetCommand(char ch){
  if(ch != 0){
    if(ch == COMMAND_CHARACTER) cmd_char_counter++;

    Buffer.data[Buffer.head] = ch;
    Buffer.head++;
    
    if(Buffer.head >= BUFFER_SIZE) ResetBuffer(&Buffer);
    
    if(cmd_char_counter == 2){
      Buffer.data[Buffer.head] = '\0';
      int cmd = VerifyCommand(Buffer.data);
      ExecuteCommand(cmd);
      
      ResetBuffer(&Buffer);
      commandchar = 0;
      commandchar_isfree = true;
      cmd_char_counter = 0;
    }
    
  }
 
}





/****************************************************************************** 
  ------------------------------- Functions -------------------------------
******************************************************************************/


/*************************************************** 
Initializes the serial communication
***************************************************/
void InitSerial(){
  pinMode(WAKE_PIN, INPUT);
  RFduino_pinWakeCallback(WAKE_PIN, HIGH, WakeUp);
  
  pinMode(RX_PIN,INPUT);
  pinMode(TX_PIN,OUTPUT);
  pinMode(LED1, OUTPUT);

  InitBuffer(Buffer);

  Serial.begin(BAUD, RX_PIN, TX_PIN);
}


/*************************************************** 
Serial event interrupt handler
***************************************************/
void serialEvent(void){

    if(state == RECEIVE_N_SEND_STATE || event == WAKE_UP_EVENT){

     SerialIdleTime = millis();

     #ifndef LEDS_OFF
     BlinkLed(LED_BLINK_TIME);
     #endif
      
      char ch = Serial.read();

      //RFduinoGZLL.sendToHost(ch);
      SetCommandChar(ch);
  
 
      switch(commandchar){
        case DOUBLE_ID:   StoreAndSendData(ch, DOUBLE_ID);   break;
        case INT_ID:      StoreAndSendData(ch, INT_ID);      break;
        case STRING_ID:   StoreAndSendData(ch, STRING_ID);   break;
        case COMMAND_CHARACTER: GetCommand(ch); break;
        default:  break;
      }
  }
  else if(state == DEBUG_STATE){
      RFduinoGZLL.sendToHost(Serial.read());
  }


}

/*************************************************** 
Toggles LED1 with ms period
***************************************************/
void BlinkLed(unsigned ms){
  if(millis()-LedBlinkTime > ms){
    LedState = !LedState;
    digitalWrite(LED1, LedState);
    LedBlinkTime = millis();
  }
}

