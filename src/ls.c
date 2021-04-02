/*
 *	ls.c
 *	Low systems: hardware layer
 *	Author: Zachariasz Monka
 */
//TODO more file: ls will use ls_pin_def, ls_led led_uart etc.

#include "stm32l0xx.h"
#include "ls.h"

GPIO_InitTypeDef lls_GPIO_InitStruct;
TIM_HandleTypeDef lls_tim21;

long lls_buzz_cycle;
long lls_buzz_period;

void SystemClock_Config_high_speed(void)
{
	#define SYSCAL 32000000
	#define HCLK 32000000
	#define FCLK 32000000
	#define APB1_per 32000000
	#define APB1_tim 32000000
	#define APB2_per 32000000
	#define APB2_tim 32000000
	#define CK_PWR 32000000
	#define USART1CLK 32000000
	#define USART2CLK 32000000

	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	/** Configure the main internal regulator output voltage
	*/
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
	RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Error_Handler();
	}
}

void Error_Handler(void)
{
	for(;;);
}

enum LED_State lls_LED[8] = {0,0,0,0,0,0,0,0}; //0=off, 1=on, 2=blink

void lls_init_port(void)
{
	//todo other file


	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();


	/* Configure LEDs */
	HAL_GPIO_WritePin(LED_0_Port, LED_0_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_1_Port, LED_1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_2_Port, LED_2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_3_Port, LED_3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_4_Port, LED_4_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_5_Port, LED_5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_6_Port, LED_6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_7_Port, LED_7_Pin,GPIO_PIN_RESET);

	lls_GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	lls_GPIO_InitStruct.Pull = GPIO_NOPULL;
	lls_GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	lls_GPIO_InitStruct.Pin =  LED_0_Pin;
	HAL_GPIO_Init(LED_0_Port, &lls_GPIO_InitStruct);
	lls_GPIO_InitStruct.Pin =  LED_1_Pin;
	HAL_GPIO_Init(LED_1_Port, &lls_GPIO_InitStruct);
	lls_GPIO_InitStruct.Pin =  LED_2_Pin;
	HAL_GPIO_Init(LED_2_Port, &lls_GPIO_InitStruct);
	lls_GPIO_InitStruct.Pin =  LED_3_Pin;
	HAL_GPIO_Init(LED_3_Port, &lls_GPIO_InitStruct);
	lls_GPIO_InitStruct.Pin =  LED_4_Pin;
	HAL_GPIO_Init(LED_4_Port, &lls_GPIO_InitStruct);
	lls_GPIO_InitStruct.Pin =  LED_5_Pin;
	HAL_GPIO_Init(LED_5_Port, &lls_GPIO_InitStruct);
	lls_GPIO_InitStruct.Pin =  LED_6_Pin;
	HAL_GPIO_Init(LED_6_Port, &lls_GPIO_InitStruct);
	lls_GPIO_InitStruct.Pin =  LED_7_Pin;
	HAL_GPIO_Init(LED_7_Port, &lls_GPIO_InitStruct);


	/* Configure OUT */
	HAL_GPIO_WritePin(OUT_1_Port, OUT_1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(OUT_2_Port, OUT_2_Pin,GPIO_PIN_RESET);

	lls_GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	lls_GPIO_InitStruct.Pull = GPIO_NOPULL;
	lls_GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	lls_GPIO_InitStruct.Pin =  OUT_1_Pin;
	HAL_GPIO_Init(OUT_1_Port, &lls_GPIO_InitStruct);
	lls_GPIO_InitStruct.Pin =  OUT_2_Pin;
	HAL_GPIO_Init(OUT_2_Port, &lls_GPIO_InitStruct);

	HAL_GPIO_WritePin(OUT_1_Port, OUT_1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(OUT_2_Port, OUT_2_Pin,GPIO_PIN_RESET);


	/* Configure SW */
	lls_GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	lls_GPIO_InitStruct.Pull = GPIO_PULLUP;

	lls_GPIO_InitStruct.Pin = SW1_Pin;
	HAL_GPIO_Init(SW1_Port, &lls_GPIO_InitStruct);
	lls_GPIO_InitStruct.Pin = SW2_Pin;
	HAL_GPIO_Init(SW2_Port, &lls_GPIO_InitStruct);
	lls_GPIO_InitStruct.Pin = SW3_Pin;
	HAL_GPIO_Init(SW3_Port, &lls_GPIO_InitStruct);

	/* Configure buzz */

	HAL_GPIO_WritePin(buzz_Port, buzz_Pin,GPIO_PIN_RESET);

	lls_GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	lls_GPIO_InitStruct.Pull = GPIO_NOPULL;
	lls_GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	lls_GPIO_InitStruct.Pin =  buzz_Pin;
	HAL_GPIO_Init(buzz_Port, &lls_GPIO_InitStruct);


	/* Configure UART */
	//todo

}

void lls_init_tim(void)
{
	/* Timer 21 interrupt triggered every  */
	HAL_NVIC_SetPriority(TIM21_IRQn, 2, 0);
	__HAL_RCC_TIM21_CLK_ENABLE();

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	lls_tim21.Instance = TIM21;
	lls_tim21.Init.Prescaler = 32; //1MHz
	lls_tim21.Init.CounterMode = TIM_COUNTERMODE_DOWN;
	lls_tim21.Init.Period = 50; //20kHz
	lls_tim21.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	lls_tim21.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&lls_tim21) != HAL_OK)
	{
		Error_Handler();
	}

	 sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&lls_tim21, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&lls_tim21, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_TIM_Base_Start_IT(&lls_tim21);
}

void lls_init_exti(void)
{
	/* EXTI interrupt */
	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 3, 0);
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
	//other configuration in lls_init_port:
	//	GPIO_MODE_IT_FALLING

}

void ls_init(void)
{
	HAL_Init();
	SystemClock_Config_high_speed();
	lls_init_port();
	lls_init_tim();
	lls_init_exti();
}

void ls_led_off_all(void)
{
	lls_LED[0] = LED_OFF;
	lls_LED[1] = LED_OFF;
	lls_LED[2] = LED_OFF;
	lls_LED[3] = LED_OFF;
	lls_LED[4] = LED_OFF;
	lls_LED[5] = LED_OFF;
	lls_LED[6] = LED_OFF;
	lls_LED[7] = LED_OFF;

	HAL_GPIO_WritePin(LED_0_Port, LED_0_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_1_Port, LED_1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_2_Port, LED_2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_3_Port, LED_3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_4_Port, LED_4_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_5_Port, LED_5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_6_Port, LED_6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_7_Port, LED_7_Pin,GPIO_PIN_RESET);
}

void ls_led_on_all(void)
{
	lls_LED[0] = LED_ON;
	lls_LED[1] = LED_ON;
	lls_LED[2] = LED_ON;
	lls_LED[3] = LED_ON;
	lls_LED[4] = LED_ON;
	lls_LED[5] = LED_ON;
	lls_LED[6] = LED_ON;
	lls_LED[7] = LED_ON;

	HAL_GPIO_WritePin(LED_0_Port, LED_0_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_1_Port, LED_1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_2_Port, LED_2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_3_Port, LED_3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_4_Port, LED_4_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_5_Port, LED_5_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_6_Port, LED_6_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_7_Port, LED_7_Pin,GPIO_PIN_SET);
}

void ls_led_on(short number)
{
	lls_LED[number] = LED_ON;

	if(lls_LED[0] == LED_ON)HAL_GPIO_WritePin(LED_7_Port,LED_7_Pin,GPIO_PIN_SET);
	if(lls_LED[1] == LED_ON)HAL_GPIO_WritePin(LED_6_Port,LED_6_Pin,GPIO_PIN_SET);
	if(lls_LED[2] == LED_ON)HAL_GPIO_WritePin(LED_5_Port,LED_5_Pin,GPIO_PIN_SET);
	if(lls_LED[3] == LED_ON)HAL_GPIO_WritePin(LED_4_Port,LED_4_Pin,GPIO_PIN_SET);
	if(lls_LED[4] == LED_ON)HAL_GPIO_WritePin(LED_3_Port,LED_3_Pin,GPIO_PIN_SET);
	if(lls_LED[5] == LED_ON)HAL_GPIO_WritePin(LED_2_Port,LED_2_Pin,GPIO_PIN_SET);
	if(lls_LED[6] == LED_ON)HAL_GPIO_WritePin(LED_1_Port,LED_1_Pin,GPIO_PIN_SET);
	if(lls_LED[7] == LED_ON)HAL_GPIO_WritePin(LED_0_Port,LED_0_Pin,GPIO_PIN_SET);
}

void ls_led_off(short number)
{
	lls_LED[number] = LED_OFF;

	if(lls_LED[0] == LED_OFF)HAL_GPIO_WritePin(LED_7_Port,LED_7_Pin,GPIO_PIN_RESET);
	if(lls_LED[1] == LED_OFF)HAL_GPIO_WritePin(LED_6_Port,LED_6_Pin,GPIO_PIN_RESET);
	if(lls_LED[2] == LED_OFF)HAL_GPIO_WritePin(LED_5_Port,LED_5_Pin,GPIO_PIN_RESET);
	if(lls_LED[3] == LED_OFF)HAL_GPIO_WritePin(LED_4_Port,LED_4_Pin,GPIO_PIN_RESET);
	if(lls_LED[4] == LED_OFF)HAL_GPIO_WritePin(LED_3_Port,LED_3_Pin,GPIO_PIN_RESET);
	if(lls_LED[5] == LED_OFF)HAL_GPIO_WritePin(LED_2_Port,LED_2_Pin,GPIO_PIN_RESET);
	if(lls_LED[6] == LED_OFF)HAL_GPIO_WritePin(LED_1_Port,LED_1_Pin,GPIO_PIN_RESET);
	if(lls_LED[7] == LED_OFF)HAL_GPIO_WritePin(LED_0_Port,LED_0_Pin,GPIO_PIN_RESET);
}

void ls_buzz(int frequency, short time)
//working in interrupt, does NOT wait until the end of the sound
{
	lls_buzz_period = 10000/frequency;
	lls_buzz_cycle = 20*time;
	HAL_NVIC_EnableIRQ(TIM21_IRQn);
	//TODO off buzzer DC
}

