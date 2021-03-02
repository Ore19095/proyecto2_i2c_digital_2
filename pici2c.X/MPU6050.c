/*
 * File:   MPU6050.c
 * Author: Angel Orellana
 *
 * Created on 27 de febrero de 2021, 08:39 AM
 */


#include "MPU6050.h"

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
 * porlo menos un tamaño de 7 datos de tipo int. al salir en este arreglo 
 * se encontraran los valors convertidos a sus respectivas magnitudes fisicas,
 * con 3 decimales, los cuales corresponderan a los ultimos 3 digitos del numero  
 *para el acelerometro y para el giroscopio y temperatura los digitos decimales
 * seran los ultimos dos (leidos de derecha a izquierda)
 *
 */
void readMPU(int* guardar) {
    int valores[7];
    I2C_Master_Start();
    I2C_Master_Write(0x68); //direccion del mpu con escritura
    I2C_Master_Write(0x3B); //se prepara para leer los datos
    I2C_Master_Stop(); //fin

    I2C_Master_Start();
    I2C_Master_Write(0xE8); // direccion del sensor, con modo lectura

    valores[0] = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
    valores[1] = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
    valores[2] = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
    valores[3] = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
    valores[4] = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
    valores[5] = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
    valores[6] = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(1);

    I2C_Master_Stop(); // fin de la comunicacion 
    // despues se convierten a sus valores fisicos
    // acelerometro
    //    for (int i= 0; i<3; i++)guardar[i] = valores[i]*0.0005981;
    //    //temperatura
    //    guardar[3] =  ((float) valores[3]/340) + 36.53;
    //    //giroscopio
    //    for (int i =4; i<7; i++) guardar[i]= valores[i]*0.763;
    guardar = valores;
    return;
}

void confMPU() {

    I2C_Master_Start();
    I2C_Master_Write(0x68); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x00); //  Sample rate
    I2C_Master_Stop();


    I2C_Master_Start();
    I2C_Master_Write(0x68); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x19); //  Sample rate
    I2C_Master_Write(0x08); //1 khz de muestreo
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0x68); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x1A); //CONFIG
    I2C_Master_Write(0x00); //externo deshabilitado, y frecuencia int 8khz 
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0x68); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x1B); //gyro conf
    I2C_Master_Write(0x00); //+- 250 grados/s self test of
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0x68); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x1C); // accel conf 
    I2C_Master_Write(0x00); //+-2g y self test of 
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0x68); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x6B); // power managment 1 
    I2C_Master_Write(0x01); //giroscopio en x referencia  
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0x68); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x6C); // power managment 2 
    I2C_Master_Write(0x00); //se enciende  
    I2C_Master_Stop();



    return;

}