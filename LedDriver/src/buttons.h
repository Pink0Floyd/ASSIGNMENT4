/**
* \file buttons.h
* \brief Buttons Functions
*
* This module implements the functions to initialise and use 4 built in board buttons and 4 external buttons
* \author Filipe Loureiro & Miguel Silva
* \date 17/05/22
* \version 1.4
* \bug No bugs found
*/

#ifndef _BUTTONS_H
#define _BUTTONS_H

#include "base.h"

#define BUTTON1 11                                          // BUTTON1 pin number of GPIO_0
#define BUTTON2 12                                          // BUTTON2 pin number of GPIO_0
#define BUTTON3 24                                          // BUTTON3 pin number of GPIO_0
#define BUTTON4 25                                          // BUTTON4 pin number of GPIO_0
#define BUTTON5 03							// BUTTON5 pin number of GPIO_0
#define BUTTON6 04							// BUTTON6 pin number of GPIO_0
#define BUTTON7 28                                          // BUTTON7 pin number of GPIO_0
#define BUTTON8 29                                          // BUTTON8 pin number of GPIO_0

#define N_BUTTONS 8							// Number of buttons
#define TIME_SLEEP 50

const static int buttons_pin[8]={BUTTON1,BUTTON2,BUTTON3,BUTTON4,BUTTON5,BUTTON6,BUTTON7,BUTTON8};    // Buttons data with pins numbers             
const static int buttons_pos[8]={1,2,4,8,16,32,64,128};						      // Buttons data with corresponding position 

static struct gpio_callback but1_cb_data;                                     // Callback structure related to BUTTON 1
static struct gpio_callback but2_cb_data;                                     // Callback structure related to BUTTON 2
static struct gpio_callback but3_cb_data;                                     // Callback structure related to BUTTON 3
static struct gpio_callback but4_cb_data;                                     // Callback structure related to BUTTON 4
static struct gpio_callback but5_cb_data;                                     // Callback structure related to BUTTON 5
static struct gpio_callback but6_cb_data;                                     // Callback structure related to BUTTON 6
static struct gpio_callback but7_cb_data;                                     // Callback structure related to BUTTON 7
static struct gpio_callback but8_cb_data;                                     // Callback structure related to BUTTON 8

static int but1_flag = 0;						      // Callback variable, flag to signal a BUTTON 1 press
static int but2_flag = 0;						      // Callback variable, flag to signal a BUTTON 2 press 
static int but3_flag = 0;						      // Callback variable, flag to signal a BUTTON 3 press 
static int but4_flag = 0;						      // Callback variable, flag to signal a BUTTON 4 press 
static int but5_flag = 0;						      // Callback variable, flag to signal a BUTTON 5 press 
static int but6_flag = 0;						      // Callback variable, flag to signal a BUTTON 6 press 
static int but7_flag = 0;						      // Callback variable, flag to signal a BUTTON 7 press 
static int but8_flag = 0;						      // Callback variable, flag to signal a BUTTON 8 press 


///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:

/**
* \brief Built in and External Buttons initialization function without interrupts
*
* Initializes the board buttons by using a byte for these porpouse, button 1 match to byte=1, button 2 match to byte=2, ect
*
* \param [IN] struct device *gpio0  -> the pointer for gpio0 struct
* \param [IN] char n_buttons        -> byte corresponding to the buttons to activate
*
* \date 25/04/22
* \bug No bugs detected
*/
void buttons_init(struct device *gpio0_dev, char n_buttons);


/**
* \brief Built in and External Buttons initialization function with interrupts
*
* Initializes the board buttons by using a byte for these porpouse, button 1 match to byte=1, button 2 match to byte=2, ect
*
* \param [IN] struct device *gpio0  -> the pointer for gpio0 struct
* \param [IN] char n_buttons        -> byte corresponding to the buttons to activate
* \param [IN] char c                -> 'H' or 'h' to interrupt at rising edge
                                    -> 'L' or 'l' to interrupt at falling edge
                                    -> 'B' or 'b' to interrupt at both edges
*
* \date 25/04/22
* \bug No bugs detected
*/
void buttons_init_(struct device *gpio0_dev, char n_buttons, char c);


/**
* \brief Read Buttons Flags
*
* Return the current flag button state
*
* \param [IN] int button	    -> the button number for read the flag 
*
* \date 8/05/22
* \bug No bugs detected
*/
int read_buttons(int button);


///////////////////////////////////////////////////////////////////////////////////////
//  Private Functions:

// void buttons_callback_init(struct device *gpio0_dev,char n_buttons);
// void reset_flags();

#endif