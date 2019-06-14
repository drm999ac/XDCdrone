//###########################################################################
//
// FILE:   F2837xD_ECap.c
//
// TITLE:  F2837xD eCAP Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2837xD Support Library v3.05.00.00 $
// $Release Date: Thu Oct 18 15:48:42 CDT 2018 $
// $Copyright:
// Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

//
// Included Files
//
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#define EC_RISING          0x0
#define EC_FALLING         0x1

#define EC_ABS_MODE        0x0
#define EC_DELTA_MODE      0x1

#define EC_BYPASS          0x0
#define EC_DIV1            0x0
#define EC_DIV2            0x1
#define EC_DIV4            0x2
#define EC_DIV6            0x3
#define EC_DIV8            0x4
#define EC_DIV10           0x5

#define EC_CONTINUOUS      0x0
#define EC_ONESHOT         0x1

#define EC_EVENT1          0x0
#define EC_EVENT2          0x1
#define EC_EVENT3          0x2
#define EC_EVENT4          0x3

#define EC_ARM             0x1

#define EC_FREEZE          0x0
#define EC_RUN             0x1

#define EC_SYNCIN          0x0
#define EC_CTR_PRD         0x1
#define EC_SYNCO_DIS       0x2

#define EC_CAP_MODE        0x0
#define EC_APWM_MODE       0x1

#define EC_ACTV_HI         0x0
#define EC_ACTV_LO         0x1

#define EC_DISABLE         0x0
#define EC_ENABLE          0x1
#define EC_FORCE           0x1



//
// InitECap - This function initializes the eCAP(s) to a known state.
//
void InitECap(void)
{
//
//
//     //Initialize eCAP1/2/3/4/5/6
//    ECap1Regs.ECEINT.all = 0x0000;          // Disable all capture __interrupts
//    ECap1Regs.ECCLR.all = 0xFFFF;           // Clear all CAP __interrupt flags
//    ECap1Regs.ECCTL1.bit.CAPLDEN = 0;       // Disable CAP1-CAP4 register loads
//    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;     // Make sure the counter is stopped
//
////   //
////   // Configure peripheral registers
////   //
////   ECap1Regs.ECCTL2.bit.CONT_ONESHT = 1;   // One-shot
////   ECap1Regs.ECCTL2.bit.STOP_WRAP = 3;     // Stop at 4 events
//
//   ECap1Regs.ECCTL1.bit.CAP1POL = EC_RISING;       // Falling edge
//   ECap1Regs.ECCTL1.bit.CAP2POL = EC_FALLING;       // Rising edge
//   ECap1Regs.ECCTL1.bit.CAP3POL = EC_RISING;       // Falling edge
//   ECap1Regs.ECCTL1.bit.CAP4POL = EC_FALLING;       // Rising edge
//   ECap1Regs.ECCTL1.bit.CTRRST1 = EC_DELTA_MODE;       // Difference operation
//   ECap1Regs.ECCTL1.bit.CTRRST2 = EC_DELTA_MODE;       // Difference operation
//   ECap1Regs.ECCTL1.bit.CTRRST3 = EC_DELTA_MODE;       // Difference operation
//   ECap1Regs.ECCTL1.bit.CTRRST4 = EC_DELTA_MODE;       // Difference operation
//   ECap1Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;       // Enable CAP1-CAP4 register loads
//   ECap1Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
//
//
//   ECap1Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;
//   ECap1Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;
//
//   ECap1Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;     // Pass through
//   ECap1Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;      // Enable sync in
//
////   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable capture units
//   ECap1Regs.ECCTL2.bit.REARM = 1;         // arm one-shot
//   ECap1Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;     // Start Counter
//
//
//
//   ECap1Regs.ECEINT.bit.CEVT2 = 1;         // 2 events = __interrupt
//    //tbd...
    //
    ECap1Regs.ECCTL1.bit.CAP1POL = EC_RISING;
    ECap1Regs.ECCTL1.bit.CAP2POL = EC_RISING;
    ECap1Regs.ECCTL1.bit.CAP3POL = EC_RISING;
    ECap1Regs.ECCTL1.bit.CAP4POL = EC_RISING;
    ECap1Regs.ECCTL1.bit.CTRRST1 = EC_ABS_MODE;
    ECap1Regs.ECCTL1.bit.CTRRST2 = EC_ABS_MODE;
    ECap1Regs.ECCTL1.bit.CTRRST3 = EC_ABS_MODE;
    ECap1Regs.ECCTL1.bit.CTRRST4 = EC_ABS_MODE;
    ECap1Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;
    ECap1Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
    ECap1Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;
    ECap1Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;
    ECap1Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
    ECap1Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;

    ECap1Regs.ECEINT.bit.CEVT1 = 1;         // 1 events = __interrupt
    ECap1Regs.ECEINT.bit.CEVT2 = 1;         // 2 events = __interrupt
}

//
// InitECapGpio - This function initializes GPIO pins to function as ECAP pins
//                Each GPIO pin can be configured as a GPIO pin or up to 3
//                different peripheral functional pins. By default all pins
//                come up as GPIO inputs after reset.
//                Caution:
//                For each eCAP peripheral
//                Only one GPIO pin should be enabled for ECAP operation.
//                Comment out other unwanted lines.
//
void InitECapGpio()
{
}

//
// InitECap1Gpio - Initialize ECAP1 GPIOs
//
void InitECap1Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT7SELECT = pin;         // Set eCAP1 source to GPIO-pin
    EDIS;
}

//
// InitECap2Gpio - Initialize ECAP2 GPIOs
//
void InitECap2Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT8SELECT = pin;         // Set eCAP2 source to GPIO-pin
    EDIS;
}

//
// InitECap3Gpio - Initialize ECAP3 GPIOs
//
void InitECap3Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT9SELECT = pin;         // Set eCAP3 source to GPIO-pin
    EDIS;
}

//
// InitECap4Gpio - Initialize ECAP4 GPIOs
//
void InitECap4Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT10SELECT = pin;         // Set eCAP4 source to GPIO-pin
    EDIS;
}

//
// InitECap5Gpio - Initialize ECAP5 GPIOs
//
void InitECap5Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT11SELECT = pin;         // Set eCAP5 source to GPIO-pin
    EDIS;
}

//
// InitECap6Gpio - Initialize ECAP6 GPIOs
//
void InitECap6Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT12SELECT = pin;         // Set eCAP6 source to GPIO-pin
    EDIS;
}

//
// InitAPwm1Gpio - Initialize EPWM1 GPIOs
//
void InitAPwm1Gpio()
{
    EALLOW;
    OutputXbarRegs.OUTPUT3MUX0TO15CFG.bit.MUX0 = 3; // Select ECAP1.OUT on Mux0
    OutputXbarRegs.OUTPUT3MUXENABLE.bit.MUX0 = 1;  // Enable MUX0 for ECAP1.OUT
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;    // Select OUTPUTXBAR3 on GPIO5
    EDIS;
}

//void Init()

//
// End of file
//
