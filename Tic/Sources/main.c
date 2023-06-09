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


int a1[]={15,10};
int a2[]={15,55};
int a3[]={15,100};
int b1[]={60,10};
int b2[]={60,55};
int b3[]={60,100};
int c1[]={105,10};
int c2[]={105,55};
int c3[]={105,100};

void xa1(){lcd_putStr("X",  a1[0],a1[1],FontLarge, WHITE, TEAL);}
void xa2(){lcd_putStr("X",  a2[0],a2[1],FontLarge, WHITE, TEAL);}
void xa3(){lcd_putStr("X",  a3[0],a3[1],FontLarge, WHITE, TEAL);}


void xb1(){lcd_putStr("X",  b1[0],b1[1],FontLarge, WHITE, TEAL);}
void xb2(){lcd_putStr("X",  b2[0],b2[1],FontLarge, WHITE, TEAL);}
void xb3(){lcd_putStr("X",  b3[0],b3[1],FontLarge, WHITE, TEAL);}

void xc1(){lcd_putStr("X",  c1[0],c1[1],FontLarge, WHITE, TEAL);}
void xc2(){lcd_putStr("X",  c2[0],c2[1],FontLarge, WHITE, TEAL);}
void xc3(){lcd_putStr("X",  c3[0],c3[1],FontLarge, WHITE, TEAL);}
////--------------------------------------------------------------///
void oa1(){lcd_putStr("O",  a1[0],a1[1],FontLarge, WHITE, TEAL);}
void oa2(){lcd_putStr("O",  a2[0],a2[1],FontLarge, WHITE, TEAL);}
void oa3(){lcd_putStr("O",  a3[0],a3[1],FontLarge, WHITE, TEAL);}


void ob1(){lcd_putStr("O",  b1[0],b1[1],FontLarge, WHITE, TEAL);}
void ob2(){lcd_putStr("O",  b2[0],b2[1],FontLarge, WHITE, TEAL);}
void ob3(){lcd_putStr("O",  b3[0],b3[1],FontLarge, WHITE, TEAL);}

void oc1(){lcd_putStr("O",  c1[0],c1[1],FontLarge, WHITE, TEAL);}
void oc2(){lcd_putStr("O",  c2[0],c2[1],FontLarge, WHITE, TEAL);}
void oc3(){lcd_putStr("O",  c3[0],c3[1],FontLarge, WHITE, TEAL);}

void grid()
          {  lcd_drawLine(0, 40, 150, 40, WHITE);//HORIZONTAL 1
             lcd_drawLine(40, 0, 40 , 150, WHITE);//VERTICAL 1
             lcd_drawLine(0, 90, 150, 90, WHITE);//HORIZONTAL 2
             lcd_drawLine(90, 0, 90, 150, WHITE);//VERTICAL 2
	
          }
///---------------------------------------------------------------///

/*!
 *   Checks if the centre-switch is pressed
 */
int getCentreSwitch(void) {
   return (CENTRE_SWITCH_PDIR&CENTRE_SWITCH_MASK) == 0;
}

/*!
 *   Initialise the switch inputs before first use
 *   
 */
void switch_initialise(void) {
   // Enable port clock for centre switch
   SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;   
   
   CENTRE_SWITCH_PCR   = PORT_PCR_MUX(1)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
   CENTRE_SWITCH_PDDR &= ~CENTRE_SWITCH_MASK;
}

// Function to initialize the keypad
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



int main() {
	
    initialiseClock();
    // Initialize the keypad
    keypad_init();
    lcd_initialise();
    lcd_clear(BACKGROUND_COLOUR);
     switch_initialise();

    printf("Testing serial communication... success\n");
    while (1)
    {  
    	 grid();
        // Scan the keypad for a button press
        char key = keypad_scan();
        char f=key;
         // Check if a key is pressed
        if (key != '\0') {
            // Print the pressed key on the serial terminal
            printf("Pressed key: %c \n", key);
            if(f==1)
            {
            	xa1();
            	 printf("Pressed key 2: %c \n", f);
            }
        }
       
       
       //xa1();
       // if(key==1){xa1();};
       
    }

    return 0;
}


