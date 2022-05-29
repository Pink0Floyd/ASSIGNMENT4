/**
* \file leds.h
* \brief Builtin LEDs functions
*
* This module implements the functions to initialize and configurate the 4 built in board leds, LEDS are Active LOW
* \author Filipe Loureiro & Miguel Silva
* \date 17/05/22
* \version 1.1
* \bug No bugs found
*/

/* OBSERVATION:
* This module will suffer many updates due to the newness that this board brings to us
* In the API reference there is a topic related to the Leds: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/reference/peripherals/led.html
*/

#ifndef _LEDS_H    
#define _LEDS_H

#include "base.h"


#define LED1 13                                             // LED1 pin number of GPIO_0
#define LED2 14                                             // LED2 pin number of GPIO_0
#define LED3 15                                             // LED3 pin number of GPIO_0
#define LED4 16                                             // LED4 pin number of GPIO_0

static int leds_pin[4]={LED1,LED2,LED3,LED4};                                        // Leds data with pins numbers             
static int leds_pos[4]={1,2,4,8};                                                    // Leds data with corresponding position, acording to the functions char led 

///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:

/**
* \brief Built in Leds initialization function
*
* Initializes the board leds by using a byte for these porpouse, led 1 match to byte=1, led 2 match to byte=2, ect
*
* \author Filipe Loureiro & Miguel Silva
* \param [IN] struct device *gpio0  -> the pointer for gpio0 struct
* \param [IN] char n_leds           -> byte corresponding to the leds to connect
* \param [IN] char c                -> 'H' or 'h' to initialize the leds to a logic 1
                                    -> 'L' or 'l' to initialize the leds to a logic 0
* \date 25/04/22
* \bug Currently under tests, and continuous updating
*/
void leds_init(struct device *gpio0, char n_leds, char c);

/*
* Set the board leds by using a byte for these porpouse, led 1 match to byte=1, led 2 match to byte=2, ect
*
* \author Filipe Loureiro & Miguel Silva
* \param [IN] struct device *gpio0  -> the pointer for gpio0 struct
* \param [IN] char n_leds           -> byte corresponding to the leds to connect
* \param [IN] unsigned int state    -> 0 to set the leds to a logic 0, it means LED ON
                                    -> 1 to set the leds to a logic 1, it means LED OFF
* \date 25/04/22
* \bug Currently under tests, and continuous updating
*/

void leds_set(struct device *gpio0, int n_leds, int state);

///////////////////////////////////////////////////////////////////////////////////////
//  Private Functions:
  
#endif