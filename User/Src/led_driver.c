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