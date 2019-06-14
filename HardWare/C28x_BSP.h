/*
 * BSP.h
 *
 *  Created on: 2018年4月12日
 *      Author: Xiluna Tech
 */

#ifndef HARDWARE_C28X_BSP_H_
#define HARDWARE_C28X_BSP_H_

#include "F28x_Project.h"
#include <app_cfg.h>
#include <ucos_ii.h>
#include <cpu_core.h>
#include <lib_def.h>
#include "DronePara.h"
#include "task.h"
//init
void C28x_BSP_Init(void);
void C28x_BSP_Tick_Init(void);
void C28x_BSP_Led_Init(void);
void C28x_BSP_Spi_Init(void);
void C28x_BSP_Epwm_Init(void);
void C28x_BSP_Scia_Init(void);
void C28x_BSP_Scib_Init(void);
void C28x_BSP_Scic_Init(void);
void C28x_BSP_ADC_Init(void);
void C28x_BSP_FLASH_Init(void);
void C28x_BSP_eCAP_Init(void);


//Function function
void scia_msg(unsigned char msg);
void scib_msg(unsigned char * msg);
void scic_msg(unsigned char * msg);
void scic_Xmsg(unsigned char msg);

//External variables
extern OS_EVENT ProcessPCData_proc;//信号量
extern Uint16 RecivePCData[16];
extern OS_EVENT ProcessVisionData_proc;//信号量
extern Uint16 ReciveVisionData[16];
extern OS_EVENT ProcessReserveData_proc;//信号量
extern Uint16 ReciveReserveData[16];


// Function function
void spi_xmit(Uint16 a);
#endif /* HARDWARE_C28X_BSP_H_ */
