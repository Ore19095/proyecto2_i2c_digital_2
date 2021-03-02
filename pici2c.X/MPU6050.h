/* 
 * File: Libreria para comunicacion I2C con el sensor mpu
 * Author: Angel Orellana
 * Comments: Es necesario utilizar la libreria i2c que se encuentra alojada en
 * este repositorio 
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MPU_6050_H
#define	MPU_6050_H

#include <xc.h>
#include <stdint.h>
#include "I2C.h"
/**
 * configura el sensor para su correcto funcionamiento
 */
void confMPU(void);

/** 
 * funcion que lee los valores medidos por el acelerometro, el orden en el que 
 * son devueltos es el siguiente: Aceelerometro en x, acelerometro en y ,
 * acelerometro en z, temperatura, giroscopio en x, giroscopio en y , 
 * giroscoio en z. Para saber la razon de porque el orden es asi, leer la 
 * hoja de datos del mpu6050
 * @param valores: este parametro es un arreglo en donde se escribiran los 7 
 * valores en donde valores[0]=acelerometrox ,valores[1]=acelerometroy ,
 * valores[2]=acelerometroz,  valores[3]=temperatura, valores[4]=giroscopiox,
 * valores[5]=giroscopioy, valores[6]=giroscopioz. este parametro debe de tener
 * porlo menos un tamaño de 7 datos de tipo entero.
 */
void readMPU(int*);

#endif	/* MPU_6050_H */

