
#include "base.h"
#include "gpio.h"
#include "buttons.h"
#include "state.h"

#define INITIAL_STATE 2

void main()
{
	printk("\n\n\nStart\n");
//	const struct device *gpio0_dev;
//      gpio0_dev=gpio0_init();
//      buttons_init_(gpio0_dev,255,'h');
	buttons_init_(gpio0_init(),255,'h');
	int state=INITIAL_STATE;
	while(state!=NO_STATE)
	{
		state=state_machine(state);
	}
	state=state_machine(state);
	printk("PROGRAM ENDED\n\n\n");
}
