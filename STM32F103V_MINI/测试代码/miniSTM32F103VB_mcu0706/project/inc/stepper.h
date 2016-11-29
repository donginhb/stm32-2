//file: setpper.h
#ifndef __STEPPER_H
#define __STEPPER_H

//**************************************************8
typedef enum {
	STEP_CUR_WORK_MODE =1,
	STEP_CUR_WEAK_MODE
}SetpperCurMode;

typedef enum {

	STEP_DIR_CW = 1,	/*ÍËÖ½*/
	STEP_DIR_CCW, 		/*½øÖ½*/
	
}SetpperDir;

typedef enum{
	STEP_FULL,
	STEP_HALF,
	STEP_QUARTER,
	STEP_MAX,
}StepperPhase;


extern void Init_Stepper(void);
extern void Stepper_ModeSet( SetpperCurMode mode , SetpperDir run_dir);
extern void StepperPrintFeedPaper(u16 Num );
extern void API_StepperBackward(void);
extern void API_StepperForward(void);
extern bool StepperTest(void);
extern void SetpperBack(void);
extern void MC_StepperNumClear(void);
extern bool MC_StepperNum_IsElapsed(void);

#endif

