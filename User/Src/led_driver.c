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
        light->turn_on = !light->turn_on;
        btn->released_event = 0;
        break;
      case LONG_PRESSED:
        if (!light->adjusted)
        {
          encoder_st_bright.delta = 0;
          encoder_st_color.delta = 0;
          encoder_st_tone.delta = 0;
        }
        light->adjusted = true;
        
        light->bright = clamp(light->bright + encoder_st_bright.delta, 0, 1000);
        
        light->color = clamp(light->color + encoder_st_color.delta, 0, 1000);
        
        light->tone = clamp(light->tone + encoder_st_tone.delta, 0, 1000);
        
        encoder_st_bright.delta = 0;
        encoder_st_color.delta = 0;
        encoder_st_tone.delta = 0;
        break;
      case LONGLONG_PRESSED:
        btn->time_p = NOT_PRESSED;
        light->adjusted = false;
        btn->released_event = 0;
        break;
      default:
        break;
    }
  }
}

void LIGHT_State_Init(light_st *light)
{
  light->bright = 600;
  light->color = 0;
  light->tone = 650;
  light->turn_on = false;
  light->adjusted = false;
}

int32_t clamp (uint32_t v, uint32_t min, uint32_t max)
{
  if (v < min) return min;
  if (v > max) return max;
  return v;
}

int32_t lerp(int32_t a, int32_t b, int32_t t, int32_t t_max)
{
    return a + (b - a) * t / t_max;
}

void LIGHT_CalcRGB(const light_st *light, uint16_t *pwm_r, uint16_t *pwm_g, uint16_t *pwm_b)
{
  uint16_t r, g, b;

  if (!light->turn_on || light->bright == 0)
  {
    *pwm_r = *pwm_g = *pwm_b = 0;
    return;
  }

  if (light->color == 0)
  {
    tone_white(light->tone, &r, &g, &b);
  }
  else
  {
    hue_to_rgb(light->color, &r, &g, &b);
  }

  r = r * light->bright / 1000;
  g = g * light->bright / 1000;
  b = b * light->bright / 1000;

  *pwm_r = r;
  *pwm_g = g;
  *pwm_b = b;

  if (*pwm_r > 1000) *pwm_r = 1000;
  if (*pwm_g > 1000) *pwm_g = 1000;
  if (*pwm_b > 1000) *pwm_b = 1000;
}

static void tone_white(uint16_t tone, uint16_t *r, uint16_t *g, uint16_t *b)
{
  if (tone <= 500)
  {
    *r = 1000;
    *g = 800 + (tone * 200) / 500;
    *b = 400 + (tone * 600) / 500;
  }
  else
  {
    uint16_t t = tone - 500;
    *r = 1000 - (t * 600) / 500;
    *g = 1000 - (t * 100) / 500;
    *b = 1000;
  }
}

static void hue_to_rgb(uint16_t hue, uint16_t *r, uint16_t *g, uint16_t *b)
{
  // hue: 0..1000
  uint32_t h = hue * 6;   // 0..6000
  uint32_t sector = h / 1000;   // 0..5
  uint32_t pos = h % 1000;      // 0..999

  uint32_t inv = 1000 - pos;

  switch (sector)
  {
    case 0: // R -> Y
      *r = 1000;
      *g = pos;
      *b = 0;
      break;

    case 1: // Y -> G
      *r = inv;
      *g = 1000;
      *b = 0;
      break;

    case 2: // G -> C
      *r = 0;
      *g = 1000;
      *b = pos;
      break;

    case 3: // C -> B
      *r = 0;
      *g = inv;
      *b = 1000;
      break;

    case 4: // B -> M
      *r = pos;
      *g = 0;
      *b = 1000;
      break;

    default: // M -> R
      *r = 1000;
      *g = 0;
      *b = inv;
      break;
  }
}
