
#include "pwm.h"

void pwm_init()
{
      // Initialise GPIO0:
      gpio0_init();

      // Initialize PWM:
      pwm0_dev = device_get_binding(DT_LABEL(PWM0_NID));
      if (pwm0_dev == NULL) 
      {
	    printk("Error: Failed to bind to PWM0\n r");
	    return;
      }
      printk("Initialized PWM module\n");
}

void pwm_led_set(uint16_t dutty_cycle)
{
      int ret=0;
      ret = pwm_pin_set_usec(pwm0_dev, LED1, pwmPeriod_us,(unsigned int)(dutty_cycle), PWM_POLARITY_NORMAL);
      if (ret)
	{
		printk("Error %d: failed to set pulse width\n", ret);
		return;
      }
}