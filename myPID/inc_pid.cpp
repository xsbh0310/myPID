#include "stdafx.h"
#include "inc_pid.h"

//----------------------------------------------------------------------------
void IncPID_Init(IncPID_t *IncPID, float Kp, float Ki, float Kd, float val_min, float val_max)
{
	IncPID->set_val = 0.00;
	IncPID->cul_val = 0.00;
	IncPID->out_val = 0.00;

	IncPID->val_min = val_min;
	IncPID->val_max = val_max;

	IncPID->Kp = Kp;
	IncPID->Ki = Ki;
	IncPID->Kd = Kd;

	IncPID->Kp_err = 0.0;
	IncPID->Ki_err = 0.0;
	IncPID->Kd_err = 0.0;

	IncPID->Ek = 0.0;
	IncPID->Ek_1 = 0.0;
	IncPID->Ek_2 = 0.0;
}

//----------------------------------------------------------------------------
float IncPID_Calc(IncPID_t *IncPID, float set_val, float cul_val)
{
	//设定值
	IncPID->set_val = set_val;
	//当前值
	IncPID->cul_val = cul_val;

	//偏差
	IncPID->Ek = set_val - cul_val;

	//比例差值E[k]-E[k-1]
	IncPID->Kp_err = IncPID->Ek - IncPID->Ek_1;

	//积分差值E[k]
	IncPID->Ki_err = 0;
	//-- 抗积分饱和
	//---- 上过调
	if(IncPID->out_val > IncPID->val_max)
	{
		//防止进一步上过调
		if(IncPID->Ek <= 0)
		{
			IncPID->Ki_err = IncPID->Ek;
		}
	}
	//---- 下过调
	else if(IncPID->out_val < IncPID->val_min)
	{
		//防止进一步下过调
		if(IncPID->Ek >= 0)
		{
			IncPID->Ki_err = IncPID->Ek;
		}
	}
	//---- 未过调
	else
	{
		IncPID->Ki_err = IncPID->Ek;
	}

	//微分差值E[k]-2E[k-1]+E[k-2]
	IncPID->Kd_err = IncPID->Ek - IncPID->Ek_1 - IncPID->Ek_1 + IncPID->Ek_2;

	//本次输出
	IncPID->out_val  = IncPID->Kp * IncPID->Kp_err; //比例E[k]-E[k-1]
	IncPID->out_val += IncPID->Ki * IncPID->Ki_err; //积分E[k]
	IncPID->out_val += IncPID->Kd * IncPID->Kd_err; //微分E[k]-2E[k-1]+E[k-2]

	//输出限位
	if(IncPID->out_val < IncPID->val_min)
	{
		IncPID->out_val = IncPID->val_min;
	}
	else if(IncPID->out_val > IncPID->val_max)
	{
		IncPID->out_val = IncPID->val_max;
	}

	//更新E[k-2]
	IncPID->Ek_2 = IncPID->Ek_1; //E[k-2] = E[k-1]
	//更新E[k-1]
	IncPID->Ek_1 = IncPID->Ek; //E[k-1] = E[k]

	return IncPID->out_val;
}
