/******************** (C) COPYRIGHT 2015-2017 Xiluna Tech ************************
 * 作者   :Xiluna Tech
 * 文件名 :Position_control.c
 * 描述   :外环控制函数
 * 官网   :http://xiluna.com/
 * 公众号 :XilunaTech
**********************************************************************************/
#include "Position_control.h"

void Position_control(unsigned char Data_flag,float Climb,float Decline){
//    /************************ 降落控制  ************************/

    static unsigned char hover= 0; //悬停标志位
    static unsigned char controlCnt =0; //用于控制周期的计数
    static float TgtHeight = 0;   // 目标高度变量


        controlCnt++; //控制周期计数  内环每次都做控制，外环两次控制周期做一次控制
    if(FlightControl.landFlag==1)
    {
        //缓慢降落
        TgtHeight = TgtHeight - Decline;

        /************************高度降落控制 ************************/
                if(controlCnt ==2)
                {
                      //外环单P控制器
                        float heightErro = TgtHeight - RT_Info.Height;
                        OriginalPosZ.value = Limits_data( PID_ParaInfo.PosZ.Kp * heightErro , 0.8f ,-0.8f);
                }
        //速度环PID控制器
        OriginalVelZ.value = Limits_data(  PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,OriginalPosZ.value,RT_Info.Height_V,0.005,1,lowpass_filter) ,2,-2);
              //加速度环PID控制器
                OriginalAccZ.value =  Limits_data(PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,OriginalVelZ.value,RT_Info.accZaxis,0.005,150,lowpass_filter),250,-250);

        /*10cm以下 电机怠速*/
        if(RT_Info.Height<0.1f){
            FlightControl.OnOff = Drone_Land;
            FlightControl.landFlag = 0;
            TgtHeight = 0;
            FlightControl.ControlStart = false;
            Target_Info.Height = 0.90f; //恢复初始的默认目标高度
        }
    }
    else
    {
                /* 手柄遥控高度控制器 */
        if(RockerControl.ZaxisPos ==0)
        {
            /* 第一次回到悬停状态，将现在的高度设置为目标高度 */
            if(hover ==1)
            {
                Target_Info.Height = RT_Info.Height ;
                hover=0 ;
            }
            /************************高度悬停控制 ************************/
                        /* 第一次起飞缓慢上升 */
                        if(TgtHeight < Target_Info.Height && FlightControl.LaunchFlag == true){
                            TgtHeight = TgtHeight + Climb ;
                            }
                        else{
                                    TgtHeight = Target_Info.Height;
                                    FlightControl.LaunchFlag = false ;
                        }

                        RT_Info.CpuTick = TgtHeight;

                        if(controlCnt ==2)
                        {
                                //外环单P控制器
                                float heightErro = TgtHeight - RT_Info.Height;
                                OriginalPosZ.value = Limits_data( PID_ParaInfo.PosZ.Kp * heightErro ,0.8f ,-0.8f);  //±0.5m/s的目标速度
                        }
                            //速度环PID控制器
                        OriginalVelZ.value = Limits_data(  PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,OriginalPosZ.value,RT_Info.Height_V,0.005,1,lowpass_filter) ,2.5,-2.5);
                        //加速度环PID控制器
                        OriginalAccZ.value =  Limits_data(PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,OriginalVelZ.value,RT_Info.accZaxis,0.005,150,lowpass_filter),250,-250);
        }
        else
        {
            OriginalVelZ.value = Limits_data(  PID_Control(&PID_ParaInfo.VelZ,&OriginalVelZ,RockerControl.ZaxisPos/100,RT_Info.Height_V,0.005,1,lowpass_filter) ,2.5,-2.5);
                        //加速度环PID控制器
                        OriginalAccZ.value =  Limits_data(PID_Control(&PID_ParaInfo.AccZ,&OriginalAccZ,OriginalVelZ.value,RT_Info.accZaxis,0.005,150,lowpass_filter),250,-250);
            hover =1;
        }
    }

        /*
            悬停油门 = 加速度环控制量（积分起主导作用） + 电机参数表单电压下所对应的悬停油门    注*（如果电机参数曲线为各个电压下，可由参数表直接实时算出悬停油门）
            此时输出Z轴的升力 F = mg
            当需要输出a（OriginalAccZ.value）的加速度时，输出力 F1=m(g+a)   注*（如果整机质量已知，即可算出每个电机需要提供的升力，并通过电机参数表曲线将升力转换为对应油门）
            此处因为要通用于不同轴距的多个机型，所以m、F与油门的关系量都未知，因此有以下关系式：
            F1/F = 1 + a/g
            因此此时应输出：悬停油门*(1 + a/g)
        */

        UAVThrust.HeightThrust =  OriginalAccZ.value + UAVThrust.BasicThrust;

    /************************ 位置环速度控制器  ************************/
    //只有飞行器的高度大于10cm才开始进行位置控制
    if(RT_Info.Height > 0.10f){
        switch (Data_flag){
            /************************ 有头模式（无定位）  ************************/
            case 0:
                Target_Info.Pitch =  RockerControl.XaxisPos;
                Target_Info.Roll =  RockerControl.YaxisPos;
                break;
            /************************ 无头模式（无定位）  ************************/
            case 1:

                break;
            /************************ 定点模式  ************************/
            case 2:
                              if(controlCnt ==2)
                                {
                                        if(RockerControl.XaxisPos == 0  && RockerControl.YaxisPos == 0 &&
                                                        Sensor_Info.Raspberry_Xaxis!=0 && Sensor_Info.Raspberry_Yaxis!=0)
                                        {
                                                OriginalPosX.value = PID_ParaInfo.PosX.Kp * RT_Info.PointX;

                                                Target_Info.Pitch =  Limits_data( - PID_Control(&PID_ParaInfo.VelX,&OriginalVelX,OriginalPosX.value,
                                                                                                                     RT_Info.PointX_V,0.005,3,lowpass_filter) , 6 , -6 );

                                                OriginalPosY.value = PID_ParaInfo.PosY.Kp * RT_Info.PointY;

                                                Target_Info.Roll = Limits_data( PID_Control(&PID_ParaInfo.VelY,&OriginalVelY,OriginalPosY.value,
                                                                                                                        RT_Info.PointY_V,0.005,3,lowpass_filter) , 6 , -6);
                                        }
                                        else
                                        {
                                                Target_Info.Pitch = 0.3f * RockerControl.XaxisPos;
                                                Target_Info.Roll = 0.3f * RockerControl.YaxisPos;
                                        }
                                }
                break;
            /************************ 光流定点 ************************/
            case 3:
                                if(controlCnt ==2)
                                {
                                    if(RockerControl.XaxisPos == 0  && RockerControl.YaxisPos == 0)
                                    {
                                            OriginalFlowX.value =   PID_ParaInfo.FlowX.Kp  * RT_Info.FlowX  ;
                                            OriginalFlowY.value =   PID_ParaInfo.FlowY.Kp  * RT_Info.FlowY  ;

                                            Target_Info.Pitch = - Limits_data( PID_Control(&PID_ParaInfo.FlowVelX,&OriginalFlowVelX,OriginalFlowX.value,
                                                                                                                 RT_Info.FlowX_V,0.005,1.5,lowpass_filter) , 25, -25 ) ;

                                            Target_Info.Roll = Limits_data( PID_Control(&PID_ParaInfo.FlowVelY,&OriginalFlowVelY,OriginalFlowY.value,
                                                                                                                    RT_Info.FlowY_V,0.005,1.5,lowpass_filter) , 25, -25 );
                                    }
                                    else
                                    {
                                            Target_Info.Pitch =  RockerControl.XaxisPos;
                                            Target_Info.Roll =  RockerControl.YaxisPos;
                                    }
                                }
                break;
                        /************************ 视觉里程计模式  ************************/
            case 4:
                if(controlCnt ==2)
                  {
                          if(RockerControl.XaxisPos == 0  && RockerControl.YaxisPos == 0 &&
                                         Sensor_Info.Raspberry_Yaxis!=0)
                          {
                              if(RT_Info.Height < 0.9*Target_Info.Height )
                              {
                                   OriginalFlowX.value =   PID_ParaInfo.FlowX.Kp  * RT_Info.FlowX_V  ;
                                   Target_Info.Pitch = - Limits_data( PID_Control(&PID_ParaInfo.FlowVelX,&OriginalFlowVelX,OriginalFlowX.value,
                                                                                                    RT_Info.FlowX_V,0.005,1.5,lowpass_filter) , 25, -25 ) ;
                             }

                              if((RT_Info.Height > 0.9*Target_Info.Height)&&(RT_Info.Height < 1.15*Target_Info.Height)  )
                              {
                                  // float XSpeedErro = Target_Info.FlowVel_X - RT_Info.FlowX_V ;
                                  // OriginalFlowX.value =   PID_ParaInfo.FlowX.Kp  * XSpeedErro  ;
                                  Target_Info.Pitch =  -Limits_data( PID_Control(&PID_ParaInfo.FlowVelX,&OriginalFlowVelX,Target_Info.FlowVel_X,
                                                                                                     RT_Info.FlowX_V,0.005,1.5,lowpass_filter) , 25, -25 ) ;
                              }


                                  OriginalPosY.value = PID_ParaInfo.PosY.Kp * RT_Info.PointY;
                                  Target_Info.Roll = Limits_data( PID_Control(&PID_ParaInfo.VelY,&OriginalVelY,OriginalPosY.value,
                                                                                                          RT_Info.PointY_V,0.005,3,lowpass_filter) , 6 , -6);

                                  // Target_Info.Yaw = Target_Info.BlackLineYaw;
                          }
                          else
                          {
                                  Target_Info.Pitch = 0.3f * RockerControl.XaxisPos;
                                  Target_Info.Roll = 0.3f * RockerControl.YaxisPos;
                          }
                  }
                break;
            case 5:
                if(controlCnt ==2)
                {
                    if(RT_Info.Height < 0.35)
                    {
                        OriginalPosX.value = PID_ParaInfo.PosX.Kp * RT_Info.PointX;

                        Target_Info.Pitch =  Limits_data( - PID_Control(&PID_ParaInfo.VelX,&OriginalVelX,OriginalPosX.value,
                                                                                             RT_Info.PointX_V,0.005,3,lowpass_filter) , 6 , -6 );

                        OriginalPosY.value = PID_ParaInfo.PosY.Kp * RT_Info.PointY;

                        Target_Info.Roll = Limits_data( PID_Control(&PID_ParaInfo.VelY,&OriginalVelY,OriginalPosY.value,
                                                                                                RT_Info.PointY_V,0.005,3,lowpass_filter) , 6 , -6);
                    }
                    else if(RT_Info.Height > 0.35)
                    {
                        if(RT_Info.VisionFlag == 0)
                        {
                            OriginalPosX.value = PID_ParaInfo.PosX.Kp * RT_Info.PointX;

                            Target_Info.Pitch =  Limits_data( - PID_Control(&PID_ParaInfo.VelX,&OriginalVelX,OriginalPosX.value,
                                                                                                 RT_Info.PointX_V,0.005,3,lowpass_filter) , 6 , -6 );

                            OriginalPosY.value = PID_ParaInfo.PosY.Kp * RT_Info.PointY;

                            Target_Info.Roll = Limits_data( PID_Control(&PID_ParaInfo.VelY,&OriginalVelY,OriginalPosY.value,
                                                                                                    RT_Info.PointY_V,0.005,3,lowpass_filter) , 6 , -6);
                        }
                        if(RT_Info.VisionFlag == 1)
                        {
                            OriginalFlowX.value =   PID_ParaInfo.FlowX.Kp  * RT_Info.FlowX  ;
                            Target_Info.Pitch = - Limits_data( PID_Control(&PID_ParaInfo.FlowVelX,&OriginalFlowVelX,OriginalFlowX.value,
                                                                                               RT_Info.FlowX_V,0.005,1.5,lowpass_filter) , 25, -25 ) ;

                            OriginalPosY.value = PID_ParaInfo.PosY.Kp * RT_Info.PointY;
                            Target_Info.Roll = Limits_data( PID_Control(&PID_ParaInfo.VelY,&OriginalVelY,OriginalPosY.value,
                                                                                                    RT_Info.PointY_V,0.005,3,lowpass_filter) , 6 , -6);
                        }
                    }
                }
                break;
            case 6:
                if(controlCnt ==2)
                {
                    OriginalPosX.value = PID_ParaInfo.PosX.Kp * RT_Info.PointX;

                    Target_Info.Pitch =  Limits_data( - PID_Control(&PID_ParaInfo.VelX,&OriginalVelX,OriginalPosX.value,
                                                                                         RT_Info.PointX_V,0.005,3,lowpass_filter) , 6 , -6 );

                    OriginalPosY.value = PID_ParaInfo.PosY.Kp * RT_Info.PointY;

                    Target_Info.Roll = Limits_data( PID_Control(&PID_ParaInfo.VelY,&OriginalVelY,OriginalPosY.value,
                                                                                            RT_Info.PointY_V,0.005,3,lowpass_filter) , 6 , -6);

                }
                break;
            default:

                break;
        }

    }
        if(controlCnt == 2)
            controlCnt =0;
}


