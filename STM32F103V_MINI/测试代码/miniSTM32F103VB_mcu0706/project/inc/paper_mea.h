
//paper_mea.h

#ifndef  __PAPER_MEA_H
#define	__PAPER_MEA_H

//stm32 -pin68-PA9-74hc14(Y-PIN8) -->stm32 PIN68 : H : 无纸, L :有纸;---LC4600传感器
typedef enum{
	PAPER_NO = Bit_SET,
	PAPER_EXIST = Bit_RESET,
}PaperFlag;

typedef struct{
	//u16 CurDist;
	bool MeaPaperEdgeFlag;
	u16 NearDist;	/*纸张的近端点位置，单位:光栅边沿数*/
	u16 FarDist;		/*纸张的远端点位置，单位:光栅边沿数*/
	u16 With;		/*纸张宽度,  单位: mm*/
}PrintPaper_t;

//extern volatile PrintPaper_t PrintPaperStructure;

extern void Init_PaperMea(void);
//extern PaperFlag PaperMeaCheck(void);
extern void PaperEdgeGet(void);

//extern void PaperMeaPaperEdgeFlagClear(void);
extern bool PaperMeaEdge_IsElapsed(void);
extern bool PaperCalWith(void);
//extern void PaperNoteEdgeNear(void);
//extern void PaperNoteEdgeFar(void);
extern u16 PaperWithGet(void);
extern void PaperMeaPaperEdgeFlagClear(void);
extern void PaperMeaReset(void);
#endif //__PAPER_MEA_H

