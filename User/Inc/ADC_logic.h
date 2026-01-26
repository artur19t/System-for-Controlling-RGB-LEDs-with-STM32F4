#ifndef _ADC_LOGIC
#define _ADC_LOGIC

#include "main.h"

void encoder_task(void);
uint16_t ADC_Read(void);
static uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);

#endif