
#include "gpio.h"

/*
  const struct device *gpio0_dev;
  gpio0_dev=gpio0_init();
*/

struct device *gpio0_init()
{
  #define GPIO0_NID DT_NODELABEL(gpio0)                       // Get the gpio0 identifier from the device tree
  #define GPIO0_LABEL DT_LABEL(GPIO0_NID)                     // Get the gpio0 label from the device tree

  struct device *gpio0_dev;                                    // Pointer to GPIO device structure

  gpio0_dev=device_get_binding(GPIO0_LABEL);                
  if(gpio0_dev==NULL)
  {
    printk("Failed to bind to GPIO0\n\r");        
  }  

  return gpio0_dev;
}


/*
  const struct device *gpio1_dev;
  gpio1_dev=gpio1_init();
*/

struct device *gpio1_init()
{
  #define GPIO1_NID DT_NODELABEL(gpio1)                       // Get the gpio0 identifier from the device tree
  #define GPIO1_LABEL DT_LABEL(GPIO1_NID)                     // Get the gpio0 label from the device tree

  struct device *gpio1_dev;                                    // Pointer to GPIO device structure

  gpio1_dev=device_get_binding(GPIO1_LABEL);                
  if(gpio1_dev==NULL)
  {
    printk("Failed to bind to GPIO1\n\r");        
  }
  else
  {
    printk("Bind to GPIO1 successfull \n\r");        
  }    

  return gpio1_dev;
}