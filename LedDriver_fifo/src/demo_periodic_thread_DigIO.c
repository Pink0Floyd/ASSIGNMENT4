/*
 * Paulo Pedreiras, 2022/02
 * Zephyr: Simple thread and digital IO example
 * 
 * Reads a button and sets a led according to the button state
 *
 * Base documentation:
 *  Zephyr kernel: 
 *      https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/reference/kernel/index.html
 *      
 *  DeviceTree 
 *      Board DTS can be found in BUILD_DIR/zephyr/zephyr.dts
 *      https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/guides/dts/api-usage.html#dt-from-c  
 *
 *  HW info
 *      https://infocenter.nordicsemi.com/topic/struct_nrf52/struct/nrf52840.html
 *      Section: nRF52840 Product Specification -> Peripherals -> GPIO / GPIOTE
 * 
 *      Board specific HW info can be found in the nRF52840_DK_User_Guide_20201203. I/O pins available at pg 27
 * 
 * 
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <sys/printk.h>
#include <sys/__assert.h>
#include <string.h>
#include <timing/timing.h>
#include <stdio.h>


/* Size of stack area used by each thread (can be thread specific, if necessary)*/
#define STACK_SIZE 1024

/* Thread scheduling priority */
#define thread_A_prio 1

/* Therad periodicity (in ms)*/
#define thread_A_period 20


/* Create thread stack space */
K_THREAD_STACK_DEFINE(thread_A_stack, STACK_SIZE);
  
/* Create variables for thread data */
struct k_thread thread_A_data;

/* Create task IDs */
k_tid_t thread_A_tid;

/* Thread code prototypes */
void thread_A_code(void *argA, void *argB, void *argC);

/* Refer to dts file */
#define GPIO0_NID DT_NODELABEL(gpio0) 
#define BOARDLED1 0xd /* Pin at which LED is connected. Addressing is direct (i.e., pin number) */
#define BOARDBUT1 0xb /* Pin at which BUT1 is connected. Addressing is direct (i.e., pin number) */


/* Main function */
void main(void) {

    thread_A_tid = k_thread_create(&thread_A_data, thread_A_stack,
        K_THREAD_STACK_SIZEOF(thread_A_stack), thread_A_code,
        NULL, NULL, NULL, thread_A_prio, 0, K_NO_WAIT);


    return;

} 

/* Thread code implementation */
void thread_A_code(void *argA , void *argB, void *argC)
{
    /* Local vars */
    int64_t fin_time=0, release_time=0;     /* Timing variables to control task periodicity */
    const struct device *gpio0_dev;          /* Pointer to GPIO device structure */
    int ret=0;                              /* Generic return value variable */
    
    /* Task init code */
    printk("Thread A init (periodic)\n");

    /* Bind to GPIO 0 */
    gpio0_dev = device_get_binding(DT_LABEL(GPIO0_NID));
    if (gpio0_dev == NULL) {
        printk("Failed to bind to GPIO0\n\r");        
	return;
    }
    else {
        printk("Bind to GPIO0 successfull \n\r");        
    }
    
    /* Configure PIN */
    ret = gpio_pin_configure(gpio0_dev, BOARDLED1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Failed to configure LED 1 \n\r");
	return;
    }
    ret = gpio_pin_configure(gpio0_dev, BOARDBUT1, GPIO_INPUT | GPIO_PULL_UP);
    if (ret < 0) {
        printk("Failed to configure BUT 1 \n\r");
	return;
    }
       
    /* Compute next release instant */
    release_time = k_uptime_get() + thread_A_period;

    /* Thread loop */
    while(1) {        
        
        printk("Thread A activated\n\r");  
        
        if(gpio_pin_get(gpio0_dev,BOARDBUT1))
            gpio_pin_set(gpio0_dev, BOARDLED1, 1);
        else
            gpio_pin_set(gpio0_dev, BOARDLED1, 0);
       
        /* Wait for next release instant */ 
        fin_time = k_uptime_get();
        if( fin_time < release_time) {
            k_msleep(release_time - fin_time);
            release_time += thread_A_period;

        }
    }

    /* Stop timing functions */
    timing_stop();
}
