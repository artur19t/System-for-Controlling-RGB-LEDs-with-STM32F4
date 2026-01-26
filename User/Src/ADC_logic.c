#include "ADC_logic.h"

uint16_t adc_prev = 0;
uint16_t brightness = 0;
uint16_t color = 0;

void encoder_task(void)
{
  static uint8_t div = 0;
  if (++div < 30)
  {
    return;
  }
  div = 0;
  
  uint16_t adc = ADC_Read();
  if (abs(adc-adc_prev)>20)
  {
    brightness = map(adc, 0, 4095, 0, 1000);
    color = map(adc, 0, 4095, 0, 360);
    adc_prev = adc;
  }
}

uint16_t ADC_Read(void)
{
  LL_ADC_REG_StartConversionSWStart(ADC1);
  while (!LL_ADC_IsActiveFlag_EOCS(ADC1));
  return LL_ADC_REG_ReadConversionData12(ADC1);
}

static uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
  if (x <= in_min) return out_min;
  if (x >= in_max) return out_max;

  return (x - in_min) * (out_max - out_min)
         / (in_max - in_min)
         + out_min;
}

typedef struct {
  uint16_t r;
  uint16_t g;
  uint16_t b;
} rgb_t;

rgb_t HSV_to_RGB(uint16_t h, uint8_t s, uint16_t v)
{
  rgb_t out = {0};

  uint8_t region = h / 60;
  uint16_t remainder = (h - region * 60) * 255 / 60;

  uint16_t p = (v * (255 - s)) / 255;
  uint16_t q = (v * (255 - (s * remainder) / 255)) / 255;
  uint16_t t = (v * (255 - (s * (255 - remainder)) / 255)) / 255;

  switch (region) {
    case 0: out = (rgb_t){v, t, p}; break;
    case 1: out = (rgb_t){q, v, p}; break;
    case 2: out = (rgb_t){p, v, t}; break;
    case 3: out = (rgb_t){p, q, v}; break;
    case 4: out = (rgb_t){t, p, v}; break;
    default: out = (rgb_t){v, p, q}; break;
  }

  return out;
}
