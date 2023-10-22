#ifndef __PID_H_
#define __PID_H_

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <stdint.h>
#include <string.h>

extern volatile int pulseBase;

extern volatile double posBase, setBase, outputBase, lastoutputBase;
extern volatile double E1, E2, Ea, alpha1, beta1, gama1, T;
extern volatile double Kd1, Kp1, Ki1;

/* ------------------------ Public ------------------------- */
#define _PID_8BIT_PWM_MAX       UINT8_MAX
#define _PID_SAMPLE_TIME_MS_DEF 100

#ifndef _FALSE

	#define _FALSE 0

#endif

#ifndef _TRUE

	#define _TRUE 1

#endif

/* ---------------------- By compiler ---------------------- */
#ifndef GetTime

	/* ---------------------- By compiler ---------------------- */

	#ifdef __CODEVISIONAVR__  /* Check compiler */

		#define GetTime()   0

	/* ------------------------------------------------------------------ */

	#elif defined(__GNUC__) && !defined(USE_HAL_DRIVER)  /* Check compiler */

		#define GetTime()   0

	/* ------------------------------------------------------------------ */

	#elif defined(USE_HAL_DRIVER)  /* Check driver */

		#define GetTime()   HAL_GetTick()

	/* ------------------------------------------------------------------ */

	#else
	#endif /* __CODEVISIONAVR__ */
	/* ------------------------------------------------------------------ */

#endif

/* --------------------------------------------------------- */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* PID Mode */
typedef enum
{
	
	_PID_MODE_MANUAL    = 0,
	_PID_MODE_AUTOMATIC = 1
	
}PIDMode_TypeDef;

/* PID P On x */
typedef enum
{
	
	_PID_P_ON_M = 0, /* Proportional on Measurement */
	_PID_P_ON_E = 1
	
}PIDPON_TypeDef;

/* PID Control direction */
typedef enum
{
	
	_PID_CD_DIRECT  = 0,
	_PID_CD_REVERSE = 1
	
}PIDCD_TypeDef;


/* PID Structure */
#pragma pack(push, 1)  // Pack struct members tightly

typedef struct
{
	
	PIDPON_TypeDef  POnE;
	PIDMode_TypeDef InAuto;

	PIDPON_TypeDef  POn;
	PIDCD_TypeDef   ControllerDirection;

	uint32_t        LastTime;
	uint32_t        SampleTime;

	double          DispKp;
	double          DispKi;
	double          DispKd;

	double          Kp;
	double          Ki;
	double          Kd;

	double          *MyInput;
	double          *MyOutput;
	double          *MySetpoint;

	double          OutputSum;
	double          LastInput;

	double          OutMin;
	double          OutMax;
	
}PID_TypeDef;

#pragma pack(pop)  // Restore default struct packing

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Class ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prototype ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* :::::::::::::: Init ::::::::::::: */
void PID_Init(PID_TypeDef *uPID);

void PID(PID_TypeDef *uPID, double *Input, double *Output, double *Setpoint, double Kp, double Ki, double Kd, PIDPON_TypeDef POn, PIDCD_TypeDef ControllerDirection);
void PID2(PID_TypeDef *uPID, double *Input, double *Output, double *Setpoint, double Kp, double Ki, double Kd, PIDCD_TypeDef ControllerDirection);

/* ::::::::::: Computing ::::::::::: */
uint8_t PID_Compute(PID_TypeDef *uPID);

/* ::::::::::: PID Mode :::::::::::: */
void            PID_SetMode(PID_TypeDef *uPID, PIDMode_TypeDef Mode);
PIDMode_TypeDef PID_GetMode(PID_TypeDef *uPID);

/* :::::::::: PID Limits ::::::::::: */
void PID_SetOutputLimits(PID_TypeDef *uPID, double Min, double Max);

/* :::::::::: PID Tunings :::::::::: */
void PID_SetTunings(PID_TypeDef *uPID, double Kp, double Ki, double Kd);
void PID_SetTunings2(PID_TypeDef *uPID, double Kp, double Ki, double Kd, PIDPON_TypeDef POn);

/* ::::::::: PID Direction ::::::::: */
void          PID_SetControllerDirection(PID_TypeDef *uPID, PIDCD_TypeDef Direction);
PIDCD_TypeDef PID_GetDirection(PID_TypeDef *uPID);

/* ::::::::: PID Sampling :::::::::: */
void PID_SetSampleTime(PID_TypeDef *uPID, int32_t NewSampleTime);

/* ::::::: Get Tunings Param ::::::: */
double PID_GetKp(PID_TypeDef *uPID);
double PID_GetKi(PID_TypeDef *uPID);
double PID_GetKd(PID_TypeDef *uPID);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#endif /* __PID_H_ */
