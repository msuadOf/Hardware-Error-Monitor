#ifndef _HEM_H
#define _HEM_H

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
} HEM_t;
HEM_t fsm_state;

void HEM_HAL_Turnoff_Circuit()
{
    // need to be completed
}
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
/**
 * @brief 抽象的主功率路径封装函数，需要在移植的时候完成
 *          给软起动函数调用，完成系统软起动功能
 *
 * @param out : 主功率路径启动
 * @param in
 */
void HEM_HAL_Main_PowerPath(float *out, float in)
{
}

void HEM_error_handler(HEM_error_trace_enum error_trace)
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

long int get_SysTick()
{
    return 0;
}
void fsm_Self_Test()
{
}
void fsm_Sys_Init()
{
}
void fsm_Soft_Start()
{
}
void fsm_Work()
{
}
void fsm_Error()
{
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
