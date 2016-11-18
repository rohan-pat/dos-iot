/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
	recvclr();
	int32 i = 100;
	
	
	GPIO_set_dir(1, GPIO_PIN_13, DIR_OUT);
	GPIO_set_dir(1, GPIO_PIN_12, DIR_OUT);
	
	GPIO_high(1, GPIO_PIN_13);
	GPIO_low(1, GPIO_PIN_12);

	while(1)
	{
		delay(5000000);		
		GPIO_low(1, GPIO_PIN_13);
		printf("\nOff");
		delay(5000000);	
		GPIO_high(1, GPIO_PIN_13);
		printf("\nOn");
	}

			
	
	
	/*GPIO_set_dir(1, GPIO_PIN_22, DIR_OUT);
	GPIO_set_dir(1, GPIO_PIN_23, DIR_OUT);
	GPIO_set_dir(1, GPIO_PIN_24, DIR_OUT);	


	while(--i > 0)
	{		
		kprintf("\n Start");
		GPIO_high(1, GPIO_PIN_22);
		printf("\n 22");
		delay(5000000);
		printf("\n 23");
		GPIO_low(1, GPIO_PIN_22);
		delay(5000000);

		GPIO_high(1, GPIO_PIN_23);
		printf("\n 23");
		delay(5000000);
		GPIO_low(1, GPIO_PIN_23);
		printf("\n 23");
		delay(5000000);

		GPIO_high(1, GPIO_PIN_24);
		printf("\n 24");
		delay(5000000);
		GPIO_low(1, GPIO_PIN_24);
		printf("\n 24");
		delay(5000000);
	}*/

	return OK;
}
