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

	while(1)
	{
		ls_led_on_all();
		HAL_Delay(2);
		ls_led_off_all();
		HAL_Delay(500);
	}
}
