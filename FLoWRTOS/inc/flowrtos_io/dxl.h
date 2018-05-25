/*
	Copyright (C) 2018 ER2C
	Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

// speed = 0 - 1023 
// position = goal_posotion : 0 - 1023 / derajat : 0 - 300

#ifndef DXL_H
#define DXL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "flowrtos.h"

// funtion for send hexa to dynamixel
void SendData(UART_Type *base, const uint8_t *txBuff, uint32_t txSize);

// function for set dynamixel
void SetDxl(unsigned char ID, unsigned int Position, unsigned int Speed);

#ifdef __cplusplus
}
#endif
#endif
