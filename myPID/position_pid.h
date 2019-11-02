#ifndef __POSITION_PID_H__
#define __POSITION_PID_H__

#include <stdio.h>
#include <tchar.h>

//----------------------------------------------------------------------------
//位置式PID
struct PositionPID
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
};
typedef struct PositionPID PositionPID_t;

//----------------------------------------------------------------------------
extern void PositionPID_Init(PositionPID_t *PositionPID, float Kp, float Ki, float Kd, float val_min, float val_max);
extern float PositionPID_Calc(PositionPID_t *PositionPID, float set_val, float cul_val);

#endif __POSITION_PID_H__
