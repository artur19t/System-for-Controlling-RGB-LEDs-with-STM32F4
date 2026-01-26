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