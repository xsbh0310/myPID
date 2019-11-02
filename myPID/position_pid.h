#ifndef __POSITION_PID_H__
#define __POSITION_PID_H__

#include <stdio.h>
#include <tchar.h>

//----------------------------------------------------------------------------
//λ��ʽPID
struct PositionPID
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
};
typedef struct PositionPID PositionPID_t;

//----------------------------------------------------------------------------
extern void PositionPID_Init(PositionPID_t *PositionPID, float Kp, float Ki, float Kd, float val_min, float val_max);
extern float PositionPID_Calc(PositionPID_t *PositionPID, float set_val, float cul_val);

#endif __POSITION_PID_H__
