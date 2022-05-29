
#include "pwm.h"

// Global Variables:

static const struct device *pwm0_dev;		// Pointer to PWM device structure 
static unsigned int pwmPeriod_us = 1000;		// PWM priod in us

void pwm_init()
{
      // Initialise GPIO0:
      gpio0_init();

      // Initialize PWM:
      pwm0_dev = device_get_binding(DT_LABEL(PWM0_NID));
      if (pwm0_dev == NULL) 
      {
	    printk("\tError: Failed to bind to PWM0\n r");
	    return;
      }
      printk("\tInitialised PWM module\n");
}

void pwm_led_set(uint16_t duty_cycle)
{
      int ret[4]={};
//	ret[1] = pwm_pin_set_usec(pwm0_dev, LED3, pwmPeriod_us,(unsigned int)(pwmPeriod_us*duty_cycle/100), PWM_POLARITY_NORMAL);
	ret[0] = pwm_pin_set_usec(pwm0_dev, LED1, pwmPeriod_us,(unsigned int)(pwmPeriod_us*duty_cycle/100), PWM_POLARITY_NORMAL);

//	ret[2] = pwm_pin_set_usec(pwm0_dev, LED2, pwmPeriod_us,(unsigned int)(pwmPeriod_us*(100-duty_cycle)/100), PWM_POLARITY_NORMAL);
//	ret[3] = pwm_pin_set_usec(pwm0_dev, LED4, pwmPeriod_us,(unsigned int)(pwmPeriod_us*(100-duty_cycle)/100), PWM_POLARITY_NORMAL);
      if (ret[0]+ret[1]+ret[2]+ret[3]!=0)
	{
		printk("\tError: failed to set pulse width\n");
		return;
      }
}