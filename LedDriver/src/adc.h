/**
* \file adc.h
* \brief Analog-Digital Converter module
*
* This module contains functions to implement an AD converter
*
* \author Filipe Loureiro & Miguel Silva
* \date 25/05/22
* \version 2.1
* \bug No bugs detected
*/

#include "base.h"

#define ADC_NID DT_NODELABEL(adc) 
#define ADC_RESOLUTION 10
#define ADC_GAIN ADC_GAIN_1_4
#define ADC_REFERENCE ADC_REF_VDD_1_4
#define ADC_ACQUISITION_TIME ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 40)
#define ADC_CHANNEL_ID 1

#define ADC_CHANNEL_INPUT NRF_SAADC_INPUT_AIN1 
#define BUFFER_SIZE 1
#define TIMER_INTERVAL_MSEC 1000

void adc_init();