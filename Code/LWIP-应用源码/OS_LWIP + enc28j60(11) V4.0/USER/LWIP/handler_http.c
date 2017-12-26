#include "..\..\config.h"
#include "stm32f10x.h"
#include "cc.h"
#include "def.h"
#include "api.h"
#include "err.h"

#define HTTP_HTML_HEADER		"HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n"

const char set_html[] = {1};
const char set1_html[] = {1};
//*------------------------------------------------------------------------------------------------
//* �������� : Handler_HTTPGet
//* �������� : ����HTTPЭ���GET����
//* ��ڲ��� : <pstConn>[in] ָ��ST_NETCONN�ṹ��ָ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------

void vHandler_HTTP(ST_NETCONN *pstConn)
{
	ST_NETBUF 		*__pstNetbuf;
	INT8S			*__pbData;
	u16_t			__s32Len;
    err_t Err_t;

//	Err_t = netconn_recv(pstConn ,NULL);

//	if(Err_t != NULL)
	{
	//	netbuf_data(__pstNetbuf, &__pbData, &__s32Len);

	//	if(memstr(__pbData, "GET", 3, __s32Len))
		{
			//__Handler_HTTPGet(pstConn);
		}
		//else if(memstr(__pbData, "POST", 3, __s32Len))
		{
			//__Handler_HTTPPost(pstConn, __pstNetbuf);
		//	netbuf_delete(__pstNetbuf);	
		//	netconn_close(pstConn);
			return;
		}
	}
	netbuf_delete(__pstNetbuf);	
	netconn_close(pstConn);
}
