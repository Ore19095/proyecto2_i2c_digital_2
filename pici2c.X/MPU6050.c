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
void readMPU(float* datos) {
    char valores[14];//valores temporales
    int guardar[7]; // arreglo donde se van a guardar los datos 
     
    I2C_Start(0xD0);
    //while (SSPCON2bits.ACKSTAT);
    I2C_Master_Write(0x3B);
    //while (SSPCON2bits.ACKSTAT);
    I2C_Master_Start();
    I2C_Master_Write(0xD1);
    for (int i = 0; i < 13; i++) valores[i] = I2C_Read(0);
    valores[13] = I2C_Read(1);
    I2C_Master_Stop();
    //        //-------------------------
    //        
    guardar[0] = ((int) valores[0] << 8) | ((int) valores[1]);
    guardar[1] = ((int) valores[2] << 8) | ((int) valores[3]);
    guardar[2] = ((int) valores[4] << 8) | ((int) valores[5]);
    guardar[3] = ((int) valores[6] << 8) | ((int) valores[7]);
    guardar[4] = ((int) valores[8] << 8) | ((int) valores[9]);
    guardar[5] = ((int) valores[10] << 8) | ((int) valores[11]);
    guardar[6] = ((int) valores[12] << 8) | ((int) valores[13]);
    
    datos[0] = ((float) guardar[0]) * 0.0005982; //aceleracion en m/s^2
    datos[1] = ((float) guardar[1]) * 0.0005982; //aceleracion en m/s^2
    datos[2] = ((float) guardar[2]) * 0.0005982; //aceleracion en m/s^2
    datos[3] = ((float) guardar[3])/340 + 36.53;
    datos[4] = ((float) guardar[4]) * 0.00763; //grados/s
    datos[5] = ((float) guardar[5]) * 0.00763; //grados/s
    datos[6] = ((float) guardar[6]) * 0.00763; //grados/s
    
    
    
    return;
}

void confMPU() {

    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x6B); // power managment 1 
    I2C_Master_Write(0x01); //giroscopio en x referencia  
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x00); //  Sample rate
    I2C_Master_Stop();


    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x19); //  Sample rate
    I2C_Master_Write(0x08); //1 khz de muestreo
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x1A); //CONFIG
    I2C_Master_Write(0x00); //externo deshabilitado, y frecuencia int 8khz 
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x1B); //gyro conf
    I2C_Master_Write(0x00); //+- 250 grados/s self test of
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x1C); // accel conf 
    I2C_Master_Write(0x00); //+-2g y self test of 
    I2C_Master_Stop();



    I2C_Master_Start();
    I2C_Master_Write(0x68); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x6C); // power managment 2 
    I2C_Master_Write(0x00); //se enciende  
    I2C_Master_Stop();



    return;

}