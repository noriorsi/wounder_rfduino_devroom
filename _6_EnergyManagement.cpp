#include "_5_EnergyManagement.h"


/****************************************************************************** 
  ------------------------------- Variables -------------------------------
******************************************************************************/



/****************************************************************************** 
  ------------------------------- Functions -------------------------------
******************************************************************************/

/*************************************************** 
Enters deep sleep mode and wakes up after a delay
***************************************************/
void DeepSleepDelay(uint64_t ms){

  //Update: Disabling these causes some unwanted errors and the power comsumption doesnt seem the decrease.
  
  // Disable the Serial and the Wire for low power mode
  //NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos);
  //NRF_TWI1->ENABLE = (TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos);

  //Swtich off leds
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  Serial.end();
  RFduinoGZLL.end();
  
  RFduino_ULPDelay(ms);

  // Re-Enable the Serial and the Wire
  //NRF_TWI1->ENABLE = (TWI_ENABLE_ENABLE_Enabled << TWI_ENABLE_ENABLE_Pos);
  //NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);

  Serial.begin(BAUD, RX_PIN, TX_PIN);
  RFduinoGZLL.begin(DEVICE_ROLE);
}


/*************************************************** 
Wakes up the device
***************************************************/
int WakeUp(long unsigned int a){
  
  NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);

  if(parametric_active){
  NRF_TWI1->ENABLE = (TWI_ENABLE_ENABLE_Enabled << TWI_ENABLE_ENABLE_Pos);
  NRF_SPI0->ENABLE = (SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos);
  }
  
  Serial.begin(BAUD, RX_PIN, TX_PIN);
  RFduinoGZLL.begin(DEVICE_ROLE);

  #ifndef LEDS_OFF
  digitalWrite(LED2, HIGH);
  delay(10);
  digitalWrite(LED2, LOW);
  #endif
  
  event = WAKE_UP_EVENT;
  return 0;
}


/*************************************************** 
Enters shut-off mode, wake up only with external reset
***************************************************/
void SystemOff(){

  //RFduino_pinWakeCallback(WAKE_PIN, DISABLE, WakeUp);
  
  // Disable the Serial and the Wire for low power mode
  //NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos);
  //NRF_TWI1->ENABLE = (TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos);

  //Swtich off leds
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  Serial.end();
  RFduinoGZLL.end(); 

  RFduino_systemOff();
}


/*************************************************** 
Enters shut-off mode, wake up only with external reset
***************************************************/
void ParametricSleep(){
  
   //Disable the Serial and the Wire for low power mode
  NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos);
  NRF_TWI1->ENABLE = (TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos);
  NRF_SPI0->ENABLE = (SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  
  RFduino_ULPDelay(1000);
}





