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

	ls_led_blink_1Hz(0);
	ls_led_blink_1Hz(7);

	while(1)
	{

	}
}

/* interup */
//todo interrup_file
volatile uint8_t lls_debouncing_ch1 = 0;
volatile uint8_t lls_debouncing_ch2 = 0;
volatile uint8_t lls_debouncing_ch3 = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *lls_tim)
{

	if(lls_tim->Instance == TIM22)//check source
	//100Hz
	{
		//LED blink
		extern enum LED_State lls_LED[8];
		static volatile uint8_t lls_blink_counter = 0;
		lls_blink_counter ++;
		if(lls_blink_counter >= 100)
			lls_blink_counter = 0;

		if(lls_blink_counter == 0)
		{
			if(lls_LED[0] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_7_Port,LED_7_Pin,GPIO_PIN_SET);
			if(lls_LED[1] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_6_Port,LED_6_Pin,GPIO_PIN_SET);
			if(lls_LED[2] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_5_Port,LED_5_Pin,GPIO_PIN_SET);
			if(lls_LED[3] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_4_Port,LED_4_Pin,GPIO_PIN_SET);
			if(lls_LED[4] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_3_Port,LED_3_Pin,GPIO_PIN_SET);
			if(lls_LED[5] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_2_Port,LED_2_Pin,GPIO_PIN_SET);
			if(lls_LED[6] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_1_Port,LED_1_Pin,GPIO_PIN_SET);
			if(lls_LED[7] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_0_Port,LED_0_Pin,GPIO_PIN_SET);
		}
		if(lls_blink_counter == 50)
		{
			if(lls_LED[0] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_7_Port,LED_7_Pin,GPIO_PIN_RESET);
			if(lls_LED[1] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_6_Port,LED_6_Pin,GPIO_PIN_RESET);
			if(lls_LED[2] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_5_Port,LED_5_Pin,GPIO_PIN_RESET);
			if(lls_LED[3] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_4_Port,LED_4_Pin,GPIO_PIN_RESET);
			if(lls_LED[4] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_3_Port,LED_3_Pin,GPIO_PIN_RESET);
			if(lls_LED[5] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_2_Port,LED_2_Pin,GPIO_PIN_RESET);
			if(lls_LED[6] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_1_Port,LED_1_Pin,GPIO_PIN_RESET);
			if(lls_LED[7] == LED_BLINK_1Hz)HAL_GPIO_WritePin(LED_0_Port,LED_0_Pin,GPIO_PIN_RESET);
		}
		if(lls_blink_counter % 20 == 0)
		{
			if(lls_LED[0] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_7_Port,LED_7_Pin,GPIO_PIN_SET);
			if(lls_LED[1] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_6_Port,LED_6_Pin,GPIO_PIN_SET);
			if(lls_LED[2] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_5_Port,LED_5_Pin,GPIO_PIN_SET);
			if(lls_LED[3] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_4_Port,LED_4_Pin,GPIO_PIN_SET);
			if(lls_LED[4] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_3_Port,LED_3_Pin,GPIO_PIN_SET);
			if(lls_LED[5] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_2_Port,LED_2_Pin,GPIO_PIN_SET);
			if(lls_LED[6] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_1_Port,LED_1_Pin,GPIO_PIN_SET);
			if(lls_LED[7] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_0_Port,LED_0_Pin,GPIO_PIN_SET);
		}
		if(lls_blink_counter % 20 == 10)
		{
			if(lls_LED[0] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_7_Port,LED_7_Pin,GPIO_PIN_RESET);
			if(lls_LED[1] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_6_Port,LED_6_Pin,GPIO_PIN_RESET);
			if(lls_LED[2] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_5_Port,LED_5_Pin,GPIO_PIN_RESET);
			if(lls_LED[3] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_4_Port,LED_4_Pin,GPIO_PIN_RESET);
			if(lls_LED[4] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_3_Port,LED_3_Pin,GPIO_PIN_RESET);
			if(lls_LED[5] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_2_Port,LED_2_Pin,GPIO_PIN_RESET);
			if(lls_LED[6] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_1_Port,LED_1_Pin,GPIO_PIN_RESET);
			if(lls_LED[7] == LED_BLINK_5Hz)HAL_GPIO_WritePin(LED_0_Port,LED_0_Pin,GPIO_PIN_RESET);
		}

		//debouncing
		if(lls_debouncing_ch1)
		{
			if(HAL_GPIO_ReadPin(SW1_Port,SW1_Pin)!=0)
				lls_debouncing_ch1--;
		}
		if(lls_debouncing_ch2)
		{
			if(HAL_GPIO_ReadPin(SW2_Port,SW2_Pin)!=0)
				lls_debouncing_ch2--;
		}
		if(lls_debouncing_ch3)
		{
			if(HAL_GPIO_ReadPin(SW3_Port,SW3_Pin)!=0)
				lls_debouncing_ch3--;
		}

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
		if(lls_debouncing_ch3 == 0)
		{
			lls_debouncing_ch3 = 4;// debouncing 30/40ms

			ls_led_off_all();
		}
	}
	if(HAL_GPIO_ReadPin(SW2_Port,SW2_Pin)==0) //interrup SW2
	{
		if(lls_debouncing_ch2 == 0)
		{
			lls_debouncing_ch2 = 4;// debouncing 30/40ms

			ls_led_on_all();
		}
	}
	if(HAL_GPIO_ReadPin(SW1_Port,SW1_Pin)==0) //interrup SW1
	{
		if(lls_debouncing_ch1 == 0)
		{
			lls_debouncing_ch1 = 4;// debouncing 30/40ms

			ls_buzz(3000, 100);
		}
	}
}
