/*
 * ProcessPCData.c
 *
 *  Created on: 2018年4月24日
 *      Author: Xiluna Tech
 */

#include "ProcessPCData.h"

float_union HexToFloat;

Acce_Unit acce_sample[6]={0};//三行6列，保存6面待矫正数据

Acce_Unit new_offset={
  0,0,0,
};
Acce_Unit new_scales={
  1.0,1.0,1.0,
};

float UnsignedcharToFloat(Uint16 *DataofPC,unsigned char sequence){
    HexToFloat.sv[0] = (((Uint16)DataofPC[sequence+1]) << 8 | DataofPC[sequence]);
    HexToFloat.sv[1] = (((Uint16)DataofPC[sequence+3]) << 8 | DataofPC[sequence+2]);
    return HexToFloat.fv;
}

void Process_PCData(Uint16 *PCData){
    /* 飞行控制指令  */
    if(PCData[0]==0x55 && PCData[1]==0xAA){
        /*启动关闭降落无人机*/
        if(PCData[2]==0xff  && RT_Info.lowPowerFlag==0){
            if(PCData[3]==0){
                FlightControl.OnOff = Drone_Off;
            }
            else if(PCData[3]==1){
                FlightControl.OnOff = Drone_On;
            }
            else if(PCData[3]==2){
                FlightControl.landFlag=1;
            }
        }
        /*平衡木实验外环参数*/
        else if(PCData[2]==0x01 && FlightControl.DroneMode!=Drone_Mode_4Axis )
        {
            /*  Target_Pitch */
            Target_Info.Pitch = UnsignedcharToFloat(PCData,3);
            /*  Target_Roll */
            Target_Info.Roll = UnsignedcharToFloat(PCData,7);
            /*  Target_Yaw */
            Target_Info.Yaw = UnsignedcharToFloat(PCData,11);
        }
        /*选择实验飞行模式同时配置相应的基础量*/
        else if(PCData[2]==0x02)
        {
            switch(PCData[3])
            {
                case 0:
                    FlightControl.DroneMode=Drone_Mode_None;
                    break;
                case 1:
                    FlightControl.DroneMode=Drone_Mode_RatePitch;
                    UAVThrust.BasicThrust=300;
                    break;
                case 2:
                    FlightControl.DroneMode=Drone_Mode_RateRoll;
                    UAVThrust.BasicThrust=300;
                    break;
                case 3:
                    FlightControl.DroneMode=Drone_Mode_Pitch;
                    UAVThrust.BasicThrust=300;
                    break;
                case 4:
                    FlightControl.DroneMode=Drone_Mode_Roll;
                    UAVThrust.BasicThrust=300;
                    break;
                case 5:
                    FlightControl.DroneMode=Drone_Mode_4Axis;
                    UAVThrust.BasicThrust=470;
                    break;
                default:
                    break;
            }
        }
        /*读取PID*/
        else if(PCData[2]==0x03)
        {
            FlightControl.ReportSW = Report_SET;
        }
        /*设置目标Rate*/
        else if(PCData[2]==0x04){
            Target_Info.RatePitch = UnsignedcharToFloat(PCData,3)/2;
            Target_Info.RateRoll = UnsignedcharToFloat(PCData,7)/2;
        }
        /*飞行器飞行过程中手柄的值(pitch roll height yaw)*/
        else if(PCData[2]==0x05){
            RockerControl.XaxisPos =  (float)( (int16)( ( (int16)PCData[4]<<8 ) + PCData[3] ) );
            RockerControl.YaxisPos = (float)( (int16)(( (int16)PCData[6]<<8 ) + PCData[5]) );
            RockerControl.Navigation = (float)( (int16)(( (int16)PCData[8]<<8 ) + PCData[7]) );
            RockerControl.ZaxisPos = (float)( (int16)(( (int16)PCData[10]<<8 ) + PCData[9]) );
        }
//        /*飞行器飞行过程中手柄的值(height yaw)*/
//        else if(PCData[2]==0x06){
//            RockerControl.Navigation = UnsignedcharToFloat(PCData,3);
//            RockerControl.ZaxisPos = UnsignedcharToFloat(PCData,7);
//        }
        /* 设置Pitch的PID参数 */
        else if(PCData[2]==0x07){
            PID_ParaInfo.Pitch.Kp= UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.Pitch.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.Pitch.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置ROll的PID参数 */
        else if(PCData[2]==0x08){
            PID_ParaInfo.Roll.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.Roll.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.Roll.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置Yaw的PID参数 */
        else if(PCData[2]==0x09){
            PID_ParaInfo.Yaw.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.Yaw.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.Yaw.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置Height的PID参数 */
        else if(PCData[2]==0x0A){
            PID_ParaInfo.PosZ.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.PosZ.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.PosZ.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置accPitch的PID参数 */
        else if(PCData[2]==0x0B){
            PID_ParaInfo.PitchRate.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.PitchRate.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.PitchRate.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置accRoll的PID参数 */
        else if(PCData[2]==0x0C){
            PID_ParaInfo.RollRate.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.RollRate.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.RollRate.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置accYaw的PID参数 */
        else if(PCData[2]==0x0D){
            PID_ParaInfo.YawRate.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.YawRate.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.YawRate.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置accHeight的PID参数 */
        else if(PCData[2]==0x0E){
            PID_ParaInfo.VelZ.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.VelZ.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.VelZ.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置AccZ的PID参数 */
        else if(PCData[2]==0x0F){
            PID_ParaInfo.AccZ.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.AccZ.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.AccZ.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置PositionX的PID参数 */
        else if(PCData[2]==0x12){
            PID_ParaInfo.PosX.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.PosX.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.PosX.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置PositionY的PID参数 */
        else if(PCData[2]==0x13){
            PID_ParaInfo.PosY.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.PosY.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.PosY.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置PositionVX的PID参数 */
        else if(PCData[2]==0x14){
            PID_ParaInfo.VelX.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.VelX.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.VelX.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置PositionVY的PID参数 */
        else if(PCData[2]==0x15){
            PID_ParaInfo.VelY.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.VelY.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.VelY.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置FlowX的PID参数 */
        else if(PCData[2]==0x16){
            PID_ParaInfo.FlowX.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.FlowX.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.FlowX.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置FlowVelX的PID参数 */
        else if(PCData[2]==0x17){
            PID_ParaInfo.FlowVelX.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.FlowVelX.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.FlowVelX.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置FlowY的PID参数 */
        else if(PCData[2]==0x18){
            PID_ParaInfo.FlowY.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.FlowY.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.FlowY.Kd = UnsignedcharToFloat(PCData,11);
            FlightControl.ReportSW = Report_SET;
            Write_Config();
        }
        /* 设置FlowVelY的PID参数 */
        else if(PCData[2]==0x19){
            PID_ParaInfo.FlowVelY.Kp = UnsignedcharToFloat(PCData,3);
            PID_ParaInfo.FlowVelY.Ki = UnsignedcharToFloat(PCData,7);
            PID_ParaInfo.FlowVelY.Kd = UnsignedcharToFloat(PCData,11);
            Write_Config();
            FlightControl.ReportSW = Report_SET;
        }
        /*陀螺仪校准*/
        else if(PCData[2]==0x30)
        {
            OffsetData.GyroX  = RT_Info.GyroX ;
            OffsetData.GyroY  = RT_Info.GyroY ;
            OffsetData.GyroZ  = RT_Info.GyroZ ;
            Write_Config();
        }

        /*偏置角度*/
        else if(PCData[2] == 0x32)
        {
            Errangle_Info.fixedErroPitch = RT_Info.Pitch;
            Errangle_Info.fixedErroRoll = RT_Info.Roll;
            Write_Config();
            FlightControl.ReportSW=Report_SET;
        }

        /*加速度校准*/
                /*第一面飞控平放，Z轴正向朝着正上方，Z axis is about 1g,X、Y is about 0g*/
                /*第二面飞控平放，X轴正向朝着正上方，X axis is about 1g,Y、Z is about 0g*/
                /*第三面飞控平放，X轴正向朝着正下方，X axis is about -1g,Y、Z is about 0g*/
                /*第四面飞控平放，Y轴正向朝着正下方，Y axis is about -1g,X、Z is about 0g*/
                /*第五面飞控平放，Y轴正向朝着正上方，Y axis is about 1g,X、Z is about 0g*/
                /*第六面飞控平放，Z轴正向朝着正下方，Z axis is about -1g,X、Y is about 0g*/
                else if(PCData[2]==0x31)
                {
                        unsigned char Pretime =0 ;
                        static int16_t AccData[6] ={0};
                        static float PreparationAccX,PreparationAccY,PreparationAccZ =0;
                        Pretime = 0 ;
                        if(PCData[3]==0x01)
                        {
                            while( Pretime < 100)
                            {
                                    Pretime ++;
                                    MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
                                    PreparationAccX += (float)AccData[0] /4096 * GRAVITY_MSS;
                                    PreparationAccY += (float)AccData[1] /4096 * GRAVITY_MSS;
                                    PreparationAccZ += (float)AccData[2] /4096 * GRAVITY_MSS;
                                    OSTimeDly(4);
                            }
                            acce_sample[0].x = PreparationAccX /100 ;
                            acce_sample[0].y = PreparationAccY /100 ;
                            acce_sample[0].z = PreparationAccZ /100 ;
                            PreparationAccX = PreparationAccY = PreparationAccZ =0;
                        }
                        else if(PCData[3]==0x02)
                        {
                            while( Pretime < 100)
                            {
                                    Pretime ++;
                                    MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
                                    PreparationAccX += (float)AccData[0] /4096 * GRAVITY_MSS ;
                                    PreparationAccY += (float)AccData[1] /4096 * GRAVITY_MSS;
                                    PreparationAccZ += (float)AccData[2] /4096 * GRAVITY_MSS;
                                    OSTimeDly(4);
                            }
                            acce_sample[5].x = PreparationAccX /100 ;
                            acce_sample[5].y = PreparationAccY /100 ;
                            acce_sample[5].z = PreparationAccZ /100 ;
                            PreparationAccX = PreparationAccY = PreparationAccZ =0;
                        }
                        else if(PCData[3]==0x03)
                        {
                            while( Pretime < 100)
                            {
                                    Pretime ++;
                                    MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
                                    PreparationAccX += (float)AccData[0] /4096 * GRAVITY_MSS;
                                    PreparationAccY += (float)AccData[1] /4096 * GRAVITY_MSS;
                                    PreparationAccZ += (float)AccData[2] /4096 * GRAVITY_MSS;
                                    OSTimeDly(4);
                            }
                            acce_sample[2].x = PreparationAccX /100 ;
                            acce_sample[2].y = PreparationAccY /100 ;
                            acce_sample[2].z = PreparationAccZ /100 ;
                            PreparationAccX = PreparationAccY = PreparationAccZ =0;
                        }
                        else if(PCData[3]==0x04)
                        {
                            while( Pretime < 100)
                            {
                                    Pretime ++;
                                    MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
                                    PreparationAccX += (float)AccData[0] /4096 * GRAVITY_MSS;
                                    PreparationAccY += (float)AccData[1] /4096 * GRAVITY_MSS;
                                    PreparationAccZ += (float)AccData[2] /4096 * GRAVITY_MSS;
                                    OSTimeDly(4);
                            }
                            acce_sample[1].x = PreparationAccX /100 ;
                            acce_sample[1].y = PreparationAccY /100 ;
                            acce_sample[1].z = PreparationAccZ /100 ;
                            PreparationAccX = PreparationAccY = PreparationAccZ =0;
                        }
                        else if(PCData[3]==0x05)
                        {
                            while( Pretime < 100)
                            {
                                    Pretime ++;
                                    MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
                                    PreparationAccX += (float)AccData[0] /4096 * GRAVITY_MSS;
                                    PreparationAccY += (float)AccData[1] /4096 * GRAVITY_MSS;
                                    PreparationAccZ += (float)AccData[2] /4096 * GRAVITY_MSS;
                                    OSTimeDly(4);
                            }
                            acce_sample[3].x = PreparationAccX /100 ;
                            acce_sample[3].y = PreparationAccY /100 ;
                            acce_sample[3].z = PreparationAccZ /100 ;
                            PreparationAccX = PreparationAccY = PreparationAccZ =0;
                        }
                        else if(PCData[3]==0x06)
                        {
                            while( Pretime < 100)
                            {
                                    Pretime ++;
                                    MPU6500_readGyro_Acc(&AccData[3],&AccData[0]);
                                    PreparationAccX += (float)AccData[0] /4096 * GRAVITY_MSS;
                                    PreparationAccY += (float)AccData[1] /4096 * GRAVITY_MSS;
                                    PreparationAccZ += (float)AccData[2] /4096 * GRAVITY_MSS;
                                    OSTimeDly(4);
                            }
                            acce_sample[4].x = PreparationAccX /100 ;
                            acce_sample[4].y = PreparationAccY /100 ;
                            acce_sample[4].z = PreparationAccZ /100 ;
                            PreparationAccX = PreparationAccY = PreparationAccZ =0;
                        }
                        else if(PCData[3]==0xFF)
                        {
                            while(!Calibrate_accel(acce_sample,&new_offset,&new_scales));
                            OffsetData.AccX = new_offset.x;
                            OffsetData.AccY = new_offset.y;
                            OffsetData.AccZ = new_offset.z;
                            OffsetData.AccXScale = new_scales.x ;
                            OffsetData.AccYScale = new_scales.y ;
                            OffsetData.AccZScale = new_scales.z ;
                            Write_Config();
                        }

                }

        else if(PCData[2]==0x33) //校准磁力计
        {
            if(PCData[3]==1)
            {
                OffsetData.MagOffseting = true;
                LSM303_Start_Calib();
            }
            else if (PCData[3]==2)
            {
                OffsetData.MagOffseting = false;
                LSM303_Save_Calib();
                Write_Config();
            }
        }
    }
}


