#include "IT_handlers.h"

// --- table button IT ---
void EXTI1_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1))
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
    btn_table.event = 1;
  }
}


// --- room button IT ---
void EXTI2_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_2))
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
    btn_room.event = 1;
  }
}

// --- bed button IT ---
void EXTI3_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_3))
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_3);
    btn_bed.event = 1;
  }
}
