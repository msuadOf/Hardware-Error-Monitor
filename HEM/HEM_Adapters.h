#ifndef _HEM_Adapters_H
#define _HEM_Adapters_H

/**
 * @brief 抽象的主功率路径输出值封装函数，需要在移植的时候完成
 *          给软起动函数调用，完成系统软起动功能
 *
 * @param out : 主功率路径控制参数，0-100
 */
void HEM_HAL_Main_PowerPath(double out)
{
}/**
 * @brief 抽象的主功率路径封装函数，需要在移植的时候完成
 *          给软起动函数调用，完成系统软起动功能
 *
 * @param out : 主功率路径控制参数
 * @param in
 */
void HEM_HAL_Main_PowerPath(float *out, float in)
{
}
void HEM_HAL_Turnoff_Circuit()
{
    // need to be completed
}
long int HEM_HAL_get_SysTick()
{
    return 0;
}
#endif