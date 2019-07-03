/*
 * DronePara.h
 *
 *  Created on: 2018年4月17日
 *      Author: Xiluna Tech
 */

#ifndef PARAMETER_DRONEPARA_H_
#define PARAMETER_DRONEPARA_H_

#include "F2837xD_device.h"

typedef enum
{
  Report_SET      = 0x01,
  Report_RESET    = 0x00,
}DroneReportSW_TypeDef;

typedef enum{
  Drone_Mode_None=0,
  Drone_Mode_RatePitch, //姿态内环
  Drone_Mode_RateRoll,
  Drone_Mode_Pitch,     //姿态外环
  Drone_Mode_Roll,
  Drone_Mode_4Axis,     //四轴飞行
}DroneFlightMode_TypeDef;

typedef enum{
    Drone_Off  = 0x00,//关闭电机
    Drone_On   = 0x01,//起飞
    Drone_Land = 0x02,//降落
}DroneFlightOnOff_TypeDef;

typedef struct{
    DroneFlightOnOff_TypeDef OnOff;
    DroneFlightMode_TypeDef DroneMode;
    DroneReportSW_TypeDef ReportSW;
    int landFlag;
    _Bool LaunchFlag;
    _Bool ControlStart;
}DroneFlightControl;

typedef enum{
    Data_Headmode = 0,
    Data_Headfree = 1,
    Data_Point = 2,
    Data_Flow = 3,
    Data_Follow = 4,
    Data_PointAngle = 5,
    Data_MultiBlock = 6,
    Data_SpeedSetimate = 7,
}FlyMode;

typedef struct{
    //滤波时间
    float Merge_t;
    //参数
    float Q_Position;
    float Q_Velocity;
    float Q_Bias;
    float R_Position;
    //状态
    float Axis_Pos;
    float Axis_Vel;
    float Axis_Bias;
    float Axis_Err;
    float AxisPCt_0;
    float AxisPCt_1;
    float AxisPCt_2;
    float AxisE;
    char AxisC_0;
    float AxisK_0;
    float AxisK_1;
    float AxisK_2;
    float Axist_0;
    float Axist_1;
    float Axist_2;
    float AxisPdot[9];
    float AxisPP[3][3];
}KalmanFilter;

typedef struct{
    float Pitch;
    float Roll;
    float Yaw;
    float RateRoll;
    float RatePitch;
    float RateYaw;
    float Height;
    float VelHeight;
    float AccHeight;
    float BlackLineV;
    float BlackLineYaw;
    float FlowVel_X;
    float FlowVel_Y;
}DroneTargetInfo;

typedef struct{
    float fixedErroPitch;
    float fixedErroRoll;
}DroneErrangle;


typedef struct{
    //状态
    float error;
    float lasterror;
    float differential;
    float differentialFliter;
    float pOut;
    float iOut;
    float dOut;
    float value;
}PIDOut;

typedef struct{
    //参数
    float Kp;
    float Ki;
    float Kd;
}PID;

typedef struct
{
    PID Pitch;
    PID Roll;
    PID Yaw;

    PID PitchRate;
    PID RollRate;
    PID YawRate;

    PID PosX;
    PID PosY;
    PID PosZ;

    PID VelX;
    PID VelY;
    PID VelZ;

    PID AccZ;

    PID FlowX;
    PID FlowY;
    PID FlowVelX;
    PID FlowVelY;

}PIDPara;

typedef enum
{
    Auto       = 0x01 ,   //自稳模式
    AltHold    = 0x02 ,     //定高
    PosHold    = 0x03 ,   //GPS定点
    RTL        = 0x04 ,   //返航模式
    NoGPS      = 0x05 ,   //无GPS定位模式
}FlightMode;

typedef enum
{
    Heading       = 0x01 ,   //有头模式
    Headless      = 0x02 ,     //无头模式
}HeadingMode;

typedef enum
{
    On       = 0x01 ,  //开
    Off      = 0x02 ,  //关
}Switch;


typedef struct{
    float XaxisPos;
    float YaxisPos;
    float ZaxisPos;
    float Navigation;
}RemoteControl;


/*遥控器数据与控制模式*/
typedef struct
{
    FlightMode FlightControlMode; //遥控飞行模式
    HeadingMode FlightHeadingMode ; //遥控飞行有头无头模式设置
    FlightMode CH5_Mode1;   //第五通道的模式1
    FlightMode CH5_Mode2;   //第五通道的模式2
    FlightMode CH5_Mode3;   //第五通道的模式3
    HeadingMode CH6_Mode1;   //第六通道的模式1
    HeadingMode CH6_Mode2;   //第六通道的模式2
    Switch CH7_Mode1;   //第七通道的模式1
    Switch CH7_Mode2;   //第七通道的模式2
    int SafeThrottle;   //遥控器失控保护油门
    unsigned char TakeOff_Flag; //起飞标志位
}Remote_Control;

/*遥控信息*/
typedef struct
{
    unsigned int CH1;// 通道1 副翼
    unsigned int CH2;// 通道2 升降舵
    unsigned int CH3;// 通道3 油门
    unsigned int CH4;// 通道4 方向舵
    unsigned int CH5;// 通道5 飞行模式
    unsigned int CH6;// 通道6
    unsigned int CH7;// 通道7
    unsigned int CH8;// 通道8

    unsigned int CH1_Max ,CH1_Min ,CH1_Mid ; // 通道1 最大最小和回中值
    unsigned int CH2_Max ,CH2_Min ,CH2_Mid ; // 通道2 最大最小和回中值
    unsigned int CH3_Max ,CH3_Min ,CH3_Mid ; // 通道3 最大最小和回中值
    unsigned int CH4_Max ,CH4_Min ,CH4_Mid ; // 通道4 最大最小和回中值
    unsigned int CH5_Max ,CH5_Min ,CH5_Mid ; // 通道5 最大最小和回中值
    unsigned int CH6_Max ,CH6_Min ,CH6_Mid ; // 通道6 最大最小和回中值
    unsigned int CH7_Max ,CH7_Min ,CH7_Mid ; // 通道7 最大最小和回中值
    unsigned int CH8_Max ,CH8_Min ,CH8_Mid ; // 通道8 最大最小和回中值
}Controller;

typedef struct{
    float PitchThrust;
    float RollThrust;
    float YawThrust;
    float HeightThrust;
    float BasicThrust;
}Thrust;

typedef struct
{
    unsigned int M1;
    unsigned int M2;
    unsigned int M3;
    unsigned int M4;
}Throttle;

/*校准数据*/
typedef struct
{
    _Bool MagOffseting;
    Uint16 MagX;
    Uint16 MagY;
    Uint16 MagZ;
    float GyroX;
    float GyroY;
    float GyroZ;
    float AccX;
    float AccY;
    float AccZ;
    float AccXScale;
    float AccYScale;
    float AccZScale;
}OffsetInfo;

typedef enum
{
    Lift     = 0x01 ,   //升降
    Hover    = 0x02 ,     //悬停
}Remote_Control_Status;

typedef enum
{
    Sonar       = 0x01 ,   //声呐
//  Barometer   = 0x02 ,     //气压计
}Height_Data_Switching;


/*无人机实时信息*/
typedef struct
{
    float Pitch;
    float Roll;
    float Yaw;
    float HomeYaw;
    float ratePitch;
    float HeadfreeYaw;    //无头模式下yaw角度
    float Headfreezeta;   //无头模式旋转Zeta角
    float rateRoll;
    float rateYaw;
    float accXaxis;
    float accYaxis;
    float accZaxis;
    float EstiX;
    float EstiY;
    float EstiZ;
    float Height;
    float Height_V;
    float Barometer;      //气压计数据
    float Barometer_V;    //气压计速度
    float FlowX;
    float FlowY;
    float FlowX_V;
    float FlowY_V;
    float PointX;
    float PointY;
    float PointX_V;
    float PointY_V;
    float batteryVoltage;
    float AccX;
    float AccY;
    float AccZ;
    float GyroX;
    float GyroY;
    float GyroZ;
    float MagX;
    float MagY;
    float MagZ;
    int lowPowerFlag;
    float CpuTick;
    unsigned char AllowLanding;  // 遥控器控制降落标志
    Remote_Control_Status  controlStatus;  //专业遥控器控制状态
    Height_Data_Switching  heightDataSwitching;  //高度数据来源切换
    char VisionFlag;
}DroneRTInfo;

typedef struct{
    float US100_Zaxis;
    float MS5611_Zaxis;
    float Raspberry_Xaxis;
    float Raspberry_Yaxis;
    float FlowVelX;
    float FlowVelY;
    float VIO_Xaxis;
    float VIO_Yaxis;
    float VIO_Zaxis;
    float VectX;
    float VectY;
    float VectZ;
}SensorData;

//float 联合体
typedef union{
        float fv;
        Uint16 sv[2];
}float_union;

//flash 保存
typedef struct {
    Uint16 isGood;
    PIDPara pidPara;
    OffsetInfo Offset_Data;
    Controller ControlData;
}FlashData;


#endif /* PARAMETER_DRONEPARA_H_ */
