// void fsm_Soft_Start()
// {
//     static long int t0=HEM_HAL_get_SysTick();
//     long int t1=HEM_HAL_get_SysTick();
//     long int t=t1-t0;
//     if(t>HEM_CONFIG_SoftStart_TimeBase_SysTick){
//         Slew_Func();
//     }
// }