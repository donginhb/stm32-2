#ifndef __DES_H__
#define __DES_H__

#define EN_DES 1
#define DE_DES 0

void deskey(unsigned char *temp,unsigned char key[16][8]);

void des(unsigned char *plain,unsigned char key_6[16][8],unsigned char mode,unsigned char *ciphertext);

#endif//__DES_H__

