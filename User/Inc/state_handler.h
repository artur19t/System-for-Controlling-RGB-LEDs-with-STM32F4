#ifndef _STATE_HANDLER
#define _STATE_HANDLER

#include "main.h"

#define DEBOUNCE_TIME 50

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
  GPIO_TypeDef *port;
  uint8_t pin;
}but_struct;

#endif