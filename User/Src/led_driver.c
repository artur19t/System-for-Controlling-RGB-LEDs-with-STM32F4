#include "led_driver.h"

encoder_st encoder_st_bright = {
  .delta = 0,
  .GPIOx = GPIOA,
  .last_AB = 0,
  .PinA = LL_GPIO_PIN_3,
  .PinB = LL_GPIO_PIN_4
};

encoder_st encoder_st_color = {
  .delta = 0,
  .GPIOx = GPIOA,
  .last_AB = 0,
  .PinA = LL_GPIO_PIN_5,
  .PinB = LL_GPIO_PIN_6
};

encoder_st encoder_st_tone = {
  .delta = 0,
  .GPIOx = GPIOA,
  .last_AB = 0,
  .PinA = LL_GPIO_PIN_7,
  .PinB = LL_GPIO_PIN_8
};
light_st light_bed;
light_st light_room;
light_st light_table;
// --- encoder read delta ---
void encoder_read_delta(encoder_st *encoder_user) {
  uint8_t current_AB = (LL_GPIO_IsInputPinSet(encoder_user->GPIOx, encoder_user->PinA) << 1)
                       | LL_GPIO_IsInputPinSet(encoder_user->GPIOx, encoder_user->PinB);

  // 00, 01, 11, 10
  switch ((encoder_user->last_AB << 2) | current_AB) {
    case 0b0001:
    case 0b0111:
    case 0b1110:
    case 0b1000:
      (encoder_user->delta)++; 
      break;

    case 0b0010:
    case 0b0100:
    case 0b1101:
    case 0b1011:
      (encoder_user->delta)--; 
      break;

    default:
      break;
  }
  encoder_user->last_AB = current_AB;
}

void LIGHT_state_handler(but_struct *btn, light_st *light)
{
  int32_t tmp;
  if(btn->released_event)
  {
    switch (btn->time_p)
    {
      case SHORT_PRESSED:
        break;
      case LONG_PRESSED:
        if (!light->adjusted)
        {
          encoder_st_bright.delta = 0;
          encoder_st_color.delta = 0;
          encoder_st_tone.delta = 0;
        }
        light->adjusted = true;
        tmp = light->bright += encoder_st_bright.delta;
        if (tmp < 0) tmp = 0;
        if (tmp > 1000) tmp = 1000;
        light->bright = tmp;
        
        tmp = light->color += encoder_st_color.delta;
        if (tmp < 0) tmp = 0;
        if (tmp > 1000) tmp = 1000;
        light->color = tmp;
        
        tmp = light->tone += encoder_st_tone.delta;
        if (tmp < 0) tmp = 0;
        if (tmp > 1000) tmp = 1000;
        light->tone = tmp;
        
        encoder_st_bright.delta = 0;
        encoder_st_color.delta = 0;
        encoder_st_tone.delta = 0;
        break;
      case LONGLONG_PRESSED:
        btn->time_p = NOT_PRESSED;
        light->adjusted = false;
        break;
      default:
        break;
    }
  }
  btn->released_event = 0;
}

void LIGHT_State_Init(light_st *light)
{
  light->bright = 600;
  light->color = 0;
  light->tone = 650;
  light->turn_on = false;
  light->adjusted = false;
}
