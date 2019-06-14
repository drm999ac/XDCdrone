/*
 * I2C.c
 *
 *  Created on: 2019年3月28日
 *      Author: SXJ
 */

#include "I2C.h"

void IIC_Init(void)
{
//    I2cbRegs.I2CSAR.all = 0xEE;     // Slave address - EEPROM control code
//
//    I2cbRegs.I2CPSC.all = 16;         // Prescaler - need 7-12 Mhz on module clk//预分频器-在模块CLK上需要7-12兆赫
//    I2cbRegs.I2CCLKL = 10;            // NOTE: must be non zero
//    I2cbRegs.I2CCLKH = 5;             // NOTE: must be non zero
//    I2cbRegs.I2CIER.all = 0x24;       // Enable SCD & ARDY __interrupts
//
//    I2cbRegs.I2CMDR.all = 0x0020;     // Take I2C out of reset
//                                      // Stop I2C when suspended
//
//    I2cbRegs.I2CFFTX.all = 0x6000;    // Enable FIFO mode and TXFIFO
//    I2cbRegs.I2CFFRX.all = 0x2040;    // Enable RXFIFO, clear RXFFINT,

//    EALLOW;
//    GpioCtrlRegs.GPBMUX1.bit.GPIO34=0;      //选择数字I/O模式
//    GpioCtrlRegs.GPBPUD.bit.GPIO34=0;       //使能内部上拉电阻

//    EDIS;
//    SDA_Output();
    GPIO_SetupPinMux(34, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(34, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(35, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(35, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_WritePin(34,1);
    GPIO_WritePin(35,1);
//    SDA_High();
//    SCL_High();
}


void IIC_Start(void)
{
    SDA_Output();
    SCL_High();   // Set the SCL
    SDA_High();   // Set the SDA
    DELAY_US(I2CDelay);
    SDA_Low();    // Clear the SDA while SCL is high indicates the start signal
    DELAY_US(I2CDelay);
    SCL_Low();    // Clear the SCL to get ready to transmit
}

void IIC_Stop(void)
{
    SDA_Output();
    SCL_Low();    // Clear the SCL
    SDA_Low();    // Clear the SDA
    DELAY_US(I2CDelay);
    SCL_High();   // Set the SCL
    SDA_High();   // Set the SDA while SCL is high indicates the finish signal
    DELAY_US(I2CDelay);
}

unsigned char IIC_Wait_Ack(void)
{
    int ErrTime=0;
    int ReadAck=0;
    SDA_Input();  // Config SDA GPIO as Input
    SDA_High();
    DELAY_US(I2CDelay);
    SCL_High();   // Set the SCL and wait for ACK
    DELAY_US(I2CDelay);

    ReadAck = GPIO_ReadPin(34); ;  // Read the input
    while(ReadAck)
    {
        ErrTime++;
        if(ErrTime>250)
        {
                 //Error handler:Set error flag, retry or stop.
                //Define by users
             IIC_Stop();
             return 1;
         }
     }

      SCL_Low();   // Clear the SCL for Next Transmit
      return 0;

}

void IIC_Ack(void)          //I2C_MSGSTAT_SEND_WITHSTOP
{
    SCL_Low();
    SDA_Output();
    SDA_Low();
    DELAY_US(10);
    SCL_High();
    DELAY_US(10);
    SCL_Low();
}

void IIC_NAck(void)         //I2C_MSGSTAT_SEND_NOSTOP
{
    SCL_Low();     // Clear the SCL to get ready to transmit
    SDA_Output();
    SDA_High();    // Clear the SDA
    DELAY_US(10);
    SCL_High();    // Set the SCL
    DELAY_US(10);
    SCL_Low();      // Clear the SCL
}

void IIC_Send_Byte(unsigned char txd)
{
    int t;
    SDA_Output();   // Config SDA GPIO as output
    SCL_Low();      // Clear the SCL to get ready to transmit
    for(t=0;t<8;t++)
        {
           SDA_Data_Register = (txd & 0x80)>>7;  // Send the LSB
           txd<<=1;
           DELAY_US(10);
           SCL_High();   // Set the SCL
           DELAY_US(10);
           SCL_Low();    // Clear the SCL
           DELAY_US(10);
        }

}

unsigned char IIC_Read_Byte(unsigned char ack)
{
    int t;
    unsigned char receive=0;
    SDA_Input();
    for(t=0;t<8;t++)
    {
        SCL_Low();   // Clear the SCL
        DELAY_US(10);
        SCL_High();   // Set the SCL
        receive<<=1;
        if(GPIO_ReadPin(34))
        {
          receive++;
        }
        DELAY_US(10);
     }
    if (!ack)
        IIC_NAck();
    else
        IIC_Ack();
     return receive;
}


