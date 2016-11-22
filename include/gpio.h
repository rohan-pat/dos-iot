/* gpio.h */


#define DIR_IN 0
#define DIR_OUT 1

#define GPIO0 		0		/* GPIO ID */
#define GPIO1 		1
#define GPIO2 		2
#define GPIO3		3
#define GPIO0_ADDR	0x44e07000
#define GPIO1_ADDR 	0x4804c000
#define GPIO2_ADDR 	0x481AC000
#define GPIO3_ADDR 	0x481AE000


/* register offset */
#define GPIO_OE			0x134
#define GPIO_DATAIN 		0x138
#define GPIO_DATAOUT 		0x13C
#define GPIO_CLEARDATAOUT		0x190
#define GPIO_SETDATAOUT		0x194

#define GPIO_PIN_0	(1<< 0)
#define GPIO_PIN_1	(1<< 1)
#define GPIO_PIN_2	(1<< 2)
#define GPIO_PIN_3	(1<< 3)
#define GPIO_PIN_4	(1<< 4)
#define GPIO_PIN_5	(1<< 5)
#define GPIO_PIN_6	(1<< 6)
#define GPIO_PIN_7	(1<< 7)
#define GPIO_PIN_8	(1<< 8)
#define GPIO_PIN_9	(1<< 9)
#define GPIO_PIN_10	(1<< 10)
#define GPIO_PIN_11	(1<< 11)
#define GPIO_PIN_12	(1<< 12)
#define GPIO_PIN_13	(1<< 13)
#define GPIO_PIN_14	(1<< 14)
#define GPIO_PIN_15	(1<< 15)
#define GPIO_PIN_16	(1<< 16)
#define GPIO_PIN_17	(1<< 17)
#define GPIO_PIN_18	(1<< 18)
#define GPIO_PIN_19	(1<< 19)
#define GPIO_PIN_20	(1<< 20)
#define GPIO_PIN_21	(1<< 21)
#define GPIO_PIN_22	(1<< 22)
#define GPIO_PIN_23	(1<< 23)
#define GPIO_PIN_24	(1<< 24)
#define GPIO_PIN_25	(1<< 25)
#define GPIO_PIN_26	(1<< 26)
#define GPIO_PIN_27	(1<< 27)
#define GPIO_PIN_28	(1<< 28)
#define GPIO_PIN_29	(1<< 29)
#define GPIO_PIN_30	(1<< 30)
#define GPIO_PIN_31	(1<< 31)


/* Clock Module Memory Registers */
#define CM_WKUP (0x44E00400)
#define CM_WKUP_ADC_TSC_CLKCTRL (CM_WKUP+0xBC)
#define CM_WKUP_MODULEMODE_ENABLE (0x02)
#define CM_WKUP_IDLEST_DISABLED (0x03<<16)

#define CM_PER (0x44E00000)
#define CM_PER_EPWMSS1_CLKCTRL (CM_PER+0xCC)
#define CM_PER_EPWMSS0_CLKCTRL (CM_PER+0xD4)
#define CM_PER_EPWMSS2_CLKCTRL (CM_PER+0xD8)


/* Analog Digital Converter Memory Registers */
#define ADC_TSC (0x44E0D000)

#define ADC_CTRL (ADC_TSC+0x40)
#define ADC_STEPCONFIG_WRITE_PROTECT_OFF (0x01<<2)
#define ADC_STEPENABLE (ADC_TSC+0x54)

#define ADCSTEPCONFIG1 (ADC_TSC+0x64)
#define ADCSTEPDELAY1  (ADC_TSC+0x68)
#define ADCSTEPCONFIG2 (ADC_TSC+0x6C)
#define ADCSTEPDELAY2  (ADC_TSC+0x70)
#define ADCSTEPCONFIG3 (ADC_TSC+0x74)
#define ADCSTEPDELAY3  (ADC_TSC+0x78)
#define ADCSTEPCONFIG4 (ADC_TSC+0x7C)
#define ADCSTEPDELAY4  (ADC_TSC+0x80)
#define ADCSTEPCONFIG5 (ADC_TSC+0x84)
#define ADCSTEPDELAY5  (ADC_TSC+0x88)
#define ADCSTEPCONFIG6 (ADC_TSC+0x8C)
#define ADCSTEPDELAY6  (ADC_TSC+0x90)
#define ADCSTEPCONFIG7 (ADC_TSC+0x94)
#define ADCSTEPDELAY7  (ADC_TSC+0x98)
#define ADCSTEPCONFIG8 (ADC_TSC+0x9C)
#define ADCSTEPDELAY8  (ADC_TSC+0xA0)

#define ADC_AVG0  (0x000)
#define ADC_AVG2  (0x001)
#define ADC_AVG4  (0x010)
#define ADC_AVG8  (0x011)
#define ADC_AVG16 (0x100) 

#define ADC_FIFO0DATA (ADC_TSC+0x100)
#define ADC_FIFO_MASK (0xFFF)


