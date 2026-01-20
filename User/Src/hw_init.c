#include "hw_init.h"

// --- GPIO ---

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
// --- USART ---