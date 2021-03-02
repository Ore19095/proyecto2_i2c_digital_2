/*
 * File:   main.c
 * Author: AngelOrellana
 *
 * Created on 25 de febrero de 2021, 05:08 PM
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
#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "I2C.h"
#include "UART.h"
#include "MPU6050.h"


void main(void) {
    __delay_ms(1000);
    ANSEL = 0;
    TRISA = 0;
    PORTA = 0;
    char buffer[25];
    //int estado;
    I2C_Master_Init();
    UARTInit(9600,1);
    uint8_t val= 1;
    confMPU();
    char valores[8];
    int valorx,valory,valorz,temp;
    while(1){
        I2C_Start(0xD0);
        while(SSPCON2bits.ACKSTAT);
        I2C_Master_Write(0x3B);
        while(SSPCON2bits.ACKSTAT);        
//        while(SSPCON2bits.ACKSTAT);
//        I2C_Master_RepeatedStart();
//        I2C_Master_Write(0xD1);
//        while(SSPCON2bits.ACKSTAT);
//        valores[0] = I2C_Read(1);
//        I2C_Master_Stop();
//        
//        I2C_Start(0xD0);
//        while(SSPCON2bits.ACKSTAT);
//        I2C_Master_Write(0x3B);
//        while(SSPCON2bits.ACKSTAT);
//        I2C_Master_RepeatedStart();
//        I2C_Master_Write(0xD1);
//        while(SSPCON2bits.ACKSTAT);
//        valores[1] = I2C_Read(1);
//        I2C_Master_Stop();
//        
        I2C_Start(0xD0);
        while(SSPCON2bits.ACKSTAT);
        I2C_Master_Write(0x3B);
        while(SSPCON2bits.ACKSTAT);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        for (int i= 0; i<7;i++) valores[i] = I2C_Read(0);
        valores[7] = I2C_Read(1);
        I2C_Master_Stop();
//        //-------------------------
//        
        valorx = ((int) valores[0] << 8  ) | ((int) valores[1] );
        valory = ((int) valores[2] << 8  ) | ((int) valores[3] );
        valorz = ((int) valores[4] << 8  ) | ((int) valores[5] );
        temp = ((int) valores[6] << 8  ) | ((int) valores[7] );
        sprintf(buffer,"Ax: %i ",valorx);
        UARTSendString(buffer,15);
        sprintf(buffer,"Ay: %i ",valory);
        UARTSendString(buffer,15);
        sprintf(buffer,"Az: %i ",valorz);
        UARTSendString(buffer,15);
        sprintf(buffer,"Temp: %i ",temp);
        UARTSendString(buffer,15);
        UARTSendChar('\n');
        __delay_ms(250);
        val++;
        
    }
    return;
}
