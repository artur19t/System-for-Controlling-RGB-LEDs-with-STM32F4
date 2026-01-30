#ifndef _LED_DRIVER
#define _LED_DRIVER

#include "state_handler.h"
#include "main.h"

typedef struct {
  GPIO_TypeDef *GPIOx;
  uint32_t PinA;
  uint32_t PinB;
  uint8_t last_AB;
  int16_t delta;
} encoder_st;

typedef struct {
  uint16_t bright;
  uint16_t tone;
  uint16_t color;
  bool turn_on;
  bool adjusted;
} light_st;
void encoder_read_delta(encoder_st *encoder_user);
void LIGHT_state_handler(but_struct *btn, light_st *light);
void LIGHT_State_Init(light_st *light);

#endif