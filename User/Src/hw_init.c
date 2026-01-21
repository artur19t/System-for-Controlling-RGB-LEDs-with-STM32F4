#include "hw_init.h"

// --- GPIO ---
//PB 0,1,2
// --- PB0, Button for bed led ---
void GPIO_Button_Bed_Init(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  
  LL_GPIO_InitTypeDef GPIO_Usr_Struct = {0};
  GPIO_Usr_Struct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_Usr_Struct.Pin = LL_GPIO_PIN_0;
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

// --- PB0, Button for room led ---
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

// --- Interrupts ----
void IT_BUTTONS_Init(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_EXTI_InitTypeDef IT_But_Init = {0};
  IT_But_Init.LineCommand = ENABLE;
  IT_But_Init.Line_0_31 = LL_EXTI_LINE_0 | LL_EXTI_LINE_1 | LL_EXTI_LINE_2;
  IT_But_Init.Mode = LL_EXTI_MODE_IT;
  IT_But_Init.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&IT_But_Init);
  
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE0);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE1);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE2);
  
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0);
  NVIC_SetPriority(EXTI0_IRQn, 0);
  NVIC_EnableIRQ(EXTI0_IRQn);
  
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_1);
  NVIC_SetPriority(EXTI1_IRQn, 0);
  NVIC_EnableIRQ(EXTI1_IRQn);
  
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_2);
  NVIC_SetPriority(EXTI2_IRQn, 0);
  NVIC_EnableIRQ(EXTI2_IRQn);
}

// --- USART ---