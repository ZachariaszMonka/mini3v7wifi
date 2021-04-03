/*
 *	ls.h
 *	Low systems: hardware layer
 *	Author: Zachariasz Monka
 */

#ifndef LS_H_
#define LS_H_

#include "stm32l0xx.h"

extern GPIO_InitTypeDef lls_GPIO_InitStruct;
extern TIM_HandleTypeDef lls_tim21;
extern TIM_HandleTypeDef lls_tim22;

extern long lls_buzz_cycle;
extern long lls_buzz_period;

#define wifi_RES_Pin GPIO_PIN_0
#define wifi_RES_Port GPIOA
#define wifi_EN_Pin GPIO_PIN_1
#define wifi_EN_Port GPIOA
#define wifi_Tx_Pin GPIO_PIN_2
#define wifi_Tx_Port GPIOA
#define wifi_Rx_Pin GPIO_PIN_3
#define wifi_Rx_Port GPIOA

#define uart_Tx_Pin GPIO_PIN_6
#define uart_Tx_Port GPIOB
#define uart_Rx_Pin GPIO_PIN_7
#define uart_Rx_Port GPIOB

#define SW1_Pin GPIO_PIN_15
#define SW1_Port GPIOA
#define SW1_EXTI_IRQn EXTI4_15_IRQn
#define SW2_Pin GPIO_PIN_4
#define SW2_Port GPIOA
#define SW2_EXTI_IRQn EXTI4_15_IRQn
#define SW3_Pin GPIO_PIN_5
#define SW3_Port GPIOA
#define SW3_EXTI_IRQn EXTI4_15_IRQn

#define IO_Pin GPIO_PIN_5
#define IO_Port GPIOB
#define IO_EXTI_IRQn EXTI4_15_IRQn

#define LED_0_Pin GPIO_PIN_6
#define LED_0_Port GPIOA
#define LED_1_Pin GPIO_PIN_7
#define LED_1_Port GPIOA
#define LED_2_Pin GPIO_PIN_0
#define LED_2_Port GPIOB
#define LED_3_Pin GPIO_PIN_1
#define LED_3_Port GPIOB
#define LED_4_Pin GPIO_PIN_8
#define LED_4_Port GPIOA
#define LED_5_Pin GPIO_PIN_9
#define LED_5_Port GPIOA
#define LED_6_Pin GPIO_PIN_10
#define LED_6_Port GPIOA
#define LED_7_Pin GPIO_PIN_11
#define LED_7_Port GPIOA

#define buzz_Pin GPIO_PIN_12
#define buzz_Port GPIOA

#define OUT_2_Pin GPIO_PIN_3
#define OUT_2_Port GPIOB
#define OUT_1_Pin GPIO_PIN_4
#define OUT_1_Port GPIOB


void SystemClock_Config_high_speed(void);
void Error_Handler(void);

void ls_init(void);

enum LED_State {LED_OFF = 0, LED_ON = 1, LED_BLINK_1Hz, LED_BLINK_5Hz};

void ls_led_on_all(void);
void ls_led_off_all(void);
void ls_led_on(short number);
void ls_led_off(short number);
void ls_led_blink_1Hz(short number);
void ls_led_blink_5Hz(short number);

void ls_buzz(int frequency, short time);


//void ls_out1_PWM(short wide);
//void ls_out2_PWM(short wide);
//void ls_out1_on(void);
//void ls_out2_on(void);
//void ls_out1_off(void);
//void ls_out2_off(void);


#endif /* LS_H_ */
