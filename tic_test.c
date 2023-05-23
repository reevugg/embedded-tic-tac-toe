/*
1 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */
#include <stdio.h>
#include "MK20D5.h"  
#include "clock.h"
#include <stdlib.h>
#include "nokia_LCD.h"
#include "uart.h"
#include "Freedom.h"
#include "Die.h"

// Define rows and columns
#define BACKGROUND_COLOUR TEAL

#define CENTRE_SWITCH_PCR          PCR(CENTRE_SWITCH_PORT,CENTRE_SWITCH_NUM)
#define CENTRE_SWITCH_PDIR         PDIR(CENTRE_SWITCH_PORT)  // Data input
#define CENTRE_SWITCH_PDDR         PDDR(CENTRE_SWITCH_PORT)  // Data direction
#define CENTRE_SWITCH_MASK         (1<<CENTRE_SWITCH_NUM)

#define ROW1 (1<<4)
#define ROW2 (1<<3)
#define ROW3 (1<<1)
#define ROW4 (1<<8)

#define COL1 (1<<1)
#define COL2 (1<<3)
#define COL3 (1<<2)
#define COL4 (1<<2)



int board[3][3]={{ 0, 0, 0},
                 { 0, 0, 0},
                 { 0, 0, 0}};


int player=0;

void keypad_init() {
	
	SIM_SCGC5 |=SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTC_MASK| SIM_SCGC5_PORTD_MASK;
	
    // Configure row pins 
	PORTC_PCR4 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;//	ROW 1
	PORTC_PCR3 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;//ROW 2
	PORTA_PCR1 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;//ROW 3
	PORTC_PCR8 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;// ROW 4
	
	
    // Configure column pins 
	PORTD_PCR1 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;//COL 1
	PORTD_PCR3 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;//COL 2
	PORTD_PCR2 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;//COL 3
	PORTC_PCR2 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;// COL4 
	
	// Set the direction of column pins as outputs
	GPIOD_PDDR |= (COL1 | COL2 | COL3);
	GPIOC_PDDR |= COL4;

	// Set the direction of row pins as inputs
	GPIOC_PDDR &= ~(ROW4 | ROW2 | ROW1);
	GPIOA_PDDR &= ~(ROW3);

}

void delay()
{
int delayCount;
for(delayCount=0;delayCount<1000000;delayCount++)
{
asm("nop");
}
}
char keypad_scan() {
    int col;
    char keypad[4][4] = {
        { '1', '2', '3', 'A' },
        { '4', '5', '6', 'B' },
        { '7', '8', '9', 'C' },
        { '*', '0', '#', 'D' }
    };

    for (col = 0; col < 4; col++) {
        // Set current column to low
        switch (col) {
            case 0:
                GPIOD_PCOR |= COL1;
                break;
            case 1:
                GPIOD_PCOR |= COL2;
                break;
            case 2:
                GPIOD_PCOR |= COL3;
                break;
            case 3:
                GPIOC_PCOR |= COL4;
                break;
        }

        // Check rows
        if (!(GPIOC_PDIR & ROW1)) {
            while (!(GPIOC_PDIR & ROW1));  // Wait for button release
            return keypad[0][col];
        }
        if (!(GPIOC_PDIR & ROW2)) {
            while (!(GPIOC_PDIR & ROW2));  // Wait for button release
            return keypad[1][col];
        }
        if (!(GPIOA_PDIR & ROW3)) {
            while (!(GPIOA_PDIR & ROW3));  // Wait for button release
            return keypad[2][col];
        }
        if (!(GPIOC_PDIR & ROW4)) {
            while (!(GPIOC_PDIR & ROW4));  // Wait for button release
            return keypad[3][col];
        }

        // Set current column back to high
        switch (col) {
            case 0:
                GPIOD_PSOR |= COL1;
                break;
            case 1:
                GPIOD_PSOR |= COL2;
                break;
            case 2:
                GPIOD_PSOR |= COL3;
                break;
            case 3:
                GPIOC_PSOR |= COL4;
                break;
        }
    }

    return '0';
}
void game(char sw)
              {
	             if(sw=='1'){board[0][0]=1;}
	             if(sw=='2'){board[0][1]=1;}
	             if(sw=='3'){board[0][2]=1;}
	             if(sw=='4'){board[1][1]=1;}
	             if(sw=='5'){board[1][2]=1;}
	             if(sw=='6'){board[1][3]=1;}
	             if(sw=='7'){board[3][1]=1;}
	             if(sw=='8'){board[3][2]=1;}
	             if(sw=='9'){board[3][3]=1;}
	             if(sw=='A'){player=1;}
	             if(sw=='B'){player=2;}
              }

void printBoard() {
  
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("Player: %c \n", player);
}

int main() {
	
    initialiseClock();
    // Initialize the keypad
    keypad_init();
    lcd_initialise();
    lcd_clear(BACKGROUND_COLOUR);
    

    printf("Testing serial communication... success\n");
    while (1)
    {  
    	
    	        char key = keypad_scan();
    	        char f = key;
    	        

    	        if (f!= '0') 
    	        {
    	           printf("Pressed key: %c \n", key);
    	           game(key);
    	           printBoard();
    	           delay();
    	                
    	                
    	                
    	            }
    	        }
        
       
       
       //xa1();
       // if(key==1){xa1();};
       
    

    return 0;
}


