/**
 * @file example_main.c
 * @author msuad (cube@msuad.top)
 * @brief 本示例代码以最基础的Buck电路为例
 * @version 0.1
 * @date 2023-07-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <HEM/HEM.h>

// imagine virtual hardware api
// 设想一下虚拟的操作硬件的api
void bsp_BuckPWM_setDuty(float duty){}
float bsp_BuckADC_getVoltageVal(){}
float PID_Controller(float aim,float current,float Kp,float Ki,float Kd){}

//中断回调函数标识符号
#define __interrupt

__interrupt void TIM_ISR(){
    float adc_Vol_val=bsp_BuckADC_getVoltageVal();
    //PID控制电压回路，稳压10V
    float duty=PID_Controller(10,adc_Vol_val,10,1,0.1);
    bsp_BuckPWM_setDuty(duty);
}

int main(){
    // ...init Periph

    while (1)
    {
        HEM_fsm_monitor();//状态机入口函数
    }
    
}