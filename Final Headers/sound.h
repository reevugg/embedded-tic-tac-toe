//--------PASS TASK 4.1------------
#include "derivative.h" 
#include "utilities.h"
#include "clock.h"
#include <stdio.h>

#define BUZZER_MASK (1<<0);

int count = 0;


uint32_t SysTick_Config( uint32_t ticks) 
{
	if((ticks - 1) > SysTick_RVR_RELOAD_MASK) 
	{
		//Reload value impossible 
		return(1);
	}
	//Set reload register
	
	SYST_RVR = SysTick_RVR_RELOAD(ticks - 1);

	// Set Priority for Systick Interrupt 
	NVIC_SetIrqPriority (INT_SysTick , 0);

	// Load the SysTick Counter Value 
	SYST_CVR = 0;

	// Configure Systick 
	SYST_CSR = 
			SysTick_CSR_CLKSOURCE_MASK |// Use system core clock
			SysTick_CSR_TICKINT_MASK | // Enable interrupts
			SysTick_CSR_ENABLE_MASK; // Enable timer

// Function successful 
return(0);
}

void SysTick_Handler(void)
{
	count++;
	//increase value continuously by 1
}

void delayMs( unsigned int delay)
{
	count = 0;
	while (count <delay);
}

void initialisePINs(void)
{
	//makes sure clock runs at 48MHz
	initialiseClock();
	
	// Enable clock to PORTE
	SIM_SCGC5 |=SIM_SCGC5_PORTE_MASK;
	
	// Configure as port pin with interrupts, button connection
	PORTE_PCR0 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;

	GPIOE_PDDR |= BUZZER_MASK;
}

//Set up PIT module for tone
void initialisePIT( int channel, uint32_t interval)
{
	// Enable clock to PIT
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	// Enable PIT with "Freeze Mask"
	PIT_MCR = PIT_MCR_FRZ_MASK;
	
	// Set reload value
	PIT_LDVAL(channel)= interval - 1;
	
	// Enable this channel with interrupts
	PIT_TCTRL(channel) = PIT_TCTRL_TEN_MASK|PIT_TCTRL_TIE_MASK;
	
	// Enable NVIC as a listener for interrupts
	NVIC_EnableIrq(INT_PIT0+channel);
}

void PIT_Ch0_IRQHandler( void )
{
	// Toggle the speaker
	GPIOE_PTOR = BUZZER_MASK;
	
	// Clear the interrupt request from PIT
	PIT_TFLG0 = PIT_TFLG_TIF_MASK;
}



void playTone (int frequency, int time_ms)
{
	int PITticks = (48000000/(frequency*2)); //PIT Generates quare wate to play tone
	initialisePIT(0, PITticks);
	delayMs(time_ms);
	NVIC_DisableIrq(INT_PIT0); // turn off tune
}


/*
int main(void)
{

	initialisePINs();
	SysTick_Config(48000);//calling and giving reload value

	unsigned int freq[] = {262, 294, 330, 350, 392, 440, 494, 523};//song frequencies
	unsigned int time_duration = 500;// 500ms

	
	for(;;) 
	{	   
	   
		__asm("wfi"); //wait for interrupt
		int k;
		for (k = 0; k<8; k++)//for 8 frequencies
		{
			playTone( freq[k],time_duration);
		}
		delayMs(1500); 
	}
	
	return 0;
}
*/
