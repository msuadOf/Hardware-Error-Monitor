#ifndef _HEM_H
#define _HEM_H

#include <HEM/HEM_Adapters.h>

#define HEM_CONFIG_SoftStart_TimeBase_SysTick 10
#define HEM_CONFIG_SoftStart_refValue_AimValue 1
#define HEM_CONFIG_SoftStart_slewRate 1

// 状态机
typedef enum sys_state
{
    Self_Test,
    Sys_Init,
    Soft_Start,
    Work,
    Error
} sys_state_enum;

typedef enum HEM_error_trace
{
    Over_Voltage,
    Over_Current
} HEM_error_trace_enum;
typedef struct HEM
{
    sys_state_enum state;
    sys_state_enum state_last;
    sys_state_enum state_next;

    int fsm_state_jump_lock;
} HEM_t;
HEM_t fsm_state;

void HEM_error(HEM_error_trace_enum error_trace)
{
    switch (error_trace)
    {
    case Over_Voltage:
    {
        HEM_HAL_Turnoff_Circuit();
    }
    break;

    default:
    {
        HEM_HAL_Turnoff_Circuit();
    }
    break;
    }
}

void HEM_fsm_State_Update(sys_state_enum nextState)
{
    fsm_state.state_last = fsm_state.state;
    fsm_state.state = nextState;
}
void fsm_Self_Test()
{
    HEM_fsm_State_Update(Sys_Init);
}
void fsm_Sys_Init()
{
    HEM_fsm_State_Update(Soft_Start);
}

// ========= 软起动：========

/**
 * 斜坡函数 实现类似y=ax+b功能
 * @param slewVal x
 * @param refVal  y
 * @param slewRate a
 * @return
 */
float Slew_Func(float *slewVal, float refVal, float slewRate)
{
    static float diff = 0;
    diff = refVal - *slewVal;
    if (diff >= slewRate)
    {
        *slewVal += slewRate;
        return (1);
    }
    else if (-diff >= slewRate)
    {
        *slewVal -= slewRate;
        return (-1);
    }
    else
    {
        *slewVal = refVal;
        return (0);
    }
}

void fsm_Soft_Start()
{
    static long int t0=0 ,i=0;
    if(i==0){
        t0=HEM_HAL_get_SysTick();
        i=1;
    }
    long int t1;
    t1 = HEM_HAL_get_SysTick();
    long int t = t1 - t0;
    double out = 0;
    if (t > HEM_CONFIG_SoftStart_TimeBase_SysTick)
    {
        if (!Slew_Func(&out, HEM_CONFIG_SoftStart_refValue_AimValue, HEM_CONFIG_SoftStart_slewRate)){
            HEM_fsm_State_Update(Work);
        }
            HEM_HAL_Main_PowerPath(out);
    }
}
void fsm_Work()
{
}
void fsm_Error()
{
}
void HEM_fsm_monitor_init()
{
    fsm_state.state = Self_Test;
}
void HEM_fsm_monitor()
{
    switch (fsm_state.state)
    {
    case Self_Test:
    {
        fsm_Self_Test();
    }
    break;

    case Sys_Init:
    {
        fsm_Sys_Init();
    }
    break;

    case Soft_Start:
    {
        fsm_Soft_Start();
    }
    break;
    case Work:
    {
        fsm_Work();
    }
    break;

    case Error:
    {
        fsm_Error();
    }
    break;

    default:
    {
        fsm_Error();
    }
    break;
    }
}

#endif // !_HEM_H
