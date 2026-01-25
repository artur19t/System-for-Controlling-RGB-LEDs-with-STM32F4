#include "hw_init.h"

// --- GPIO ---
//PB 1(table),2(room),3(bed),9(motion sensor)
//FOR PWM: PB 0,4,5(TIM3); PB 6,7,8 (TIM4); PA 0,1,2 (TIM5)
void GPIO_PWM_UsrInit(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
  GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_4 | LL_GPIO_PIN_5; //TIM3
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_7 | LL_GPIO_PIN_8; //TIM4
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1 | LL_GPIO_PIN_2; //TIM5
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// --- PB3, Button for bed led ---
void GPIO_Button_Bed_Init(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  
  LL_GPIO_InitTypeDef GPIO_Usr_Struct = {0};
  GPIO_Usr_Struct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_Usr_Struct.Pin = LL_GPIO_PIN_3;
  GPIO_Usr_Struct.Pull = LL_GPIO_PULL_DOWN;
  GPIO_Usr_Struct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOB, &GPIO_Usr_Struct);
}

// --- PB1, Button for table led ---
void GPIO_Button_Table_Init(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  
  LL_GPIO_InitTypeDef GPIO_Usr_Struct = {0};
  GPIO_Usr_Struct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_Usr_Struct.Pin = LL_GPIO_PIN_1;
  GPIO_Usr_Struct.Pull = LL_GPIO_PULL_DOWN;
  GPIO_Usr_Struct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOB, &GPIO_Usr_Struct);
}

// --- PB2, Button for room led ---
void GPIO_Button_Room_Init(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  
  LL_GPIO_InitTypeDef GPIO_Usr_Struct = {0};
  GPIO_Usr_Struct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_Usr_Struct.Pin = LL_GPIO_PIN_2;
  GPIO_Usr_Struct.Pull = LL_GPIO_PULL_DOWN;
  GPIO_Usr_Struct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOB, &GPIO_Usr_Struct);
}

// --- PB9, Motion sensor ---
void GPIO_Motion_Sensor_Init (void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  
  LL_GPIO_InitTypeDef GPIO_Init = {0};
  GPIO_Init.Mode = LL_GPIO_MODE_INPUT;
  GPIO_Init.Pin = LL_GPIO_PIN_9;
  GPIO_Init.Pull = LL_GPIO_PULL_NO;
  GPIO_Init.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOB, &GPIO_Init);
}

// --- Encoder analog gpio ---
void GPIO_ADC_Init(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin  = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;

  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// --- Interrupts ----
void IT_BUTTONS_Init(void)
{
  LL_EXTI_InitTypeDef IT_But_Init = {0};
  IT_But_Init.LineCommand = ENABLE;
  IT_But_Init.Line_0_31 = LL_EXTI_LINE_1 | LL_EXTI_LINE_2 | LL_EXTI_LINE_3;
  IT_But_Init.Mode = LL_EXTI_MODE_IT;
  IT_But_Init.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&IT_But_Init);
  
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE1);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE2);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE3);
  
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_1);
  NVIC_SetPriority(EXTI1_IRQn, 0);
  NVIC_EnableIRQ(EXTI1_IRQn);
  
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_2);
  NVIC_SetPriority(EXTI2_IRQn, 0);
  NVIC_EnableIRQ(EXTI2_IRQn);
  
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_3);
  NVIC_SetPriority(EXTI3_IRQn, 0);
  NVIC_EnableIRQ(EXTI3_IRQn);
}


void IT_Motion_Sens_Init(void)
{
  LL_EXTI_InitTypeDef IT_Usr_Struct = {0};
  IT_Usr_Struct.LineCommand = ENABLE;
  IT_Usr_Struct.Line_0_31 = LL_EXTI_LINE_9;
  IT_Usr_Struct.Mode = LL_EXTI_MODE_IT;
  IT_Usr_Struct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&IT_Usr_Struct);
  
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE9);
  
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_9);
  NVIC_SetPriority(EXTI9_5_IRQn, 0);
  NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void SYSCFG_Usr_Init(void)
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
}

// --- SysTick Init ---
void SysTick_UsrInit(void)
{
  SysTick->LOAD = (SystemCoreClock / 1000) - 1;
  SysTick->VAL  = 0;

  SysTick->CTRL =
      SysTick_CTRL_CLKSOURCE_Msk |  // HCLK
      SysTick_CTRL_TICKINT_Msk  |  // IRQ enable
      SysTick_CTRL_ENABLE_Msk;     // SysTick enable
}

// --- PWM ---
void PWM_Timer_UsrInit(TIM_TypeDef *TIMx)
{
  if (TIMx == TIM5)
  {
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
  }else if (TIMx == TIM3) 
  {
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
  }else if (TIMx == TIM4) 
  {
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
  }

  LL_TIM_SetPrescaler(TIMx, 84-1); //1MHz
  LL_TIM_SetAutoReload(TIMx, 1000-1); //1KHz
  LL_TIM_SetCounterMode(TIMx, LL_TIM_COUNTERMODE_UP);

  // PWM mode
  LL_TIM_OC_SetMode(TIMx, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
  LL_TIM_OC_SetMode(TIMx, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);
  LL_TIM_OC_SetMode(TIMx, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);

  // Start from 0 duty
  LL_TIM_OC_SetCompareCH1(TIMx, 0);
  LL_TIM_OC_SetCompareCH2(TIMx, 0);
  LL_TIM_OC_SetCompareCH3(TIMx, 0);

  // Preload
  LL_TIM_OC_EnablePreload(TIMx, LL_TIM_CHANNEL_CH1);
  LL_TIM_OC_EnablePreload(TIMx, LL_TIM_CHANNEL_CH2);
  LL_TIM_OC_EnablePreload(TIMx, LL_TIM_CHANNEL_CH3);

  // Polarity
  LL_TIM_OC_SetPolarity(TIMx, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH);
  LL_TIM_OC_SetPolarity(TIMx, LL_TIM_CHANNEL_CH2, LL_TIM_OCPOLARITY_HIGH);
  LL_TIM_OC_SetPolarity(TIMx, LL_TIM_CHANNEL_CH3, LL_TIM_OCPOLARITY_HIGH);

  // Enable channels
  LL_TIM_CC_EnableChannel(TIMx, LL_TIM_CHANNEL_CH1);
  LL_TIM_CC_EnableChannel(TIMx, LL_TIM_CHANNEL_CH2);
  LL_TIM_CC_EnableChannel(TIMx, LL_TIM_CHANNEL_CH3);

  LL_TIM_EnableARRPreload(TIMx);

  LL_TIM_GenerateEvent_UPDATE(TIMx);
  LL_TIM_EnableCounter(TIMx);
}

// --- ADC for enkoder ---
void ADC1_Init(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

  LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);
  LL_ADC_SetDataAlignment(ADC1, LL_ADC_DATA_ALIGN_RIGHT);

  LL_ADC_SetSequencersScanMode(ADC1, LL_ADC_SEQ_SCAN_DISABLE);
  LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);
  LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);

  LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_3);

  LL_ADC_SetChannelSamplingTime(
      ADC1,
      LL_ADC_CHANNEL_3,
      LL_ADC_SAMPLINGTIME_84CYCLES
  );

  LL_ADC_Enable(ADC1);
}