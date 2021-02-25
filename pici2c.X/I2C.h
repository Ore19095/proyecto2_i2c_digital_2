/*
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef I2C_H
#define	I2C_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define I2C_MODE master //cambiar a slave si se quiere configurar como esclavo
#define _XTAL_OSC 4000000 //cambiar si es necesario
#define I2C_FREC 100000 //calculado para 100khz, si se cambia a 400khz colocar 
                        // en 0 el bit SMP de SSPSTAT
//este valor se calcula solo
#
/**
 * Inicializa el mssp como i2c cambiar el valor de la constante I2C_MODE para 
 * determinar si se inicializa como maestro o como esclavo al igual que cambiar
 * _XTAL_FREC
 */


#endif	/* XC_HEADER_TEMPLATE_H */

