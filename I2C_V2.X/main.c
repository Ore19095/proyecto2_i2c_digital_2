/*
 * File:   main.c
 * Author: AngelOrellana
 *
 * Created on 3 de marzo de 2021, 12:42 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#include "I2C.h"
#include "UART.h"
#include "MPU6050.h"
void main(void) {
   
    ANSEL = 0;
    TRISA = 0;
    PORTA = 0;
    char buffer[15];
    char comando; //almacena el comando recibido por uart
    I2C_Master_Init();
    UARTInit(9600, 1);
    confMPU();
    int status;
    int datos[7];
    while (1) {
        readMPU(datos);

        PORTA = ~PORTA;
        
        sprintf(buffer,"Ax: %i ",datos[0]);
        UARTSendString(buffer,15);
        sprintf(buffer,"Ay: %i ",datos[1]);
        UARTSendString(buffer,15);
        sprintf(buffer,"Az: %i ",datos[2]);
        UARTSendString(buffer,15);
        sprintf(buffer,"T: %i ",datos[3]);
        UARTSendString(buffer,15);
        UARTSendChar('\n');
//        buffer = ftoa(datos[0], status);
//        UARTSendString(" ", 10);
//        UARTSendString(buffer, 6);
//
//        buffer = ftoa(datos[1], status);
//        UARTSendString(" ", 10);
//        UARTSendString(buffer, 6);
//
//        buffer = ftoa(datos[2], status);
//        UARTSendString(" ", 6);
//        UARTSendString(buffer, 6);
//
//        buffer = ftoa(datos[3], status);
//        UARTSendString(" ", 6);
//        UARTSendString(buffer, 6);
//
//        buffer = ftoa(datos[4], status);
//        UARTSendString(" ", 6);
//        UARTSendString(buffer, 6);
//        buffer = ftoa(datos[5], status);
//        UARTSendString(" ", 6);
//        UARTSendString(buffer, 6);
//
//        buffer = ftoa(datos[6], status);
//        UARTSendString(" ", 6);
//        UARTSendString(buffer, 6);
//
//        UARTSendChar('\n');
    }
    return;
}