#include "stm32f4xx.h"



void KEY_Init(void);
void LED_Init(void);



int main(void)
{

SystemCoreClockUpdate();
KEY_Init();
LED_Init();

	
while(1)
{

}

}

void KEY_Init(void)

{
	
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

//RCC
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
//GPIO
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_4;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
 // GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  //GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	
//EXTI	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line4;
  EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);

//NVIC
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;

  NVIC_Init(&NVIC_InitStruct);
}


void LED_Init(void)

{
	GPIO_InitTypeDef GPIO_InitStruct;
//RCC
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
//GPIO
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_13 ;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}

void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4))//(EXTI->PR & 1)
  {
    EXTI_ClearITPendingBit(EXTI_Line4);
    GPIO_ToggleBits(GPIOC, GPIO_Pin_13);
  }
}



