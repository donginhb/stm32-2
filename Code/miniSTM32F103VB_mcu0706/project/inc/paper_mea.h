
//paper_mea.h

#ifndef  __PAPER_MEA_H
#define	__PAPER_MEA_H

//stm32 -pin68-PA9-74hc14(Y-PIN8) -->stm32 PIN68 : H : ��ֽ, L :��ֽ;---LC4600������
typedef enum{
	PAPER_NO = Bit_SET,
	PAPER_EXIST = Bit_RESET,
}PaperFlag;

typedef struct{
	//u16 CurDist;
	bool MeaPaperEdgeFlag;
	u16 NearDist;	/*ֽ�ŵĽ��˵�λ�ã���λ:��դ������*/
	u16 FarDist;		/*ֽ�ŵ�Զ�˵�λ�ã���λ:��դ������*/
	u16 With;		/*ֽ�ſ��,  ��λ: mm*/
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

