#include <xinu.h>

#define REG(n) (*((volatile uint32*)(n)))

int32 p8_PortSet[] = {-1, -1, 1, 1, 1, 1, 2, 2,
			2, 2, 1, 1, 0, 0, 1, 1, 
			0, 2, 0, 1, 1, 1, 1, 1, 
			1, 1, 2, 2, 2, 2, 0, 0, 
			0, 2, 0, 2, 2, 2, 2, 2, 
			2, 2, 2, 2, 2, 2};

/* GPIO Port ID set of Beaglebone Black P8  ,
 * 0 as GND , offset X as GPIO ID m this value must combine with GPIO number
 */
uint32 p8_PortIDSet[] = {0,	0,	1<<6,	1<<7,	1<<2,	1<<3,	1<<2,	1<<3,	
			1<<5,	1<<4,	1<<13,	1<<12,	1<<23,	1<<26,	1<<15,	
			1<<14,	1<<27,	1<<1,	1<<22,	1<<31,	1<<30,	1<<5,	
			1<<4,	1<<1,	1<<0,	1<<29,	1<<22,	1<<24,	1<<23,	
			1<<25,	1<<10,	1<<11,	1<<9,	1<<17,	1<<8,	1<<16,	
			1<<14,	1<<15,	1<<12,	1<<13,	1<<10,	1<<11,	1<<8,	
			1<<9,	1<<6,	1<<7};

/* GPIO Port number set of Beaglebone Black P9  ,
 * -1 as GND or VCC , 0 / 1 / 2 for GPIO 0/1/2
 */
int32 p9_PortSet[] = {-1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, 0, 1, 0, 1, 1, 
			1, 0, 0, 0, 0, 0, 0, 1, 0, 
			3, 0, 3, 3, 3, 3, 3, -1, -1, 
			-1, -1, -1, -1, -1, -1, -1, 
			0, 0, -1, -1, -1, -1};

/*  GPIO Port ID set of Beaglebone Black P9  ,
 * 0 as GND , offset X as GPIO ID m this value must combine with GPIO number
 */
uint32 p9_PortIDSet[]={0,	0,	0,	0,	0,	0,	0,	0,	
			0,	0,	1<<30,	1<<28,	1<<31,	1<<18,	1<<16,	1<<19,	
			1<<5,	1<<4,	1<<13,	1<<12,	1<<3,	1<<2,	1<<17,	
			1<<15,	1<<21,	1<<14,	1<<19,	1<<17,	1<<15,	1<<16,	
			1<<14,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1<<20,	
			1<<7,	0,	0,	0,	0};

int32* PortSet_ptr[] = {p8_PortSet, p9_PortSet};
uint32* PortIDSet_ptr[] = {p8_PortIDSet, p9_PortIDSet};


uint32 gpio_addr[]={GPIO0_ADDR, GPIO1_ADDR, GPIO2_ADDR, GPIO3_ADDR};

uint32 pin_setdir(int32 port, uint32 pin, uint32 dir)
{
	int param_error=0;			// parameter error

	if ((port < 8) || (port > 9))		// if input is not port8 and port 9 , because BBB support P8/P9 Connector
		param_error=1;
	if ((pin < 1 ) || (pin > 46))		// if pin over/underflow , range : 1~46
		param_error=1;

	if (param_error)
	{
		return(-1);
	}

	return (GPIO_set_dir(PortSet_ptr[port-8][pin-1], PortIDSet_ptr[port-8][pin-1], dir));
}

void pin_high(uint32 port, uint32 pin)
{
	*((uint32 *)((void *)gpio_addr[PortSet_ptr[port-8][pin-1]]+ GPIO_SETDATAOUT)) = PortIDSet_ptr[port-8][pin-1];
}

void pin_low(uint32 port, uint32 pin)
{
	*((uint32 *)((void *)gpio_addr[PortSet_ptr[port-8][pin-1]]+ GPIO_CLEARDATAOUT)) = PortIDSet_ptr[port-8][pin-1];
}

uint32 is_high(uint32 port, uint32 pin)
{
	return ((*((uint32 *)((void *)gpio_addr[PortSet_ptr[port-8][pin-1]]+ GPIO_DATAIN)) & PortIDSet_ptr[port-8][pin-1])!=0);
}

uint32 is_low(uint32 port, uint32 pin)
{
	return ((*((uint32 *)((void *)gpio_addr[PortSet_ptr[port-8][pin-1]]+ GPIO_DATAIN)) & PortIDSet_ptr[port-8][pin-1])==0);
}

uint32 GPIO_set_dir(int32  gpio, uint32 pinNumber, uint32 dir)
{
        int32 param_error=0;
	volatile uint32* reg;

        if (gpio > 3 || gpio < 0) 	/* GPIO range */
                param_error = 1;

        if (dir > 1)	/* pin direction error */
                param_error = 1;

        if (param_error) {
		printf("GPIO_set_dir: parameter error!\n");
                return -1;
        }

        reg=(void *)gpio_addr[gpio] + GPIO_OE;

	if (dir == DIR_OUT) {
		*reg &= ~(pinNumber);
	}
	else if (dir == DIR_IN) {
		*reg |= pinNumber;
	}

        return 0;
}


void GPIO_high(uint32 gpio ,uint32 pinNumber)
{
	*((uint32 *)((void *)gpio_addr[gpio]+GPIO_SETDATAOUT)) = pinNumber;
}

void GPIO_low(uint32 gpio ,uint32 pinNumber)
{
	*((uint32 *)((void *)gpio_addr[gpio]+GPIO_CLEARDATAOUT)) = pinNumber;
}

uint32 GPIO_read(uint32 gpio, uint32 pinNumber)
{
	 return *((uint32 *)((void *)gpio_addr[gpio]+ GPIO_DATAIN)) & pinNumber;
}


/**
 * Initializee the Analog-Digital Converter
 */
void adc_init() {

	// enable the CM_WKUP_ADC_TSC_CLKCTRL with CM_WKUP_MODUELEMODE_ENABLE
	REG(CM_WKUP_ADC_TSC_CLKCTRL) |= CM_WKUP_MODULEMODE_ENABLE;

	// wait for the enable to complete
	while(!(REG(CM_WKUP_ADC_TSC_CLKCTRL) & CM_WKUP_MODULEMODE_ENABLE)) {
		// waiting for adc clock module to initialize
		//printf("Waiting for CM_WKUP_ADC_TSC_CLKCTRL to enable with MODULEMODE_ENABLE\n");
	}
	// software reset, set bit 1 of sysconfig high?
	// make sure STEPCONFIG write protect is off
	REG(ADC_CTRL) |= ADC_STEPCONFIG_WRITE_PROTECT_OFF;

	// set up each ADCSTEPCONFIG for each ain pin
	REG(ADCSTEPCONFIG1) = 0x00<<19 | ADC_AVG16;
	REG(ADCSTEPDELAY1)  = (0x0F)<<24;
	REG(ADCSTEPCONFIG2) = 0x01<<19 | ADC_AVG16;
	REG(ADCSTEPDELAY2)  = (0x0F)<<24;
	REG(ADCSTEPCONFIG3) = 0x02<<19 | ADC_AVG16;
	REG(ADCSTEPDELAY3)  = (0x0F)<<24;
	REG(ADCSTEPCONFIG4) = 0x03<<19 | ADC_AVG16;
	REG(ADCSTEPDELAY4)  = (0x0F)<<24;
	REG(ADCSTEPCONFIG5) = 0x04<<19 | ADC_AVG16;
	REG(ADCSTEPDELAY5)  = (0x0F)<<24;
	REG(ADCSTEPCONFIG6) = 0x05<<19 | ADC_AVG16;
	REG(ADCSTEPDELAY6)  = (0x0F)<<24;
	REG(ADCSTEPCONFIG7) = 0x06<<19 | ADC_AVG16;
	REG(ADCSTEPDELAY7)  = (0x0F)<<24;
	REG(ADCSTEPCONFIG8) = 0x07<<19 | ADC_AVG16;
	REG(ADCSTEPDELAY8)  = (0x0F)<<24;

	// enable the ADC
	REG(ADC_CTRL) |= 0x01;
}

/**
 * Read in from an analog pin
 *
 * @param p pin to read value from
 * @returns the analog value of pin p
 */
uint32 analogRead(uint32 ain) {
	
	// the clock module is not enabled
	if(REG(CM_WKUP_ADC_TSC_CLKCTRL) & CM_WKUP_IDLEST_DISABLED)
		adc_init();
	
	// enable the step sequencer for this pin
	REG(ADC_STEPENABLE) |= (0x01<<(ain+1));

	// return the the FIFO0 data register
	return REG(ADC_FIFO0DATA) & ADC_FIFO_MASK;
}


