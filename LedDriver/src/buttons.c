
#include "buttons.h"

// Calback Functions:
void but1_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
 {
      reset_flags();
      but1_flag=1;										      // Update Flag                               
 } 

 void but2_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
 {
      reset_flags();
      but2_flag=1;										      // Update     
 } 

 void but3_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
 {
      reset_flags();
      but3_flag=1;										      // Update Flag 
 } 

 void but4_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
    {
      reset_flags();
      but4_flag=1;										      // Update Flag
    } 

void but5_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
    {
      reset_flags();
      but5_flag=1;										      // Update Flag
    }

 void but6_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
    {
      reset_flags();
      but6_flag=1;										      // Update Flag
    }

void but7_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
    {
      reset_flags();
      but7_flag=1;										      // Update Flag
    }
  
void but8_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
    {
      reset_flags();
      but8_flag=1;										      // Update Flag
    }


// Buttons initialise without interrupts:
void buttons_init(struct device *gpio0_dev, char n_buttons)                                     // Initialize the board's buttons  
{
  int i=0;
  int ret=0;

  for(i=0; i<N_BUTTONS; i++)
  {
    //printk("%d\n\r",buttons_pos[i]);
    if((n_buttons & buttons_pos[i]) == buttons_pos[i])
    {
      ret = gpio_pin_configure(gpio0_dev, buttons_pin[i], GPIO_INPUT | GPIO_PULL_UP);
      if (ret < 0) 
      {
        printk("Error %d: Failed to configure Button %d \n\r", ret, (i+1));
	return;
      }
    }
  }
}

// Buttons Initialise with interrupts:
void buttons_init_(struct device *gpio0_dev, char n_buttons, char c)
{
  buttons_init(gpio0_dev,n_buttons);
  int ret=0;
  int i=0;
    
  if((c=='H') || (c='h'))                                                                           // Rising edge interrupt configuration
  {
    for(i=0; i<N_BUTTONS; i++)
    {
      if((n_buttons & buttons_pos[i]) == buttons_pos[i])
      {
        ret=gpio_pin_interrupt_configure(gpio0_dev, buttons_pin[i], GPIO_INT_EDGE_TO_ACTIVE);         // Button rising edge interrupt configuration 
        if (ret < 0)                                                                                  // In case of fail initialization and consequent error message
        { 
          printk("Error %d: failed to configure interrupt on BUTTON %d pin \n\r", ret, (i+1));
          return;
        }
      }
    }
  }
  else if((c=='L') || (c='l'))                                                                        // Falling edge interrupt configuration
  {
    for(i=0; i<N_BUTTONS; i++)
    {
      //printk("%d\n\r",buttons_pos[i]);
      if((n_buttons & buttons_pos[i]) == buttons_pos[i])
      {
        ret=gpio_pin_interrupt_configure(gpio0_dev, buttons_pin[i], GPIO_INT_EDGE_TO_INACTIVE);       // Button falling edge interrupt configuration 
        if (ret < 0)                                                                                  // In case of fail initialization and consequent error message
        { 
          printk("Error %d: failed to configure interrupt on BUTTON %d pin \n\r", ret, (i+1));
          return;
        }
      }
    }
  }
  else if((c=='B') || (c='b'))                                                                        // Rising and falling edge interrupt configuration
  {
    for(i=0; i<N_BUTTONS; i++)
    {
      //printk("%d\n\r",buttons_pos[i]);
      if((n_buttons & buttons_pos[i]) == buttons_pos[i])
      {
        ret=gpio_pin_interrupt_configure(gpio0_dev, buttons_pin[i], GPIO_INT_EDGE_BOTH);              // Button rising and fallinf edge interrupt configuration 
        if (ret < 0)                                                                                  // In case of fail initialization and consequent error message
        { 
          printk("Error %d: failed to configure interrupt on BUTTON %d pin \n\r", ret, (i+1));
          return;
        }
      }
    }
  }
      buttons_callback_init(gpio0_dev, n_buttons);
}

// Calback Function:
void buttons_callback_init(struct device *gpio0_dev, char n_buttons)
{
      if((n_buttons & 1) == 1)
      {
	    gpio_init_callback(&but1_cb_data, but1_cbfunction, BIT(BUTTON1));
	    gpio_add_callback(gpio0_dev, &but1_cb_data);
      }
      if((n_buttons & 2) == 2)
      {
	    gpio_init_callback(&but2_cb_data, but2_cbfunction, BIT(BUTTON2));
	    gpio_add_callback(gpio0_dev, &but2_cb_data);
      }
      if((n_buttons & 4) == 4)
      {
	    gpio_init_callback(&but3_cb_data, but3_cbfunction, BIT(BUTTON3));
	    gpio_add_callback(gpio0_dev, &but3_cb_data);
      }
      if((n_buttons & 8) == 8)
      {
	    gpio_init_callback(&but4_cb_data, but4_cbfunction, BIT(BUTTON4));
	    gpio_add_callback(gpio0_dev, &but4_cb_data);
      }
      if((n_buttons & 16) == 16)
      {
	    gpio_init_callback(&but5_cb_data, but5_cbfunction, BIT(BUTTON5));
	    gpio_add_callback(gpio0_dev, &but5_cb_data);
	}
      if((n_buttons & 32) == 32)
      {
	    gpio_init_callback(&but6_cb_data, but6_cbfunction, BIT(BUTTON6));
	    gpio_add_callback(gpio0_dev, &but6_cb_data);
      }
      if((n_buttons & 64) == 64)
      {
	    gpio_init_callback(&but7_cb_data, but7_cbfunction, BIT(BUTTON7));
	    gpio_add_callback(gpio0_dev, &but7_cb_data);
      }
      if((n_buttons & 128) == 128)
      {
	    gpio_init_callback(&but8_cb_data, but8_cbfunction, BIT(BUTTON8));
	    gpio_add_callback(gpio0_dev, &but8_cb_data);
      }
}

// Read Buttons Flags:
int read_buttons(int button)
{
      switch (button)
	{
		case 1:
		if(but1_flag==1)
		{	    
			k_msleep(TIME_SLEEP);  
            	but1_flag=0;
            	return 1;
            }
            else 
            {
            	    k_msleep(TIME_SLEEP);  
            	    return 0;
            }
	    break;
     
      case 2:
      
	    if(but2_flag==1)
	    {
            	    k_msleep(TIME_SLEEP);  
            	    but2_flag=0;
            	    return 1;
	    }
            else 
            {
		  k_msleep(TIME_SLEEP);  
		  return 0;
            }
	    break;
     
     case 3:
      
	    if(but3_flag==1)
            {
            	    k_msleep(TIME_SLEEP);  
            	    but3_flag=0;
            	    return 1;
            }
            else 
            {
            	    k_msleep(TIME_SLEEP);  
            	    return 0;
            }
	    break;
      case 4:
      
	    if(but4_flag==1)
            {
            	    k_msleep(TIME_SLEEP);  
            	    but4_flag=0;
            	    return 1;
            }
            else 
            {
            	    k_msleep(TIME_SLEEP);  
            	    return 0;
            }
	    break;
      case 5:
      
	    if(but5_flag==1)
            {
            	    k_msleep(TIME_SLEEP);  
            	    but5_flag=0;
            	    return 1;
            }
            else 
            {
            	    k_msleep(TIME_SLEEP);  
            	    return 0;
            }
	    break;
      case 6:
      
	    if(but6_flag==1)
            {
            	    k_msleep(TIME_SLEEP);  
            	    but6_flag=0;
            	    return 1;
            }
            else 
            {
            	    k_msleep(TIME_SLEEP);  
            	    return 0;
            }
	    break;
      case 7:
      
	    if(but7_flag==1)
            {
            	    k_msleep(TIME_SLEEP);  
            	    but7_flag=0;
            	    return 1;
            }
            else 
            {
            	    k_msleep(TIME_SLEEP);  
            	    return 0;
            }
      break;
      case 8:
      
	     if(but8_flag==1)
            {
            	    k_msleep(TIME_SLEEP);  
            	    but8_flag=0;
            	    return 1;
            }
            else 
            {
            	    k_msleep(TIME_SLEEP);  
            	    return 0;
            }
     break;
      default:
	    printk("Wrong argument for read_buttons\n\r");
	    break;
	    }
}

// Reset Buttons Flags:
void reset_flags()
{
      but1_flag=0;										      
      but2_flag=0; 
      but3_flag=0; 
      but4_flag=0; 
      but5_flag=0; 
      but6_flag=0; 
      but7_flag=0; 
      but8_flag=0;    
}

/*
// Several Buttons Callbacks, that are necessary for good interrupt use

    // Set Button 1 callback 
    gpio_init_callback(&but1_cb_data, but1_cbfunction, BIT(BUTTON1));
    gpio_add_callback(gpio0_dev, &but1_cb_data);

    // Set Button 2 callback 
    gpio_init_callback(&but2_cb_data, but2_cbfunction, BIT(BUTTON2));
    gpio_add_callback(gpio0_dev, &but2_cb_data);

    // Set Button 3 callback 
    gpio_init_callback(&but3_cb_data, but3_cbfunction, BIT(BUTTON3));
    gpio_add_callback(gpio0_dev, &but3_cb_data);

    // Set Button 4 callback 
    gpio_init_callback(&but4_cb_data, but4_cbfunction, BIT(BUTTON4));
    gpio_add_callback(gpio0_dev, &but4_cb_data);
 
 */
  
/*
void button1_init(struct device *gpio0_dev)                                                         // Button 1                 
{
  int ret=0;

  ret=gpio_pin_configure(gpio0_dev, BUTTON1, GPIO_INPUT | GPIO_PULL_UP);                            // Button pin configuration as input and internal pull-up resistor
  if (ret < 0)                                                                                      // In case of fail initialization and consequent error message
  {
    printk("Error %d: Failed to configure BUTTON 1 \n\r", ret);
    return;
  }
}


void button2_init(struct device *gpio0_dev)                                                         // Button 2
{
  int ret=0;

  ret=gpio_pin_configure(gpio0_dev, BUTTON2, GPIO_INPUT | GPIO_PULL_UP);                            // Button pin configuration as input and internal pull-up resistor
  if (ret < 0)                                                                                      // In case of fail initialization and consequent error message
  {
    printk("Error %d: Failed to configure BUTTON 2 \n\r", ret);
    return;
  }
}


void button3_init(struct device *gpio0_dev)                                                         // Button 3
{
  int ret=0;

  ret=gpio_pin_configure(gpio0_dev, BUTTON3, GPIO_INPUT | GPIO_PULL_UP);                            // Button pin configuration as input and internal pull-up resistor
  if (ret < 0)                                                                                      // In case of fail initialization and consequent error message
  {
    printk("Error %d: Failed to configure BUTTON 3 \n\r", ret);
    return;
  }
}


void button4_init(struct device *gpio0_dev)                                                         // Button 4
{
  int ret=0;

  ret=gpio_pin_configure(gpio0_dev, BUTTON4, GPIO_INPUT | GPIO_PULL_UP);                            // Button pin configuration as input and internal pull-up resistor
  if (ret < 0)                                                                                      // In case of fail initialization and consequent error message
  {
    printk("Error %d: Failed to configure BUTTON 4 \n\r", ret);
    return;
  }
}
*/

/*
// Read Buttons Functions:
int read_button1()
{     
      if(but1_flag==1)
      {	    
	    k_msleep(TIME_SLEEP);  
	    but1_flag=0;
	    return 1;
      }
      else 
      {
	    k_msleep(TIME_SLEEP);  
	    return 0;
      }
}

int read_button2()
{
      if(but2_flag==1)
      {
	    k_msleep(TIME_SLEEP);  
	    but2_flag=0;
	    return 1;
      }
      else 
      {
	    k_msleep(TIME_SLEEP);  
	    return 0;
      }
}

int read_button3()
{
      if(but3_flag==1)
      {
	    k_msleep(TIME_SLEEP);  
	    but3_flag=0;
	    return 1;
      }
      else 
      {
	    k_msleep(TIME_SLEEP);  
	    return 0;
      }
}

int read_button4()
{
      if(but4_flag==1)
      {
	    k_msleep(TIME_SLEEP);  
	    but4_flag=0;
	    return 1;
      }
      else 
      {
	    k_msleep(TIME_SLEEP);  
	    return 0;
      }
}

int read_button5()
{
      if(but5_flag==1)
      {
	    k_msleep(TIME_SLEEP);  
	    but5_flag=0;
	    return 1;
      }
      else 
      {
	    k_msleep(TIME_SLEEP);  
	    return 0;
      }
}

int read_button6()
{
      if(but6_flag==1)
      {
	    k_msleep(TIME_SLEEP);  
	    but6_flag=0;
	    return 1;
      }
      else 
      {
	    k_msleep(TIME_SLEEP);  
	    return 0;
      }
}

int read_button7()
{
      if(but7_flag==1)
      {
	    k_msleep(TIME_SLEEP);  
	    but7_flag=0;
	    return 1;
      }
      else 
      {
	    k_msleep(TIME_SLEEP);  
	    return 0;
      }
}

int read_button8()
{
      if(but8_flag==1)
      {
	    k_msleep(TIME_SLEEP);  
	    but8_flag=0;
	    return 1;
      }
      else 
      {
	    k_msleep(TIME_SLEEP);  
	    return 0;
      }
}

*/