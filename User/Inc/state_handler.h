#ifndef _STATE_HANDLER
#define _STATE_HANDLER

#include "main.h"

#define DEBOUNCE_TIME 70

typedef enum
{
  RELEASED,
  PRESSED,
  WAIT_RELEASED
}but_state;

typedef enum
{
  NOT_PRESSED,
  SHORT_PRESSED,
  LONG_PRESSED,
  LONGLONG_PRESSED,
}time_pressed;

typedef struct
{
  but_state state;
  time_pressed time_p;
  uint16_t debounce;
  uint32_t t;
  uint8_t event;
  uint8_t released_event;
  GPIO_TypeDef *port;
  uint32_t pin;
}but_struct;

void button_debounce(but_struct *btn);

#endif