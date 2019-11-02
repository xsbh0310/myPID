#ifndef __INC_PID_H__
#define __INC_PID_H__

#include <stdio.h>
#include <tchar.h>

//----------------------------------------------------------------------------
//增量式PID
struct IncPID
{
	float set_val; //设定值
	float cul_val; //当前值
	float out_val; //输出值

	float val_min; //最小值
	float val_max; //最大值

	float Kp; //比例系数Proportional
	float Ki; //积分系数Integral
	float Kd; //微分系数Derivative

	float Kp_err; //比例项差值
	float Ki_err; //积分项差值
	float Kd_err; //微分项差值

	float Ek;   //当前差值E[k]
	float Ek_1; //上次差值E[k-1]
	float Ek_2; //上上次差值E[k-2]
};
typedef struct IncPID IncPID_t;

//----------------------------------------------------------------------------
extern void IncPID_Init(IncPID_t *IncPID, float Kp, float Ki, float Kd, float val_min, float val_max);
extern float IncPID_Calc(IncPID_t *IncPID, float set_val, float cul_val);

#endif __INC_PID_H__
