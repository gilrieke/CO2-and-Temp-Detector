/* ###################################################################
**     Filename    : main.c
**     Project     : CO2 and Temp Detector
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-03-24, 20:54, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "Led_G.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "Led_Y.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "Led_R.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "fan_speed.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "TI1.h"
#include "Servo.h"
#include "PwmLdd2.h"
#include "TU3.h"
#include "AS1.h"
#include "ASerialLdd2.h"
#include "CS1.h"
#include "TU2.h"
#include "WAIT1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "string.h"
#include "App.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
byte i;
uint8_t contador = 0;

int main(void) {
  /* Write your local variable definition here */
	char comando[5] = "OFF";
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  
  // Estado Inicial 
  config_device();
  
  for(;;) {
	  Term1_ReadLine(comando);
	  if(strcmp(comando, "OFF") == 0) {
		  state = 0;
		  TI1_Disable(TI1_DeviceData);
	  }
	  
	  if(strcmp(comando, "ON") == 0) {
		  state = 1;
		  TI1_Enable(TI1_DeviceData);
	  }
	  
	  if(strcmp(comando, "PRES") == 0) {
		  Term1_ReadLine(comando);
		  presence = atoi(&comando);
	  }
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
