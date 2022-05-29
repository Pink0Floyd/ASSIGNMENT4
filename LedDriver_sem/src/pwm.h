/**
* \file pwm.h
* \brief Pulse Width Modulation module
*
* This module contains functions to implement PWM signals with variable duty-cycle
*
* \author Filipe Loureiro & Miguel Silva
* \date 25/05/22
* \version 2.4
* \bug No bugs detected
*/

#ifndef PWM_H
#define PWM_H 

#include "base.h"
#include "gpio.h"

#define PWM0_NID DT_NODELABEL(pwm0)

#define LED1 13                                             // LED1 pin number of GPIO_0
#define LED2 14                                             // LED2 pin number of GPIO_0
#define LED3 15                                             // LED3 pin number of GPIO_0
#define LED4 16                                             // LED4 pin number of GPIO_0

///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:

/**
* \brief PWM initialization function
*
* Initializes the PWM in order to use it 
*
* \bug No bugs detected
*/
void pwm_init();

/**
* \brief 
*
*\param [IN] uint16_t duty_cycle to set the PWM
* \bug No bugs detected
*/
void pwm_led_set(uint16_t duty_cycle);

#endif