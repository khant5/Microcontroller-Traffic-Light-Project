#include "TM4C123GH6PM.h"
int ns=0;
#define LCD_PORT GPIOB
#define RS 1 /* BIT0 mask */
#define RW 2 /* BIT1 mask */
#define EN 4 /* BIT2 mask */
void delayMs(int n);
void delayUs(int n);
void LCD_nibble_write(unsigned char data, unsigned char control);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
/* PORTF data register */
/* PORTF data register */
#define PORTADAT (*((volatile unsigned int*)0x400043FC))
/* PORTF data direction register */
#define PORTADIR (*((volatile unsigned int*)0x40004400))
/* PORTF digital enable register */
#define PORTADEN (*((volatile unsigned int*)0x4000451C))
/* run mode clock gating register */
#define RCGCGPIO2 (*((volatile unsigned int*)0x400FE608))
/* coprocessor access control register */
#define PORTBDAT (*((volatile unsigned int*)0x400053FC))
/* PORTF data direction register */
#define PORTBDIR (*((volatile unsigned int*)0x40005400))
/* PORTF digital enable register */
#define PORTBDEN (*((volatile unsigned int*)0x4000551C))
/* run mode clock gating register */
16
#define PORTEDAT (*((volatile unsigned int*)0x400243FC))
/* PORTF data direction register */
#define PORTEDIR (*((volatile unsigned int*)0x40024400))
/* PORTF digital enable register */
#define PORTEDEN (*((volatile unsigned int*)0x4002451C))
/* run mode clock gating register */
#define PORTDDAT (*((volatile unsigned int*)0x400073FC))
/* PORTF data direction register */
#define PORTDDIR (*((volatile unsigned int*)0x40007400))
/* PORTF digital enable register */
#define PORTDDEN (*((volatile unsigned int*)0x4000751C))
#define PORTCDAT (*((volatile unsigned int*)0x400063FC))
/* PORTF data direction register */
#define PORTCDIR (*((volatile unsigned int*)0x40006400))
/* PORTF digital enable register */
#define PORTCDEN (*((volatile unsigned int*)0x4000651C))
#define PORTCPUR (*((volatile unsigned int*)0x40006510))
#define SCB_CPAC (*((volatile unsigned int*)0xE000ED88))
#define PORTDPUR (*((volatile unsigned int*)0x40007510))
#define PORTEPUR (*((volatile unsigned int*)0x40024510))
#define PORTBPUR (*((volatile unsigned int*)0x40005510))
//#define PORTFPUR (*((volatile unsigned int*)0x40025510))

//void delayMs(int n); /* function prototype for delay */
int value0=0;
int value1=0;
int value2=0;
int value3=0;
int value4=0;
int multi0=0;
int multi1=0;
int multi2=0;
int multi3=0;
int multi4=0;
int sulti0=0;
int sulti1=0;
int sulti2=0;
int sulti3=0;
int sulti4=0;
int state=0;

void s0(void) // NSG & EWR 
{
	state=0;
	ns=1; //next state is 1
	PORTDDAT=0X01; //EWR: PDO ON
	PORTEDAT=0X04; //NSG: PE2 ON 
	delayMs(5000); // Delay for 5 seconds
}
void s1 ()// EWR & NSY
{
	state=1;
	PORTDDAT=0X01;// EWR: PD0 ON
	PORTEDAT=0X02;// NSY: PE1 ON
	delayMs(2000);// Delay 2 seconds 
}
void s2 ()//NSR & EWG
{
	state=2;
	//ns=3;
	PORTDDAT=0X04;//EWG: PD2 ON
	PORTEDAT=0X01;//NSR: PE0 ON    
	delayMs(5000);//delay 5 seconds 
}
void s3 ()//NSR & EWY
{
	state=3;
	PORTDDAT=0X02;//EWY: PD1 ON 
	PORTEDAT=0X01;//NSR: PE0 ON
	delayMs(2000);
}
void s4 () //Pedestrian Crossing
{	       //EWR & NSR & takes up 16 seconds
	state=4;
	//9
	//PORTCDAT = 0x11;
	PORTADAT = 0xEC;
	//PORTE1DAT= PORTEDAT;
	PORTEDAT =0x11;

	PORTDDAT =0x01;
	 delayMs(1000);
	//8 /* write PORTF to turn off all LEDs */
	 PORTADAT = 0xFF;
	 PORTEDAT = 0x11;
	 delayMs(1000);
	//7 /* write PORTF to turn off all LEDs */
	 PORTADAT = 0xC0;
	 PORTEDAT = PORTEDAT & 0xFF;
	 delayMs(1000);
	//6 /* write PORTF to turn on all LEDs */
	 PORTADAT = 0x7C;
	 PORTEDAT =0x11;
	 delayMs(1000);
	 //5 /* write PORTF to turn off all LEDs */
	 PORTADAT = 0x6C;
	 PORTEDAT = 0x11;
	 delayMs(1000);
	//4 /* write PORTF to turn on all LEDs */
	 PORTADAT = 0xCC;
	 PORTEDAT =0x01;
	 delayMs(1000);
	 //3 /* write PORTF to turn off all LEDs */
	 PORTADAT = 0xE4;
	 PORTEDAT = 0x11;
	 delayMs(1000);
	//2 /* write PORTF to turn on all LEDs */
	 PORTADAT = 0xB4;
	 PORTEDAT = 0x11;
	 delayMs(1000);
	//1 /* write PORTF to turn off all LEDs */
	
	 PORTADAT = 0xC0;
	 PORTEDAT = 0x01;
	 delayMs(1000);
	 //0 /* write PORTF to turn on all LEDs */
	 PORTADAT = 0xF8;
	 PORTEDAT = 0x11;
	 delayMs(1000);
	 PORTADAT = 0x0 ;
	 PORTEDAT = 0x01;
	 delayMs(1000);
	 PORTADAT = 0xF8;
	 PORTEDAT = 0x11;
	 delayMs(1000);
	 PORTADAT = 0x0 ;
	 PORTEDAT = 0x01;
	 delayMs(1000);
	 PORTADAT = 0xF8;
	 PORTEDAT = 0x11;
	 delayMs(1000);
	 PORTADAT = 0x0 ;
	 PORTEDAT =0x01;
	 delayMs(1000);
	 PORTADAT = 0xF8;
	 PORTEDAT = 0x11;
	
	 delayMs(1000);
	 PORTADAT = 0x0 ;
	 PORTEDAT =0x01;
}
void s5 () //EWR & NSR  and takes up 16 seconds
{
state=5;
/* write PORTF to turn on all LEDs */
//9
//PORTCDAT = 0x11;
PORTADAT = 0xEC;
//PORTE1DAT= PORTEDAT;
PORTEDAT =0x11;
PORTDDAT =0x01;
 delayMs(1000);
//8 /* write PORTF to turn off all LEDs */
PORTADAT = 0xFF;
PORTEDAT = 0x11;
 delayMs(1000);
//7 /* write PORTF to turn off all LEDs */
 PORTADAT = 0xC0;
PORTEDAT = PORTEDAT & 0xFF;
 delayMs(1000);
//6 /* write PORTF to turn on all LEDs */
 PORTADAT = 0x7C;
PORTEDAT =0x11;
 delayMs(1000);
 //5 /* write PORTF to turn off all LEDs */
 PORTADAT = 0x6C;
PORTEDAT = 0x11;
 delayMs(1000);
//4 /* write PORTF to turn on all LEDs */
PORTADAT = 0xCC;
PORTEDAT =0x01;
 delayMs(1000);
 //3 /* write PORTF to turn off all LEDs */
 PORTADAT = 0xE4;
PORTEDAT = 0x11;
 delayMs(1000);
//2 /* write PORTF to turn on all LEDs */
 PORTADAT = 0xB4;
PORTEDAT = 0x11;
 delayMs(1000);
//1 /* write PORTF to turn off all LEDs */
 PORTADAT = 0xC0;
PORTEDAT = 0x01;
 delayMs(1000);
 //0 /* write PORTF to turn on all LEDs */
PORTADAT = 0xF8;
PORTEDAT = 0x11;
 delayMs(1000);
 PORTADAT = 0x0 ;
PORTEDAT = 0x01;
 delayMs(1000);
 PORTADAT = 0xF8;
PORTEDAT = 0x11;
 delayMs(1000);
 PORTADAT = 0x0 ;
PORTEDAT = 0x01;
 delayMs(1000);
PORTADAT = 0xF8;
PORTEDAT = 0x11;
 delayMs(1000);
 PORTADAT = 0x0 ;
PORTEDAT =0x01;
 delayMs(1000);
PORTADAT = 0xF8;
PORTEDAT = 0x11;
 delayMs(1000);
PORTADAT = 0x0 ;
PORTEDAT =0x01;
}
void values()
{
value0 = PORTCDAT;
value0=~value0;
value0 = value0 & 0x0;
 value1 = PORTCDAT;
value1=~value1;
value1 = value1 & 0x10;
value2 = PORTCDAT;
value2=~value2;
value2 = value2 & 0x20;
value3 = PORTCDAT;
value3=~value3;
value3 = value3 & 0x40;
value4 = PORTCDAT;
value4=~value4;
value4 = value4 & 0x80;
}
int count=0;
int main(void)
{
 /* enable clock to GPIOF at clock gating register */
 RCGCGPIO2 |= 0xFF;
//GPIO_PORTF_LOCK_R |=
 /* set PORTF pin3-1 as output pins */
 PORTEDIR = 0x17 ;
PORTDDIR = 0x07 ;
PORTADIR = 0xFF ;
 /* set PORTF pin3-1 as digital pins */
 PORTCPUR = 0xFF;
PORTEPUR = 0x08;
PORTBPUR = 0x08;
PORTDPUR = 0x48;
/* enable pull up for PF4 */
 PORTEDEN = 0xFF ;
 PORTADEN = 0xFF ;
 PORTCDEN = 0xFF ;
PORTBDEN = 0xFF;
 PORTDDEN = 0xFF;

 sulti0 = PORTEDAT;
sulti0=~sulti0;
sulti0 = sulti0 & 0x0;
 sulti1 = PORTEDAT;
sulti1=~sulti1;
sulti1 = sulti1 & 0x08;
sulti2 = PORTBDAT;
sulti2=~sulti2;
sulti2 = sulti2 & 0x08;
sulti3 = PORTDDAT;
sulti3=~sulti3;
sulti3 = sulti3 & 0x08;
sulti4 = PORTDDAT;
sulti4=~sulti4;
sulti4 = sulti4 & 0x40;
		if(sulti1==0x08)
		{
			LCD_init();
			 LCD_command(1); /* clear display */
			 LCD_command(0x80); /* LCD cursor location */
			 // delayMs(500);
			 LCD_data('R');
			 LCD_data('U');
			 LCD_data('R');
			 LCD_data('A');
			 LCD_data('L');
			 LCD_data('&');
			 LCD_data('C');
			 LCD_data('R');
			 LCD_data('O');
			 LCD_data('S');
			 LCD_data('S');
			 LCD_data('W');
			 LCD_data('A');
			 LCD_data('L');
			 LCD_data('K');
		}
		else if(sulti2==0x08)
		{
			LCD_init();
			 LCD_command(1); /* clear display */
			 LCD_command(0x80); /* LCD cursor location */
			 // delayMs(500);
			 LCD_data('R');
			 LCD_data('U');
			 LCD_data('R');
			 LCD_data('A');
			 LCD_data('L');
			 LCD_data(' ');
			 LCD_data('O');
			 LCD_data('N');
			 LCD_data('L');
			 LCD_data('Y');
		}
		else if(sulti3==0x08)
		{
			LCD_init();
			 LCD_command(1); /* clear display */
			 LCD_command(0x80); /* LCD cursor location */
			 // delayMs(500);
			 LCD_data('U');
			 LCD_data('R');
			 LCD_data('B');
			 LCD_data('A');
			 LCD_data('N');
			 LCD_data('&');
			 LCD_data('C');
			 LCD_data('R');
			 LCD_data('O');
			 LCD_data('S');
			 LCD_data('S');
			 LCD_data('W');
			 LCD_data('A');
			 LCD_data('L');
			 LCD_data('K');
		}
		else if(sulti4==0x40)
		{
			 LCD_init();
			 LCD_command(1); /* clear display */
			 LCD_command(0x80); /* LCD cursor location */
			 // delayMs(500);
			 LCD_data('U');
			 LCD_data('R');
			 LCD_data('B');
			 LCD_data('A');
			 LCD_data('N');
			 LCD_data(' ');
			 LCD_data('O');
			 LCD_data('N');
			 LCD_data('L');
			 LCD_data('Y');
		}
		s0();
		 while(1)
		 {
				int loop=0;
				int press=0;
				value0 = PORTCDAT;
				
				value0=~value0;
				value0 = value0 & 0x0;
				 value1 = PORTCDAT;
				value1=~value1;
				value1 = value1 & 0x10;
				value2 = PORTCDAT;
				value2=~value2;
				value2 = value2 & 0x20;
				value3 = PORTCDAT;
				value3=~value3;
				value3 = value3 & 0x40;
				value4 = PORTCDAT;
				value4=~value4;
				value4 = value4 & 0x80;
				multi0= PORTCDAT;
				multi0=~multi0;
				multi0 = multi0 & 0x0;
				 multi1 = PORTEDAT;
				multi1=~multi1;
				multi1 = multi1 & 0x08;
				multi2 = PORTBDAT;
				multi2=~multi2;
				multi2 = multi2 & 0x08;
				multi3 = PORTDDAT;
				multi3=~multi3;
				multi3 = multi3 & 0x08;
				multi4 = PORTDDAT;
				multi4=~multi4;
				multi4 = multi4 & 0x40;
			
			if(multi1==0x08)
			{
				 if((state==0) & (value3==0x40 ) & (ns==1) )
				{
					s1();
					s4();
					s2();
					loop=1;
				}
				 else if ((state==0) & ((value2 == 0x20) ) )
				{
					s1();
					s2();
				}
				while(value1==10)
				{
					ns=3;
					loop=2;
				}
				
				if((value1==0x10) && (state==2) && (value2!=0x20))
				{
					s3();
					s0();
					continue;
				}
				else if(value3==0x40 & state==2 & loop!=1 )
				{
					ns=3;
					s3();
					s5();
					s0();
					continue;
				}
			}
			else if(multi2==0x08)
			{
				 if ((state==0) & ((value2 == 0x20) ) )
				{
					s1();
					s2();
				}
				while(value1==10)
				{
					
					//s2();
					ns=3;
					loop=2;
				}
				if((value1==0x10) && (state==2) && (value2!=0x20))
				{
					s3();
					s0();
					continue;
				}
			}
			else if(multi3==0x08)
			{
				 if((state==0) & (value3==0x40 ) & (ns==1) )
				{
					s1();
					s4();
					s2();
					loop=1;
				}
				
				 else
				{
					s1();
					s2();
				}
				while(value1==10)
				{
					ns=3;
					loop=2;
				}
				if(value3==0x40 & state==2 & loop!=1 )
				{
					ns=3;
					s3();
					s5();
					s0();
					continue;
				}
				else
				{
					s3();
					s0();
					continue;
				}
			}
			else if(multi4==0x40)
			{
				s1();
				s2();
				s3();
				s0();
			
			}
		 }
}
void LCD_init(void)
{
 SYSCTL->RCGCGPIO |= 0x02; /* enable clock to GPIOB */
 LCD_PORT->DIR = 0xFF; /* set all PORTB pins as output */
 LCD_PORT->DEN = 0xFF; /* set all PORTB pins as digital pins */
 delayMs(20); /* initialization sequence */
 LCD_nibble_write(0x30, 0);
 delayMs(5);
 LCD_nibble_write(0x30, 0);
 delayUs(100);
 LCD_nibble_write(0x30, 0);
 delayUs(40);
 LCD_nibble_write(0x20, 0); /* use 4-bit data mode */
 delayUs(40);
LCD_command(0x28); /* set 4-bit data, 2-line, 5x7 font */
 LCD_command(0x06); /* move cursor right */
 LCD_command(0x01); /* clear screen, move cursor to home */
 LCD_command(0x0F); /* turn on display, cursor blinking */
}
void LCD_nibble_write(unsigned char data, unsigned char control)
{
 data &= 0xF0; /* clear lower nibble for control */
 control &= 0x0F; /* clear upper nibble for data */
 LCD_PORT->DATA = data | control; /* RS = 0, R/W = 0 */
 LCD_PORT->DATA = data | control | EN; /* pulse E */
 delayUs(0);
 LCD_PORT->DATA = data;
 LCD_PORT->DATA = 0;
}

void LCD_command(unsigned char command)
{
 LCD_nibble_write(command & 0xF0, 0); /* upper nibble first */
 LCD_nibble_write(command << 4, 0); /* then lower nibble */
 if (command < 4)
 delayMs(2); /* commands 1 and 2 need up to 1.64ms */
 else
 delayUs(40); /* all others 40 us */
}
void LCD_data(unsigned char data)
{
 LCD_nibble_write(data & 0xF0, RS); /* upper nibble first */
 LCD_nibble_write(data << 4, RS); /* then lower nibble */
 delayUs(40);
}
/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
 int i, j;
 for(i = 0 ; i < n; i++)
 for(j = 0; j < 3180; j++)
 {} /* do nothing for 1 ms */
}
/* delay n microseconds (16 MHz CPU clock) */
void delayUs(int n)
{
 int i, j;
 for(i = 0 ; i < n; i++)
 for(j = 0; j < 3; j++)
 {} /* do nothing for 1 us */
}
35
/* This function is called by the startup assembly code to perform system specific initialization
tasks. */
void SystemInit(void)
{
 /* Grant coprocessor access */
 /* This is required since TM4C123G has a floating point coprocessor */
 SCB->CPACR |= 0x00f00000;
} 
