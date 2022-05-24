#include "state.h"

static int up=0;
static int down=0;
static int sel=0;
static int ret=0;
static int e10=0;
static int e20=0;
static int e50=0;
static int e100=0;

static int error_code=0;

static int money=0;
static int product=0;
static int cost=0;
const static int price[3]={50,100,150};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions

void read_events()
{
	up=read_buttons(1);
	down=read_buttons(3);
	sel=read_buttons(2);
	ret=read_buttons(4);
	e10=read_buttons(5);
	e20=read_buttons(6);
	e50=read_buttons(7);
	e100=read_buttons(8);
}

void display_credit_state_action(int money_amount)
{
	printk("CREDIT: %i cents creditted\n",money_amount);
}

int display_credit_state_exit()
{
	int next_state=DISPLAY_CREDIT;
	read_events();
	if((up+down)!=0)
	{
		next_state=CHANGE_PRODUCT;
	}
	else if(sel!=0)
	{
		next_state=DISPLAY_PRODUCT;
	}
	else if(ret!=0)
	{
		if(money==0)
		{
			next_state=ERROR;
			error_code=ERROR_NO_RET;
		}
		else
		{
			next_state=RETURN_CREDIT;
		}
	}
	else if((e10+e20+e50+e100)!=0)
	{
		next_state=CHANGE_CREDIT;
	}
	return next_state;
}

int display_credit_state()
{
	display_credit_state_action(money);
	int next_state=DISPLAY_CREDIT;
	while(next_state==DISPLAY_CREDIT)
	{
		next_state=display_credit_state_exit();
	}
	return next_state;
}

void display_product_state_action(int selected_product)
{
	switch(selected_product)
	{
		case COFFEE:
			printk("BROWSE: Selected a Coffee with a cost of %i cents\n",cost);
			break;
		case TUNA:
			printk("BROWSE: Selected a Tuna Sandwich with a cost of %i cents\n",cost);
			break;
		case BEER:
			printk("BROWSE: Selected a Beer with a cost of %i cents\n",cost);
			break;
		default:
			printk("BROWSE: Selected an Unknown Product\n");
			break;
	}
}

int display_product_state_exit()
{
	int next_state=DISPLAY_PRODUCT;
	read_events();
	if(up+down!=0)
	{
		next_state=CHANGE_PRODUCT;
	}
	else if(sel!=0)
	{
		if(money>=cost)
		{
			next_state=RETURN_PRODUCT;
		}
		else
		{
			next_state=ERROR;
			error_code=ERROR_NO_MONEY;
		}
	}
	else if(ret!=0)
	{
		if(money==0)
		{
			next_state=ERROR;
			error_code=ERROR_NO_RET;
		}
		else
		{
			next_state=RETURN_CREDIT;
		}
	}
	else if(e10+e20+e50+e100!=0)
	{
		next_state=CHANGE_CREDIT;
	}
	return next_state;
}

int display_product_state()
{
	int next_state=DISPLAY_PRODUCT;
	display_product_state_action(product);
	while(next_state==DISPLAY_PRODUCT)
	{
		next_state=display_product_state_exit();
	}
	return next_state;
}

int error_substate()
{
	switch(error_code)
	{
		case ERROR_NO_RET:
			printk("ERROR: There is no credit to be returned\n");
			error_code=0;
			break;
		case ERROR_NO_MONEY:
			printk("ERROR: There isn't enouph credit to make the purchase\n");
			error_code=0;
			break;
		default:
			printk("ERROR: Unknown Error\n");
			break;
	}

	return DISPLAY_CREDIT;
}

int change_credit_substate()
{
	if(e10!=0)
	{
		printk("CHANGE_CREDIT: Increased credit by 10 cents\n");
		money+=10;
	}
	else if(e20!=0)
	{
		printk("CHANGE_CREDIT: Increased credit by 20 cents\n");
		money+=20;
	}
	else if(e50!=0)
	{
		printk("CHANGE_CREDIT: Increased credit by 50 cents\n");
		money+=50;
	}
	else if(e100!=0)
	{
		printk("CHANGE_CREDIT: Increased credit by 1 euro\n");
		money+=100;
	}

	return DISPLAY_CREDIT;
}

int return_credit_substate()
{
	printk("RETURN_CREDIT: Returned %i cents to the user\n",money);
	money=0;

	return DISPLAY_CREDIT;
}

int change_product_substate()
{
	if(up!=0)
	{
		printk("CHANGE_PRODUCT: Next prod\n");
		if(product==2)
		{
			product=0;
		}
		else
		{
			product++;
		}
		up=0;
	}
	else if(down!=0)
	{
		printk("CHANGE_PRODUCT: Previous prod\n");
		if(product==0)
		{
			product=2;
		}
		else
		{
			product--;
		}
		down=0;
	}
	cost=price[product];

	return DISPLAY_PRODUCT;
}

int return_product_substate()
{
	switch(product%N_PROD)
	{
		case COFFEE:
			printk("RETURN_PRODUCT: Dispensed a Coffee\n");
			money-=50;
			break;
		case TUNA:
			printk("RETURN_PRODUCT: Dispensed a Tuna Sandwich\n");
			money-=100;
			break;
		case BEER:
			printk("RETURN_PRODUCT: Dispensed a Beer\n");
			money-=150;
			break;
	}

	return DISPLAY_CREDIT;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Member Function

int state_machine(int state)
{
	int next_state=NO_STATE;
	switch(state)
	{
		case DISPLAY_CREDIT:
			next_state=display_credit_state();
			break;
		case DISPLAY_PRODUCT:
			next_state=display_product_state();
			break;
		case ERROR:
			next_state=error_substate();
			break;
		case CHANGE_CREDIT:
			next_state=change_credit_substate();
			break;
		case RETURN_CREDIT:
			next_state=return_credit_substate();
			break;
		case CHANGE_PRODUCT:
			next_state=change_product_substate();
			break;
		case RETURN_PRODUCT:
			next_state=return_product_substate();
			break;	
		default:
			printk("Unknown State\n");
			break;
	}
}