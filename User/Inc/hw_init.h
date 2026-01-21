#ifndef _HW_INIT
#define _HW_INIT

#include "main.h"

// --- GPIO Init ---
void GPIO_Button_Room_Init(void);
void GPIO_Button_Table_Init(void);
void GPIO_Button_Bed_Init(void);
void GPIO_Motion_Sensor_Init (void);

// ---IT Init ---
void IT_BUTTONS_Init(void);
void IT_Motion_Sens_Init(void);
void SYSCFG_Usr_Init(void);
#endif