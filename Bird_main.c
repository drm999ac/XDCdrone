/******************* (C) COPYRIGHT 2018- Xiluna Tech ************************
 * 作者    ：Xiluna Tech
 * 文件名  ：Bird_main.c
 * 描述    ：High performance UAV
 * 官网    ：http://xiluna.com/
 * 公众号  ：XilunaTech
 * gitlab ：git.xiluna.com
*****************************************************************************/
#include "task.h"

//全局变量
DroneRTInfo RT_Info;                                                                     //四旋翼实时数据
DroneTargetInfo Target_Info;                                                             //四旋翼目标全局变量
DroneErrangle Errangle_Info;                                                             //四旋翼平地校准数据
DroneFlightControl FlightControl;                                                        //四旋翼状态变量
RemoteControl RockerControl;                                                             //四旋翼摇杆变量
Remote_Control  Flight_Remote_Control;                                                   //遥控器飞行设置
Controller Control_Info;                                                                 //遥控器控制全局变量
SensorData Sensor_Info;                                                                  //四旋翼定位传感器数据
FlyMode Fly_Mode;                                                                        //四旋翼飞行模式
OffsetInfo OffsetData;                                                                   //磁偏量
Thrust UAVThrust;                                                                        //飞行器扭力计算
Throttle Throttle_Info;                                                                  //飞行器扭力输出
//控制参数
PIDOut OriginalPitch,OriginalRoll,OriginalYaw,OriginalPosX,OriginalPosY,OriginalPosZ,
                    OriginalPitchRate,OriginalRollRate,OriginalYawRate,OriginalVelX,OriginalVelY,OriginalVelZ,
                        OriginalFlowX,OriginalFlowY,OriginalFlowVelX,OriginalFlowVelY,OriginalAccZ;
PIDPara PID_ParaInfo;
//融合参数
KalmanFilter XAxis,YAxis,ZAxis,Barometer;                                                                             //卡尔曼滤波融合参数

/*
*********************************************************************************************************
*                                         LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
/* Start Task's stack.                               */
CPU_STK_SIZE  App_TaskStartStk[APP_CFG_TASK_STK_SIZE];
/* IMU Task's stack.                                 */
CPU_STK_SIZE  App_TaskIMUStk[APP_CFG_TASK_STK_SIZE];
/* Attitude Task's stack.                            */
CPU_STK_SIZE  App_TaskAttitudeStk[APP_CFG_TASK_STK_SIZE];
/* Position Task's stack.                            */
CPU_STK_SIZE  App_TaskPositionStk[APP_CFG_TASK_STK_SIZE];
/* Combine  Task's stack.                            */
CPU_STK_SIZE  App_TaskCombineStk[APP_CFG_TASK_STK_SIZE];
/* ProcessVisionData Task's stack.                   */
CPU_STK_SIZE  App_TaskProcessVisionDataStk[APP_CFG_TASK_STK_SIZE];
/* ProcessReserveData Task's stack.                  */
CPU_STK_SIZE  App_TaskMS5611Stk[APP_CFG_TASK_STK_SIZE];
/* ProcessPCData Task's stack.                       */
CPU_STK_SIZE  App_TaskProcessPCDataStk[APP_CFG_TASK_STK_SIZE];
/* DataToPC Task's stack.                            */
CPU_STK_SIZE  App_TaskDataToPCStk[APP_CFG_TASK_STK_SIZE];
/* Battery Task's stack.                             */
CPU_STK_SIZE  App_TaskBatteryStk[APP_CFG_TASK_STK_SIZE];
/* LED Task's stack.                                 */
CPU_STK_SIZE  App_TaskLEDStk[APP_CFG_TASK_STK_SIZE];


/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
/* Start Task */
static  void  App_TaskStart(void  *p_arg);
/* IMU Task */
static  void  App_TaskIMU(void  *p_arg);
/* Attitude Task */
static  void  App_TaskAttitude(void  *p_arg);
/* Position Task */
static  void  App_TaskPosition(void  *p_arg);
/* Combine Task */
static  void  App_TaskCombine(void  *p_arg);
/* ProcessVisionData Task */
static  void  App_TaskProcessVisionData(void  *p_arg);
/* ProcessReserveData Task */
static  void  App_TaskMS5611(void  *p_arg);
/* ProcessPCData Task */
static  void  App_TaskProcessPCData(void  *p_arg);
/* DataToPC Task */
static  void  App_TaskDataToPC(void  *p_arg);
/* ADC Task */
static  void  App_TaskBattery(void *p_arg);
/* LED Task */
static  void  App_TaskLED(void  *p_arg);

int main(void){
/* Initialize the CPU and Board.                        */
    C28x_CPU_Init();
/* Initialize the BSP.                                  */
    C28x_BSP_Init();
/* Initialize the AHRS_HardWare.                        */
    AHRS_HardWareinit();
/* Initialize the KalmanFilter Para.                    */
    KalmanFilter_Init(&XAxis,&YAxis,&ZAxis,&Barometer);
/* Load Control Para.                                   */
    Load_ParaConfig();
/* Initialize "uC/OS-II, The Real-Time Kernel".         */
    OSInit();
/* Create the Start task.                               */
    OSTaskCreateExt(App_TaskStart,
                    (void    *)0,
                    (CPU_STK *)&App_TaskStartStk[0],
                    (INT8U    )APP_CFG_TASK_START_PRIO,
                    (INT16U   )APP_CFG_TASK_START_PRIO,
                    (CPU_STK *)&App_TaskStartStk[APP_CFG_TASK_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
/* Start multitasking (i.e. give control to uC/OS-II).  */
    OSStart();
/* Should never get here.   */
    while(DEF_TRUE){
        ;
    }
}

/*
*********************************************************************************************************
*                                            App_TaskStart()
*
* Description : First task to be scheduled. Creates the application tasks.
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : None.
*********************************************************************************************************
*/

static  void  App_TaskStart (void *p_arg)
{
    OS_CPU_SR  cpu_sr = 0;
    /* Prevent compiler warning for not using 'p_arg'    */
    (void)&p_arg;
    C28x_BSP_Tick_Init();
    /* Start the Ticker.                                 */
    OS_ENTER_CRITICAL();
    /* IMU Task.                                         */
    OSTaskCreateExt(App_TaskIMU,
                    (void    *)0,
                    (CPU_STK *)&App_TaskIMUStk[0],
                    (INT8U    )APP_CFG_TASK_IMU_PRIO,
                    (INT16U   )APP_CFG_TASK_IMU_PRIO,
                    (CPU_STK *)&App_TaskIMUStk[APP_CFG_TASK_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    /* Attitude Task.                                    */
    OSTaskCreateExt(App_TaskAttitude,
                   (void    *)0,
                   (CPU_STK *)&App_TaskAttitudeStk[0],
                   (INT8U    )APP_CFG_TASK_Attitude_PRIO,
                   (INT16U   )APP_CFG_TASK_Attitude_PRIO,
                   (CPU_STK *)&App_TaskAttitudeStk[APP_CFG_TASK_STK_SIZE - 1u],
                   (INT32U   )APP_CFG_TASK_STK_SIZE,
                   (void    *)0,
                   (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    /* Position Task.                                    */
    OSTaskCreateExt(App_TaskPosition,
                   (void    *)0,
                   (CPU_STK *)&App_TaskPositionStk[0],
                   (INT8U    )APP_CFG_TASK_Position_PRIO,
                   (INT16U   )APP_CFG_TASK_Position_PRIO,
                   (CPU_STK *)&App_TaskPositionStk[APP_CFG_TASK_STK_SIZE - 1u],
                   (INT32U   )APP_CFG_TASK_STK_SIZE,
                   (void    *)0,
                   (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    /* Combine Task.                                    */
    OSTaskCreateExt(App_TaskCombine,
                   (void    *)0,
                   (CPU_STK *)&App_TaskCombineStk[0],
                   (INT8U    )APP_CFG_TASK_Combine_PRIO,
                   (INT16U   )APP_CFG_TASK_Combine_PRIO,
                   (CPU_STK *)&App_TaskCombineStk[APP_CFG_TASK_STK_SIZE - 1u],
                   (INT32U   )APP_CFG_TASK_STK_SIZE,
                   (void    *)0,
                   (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    /* ProcessVisionData Task.                           */
    OSTaskCreateExt(App_TaskProcessVisionData,
                   (void    *)0,
                   (CPU_STK *)&App_TaskProcessVisionDataStk[0],
                   (INT8U    )APP_CFG_TASK_ProcessVisionData_PRIO,
                   (INT16U   )APP_CFG_TASK_ProcessVisionData_PRIO,
                   (CPU_STK *)&App_TaskProcessVisionDataStk[APP_CFG_TASK_STK_SIZE - 1u],
                   (INT32U   )APP_CFG_TASK_STK_SIZE,
                   (void    *)0,
                   (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    /* MS5611 Task.                           */
    OSTaskCreateExt(App_TaskMS5611,
                  (void    *)0,
                  (CPU_STK *)&App_TaskMS5611Stk[0],
                  (INT8U    )APP_CFG_TASK_MS5611_PRIO,
                  (INT16U   )APP_CFG_TASK_MS5611_PRIO,
                  (CPU_STK *)&App_TaskMS5611Stk[APP_CFG_TASK_STK_SIZE - 1u],
                  (INT32U   )APP_CFG_TASK_STK_SIZE,
                  (void    *)0,
                  (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    /* ProcessPCData Task.                                */
    OSTaskCreateExt(App_TaskProcessPCData,
                   (void    *)0,
                   (CPU_STK *)&App_TaskProcessPCDataStk[0],
                   (INT8U    )APP_CFG_TASK_ProcessPCData_PRIO,
                   (INT16U   )APP_CFG_TASK_ProcessPCData_PRIO,
                   (CPU_STK *)&App_TaskProcessPCDataStk[APP_CFG_TASK_STK_SIZE - 1u],
                   (INT32U   )APP_CFG_TASK_STK_SIZE,
                   (void    *)0,
                   (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    /* DataToPC Task.                                    */
    OSTaskCreateExt(App_TaskDataToPC,
                    (void    *)0,
                    (CPU_STK *)&App_TaskDataToPCStk[0],
                    (INT8U    )APP_CFG_TASK_DataToPC_PRIO,
                    (INT16U   )APP_CFG_TASK_DataToPC_PRIO,
                    (CPU_STK *)&App_TaskDataToPCStk[APP_CFG_TASK_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    /* Battery Task.                                    */
    OSTaskCreateExt(App_TaskBattery,
                    (void    *)0,
                    (CPU_STK *)&App_TaskBatteryStk[0],
                    (INT8U    )APP_CFG_TASK_Battery_PRIO,
                    (INT16U   )APP_CFG_TASK_Battery_PRIO,
                    (CPU_STK *)&App_TaskBatteryStk[APP_CFG_TASK_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    /* LED Task.                                        */
    OSTaskCreateExt(App_TaskLED,
                    (void    *)0,
                    (CPU_STK *)&App_TaskLEDStk[0],
                    (INT8U    )APP_CFG_TASK_LED_PRIO,
                    (INT16U   )APP_CFG_TASK_LED_PRIO,
                    (CPU_STK *)&App_TaskLEDStk[APP_CFG_TASK_STK_SIZE - 1u],
                    (INT32U   )APP_CFG_TASK_STK_SIZE,
                    (void    *)0,
                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    OSTaskSuspend(APP_CFG_TASK_START_PRIO); //挂起起始任务.
    OS_EXIT_CRITICAL();
}
/*
*********************************************************************************************************
*                                            App_TaskIMU
*
* Description : imu task
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/
static  void  App_TaskIMU (void *p_arg){
   /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;
   /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        IMU_getInfo();
//        OSTimeDly(2);
        OSTimeDlyHMSM(0,0,0,2);
    }
}
/*
*********************************************************************************************************
*                                            App_TaskAttitude
*
* Description : Attitude task
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/
static  void  App_TaskAttitude (void *p_arg){
   /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;
   /* Task body, always written as an infinite loop.       */
   Uint16 Preparationtime = 0;
   float PreparationPitch = 0;
   float PreparationRoll = 0;
//   float PreparationYaw = 0;
   _Bool PreparationFlag = true;
   FlightControl.ControlStart = false;
    while (DEF_TRUE) {
        if(FlightControl.OnOff == Drone_On ){//&& RT_Info.Height >= 0.01f){
            if(FlightControl.DroneMode == Drone_Mode_4Axis){
                if(Preparationtime < 250){
                    Preparationtime ++;
                    PreparationPitch += RT_Info.Pitch;
                    PreparationRoll += RT_Info.Roll;
                    PWM_OUTPUT(300,300,300,300);
                }
                else{
                    /*起飞平地自校准*/
                    if(PreparationFlag){
                        PreparationPitch /= 250;
                        PreparationRoll /= 250;
                        Target_Info.Yaw = RT_Info.Yaw;
                        RT_Info.FlowX =0 ;
                        RT_Info.FlowY =0 ;
                        PreparationFlag = false;
                        FlightControl.ControlStart = true;
                    }
                    if(FlightControl.ControlStart){
                        Attitude_control(PreparationPitch,PreparationRoll);
                        Safety_Protection();     //侧倾保护
                    }
               }
            }
            else{
                Attitude_control(0,0);
            }
        }
        else{
            PreparationFlag = true;
            PreparationPitch = 0;
            PreparationRoll = 0;
            Preparationtime = 0;
            OriginalPitchRate.iOut = 0;
            OriginalRollRate.iOut = 0;
            OriginalYaw.iOut = 0;
            OriginalVelZ.iOut = 0;
            OriginalVelX.iOut = 0;
            OriginalVelY.iOut = 0;
            OriginalAccZ.iOut = 0;
            OriginalFlowVelX.iOut =0;
            OriginalFlowVelY.iOut =0;
            Target_Info.Height = 0.90f; //恢复初始的默认目标高度
            Target_Info.Pitch = 0.0f; //恢复初始的默认目标俯仰
            Target_Info.Roll = 0.0f; //恢复初始的默认目标翻滚
            Target_Info.FlowVel_X = 0.39f;
            FlightControl.LaunchFlag = true; //第一次起飞标志位
            FlightControl.ControlStart = false;
            PWM_OUTPUT(0,0,0,0);
        }
//        OSTimeDly(5);
        OSTimeDlyHMSM(0,0,0,5);
    }
}

/*
*********************************************************************************************************
*                                            App_TaskPosition
*
* Description : Position task
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/
static  void  App_TaskPosition (void *p_arg){
   /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;
   /* Task body, always written as an infinite loop.       */
   float Climbing = 0.008f;
   float Declining = 0.002f;
   Target_Info.Height = 0.90f;
    while (DEF_TRUE) {
        if(FlightControl.DroneMode == Drone_Mode_4Axis && FlightControl.OnOff==Drone_On && FlightControl.ControlStart == true){
            Position_control(Fly_Mode,Climbing,Declining);
        }
//        OSTimeDly(5);
        OSTimeDlyHMSM(0,0,0,5);
    }
}


/*
*********************************************************************************************************
*                                            App_TaskCombine
*
* Description : Combine task
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/
static  void  App_TaskCombine (void *p_arg){
   /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;
   static   float FlowX_Array[60];
   static   float FlowY_Array[60];
   /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        /* 超声波数据的卡尔曼滤波融合 */
        POS_KalmanFilter(&ZAxis,Sensor_Info.US100_Zaxis,RT_Info.accZaxis);
        RT_Info.Height = ZAxis.Axis_Pos;
        RT_Info.Height_V = ZAxis.Axis_Vel;


//        POS_KalmanFilter(&Barometer,Sensor_Info.MS5611_Zaxis,RT_Info.accZaxis);
//        RT_Info.Height = Barometer.Axis_Pos;
//        RT_Info.Height_V = Barometer.Axis_Vel;

        /* 物体追踪的位置数据卡尔曼融合 */
        if(Fly_Mode == Data_Point )
        {
            /*地理坐标系的加速度X正轴  对应 相机的X正轴数据 */
            POS_KalmanFilter(&XAxis,Sensor_Info.Raspberry_Xaxis/100,RT_Info.AccX);
            RT_Info.PointX = XAxis.Axis_Pos;
            RT_Info.PointX_V = XAxis.Axis_Vel;

            /*地理坐标系的加速度Y负轴  对应 相机的Y正轴数据 */
            POS_KalmanFilter(&YAxis,Sensor_Info.Raspberry_Yaxis/100,-RT_Info.AccY);
            RT_Info.PointY = YAxis.Axis_Pos;
            RT_Info.PointY_V = YAxis.Axis_Vel;
        }
        else if(Fly_Mode == Data_Flow)
        {
            OpticalFlow_Estimation(Sensor_Info.FlowVelX /100,Sensor_Info.FlowVelY /100,RT_Info.AccX,-RT_Info.AccY);
            RT_Info.FlowX = Average_Filter(RT_Info.FlowX_V * 0.005f,30,FlowX_Array)  * 30 ;
            RT_Info.FlowY = Average_Filter(RT_Info.FlowY_V * 0.005f,30,FlowY_Array)  * 30 ;

//            RT_Info.FlowX += RT_Info.FlowX_V * 0.08f;
//            RT_Info.FlowY += RT_Info.FlowY_V * 0.08f;

        }
        else if(Fly_Mode == Data_Follow)
        {
            /*地理坐标系的加速度Y负轴  对应 相机的Y正轴数据 */
            POS_KalmanFilter(&YAxis,Sensor_Info.Raspberry_Yaxis/100,-RT_Info.AccY);
            RT_Info.PointY = YAxis.Axis_Pos;
            RT_Info.PointY_V = YAxis.Axis_Vel;
            OpticalFlow_Estimation(Sensor_Info.FlowVelX /100,Sensor_Info.FlowVelY /100,RT_Info.AccX,-RT_Info.AccY);
            RT_Info.FlowY += RT_Info.FlowY_V * 0.005f;
        }
        else if(Fly_Mode == Data_PointAngle)
        {
            if(RT_Info.Height < 0.5)
            {
                /*地理坐标系的加速度X正轴  对应 相机的X正轴数据 */
                POS_KalmanFilter(&XAxis,Sensor_Info.Raspberry_Xaxis/100,RT_Info.AccX);
                RT_Info.PointX = XAxis.Axis_Pos;
                RT_Info.PointX_V = XAxis.Axis_Vel;

                /*地理坐标系的加速度Y负轴  对应 相机的Y正轴数据 */
                POS_KalmanFilter(&YAxis,Sensor_Info.Raspberry_Yaxis/100,-RT_Info.AccY);
                RT_Info.PointY = YAxis.Axis_Pos;
                RT_Info.PointY_V = YAxis.Axis_Vel;
            }
            else if(RT_Info.Height > 0.35)
            {
                if(RT_Info.VisionFlag == 0)
                {
                    /*地理坐标系的加速度X正轴  对应 相机的X正轴数据 */
                    POS_KalmanFilter(&XAxis,Sensor_Info.Raspberry_Xaxis/100,RT_Info.AccX);
                    RT_Info.PointX = XAxis.Axis_Pos;
                    RT_Info.PointX_V = XAxis.Axis_Vel;

                    /*地理坐标系的加速度Y负轴  对应 相机的Y正轴数据 */
                    POS_KalmanFilter(&YAxis,Sensor_Info.Raspberry_Yaxis/100,-RT_Info.AccY);
                    RT_Info.PointY = YAxis.Axis_Pos;
                    RT_Info.PointY_V = YAxis.Axis_Vel;
                }
                if(RT_Info.VisionFlag == 1)
                {
                    /*地理坐标系的加速度Y负轴  对应 相机的Y正轴数据 */
                    POS_KalmanFilter(&YAxis,Sensor_Info.Raspberry_Yaxis/100,-RT_Info.AccY);
                    RT_Info.PointY = YAxis.Axis_Pos;
                    RT_Info.PointY_V = YAxis.Axis_Vel;
                }
            }
        }
        else if(Fly_Mode == Data_MultiBlock)
        {
            POS_KalmanFilter(&XAxis,Sensor_Info.Raspberry_Xaxis/100,RT_Info.AccX);
            RT_Info.PointX = XAxis.Axis_Pos;
            RT_Info.PointX_V = XAxis.Axis_Vel;

            /*地理坐标系的加速度Y负轴  对应 相机的Y正轴数据 */
            POS_KalmanFilter(&YAxis,Sensor_Info.Raspberry_Yaxis/100,-RT_Info.AccY);
            RT_Info.PointY = YAxis.Axis_Pos;
            RT_Info.PointY_V = YAxis.Axis_Vel;

        }
        else if(Fly_Mode == Data_SpeedSetimate)
        {
            RT_Info.EstiX += RT_Info.AccX*0.002;
            RT_Info.EstiY += RT_Info.AccY*0.002;
            RT_Info.EstiZ += RT_Info.AccZ*0.002;

        }


//        OSTimeDly(5);
        OSTimeDlyHMSM(0,0,0,5);
    }
}


/*
*********************************************************************************************************
*                                            App_TaskProcessVisionData
*
* Description : ProcessVisionData task
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/
OS_EVENT ProcessVisionData_proc;//信号量
Uint16 ReciveVisionData[16];
static  void  App_TaskProcessVisionData (void *p_arg){
   /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;
   INT8U err;
   ProcessVisionData_proc = *OSSemCreate(1);
   /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        OSSemPend (&ProcessVisionData_proc,0,&err);
        Process_VisionData(ReciveVisionData);
    }
}
/*
*********************************************************************************************************
*                                            App_TaskProcessReserveData
*
* Description : ProcessReserveData task
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/
Uint16 ReciveReserveData[16];
static  void  App_TaskMS5611 (void *p_arg){
   /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;
//   INT8U err;

   /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        MS5611_ThreadNew();
        OSTimeDlyHMSM(0,0,0,20);
    }
}
/*
*********************************************************************************************************
*                                            App_TaskProcessPCData
*
* Description : ProcessPCData task
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/
OS_EVENT ProcessPCData_proc;//信号量
Uint16 RecivePCData[16];
static  void  App_TaskProcessPCData (void *p_arg){
   /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;
   INT8U err;
   ProcessPCData_proc = *OSSemCreate(1);
   /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        OSSemPend (&ProcessPCData_proc,0,&err);
        Process_PCData(RecivePCData);
    }
}

/*
*********************************************************************************************************
*                                            App_TaskDataToPC
*
* Description : DataToPC task
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/
static  void  App_TaskDataToPC (void *p_arg){
   /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;
   /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
        if(FlightControl.ReportSW==Report_SET){
            sendParaInfo();
            FlightControl.ReportSW=Report_RESET;
        }else{
            if(OffsetData.MagOffseting){
                /*上传校准数据*/
                sendRTOffset();
            }
            else{
                sendRTInfo(); //上传实时数据
//                sendGyroData();  //上传陀螺仪数据
//                sendAccData(); //上传加速度数据
//                sendMagData(); //上传磁力计数据
                sendPositionData(); //上传位置数据
                sendUserData();//上传自定义数据
            }
        }
//        OSTimeDly(100);

//        unsigned char bluetooth_bound[8]="AT+BAUD8";
//        scib_msg(bluetooth_bound);
        OSTimeDlyHMSM(0,0,0,200);
    }
}

/*
*********************************************************************************************************
*                                            App_TaskBattery
*
* Description : Battery task
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/

static  void  App_TaskBattery (void *p_arg){
    /* Prevent compiler warning for not using 'p_arg'       */
    (void)&p_arg;
    /* Task body, always written as an infinite loop.       */
    float Battery_Array[5];
    while (DEF_TRUE) {
        /* 获取滤波后的电压 */
        RT_Info.batteryVoltage = Average_Filter(Get_Battery(),5,Battery_Array);
        /* 起飞电压必须高于11.10V 才可以起飞 */
        if(RT_Info.batteryVoltage<11.10f && (FlightControl.OnOff != Drone_On))
        {
            RT_Info.lowPowerFlag = 1;
            //此处可加小灯闪烁表示电池电量低
        }
        else
        {
            /*飞行中如果电压低于10.30V则自动降落*/
            if(RT_Info.batteryVoltage < 10.30f)
            {
                FlightControl.landFlag = 1;
            }
            RT_Info.lowPowerFlag = 0;
        }
//        OSTimeDly(200);
        OSTimeDlyHMSM(0,0,0,200);
    }
}

/*
*********************************************************************************************************
*                                            App_TaskLED
*
* Description : led task
*
* Argument(s) : p_arg       the argument passed by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*********************************************************************************************************
*/

static  void  App_TaskLED (void *p_arg)
{
   /* Prevent compiler warning for not using 'p_arg'       */
   (void)&p_arg;
   /* Task body, always written as an infinite loop.       */
    while (DEF_TRUE) {
//        GPIO_WritePin(31,1-GPIO_ReadPin(31));
//        OSTimeDly(1000);
        OSTimeDlyHMSM(0,0,0,500);
    }
}

