/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "gy521.h"

// conversion data type float to string then printed
void print_f2s(float data, int mantissa){
    float f;
    char str[30];
    int a, b, c, k, l = 0, m, i=0;
    f = data;

    // check for negetive float
    if(f<0.0){
        str[i++] = '-';
        f *= -1;
    }
    if(data > -1 && data < 1)
    { str[i++] = '0'; };

    a=f;    // extracting whole number
    f-=a;   // extracting decimal part
    k = mantissa;
    
    // number of digits in whole number
    while(k>-1){
        l = pow(10,k);
        m = a/l;
        if(m>0) { break; } 
        k--;
    }

    // number of digits in whole number are k+1
    for(l=k+1;l>0;l--){
        b = pow(10,l-1);
        c = a/b;
        str[i++]=c+48;
        a%=b;
    }
    str[i++] = '.';
    
    /* extracting decimal digits till mantissa */
    for(l=0;l<mantissa;l++){
        f*=10.0;
        b = f;
        str[i++]=b+48;
        f-=b;
    }
    str[i]='\0';
    PRINTF("%s",str);
}

// getting motion of (x,y,z) from accelerometer and gyroscope
void get_motion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz){
	// float accx, accy, accz, gyrox, gyroy, gyroz;
	// float alpha = 0.5, f_ax = 0, f_ay = 0, f_az = 0, f_gx = 0, f_gy = 0, f_gz = 0;
	// float imu_p, imu_r, imu_y;
	uint8_t buffer[14];

	// read multiple bytes from an 8-bit device register
	read_bytes(MPU6050_DEFAULT_ADDRESS, MPU6050_ACC_GYRO, 14, buffer);
	*ax = (((int16_t)buffer[0]) << 8) | buffer[1];
    *ay = (((int16_t)buffer[2]) << 8) | buffer[3];
    *az = (((int16_t)buffer[4]) << 8) | buffer[5];
    *gx = (((int16_t)buffer[8]) << 8) | buffer[9];
    *gy = (((int16_t)buffer[10]) << 8) | buffer[11];
    *gz = (((int16_t)buffer[12]) << 8) | buffer[13];

	//Low Pass Filter
	// f_ax = accx * alpha + (f_ax * (1.0 - alpha));
	// f_ay = accy * alpha + (f_ay * (1.0 - alpha));
	// f_az = accz * alpha + (f_az * (1.0 - alpha));

	// f_gx = gyrox * alpha + (f_gx * (1.0 - alpha));
	// f_gy = gyroy * alpha + (f_gy * (1.0 - alpha));
	// f_gz = gyroz * alpha + (f_gz * (1.0 - alpha));

	// imu_p = (atan2(-f_ay, f_az)*180.0)/MATH_PI;
	// imu_r = -(atan2(f_ax, sqrt(f_ay*f_ay + f_az*f_az))*180.0)/MATH_PI;
	// imu_y = f_gz;
}

// getting motion
void get_motion(void){
	while (UART_GetStatusFlag(BOARD_PLAN_UART_BASEADDR, uartStatusRxDataReady))
	{
		char inChar = UART_Getchar(BOARD_PLAN_UART_BASEADDR);
	    if(inChar == 'P'){ header_find = 1; }
	    else if(header_find == 1 && inChar == 'R'){ header_find = 2; }
	    else if(header_find == 2)
	    {
	      // PRINTF("%i",index_data);
	      dataRX[index_data] = (int)inChar;
	      index_data++;
	      if(index_data >= jml_dataRX){ header_find = index_data = 0; }
	    }
	    else
	    { header_find = index_data = 0; }
	}	
}

// getting euler angle of pitch, roll, and yaw
void get_euler_angles(void){
	get_motion();

	dataRX[0] = dataRX[0] & 0x00FF;
	dataRX[1] = dataRX[1] << 8;
	dataRX[2] = dataRX[2] & 0x00FF;
	dataRX[3] = dataRX[3] << 8;

	imu->pitch = ( dataRX[0] | dataRX[1] ); 
	imu->roll = ( dataRX[2] | dataRX[3] ); 
	imu->yaw = 0;

	if(imu->pitch>=10000){ imu->pitch = (imu->pitch - 10000) * -1; }
	if(imu->roll>=10000){ imu->roll = (imu->roll - 10000) * -1; }

	imu->pitch = imu->pitch / 10;
	imu->roll = imu->roll / 10;	
}

// print the value from pitch, roll, and yaw
void show_euler_angles(void){
	PRINTF("pitch = ");	print_f2s(imu->pitch, 2);	PRINTF("\t");
	PRINTF("roll = ");	print_f2s(imu->roll, 2);	PRINTF("\t");
	PRINTF("yaw = ");	print_f2s(imu->yaw, 2);		PRINTF("\n\r");
}