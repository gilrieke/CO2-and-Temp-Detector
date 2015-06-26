/*
 * App.c
 *
 *  Created on: Apr 29, 2015
 *      Author: Gil Rieke
 */

#include "Cpu.h"
#include "Events.h"
#include "App.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

// State
int state = 0, state_interior = 0;

// CO2 variables 
AS1_TComData initCO2[] = {0xFE, 0x41, 0x00, 0x60, 0x01, 0x35, 0xE8, 0x53};
AS1_TComData readCO2[] = {0xFE, 0x44, 0x00, 0x08, 0x02, 0x9f, 0x25};
AS1_TComData readTEMP[] = {0xfe, 0x44, 0x00, 0x12, 0x02, 0x94, 0x45};
byte err;
int co2;
bool f_co2answer;
bool f_co2cmd;

//Temp variable
byte temperatura;

// Fan Speed
int fan_speed = 0;

//Window Position
int window_position = 0;

// Presence
int presence = 0;

void init_CO2() {	
	word ptr;
	
	// Expected response from Sensor 
	response_exp.adress = 0xfe;
	response_exp.cmd = 0x41;
	response_exp.checksum = 0xe081;
	
	// flag for messsage read
	f_co2answer = FALSE;
	f_co2cmd = TRUE;
	while(!f_co2answer) {  // While sensor respond
		err = AS1_SendBlock((byte*)&initCO2, sizeof(initCO2), &ptr);
		WAIT1_Waitms(180);
	}
	f_co2answer = FALSE;
	AS1_ClearRxBuf();
	AS1_ClearTxBuf();
	
	// Check the respond 
	if(memcmp(&response, &response_exp, sizeof(response)) == 0) {
		
	}
	
	else{
		
	}	
}

void config_device() {
	AD1_Calibrate(TRUE);					// ADC calibration
	fan_speed_SetDutyMS(10);		// Set PWM fan
	servo_degree(0);
	init_CO2();									// Initialize CO2 Sensor
}

long read_CO2() {
	word ptr;
	long response;
	
	// flag for messsage read
	f_co2answer = FALSE;
	f_co2cmd = FALSE;
	while(!f_co2answer) {  // While sensor respond
		err = AS1_SendBlock((byte*)&readCO2, sizeof(readCO2), &ptr);
		WAIT1_Waitms(130);
	}
	f_co2answer = FALSE;
	AS1_ClearRxBuf();
	AS1_ClearTxBuf();
	
	// Expected response from Sensor 
	data_exp.adress = 0xfe;
	data_exp.cmd = 0x44;
	data_exp.count = 0x02;
	data_exp.high = data.high;
	data_exp.low = data.low;
	
	// Check the respond 
	if(memcmp(&data, &data_exp, sizeof(data)) == 0) {
		
	}
	
	else{
		
	}
	
	response = ((data.high*256) + data.low);
	return response;
}

void servo_degree(byte degree) {
	Servo_SetDutyUS(SERVO_MIN + (((SERVO_MAX - SERVO_MIN)/180)*degree));
}

void select_state( void ) {
	if (presence == 0) {
		fan_speed = 0;
		window_position = 0;
		Led_G_Off();
		Led_Y_Off();
		Led_R_Off();
		state_interior = 0;
	}
	
	else if (presence == 1 || presence == 3 || presence || 4){
		
		if(co2 < PRESENCE_CO2) {
			fan_speed = 0;
			window_position = 0;
			Led_G_On();
			Led_Y_On();
			Led_R_On();
			state_interior = 0;
		}
		
		else {
			if(temperatura <= NORMAL_TEMP) {
				Led_G_On();
				Led_Y_Off();
				Led_R_Off();
				fan_speed = 0;
				window_position = 0;
				state_interior = 1;
			}
			
			else if(temperatura > NORMAL_TEMP && temperatura <= DANGER_TEMP) {
				Led_G_On();
				Led_Y_On();
				Led_R_Off();
				fan_speed = 3;
				window_position = 30;
				state_interior = 2;
			}
			
			else if (temperatura > DANGER_TEMP && temperatura <= MORTAL_TEMP) {
				Led_G_Off();
				Led_Y_On();
				Led_R_On();
				fan_speed = 60;
				window_position = 6;
				state_interior = 2;
			}
			
			else if (temperatura > MORTAL_TEMP) {
				Led_G_Off();
				Led_Y_Off();
				Led_R_On();				
				fan_speed = 10;
				window_position = 100;
				state_interior = 3;
			}
			
			else {
				Led_G_On();
				Led_Y_Off();
				Led_R_On();	
				fan_speed = 0;
				window_position = 0;
				state_interior = 0;
			}
		}
	}
	
	else {
		
	}

}

#ifdef __cplusplus
}  /* extern "C" */
#endif 
