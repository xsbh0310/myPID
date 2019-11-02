#include "stdafx.h"
#include "position_pid.h"

//----------------------------------------------------------------------------
void PositionPID_Init(PositionPID_t *PositionPID, float Kp, float Ki, float Kd, float val_min, float val_max)
{
	PositionPID->set_val = 0.00;
	PositionPID->cul_val = 0.00;
	PositionPID->out_val = 0.00;

	PositionPID->val_min = val_min;
	PositionPID->val_max = val_max;

	PositionPID->Kp = Kp;
	PositionPID->Ki = Ki;
	PositionPID->Kd = Kd;

	PositionPID->Kp_err = 0.0;
	PositionPID->Ki_err = 0.0;
	PositionPID->Kd_err = 0.0;

	PositionPID->Ek = 0.0;
	PositionPID->Ek_1 = 0.0;
}

//----------------------------------------------------------------------------
float PositionPID_Calc(PositionPID_t *PositionPID, float set_val, float cul_val)
{
	//设定值
	PositionPID->set_val = set_val;
	//当前值
	PositionPID->cul_val = cul_val;

	//偏差
	PositionPID->Ek = set_val - cul_val;

	//比例差值E[k]
	PositionPID->Kp_err = PositionPID->Ek;

	//积分差值(E[k]+E[k-1])/2 + (E[k-1]+E[k-2])/2 + ... + (E[1]+E[0])/2
	PositionPID->Ki_err += (PositionPID->Ek + PositionPID->Ek_1) / 2;

	//微分差值E[k]-E[k-1]
	PositionPID->Kd_err = PositionPID->Ek - PositionPID->Ek_1;

	//本次输出
	PositionPID->out_val  = PositionPID->Kp * PositionPID->Kp_err; //比例E[k]
	PositionPID->out_val += PositionPID->Ki * PositionPID->Ki_err; //积分(E[k]+E[k-1])/2 + (E[k-1]+E[k-2])/2 + ... + (E[1]+E[0])/2
	PositionPID->out_val += PositionPID->Kd * PositionPID->Kd_err; //微分E[k]-E[k-1]

	//输出限位
	if(PositionPID->out_val < PositionPID->val_min)
	{
		PositionPID->out_val = PositionPID->val_min;
	}
	else if(PositionPID->out_val > PositionPID->val_max)
	{
		PositionPID->out_val = PositionPID->val_max;
	}

	//更新E[k-1]
	PositionPID->Ek_1 = PositionPID->Ek; //E[k-1] = E[k]

	return PositionPID->out_val;
}
