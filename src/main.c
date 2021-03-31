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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *lls_tim21)
{
	//20kHz do not run every time

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
