/*  main.c  - main */

#include <xinu.h>


process	main(void)
{
	recvclr();

	uint32 analogVoltage = 0;
	float temperature;
	while(1)
	{
		analogVoltage = analogRead(0);
		/*temperature = (((analogVoltage * 1.8) / 4095.0) - 0.5) * 100;*/
		printf("\n%d", analogVoltage);
		delay(3000000);
	}	

	return OK;
}
