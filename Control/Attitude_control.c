/*
 * Attitude_control.c
 *
 *  Created on: 2018骞�4鏈�23鏃�
 *      Author: Xiluna Tech
 */
#include "Attitude_control.h"


void Attitude_control(float PitchCalibration,float RollCalibration)
{
    static unsigned char YawHover= 0; //航向标志位
    static  float yawErro =0;
    float pitchErro = (Target_Info.Pitch-(RT_Info.Pitch-PitchCalibration));
    OriginalPitch.value = PID_ParaInfo.Pitch.Kp * pitchErro;
    if(FlightControl.DroneMode!=Drone_Mode_RatePitch)
    {
        UAVThrust.PitchThrust = PID_Control(&PID_ParaInfo.PitchRate,&OriginalPitchRate,OriginalPitch.value,
                                                                RT_Info.ratePitch,0.005,80,lowpass_filter);
    }
    else
    {
        UAVThrust.PitchThrust = PID_Control(&PID_ParaInfo.PitchRate,&OriginalPitchRate,Target_Info.RatePitch/100,
                                                                RT_Info.ratePitch,0.005,80,lowpass_filter);
    }

    float rollErro = (Target_Info.Roll-(RT_Info.Roll-RollCalibration));
    OriginalRoll.value = PID_ParaInfo.Roll.Kp * rollErro;
    if(FlightControl.DroneMode!=Drone_Mode_RateRoll)
    {
        UAVThrust.RollThrust = PID_Control(&PID_ParaInfo.RollRate,&OriginalRollRate,OriginalRoll.value,
                                                                  RT_Info.rateRoll,0.005,80,lowpass_filter);
    }
    else
    {
        UAVThrust.RollThrust = PID_Control(&PID_ParaInfo.RollRate,&OriginalRollRate,Target_Info.RateRoll/100,
                                                                   RT_Info.rateRoll,0.005,80,lowpass_filter);
    }

    if(RockerControl.Navigation == 0)
    {
        if(YawHover ==1)
        {
            Target_Info.Yaw = RT_Info.Yaw;
            YawHover=0;
        }
        switch(Fly_Mode)
        {
        case Data_Headmode:
        case Data_Headfree:
        case Data_Point:
        case Data_Flow:
        case Data_Follow:
            if(Target_Info.Yaw - RT_Info.Yaw>=180)
            {
                yawErro=(Target_Info.Yaw - RT_Info.Yaw) - 360 ;
            }
            else if(Target_Info.Yaw - RT_Info.Yaw<-180)
            {
                yawErro=(Target_Info.Yaw - RT_Info.Yaw) + 360 ;
            }
            else
            {
                yawErro=(Target_Info.Yaw - RT_Info.Yaw);
            }
            break;
        case Data_PointAngle:
            if(RT_Info.Height < 0.35)
            {
                if(Target_Info.Yaw - RT_Info.Yaw>=180)
                {
                    yawErro=(Target_Info.Yaw - RT_Info.Yaw) - 360 ;
                }
                else if(Target_Info.Yaw - RT_Info.Yaw<-180)
                {
                    yawErro=(Target_Info.Yaw - RT_Info.Yaw) + 360 ;
                }
                else
                {
                    yawErro=(Target_Info.Yaw - RT_Info.Yaw);
                }
            }
            else
            {
                if(RT_Info.VisionFlag == 1)
                    yawErro = Target_Info.BlackLineYaw;
                else
                    if(Target_Info.Yaw - RT_Info.Yaw>=180)
                    {
                        yawErro=(Target_Info.Yaw - RT_Info.Yaw) - 360 ;
                    }
                    else if(Target_Info.Yaw - RT_Info.Yaw<-180)
                    {
                        yawErro=(Target_Info.Yaw - RT_Info.Yaw) + 360 ;
                    }
                    else
                    {
                        yawErro=(Target_Info.Yaw - RT_Info.Yaw);
                    }
            }

            break;
        case Data_MultiBlock:
            yawErro = Target_Info.BlackLineYaw;
            break;
        default:
            break;
        }

        // 倾角分离，使用衰减算法来保持Pitch和Roll在大航向偏差控制下的稳定性   0.7为衰减系数
//        yawErro = 0.7f * yawErro  * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);
        OriginalYaw.value = PID_ParaInfo.Yaw.Kp * yawErro;
        UAVThrust.YawThrust = Limits_data (PID_Control(&PID_ParaInfo.YawRate,&OriginalYaw, OriginalYaw.value ,RT_Info.rateYaw,0.005,80,lowpass_filter),100,-100);
    }
    else
    {
        // 倾角分离，使用衰减算法来保持Pitch和Roll在大航向偏差控制下的稳定性   0.8为衰减系数
        float GyroZErro =  RockerControl.Navigation  * cos(RT_Info.Pitch * 0.0174f) * cos(RT_Info.Roll * 0.0174f);
        UAVThrust.YawThrust = Limits_data (PID_Control(&PID_ParaInfo.YawRate,&OriginalYawRate, GyroZErro,RT_Info.rateYaw,0.005,80,lowpass_filter),100,-100);
        YawHover =1;
    }

    Calculate_Thrust();
}

void Throttle_Angle_Compensate(void)//油门倾角补偿
{
  float CosPitch_CosRoll=ABS(cos(RT_Info.Pitch/180*PI)*cos(RT_Info.Roll/180*PI));
  float Temp=0;
  if(CosPitch_CosRoll>=0.999999f)  CosPitch_CosRoll=0.999999f;
  if(CosPitch_CosRoll<=0.000001f)  CosPitch_CosRoll=0.000001f;
  if(CosPitch_CosRoll<=0.50f)  CosPitch_CosRoll=0.50f;//Pitch,Roll约等于30度
  if(UAVThrust.HeightThrust != 0)//高度油门有调节
  {
      Temp=(uint16_t)(MAX(ABS(100*RT_Info.Pitch),ABS(100*RT_Info.Roll)));
      Temp=Limits_data(9000-Temp,3000,0)/(3000*CosPitch_CosRoll);
      UAVThrust.BasicThrust= 530*Temp; //油门倾角补偿
      UAVThrust.BasicThrust=(uint16_t)(Limits_data(UAVThrust.BasicThrust,570,530));
  }
  else UAVThrust.BasicThrust= 530;
}

void Calculate_Thrust(){
    if(FlightControl.DroneMode==Drone_Mode_4Axis)
    {
//        Throttle_Angle_Compensate();//油门倾角补偿
        Throttle_Info.M1 =  - UAVThrust.PitchThrust * 14.1 / RT_Info.batteryVoltage
                            - UAVThrust.RollThrust * 14.1 / RT_Info.batteryVoltage
                            - UAVThrust.YawThrust * 15.0 / RT_Info.batteryVoltage
                            + UAVThrust.HeightThrust * 15.3 / RT_Info.batteryVoltage;

        Throttle_Info.M2 =  + UAVThrust.PitchThrust * 14.1 / RT_Info.batteryVoltage
                            - UAVThrust.RollThrust * 14.1 / RT_Info.batteryVoltage
                            + UAVThrust.YawThrust * 15.0 / RT_Info.batteryVoltage
                            + UAVThrust.HeightThrust * 15.3 / RT_Info.batteryVoltage;

        Throttle_Info.M3 =  + UAVThrust.PitchThrust* 14.1 / RT_Info.batteryVoltage
                            + UAVThrust.RollThrust* 14.1 / RT_Info.batteryVoltage
                            - UAVThrust.YawThrust * 15.0 / RT_Info.batteryVoltage
                            + UAVThrust.HeightThrust * 15.3 / RT_Info.batteryVoltage;

        Throttle_Info.M4 =  - UAVThrust.PitchThrust * 14.1 / RT_Info.batteryVoltage
                            + UAVThrust.RollThrust * 14.1 / RT_Info.batteryVoltage
                            + UAVThrust.YawThrust * 15.0 / RT_Info.batteryVoltage
                            + UAVThrust.HeightThrust * 15.3 / RT_Info.batteryVoltage;
    }
    else if(FlightControl.DroneMode==Drone_Mode_Pitch || FlightControl.DroneMode==Drone_Mode_RatePitch)
    {
        Throttle_Info.M1 = - UAVThrust.PitchThrust + UAVThrust.BasicThrust;
        Throttle_Info.M2 = + UAVThrust.PitchThrust + UAVThrust.BasicThrust;
        Throttle_Info.M3 = + UAVThrust.PitchThrust + UAVThrust.BasicThrust;
        Throttle_Info.M4 = - UAVThrust.PitchThrust + UAVThrust.BasicThrust;
    }
    else if(FlightControl.DroneMode==Drone_Mode_Roll || FlightControl.DroneMode==Drone_Mode_RateRoll)
    {
        Throttle_Info.M1 = - UAVThrust.RollThrust + UAVThrust.BasicThrust;
        Throttle_Info.M2 = - UAVThrust.RollThrust + UAVThrust.BasicThrust;
        Throttle_Info.M3 = + UAVThrust.RollThrust + UAVThrust.BasicThrust;
        Throttle_Info.M4 = + UAVThrust.RollThrust + UAVThrust.BasicThrust;
    }

    if(Throttle_Info.M1 > 900)  Throttle_Info.M1=900;
    if(Throttle_Info.M2 > 900)  Throttle_Info.M2=900;
    if(Throttle_Info.M3 > 900)  Throttle_Info.M3=900;
    if(Throttle_Info.M4 > 900)  Throttle_Info.M4=900;

    if(Throttle_Info.M1 < 50)  Throttle_Info.M1=50;
    if(Throttle_Info.M2 < 50)  Throttle_Info.M2=50;
    if(Throttle_Info.M3 < 50)  Throttle_Info.M3=50;
    if(Throttle_Info.M4 < 50)  Throttle_Info.M4=50;

    PWM_OUTPUT(Throttle_Info.M1,Throttle_Info.M2,Throttle_Info.M3,Throttle_Info.M4);
}

void PWM_OUTPUT(unsigned int Motor1,
                unsigned int Motor2,
                unsigned int Motor3,
                unsigned int Motor4){
    Motor1+=1000;
    Motor2+=1000;
    Motor3+=1000;
    Motor4+=1000;

    if(RT_Info.lowPowerFlag==1){
        EPwm2Regs.CMPA.bit.CMPA = (unsigned int)(6.25*1000);
        EPwm2Regs.CMPB.bit.CMPB = (unsigned int)(6.25*1000);
        EPwm6Regs.CMPA.bit.CMPA = (unsigned int)(6.25*1000);
        EPwm6Regs.CMPB.bit.CMPB = (unsigned int)(6.25*1000);
     }
     else{
          EPwm2Regs.CMPA.bit.CMPA = (unsigned int)(6.25*Motor1);
          EPwm2Regs.CMPB.bit.CMPB = (unsigned int)(6.25*Motor2);
          EPwm6Regs.CMPA.bit.CMPA = (unsigned int)(6.25*Motor3);
          EPwm6Regs.CMPB.bit.CMPB = (unsigned int)(6.25*Motor4);
     }
}

void Safety_Protection(void){
    if(RT_Info.Pitch >=40 || RT_Info.Pitch <= -40 || RT_Info.Roll >= 40 || RT_Info.Roll <= -40){
        PWM_OUTPUT(0,0,0,0);
        while(1);
    }

}
