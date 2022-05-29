/**
* \file pwm.h
* \brief Pulse Width Modulation module
*
* This module contains functions to implement PWM signals with variable duty-cycle
*
* \author Filipe Loureiro & Miguel Silva
* \date 25/05/22
* \version 2.2
* \bug No bugs detected
*/

#ifndef PWM_H
#define PWM_H 

#include "base.h"
#include "leds.h"
#include "gpio.h"

#define PWM0_NID DT_NODELABEL(pwm0) 

// Global Variables:

static struct device *pwm0_dev;		// Pointer to PWM device structure 
static unsigned int pwmPeriod_us = 1000;		// PWM priod in us

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