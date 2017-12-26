#ifndef __TOOLS_H__
#define __TOOLS_H__

extern char HexTable[]; //ascii��>hex��ת����
extern char HEXStr[32];	//����ת����ʱ�ڴ�
extern char sssStr[5];		//����ת����ʱ�ڴ�
extern char caNewString[1024];	 //ע�ⶨ���ں����ڲ����׶�ջ��� ��ֵ�ķ�Χ����С�����һ�β�ѯ���ڴ�λ��

void Hex2HexStr(unsigned char hex);
void Hex2Str(unsigned char hex);
void U16_2Str(unsigned int portnum);
int ReplaceStr(char *sSrc, char *sSubStr, char *sReplaceStr);
static char *itoa(int value, char *string, int radix);
void Get_SerialNum(void);

#endif
