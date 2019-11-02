// myPID.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "position_pid.h"
#include "inc_pid.h"

PositionPID_t PositionPID_data;
IncPID_t IncPID_data;

int _tmain(int argc, _TCHAR* argv[])
{
	int i,j;
	float out_val = 0.00;
	float cul_val = 0.00;

#if 0 //位置式PID
	//----------------------------------------------------------------------------
	PositionPID_Init(&PositionPID_data, 0.15, 0.05, 0.00, 0.00, 20.00);
	//
	for(i=0;i<2000;i+=10)
	{
		out_val = PositionPID_Calc(&PositionPID_data, 20.00, cul_val);
		cul_val = out_val;

		printf("\r\n%04d -- %02.2f ", i, cul_val);
		for(j=0;j<(int)cul_val;j++)
		{
			printf("*");
		}
	}
#endif

#if 1 //增量式PID
	//----------------------------------------------------------------------------
	IncPID_Init(&IncPID_data, 0.15, 0.15, 0.00, 0.00, 20.00);
	//
	for(i=0;i<2000;i+=10)
	{
		out_val = IncPID_Calc(&IncPID_data, 20.00, cul_val);
		cul_val += out_val;

		printf("\r\n%04d -- %02.2f ", i, cul_val);
		for(j=0;j<(int)cul_val;j++)
		{
			printf("*");
		}
	}
#endif

	getchar();

	return 0;
}
