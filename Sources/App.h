/*
 * App.h
 *
 *  Created on: Apr 29, 2015
 *      Author: griek_000
 */

#ifndef APP_H_
#define APP_H_

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 

#define SERVO_MAX 19680
#define SERVO_MIN 17900

#define NORMAL_TEMP 25
#define DANGER_TEMP 30 
#define MORTAL_TEMP 35

#define PRESENCE_CO2 1500

// State
extern int state;
extern int state_interior;

// CO2 variables 
extern AS1_TComData initCO2[];
extern AS1_TComData readCO2[];
extern byte err;
extern bool f_co2answer, f_co2cmd;
extern int co2;

// Temp variable
extern byte temperatura;

// Fan Speed
extern int fan_speed;

//Window Position
extern int window_position;

// Presence
extern int presence;

// CO2 response struct
	struct  {
		byte adress;
		byte cmd;
		word checksum;
	}response, response_exp;

	struct  {
		byte adress;
		byte cmd;
		byte count;
		byte high;
		byte low;
	}data, data_exp;
	
// Functions
	void init_CO2();	
	void config_device();
	long read_CO2();
	void servo_degree(byte degree);
	void select_state();
	
#ifdef __cplusplus
}  /* extern "C" */
#endif 
	
	
#endif /* APP_H_ */
