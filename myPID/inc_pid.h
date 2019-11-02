#ifndef __INC_PID_H__
#define __INC_PID_H__

#include <stdio.h>
#include <tchar.h>

//----------------------------------------------------------------------------
//����ʽPID
struct IncPID
{
	float set_val; //�趨ֵ
	float cul_val; //��ǰֵ
	float out_val; //���ֵ

	float val_min; //��Сֵ
	float val_max; //���ֵ

	float Kp; //����ϵ��Proportional
	float Ki; //����ϵ��Integral
	float Kd; //΢��ϵ��Derivative

	float Kp_err; //�������ֵ
	float Ki_err; //�������ֵ
	float Kd_err; //΢�����ֵ

	float Ek;   //��ǰ��ֵE[k]
	float Ek_1; //�ϴβ�ֵE[k-1]
	float Ek_2; //���ϴβ�ֵE[k-2]
};
typedef struct IncPID IncPID_t;

//----------------------------------------------------------------------------
extern void IncPID_Init(IncPID_t *IncPID, float Kp, float Ki, float Kd, float val_min, float val_max);
extern float IncPID_Calc(IncPID_t *IncPID, float set_val, float cul_val);

#endif __INC_PID_H__
