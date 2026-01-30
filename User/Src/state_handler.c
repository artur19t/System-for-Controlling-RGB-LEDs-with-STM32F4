#include "state_handler.h"

but_struct btn_table = {
  .state = RELEASED,
  .time_p = NOT_PRESSED,
  .port = GPIOB,
  .pin = LL_GPIO_PIN_1
};

but_struct btn_room = {
  .state = RELEASED,
  .time_p = NOT_PRESSED,
  .port = GPIOB,
  .pin = LL_GPIO_PIN_2
};

but_struct btn_bed = {
  .state = RELEASED,
  .time_p = NOT_PRESSED,
  .port = GPIOB,
  .pin = LL_GPIO_PIN_3
};

but_struct btn_encoder = {
  
  .state = RELEASED,
  .time_p = NOT_PRESSED,
  .port = GPIOA,
  .pin = LL_GPIO_PIN_4
};

void button_debounce(but_struct *btn)
{
  if (btn->released_event)
    return;
  
  switch (btn->state)
  {
    case RELEASED:
      btn->debounce = DEBOUNCE_TIME;
      btn->t = 0;
      btn->time_p = NOT_PRESSED;
      if (btn->event)
      {
        btn->state = PRESSED;
        btn->event = 0;
      }
      break;

    case PRESSED:
      if (btn->event)
      {
        btn->t = 0;
        btn->time_p = NOT_PRESSED;
        btn->debounce = DEBOUNCE_TIME;
        btn->event = 0;
        break;
      }
      
      if (btn->debounce > 0)
      {
        btn->debounce--;
        break;
      }
      btn->state = WAIT_RELEASED;
      btn->debounce = DEBOUNCE_TIME;
      break;

    case WAIT_RELEASED:
      if (!LL_GPIO_IsInputPinSet(btn->port, btn->pin))
      {
        btn->state = RELEASED;
        btn->debounce = DEBOUNCE_TIME;
        btn->released_event = 1;
        btn->t = 0;
      }
      btn->t ++;
      if (btn->t >= LONG_PRESS_T)
        btn->time_p = LONGLONG_PRESSED;
      else if (btn->t >= SHORT_PRESS_T)
        btn->time_p = LONG_PRESSED;
      else
        btn->time_p = SHORT_PRESSED;
      break;
  }
}