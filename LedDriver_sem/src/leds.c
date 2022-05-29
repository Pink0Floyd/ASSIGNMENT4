
#include "leds.h"

void leds_init(struct device *gpio0_dev, char n_leds, char c)
{ 
  int ret=0;                                                                      // Local variable, for errors
  int i=0; 

  if((c=='h') || (c=='H'))                                                        // Initialize the leds to a logical 1
  {
    for(i=0; i<4; i++)
    {
    //printk("%d\n\r",leds_pos[i]);
      if((n_leds & leds_pos[i]) == leds_pos[i])
      {
        ret=gpio_pin_configure(gpio0_dev, leds_pin[i], GPIO_OUTPUT_ACTIVE);
        if (ret < 0)
        {
          printk("gpio_pin_configure(LED %d) failed with error %d\n\r",(i+1), ret);        
          return;
        }
      }
    }
  }
  else if((c=='l') || (c=='L'))
  {
    for(i=0; i<4; i++)
    {
    //printk("%d\n\r",leds_pos[i]);
      if((n_leds & leds_pos[i]) == leds_pos[i])
      {
        ret=gpio_pin_configure(gpio0_dev, leds_pin[i], GPIO_OUTPUT_INACTIVE);
        if (ret < 0)
        {
          printk("gpio_pin_configure(LED %d) failed with error %d\n\r",(i+1), ret);        
          return;
        }
      }
    }
  }

}


void leds_set(struct device *gpio0_dev, int n_leds, int state)
{

  int i=0;  
  for(i=0; i<4; i++)
  {
   //printk("%d\n\r",leds_pos[i]);
    if((n_leds & leds_pos[i]) == leds_pos[i])
    {
      gpio_pin_set(gpio0_dev, leds_pin[i], state);
    }
  }
  
}