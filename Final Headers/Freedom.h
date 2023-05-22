/*
 * Freedom.h
 *
 *  Created on: 28/05/2013
 *      Author: Peter
 */
#ifndef FREEDOM_H_
#define FREEDOM_H_

#include "utilities.h"

//=================================================================================
// LED Port bit masks
//
#define LED_GREEN_PORT         D
#define LED_GREEN_NUM          4

#define LED_RED_PORT           C
#define LED_RED_NUM            3

#define LED_BLUE_PORT          A
#define LED_BLUE_NUM           2

#define UART_NUM               0        

#define UART_RX_PIN_PORT       B
#define UART_RX_PIN_NUM       16
#define UART_RX_PIN_FN         3

#define UART_TX_PIN_PORT       B
#define UART_TX_PIN_NUM       17
#define UART_TX_PIN_FN         3
                           
                            // Elec freaks LCD Shield buttons
#define NORTH_SWITCH_PORT          C    // (A0) North
#define NORTH_SWITCH_NUM           0
#define EAST_SWITCH_PORT           C    // (A1) East
#define EAST_SWITCH_NUM            1
#define SOUTH_SWITCH_PORT          D    // (A2) South
#define SOUTH_SWITCH_NUM           6
#define CENTRE_SWITCH_PORT         D    // (A3) Centre
#define CENTRE_SWITCH_NUM          5
#define WEST_SWITCH_PORT           B    // (A4) West
#define WEST_SWITCH_NUM            1

#endif /* FREEDOM_H_ */
