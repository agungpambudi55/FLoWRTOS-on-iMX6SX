/*
    Copyright (C) 2018 ER2C
    Politektik Elektronika Negeri Surabaya
    Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "dxl.h"

void SendData(UART_Type *base, const uint8_t *txBuff, uint32_t txSize)
{
    while(txSize--)
    {
        while (!UART_GetStatusFlag(base, uartStatusTxComplete));
        UART_Putchar(base, *txBuff++);
    }
}

void SetDxl(unsigned char ID, unsigned int Position, unsigned int Speed){
    unsigned char instruction, checksum;

    //HEADER 1 & 2 :: Write Header (0xFF) data to serial
    uint8_t hex_header = 0xFF;
    SendData(BOARD_PLAN_UART_BASEADDR, &hex_header, sizeof(hex_header));
    SendData(BOARD_PLAN_UART_BASEADDR, &hex_header, sizeof(hex_header));

    //ID Dynamixel :: Write Dynamixal ID to serial  
    instruction = ID;
    SendData(BOARD_PLAN_UART_BASEADDR, &instruction, sizeof(instruction));
    checksum = instruction;

    //Instruction packet lengths :: LENGTH
    instruction = 0x07;
    SendData(BOARD_PLAN_UART_BASEADDR, &instruction, sizeof(instruction));
    checksum += instruction; 
    
    //Instruction Commands Set :: COMMAND_WRITE_DATA
    instruction = 0x03;
    SendData(BOARD_PLAN_UART_BASEADDR, &instruction, sizeof(instruction));
    checksum += instruction; 

    //Instruction RAM AREA :: RAM_GOAL_POSITION_L
    instruction = 0x1E;
    SendData(BOARD_PLAN_UART_BASEADDR, &instruction, sizeof(instruction));
    checksum += instruction;

    //Least Significant Bit
    instruction = Position & 255;
    SendData(BOARD_PLAN_UART_BASEADDR, &instruction, sizeof(instruction));  
    checksum += instruction;

    //Most Significant Bit
    instruction = Position >> 8;
    SendData(BOARD_PLAN_UART_BASEADDR, &instruction, sizeof(instruction));  
    checksum += instruction;

    //Least Significant Bit
    instruction = Speed & 255;
    SendData(BOARD_PLAN_UART_BASEADDR, &instruction, sizeof(instruction));  
    checksum += instruction;

    //Most Significant Bit
    instruction = Speed >> 8;
    SendData(BOARD_PLAN_UART_BASEADDR, &instruction, sizeof(instruction));  
    checksum += instruction;

    //Write low bit of checksum to serial
    instruction = ~checksum & 0xFF;
    SendData(BOARD_PLAN_UART_BASEADDR, &instruction, sizeof(instruction));  
}
