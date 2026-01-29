#ifndef _LED_DRIVER
#define _LED_DRIVER

#include "main.h"
typedef struct {
  GPIO_TypeDef *GPIOx;
  uint32_t PinA;
  uint32_t PinB;
  uint8_t last_AB;
  int16_t delta;
} encoder_st;

void encoder_read_delta(encoder_st *encoder_user);
#endif