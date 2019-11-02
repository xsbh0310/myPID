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
	//�趨ֵ
	PositionPID->set_val = set_val;
	//��ǰֵ
	PositionPID->cul_val = cul_val;

	//ƫ��
	PositionPID->Ek = set_val - cul_val;

	//������ֵE[k]
	PositionPID->Kp_err = PositionPID->Ek;

	//���ֲ�ֵ(E[k]+E[k-1])/2 + (E[k-1]+E[k-2])/2 + ... + (E[1]+E[0])/2
	PositionPID->Ki_err += (PositionPID->Ek + PositionPID->Ek_1) / 2;

	//΢�ֲ�ֵE[k]-E[k-1]
	PositionPID->Kd_err = PositionPID->Ek - PositionPID->Ek_1;

	//�������
	PositionPID->out_val  = PositionPID->Kp * PositionPID->Kp_err; //����E[k]
	PositionPID->out_val += PositionPID->Ki * PositionPID->Ki_err; //����(E[k]+E[k-1])/2 + (E[k-1]+E[k-2])/2 + ... + (E[1]+E[0])/2
	PositionPID->out_val += PositionPID->Kd * PositionPID->Kd_err; //΢��E[k]-E[k-1]

	//�����λ
	if(PositionPID->out_val < PositionPID->val_min)
	{
		PositionPID->out_val = PositionPID->val_min;
	}
	else if(PositionPID->out_val > PositionPID->val_max)
	{
		PositionPID->out_val = PositionPID->val_max;
	}

	//����E[k-1]
	PositionPID->Ek_1 = PositionPID->Ek; //E[k-1] = E[k]

	return PositionPID->out_val;
}
