/**
  ******************************************************************************
  * @file    main.c
  * @author  Zachariasz Monka
  * @brief   Default main function.
  ******************************************************************************
*/

#include "ls.h"
#include "stm32l0xx.h"

int main(void)
{
	ls_init();
	ls_led_on_all();
	ls_buzz(1000, 100);
	ls_led_off_all();

	while(1)
	{

	}
}

/* interup */
//todo interrup_file

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *lls_tim)
{

	if(lls_tim->Instance == TIM22)//check source
	//100Hz
	{

	}
	if(lls_tim->Instance == TIM21)//check source
	//20kHz do not run every time
	{
		if(lls_buzz_cycle-- <= 0)
		{
			HAL_GPIO_WritePin(buzz_Port,buzz_Pin,GPIO_PIN_RESET);
			HAL_NVIC_DisableIRQ(TIM21_IRQn);
		}

		if(lls_buzz_cycle % lls_buzz_period == 0)
		{
			if(HAL_GPIO_ReadPin(buzz_Port,buzz_Pin) == 1)
				HAL_GPIO_WritePin(buzz_Port,buzz_Pin,GPIO_PIN_RESET);
			else
				HAL_GPIO_WritePin(buzz_Port,buzz_Pin,GPIO_PIN_SET);
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)//falling
{
//todo ringbuffer, debouncing
	if(HAL_GPIO_ReadPin(SW3_Port,SW3_Pin)==0) //interrup SW3
	{
		ls_led_off_all();
	}
	if(HAL_GPIO_ReadPin(SW2_Port,SW2_Pin)==0) //interrup SW2
	{
		ls_led_on_all();
	}
	if(HAL_GPIO_ReadPin(SW1_Port,SW1_Pin)==0) //interrup SW1
	{
		ls_buzz(3000, 100);
	}
}
