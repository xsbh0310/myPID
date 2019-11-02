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

	IncPID->Ki_state = 1;
}

//----------------------------------------------------------------------------
float IncPID_Calc(IncPID_t *IncPID, float set_val, float cul_val)
{
	//����ʱ�رջ���
	if( (IncPID->out_val > IncPID->val_min) && (IncPID->out_val < IncPID->val_max) )
	{
		IncPID->Ki_state = 1;
	}
	else
	{
		IncPID->Ki_state = 0;
	}

	//�趨ֵ
	IncPID->set_val = set_val;
	//��ǰֵ
	IncPID->cul_val = cul_val;

	//ƫ��
	IncPID->Ek = set_val - cul_val;

	//�������
#if 0 //��ʽ1
	//������ֵE[k]
	IncPID->Kp_err = IncPID->Ek;

	//���ֲ�ֵE[k-1]
	IncPID->Ki_err = IncPID->Ek_1;

	//΢�ֲ�ֵE[k-2]
	IncPID->Kd_err = IncPID->Ek_2;

	IncPID->out_val  = IncPID->Kp * IncPID->Kp_err; //����E[k]
	IncPID->out_val -= IncPID->Ki * IncPID->Ki_err * IncPID->Ki_state; //����E[k-1]
	IncPID->out_val += IncPID->Kd * IncPID->Kd_err; //΢��E[k-2]
#endif //��ʽ1

#if 1 //��ʽ2
	//������ֵE[k]-E[k-1]
	IncPID->Kp_err = IncPID->Ek - IncPID->Ek_1;

	//���ֲ�ֵE[k]
	IncPID->Ki_err = IncPID->Ek;

	//΢�ֲ�ֵE[k]-2E[k-1]+E[k-2]
	IncPID->Kd_err = IncPID->Ek - IncPID->Ek_1 - IncPID->Ek_1 + IncPID->Ek_2;

	IncPID->out_val  = IncPID->Kp * IncPID->Kp_err; //����E[k]-E[k-1]
	IncPID->out_val += IncPID->Ki * IncPID->Ki_err * IncPID->Ki_state; //����E[k]
	IncPID->out_val += IncPID->Kd * IncPID->Kd_err; //΢��E[k]-2E[k-1]+E[k-2]
#endif //��ʽ2

	//�����λ
	if(IncPID->out_val < IncPID->val_min)
	{
		IncPID->out_val = IncPID->val_min;
	}
	else if(IncPID->out_val > IncPID->val_max)
	{
		IncPID->out_val = IncPID->val_max;
	}

	//����E[k-2]
	IncPID->Ek_2 = IncPID->Ek_1; //E[k-2] = E[k-1]
	//����E[k-1]
	IncPID->Ek_1 = IncPID->Ek; //E[k-1] = E[k]

	return IncPID->out_val;
}
