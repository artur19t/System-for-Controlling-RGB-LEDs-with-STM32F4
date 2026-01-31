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
void LIGHT_CalcRGB(const light_st *light, uint16_t *pwm_r, uint16_t *pwm_g, uint16_t *pwm_b);
static void tone_white(uint16_t tone, uint16_t *r, uint16_t *g, uint16_t *b);
static void hue_to_rgb(uint16_t hue, uint16_t *r, uint16_t *g, uint16_t *b);
int32_t clamp (uint32_t v, uint32_t min, uint32_t max);
int32_t lerp(int32_t a, int32_t b, int32_t t, int32_t t_max);

#endif