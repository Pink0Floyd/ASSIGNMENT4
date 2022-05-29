/**
* \file gpio.h
* \brief GPIO functions
*
* This module implements the functions to initialize and do some gpio configuration
* \author Filipe Loureiro & Miguel Silva
* \date 17/05/22
* \version 1.1
* \bug No bugs detected
*/

#ifndef _GPIO_H
#define _GPIO_H

#include "base.h"

///////////////////////////////////////////////////////////////////////////////////////
//  Public Functions:

/**
* \brief GPIO 0 initialization function
*
* Initializes the GPIO 0 in order to use it pins
*
* \return Return a pointer to a device struct type
* \date 25/04/22
* \bug No bugs detected
*/

struct device *gpio0_init();


/**
* \brief GPIO 1 initialization function
*
* Initializes the GPIO 1 in order to use it pins
*
* \return Return a pointer to a struct of device type
* \date 25/04/22
* \bug No bugs detected
*/
struct device *gpio1_init();

///////////////////////////////////////////////////////////////////////////////////////
//  Private Functions:

#endif