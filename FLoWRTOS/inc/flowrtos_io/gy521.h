/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#ifndef GY521_H
#define GY521_H

#ifdef __cplusplus
extern "C" {
#endif

#include "flowrtos.h"

#define MATH_PI 3.141592653589793238462643

#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND)
#define MPU6050_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)
#define MPU6050_DEFAULT_ADDRESS     MPU6050_ADDRESS_AD0_LOW

#define MPU6050_ACC_GYRO		    0x3B

#define MPU6050_WHO_AM_I_BIT        6
#define MPU6050_WHO_AM_I_LENGTH     6

int header_find = 0, index_data = 0, dataRX[4], jml_dataRX = 4;

// angles
struct euler_angles
{
	float pitch;
	float roll;
	float yaw;
};

struct euler_angles *imu;

// conversion data type float to string then printed
void print_f2s(float data, int mantissa);

// read multiple bytes from an 8-bit device register
int8_t read_bytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);

// getting motion of (x,y,z) from accelerometer and gyroscope
void get_motion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);

// getting motion
void get_motion(void);

// getting euler angle of pitch, roll, and yaw
void get_euler_angles(void);

// print the value from pitch, roll, and yaw
void show_euler_angles(void);

#ifdef __cplusplus
}
#endif
#endif
