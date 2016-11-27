/*
◆这可是用于成熟产品上的代码。
◆变换后的数据可能让人费解，程序更显得不规范。没办法！一切为了速度。
◆对同一个密钥，以后的加密解密计算不必每次都调用deskey()函数。
◆指针和数组操作的交替使用，仅在C51编译器下表现出最佳速度，其他环境未验证。

下面是算法的完整函数，要连接到你的程序可能还需要点工夫。
*/

#include <string.h>
#define no_init xdata

const unsigned char ip[65] = {0,
58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
const unsigned char fp[64] = {
8, 40, 16, 48, 24, 56, 32, 64,
7, 39, 15, 47, 23, 55, 31, 63,
6, 38, 14, 46, 22, 54, 30, 62,
5, 37, 13, 45, 21, 53, 29, 61,
4, 36, 12, 44, 20, 52, 28, 60,
3, 35, 11, 43, 19, 51, 27, 59,
2, 34, 10, 42, 18, 50, 26, 58,
1, 33, 9, 41, 17, 49, 25, 57};

const unsigned char init_newpc[16][48] = {
10,51,34,60,49,17,33,57, 2, 9,19,42, 3,35,26,25,44,58,59, 1,36,27,18,41,
22,28,39,54,37, 4,47,30, 5,53,23,29,61,21,38,63,15,20,45,14,13,62,55,31,
2,43,26,52,41, 9,25,49,59, 1,11,34,60,27,18,17,36,50,51,58,57,19,10,33,
14,20,31,46,29,63,39,22,28,45,15,21,53,13,30,55, 7,12,37, 6, 5,54,47,23,
51,27,10,36,25,58, 9,33,43,50,60,18,44,11, 2, 1,49,34,35,42,41, 3,59,17,
61, 4,15,30,13,47,23, 6,12,29,62, 5,37,28,14,39,54,63,21,53,20,38,31, 7,
35,11,59,49, 9,42,58,17,27,34,44, 2,57,60,51,50,33,18,19,26,25,52,43, 1,
45,55,62,14,28,31, 7,53,63,13,46,20,21,12,61,23,38,47, 5,37, 4,22,15,54,
19,60,43,33,58,26,42, 1,11,18,57,51,41,44,35,34,17, 2, 3,10, 9,36,27,50,
29,39,46,61,12,15,54,37,47,28,30, 4, 5,63,45, 7,22,31,20,21,55, 6,62,38,
3,44,27,17,42,10,26,50,60, 2,41,35,25,57,19,18, 1,51,52,59,58,49,11,34,
13,23,30,45,63,62,38,21,31,12,14,55,20,47,29,54, 6,15, 4, 5,39,53,46,22,
52,57,11, 1,26,59,10,34,44,51,25,19, 9,41, 3, 2,50,35,36,43,42,33,60,18,
28, 7,14,29,47,46,22, 5,15,63,61,39, 4,31,13,38,53,62,55,20,23,37,30, 6,
36,41,60,50,10,43,59,18,57,35, 9, 3,58,25,52,51,34,19,49,27,26,17,44, 2,
12,54,61,13,31,30, 6,20,62,47,45,23,55,15,28,22,37,46,39, 4, 7,21,14,53,
57,33,52,42, 2,35,51,10,49,27, 1,60,50,17,44,43,26,11,41,19,18, 9,36,59,
4,46,53, 5,23,22,61,12,54,39,37,15,47, 7,20,14,29,38,31,63,62,13, 6,45,
41,17,36,26,51,19,35,59,33,11,50,44,34, 1,57,27,10,60,25, 3, 2,58,49,43,
55,30,37,20, 7, 6,45,63,38,23,21,62,31,54, 4,61,13,22,15,47,46,28,53,29,
25, 1,49,10,35, 3,19,43,17,60,34,57,18,50,41,11,59,44, 9,52,51,42,33,27,
39,14,21, 4,54,53,29,47,22, 7, 5,46,15,38,55,45,28, 6,62,31,30,12,37,13,
9,50,33,59,19,52, 3,27, 1,44,18,41, 2,34,25,60,43,57,58,36,35,26,17,11,
23,61, 5,55,38,37,13,31, 6,54,20,30,62,22,39,29,12,53,46,15,14,63,21,28,
58,34,17,43, 3,36,52,11,50,57, 2,25,51,18, 9,44,27,41,42,49,19,10, 1,60,
7,45,20,39,22,21,28,15,53,38, 4,14,46, 6,23,13,63,37,30,62,61,47, 5,12,
42,18, 1,27,52,49,36,60,34,41,51, 9,35, 2,58,57,11,25,26,33, 3,59,50,44,
54,29, 4,23, 6, 5,12,62,37,22,55,61,30,53, 7,28,47,21,14,46,45,31,20,63,
26, 2,50,11,36,33,49,44,18,25,35,58,19,51,42,41,60, 9,10,17,52,43,34,57,
38,13,55, 7,53,20,63,46,21, 6,39,45,14,37,54,12,31, 5,61,30,29,15, 4,47,
18,59,42, 3,57,25,41,36,10,17,27,50,11,43,34,33,52, 1, 2, 9,44,35,26,49,
30, 5,47,62,45,12,55,38,13,61,31,37, 6,29,46, 4,23,28,53,22,21, 7,63,39};

const  unsigned char pk_si[256] = {
0xe0, 0x4f, 0xd7, 0x14, 0x2e, 0xf2, 0xbd, 0x81,
0x3a, 0xa6, 0x6c, 0xcb, 0x59, 0x95, 0x03, 0x78,
0x4f, 0x1c, 0xe8, 0x82, 0xd4, 0x69, 0x21, 0xb7,
0xf5, 0xcb, 0x93, 0x7e, 0x3a, 0xa0, 0x56, 0x0d,
0xf3, 0x1d, 0x84, 0xe7, 0x6f, 0xb2, 0x38, 0x4e,
0x9c, 0x70, 0x21, 0xda, 0xc6, 0x09, 0x5b, 0xa5,
0x0d, 0xe8, 0x7a, 0xb1, 0xa3, 0x4f, 0xd4, 0x12,
0x5b, 0x86, 0xc7, 0x6c, 0x90, 0x35, 0x2e, 0xf9,
0xad, 0x07, 0x90, 0xe9, 0x63, 0x34, 0xf6, 0x5a,
0x12, 0xd8, 0xc5, 0x7e, 0xbc, 0x4b, 0x2f, 0x81,
0xd1, 0x6a, 0x4d, 0x90, 0x86, 0xf9, 0x38, 0x07,
0xb4, 0x1f, 0x2e, 0xc3, 0x5b, 0xa5, 0xe2, 0x7c,
0x7d, 0xd8, 0xeb, 0x35, 0x06, 0x6f, 0x90, 0xa3,
0x14, 0x27, 0x82, 0x5c, 0xb1, 0xca, 0x4e, 0xf9,
0xa3, 0x6f, 0x90, 0x06, 0xca, 0xb1, 0x7d, 0xd8,
0xf9, 0x14, 0x35, 0xeb, 0x5c, 0x27, 0x82, 0x4e,
0x2e, 0xcb, 0x42, 0x1c, 0x74, 0xa7, 0xbd, 0x61,
0x85, 0x50, 0x3f, 0xfa, 0xd3, 0x09, 0xe8, 0x96,
0x4b, 0x28, 0x1c, 0xb7, 0xa1, 0xde, 0x72, 0x8d,
0xf6, 0x9f, 0xc0, 0x59, 0x6a, 0x34, 0x05, 0xe3,
0xca, 0x1f, 0xa4, 0xf2, 0x97, 0x2c, 0x69, 0x85,
0x06, 0xd1, 0x3d, 0x4e, 0xe0, 0x7b, 0x53, 0xb8,
0x94, 0xe3, 0xf2, 0x5c, 0x29, 0x85, 0xcf, 0x3a,
0x7b, 0x0e, 0x41, 0xa7, 0x16, 0xd0, 0xb8, 0x6d,
0x4d, 0xb0, 0x2b, 0xe7, 0xf4, 0x09, 0x81, 0xda,
0x3e, 0xc3, 0x95, 0x7c, 0x52, 0xaf, 0x68, 0x16,
0x16, 0x4b, 0xbd, 0xd8, 0xc1, 0x34, 0x7a, 0xe7,
0xa9, 0xf5, 0x60, 0x8f, 0x0e, 0x52, 0x93, 0x2c,
0xd1, 0x2f, 0x8d, 0x48, 0x6a, 0xf3, 0xb7, 0x14,
0xac, 0x95, 0x36, 0xeb, 0x50, 0x0e, 0xc9, 0x72,
0x72, 0xb1, 0x4e, 0x17, 0x94, 0xca, 0xe8, 0x2d,
0x0f, 0x6c, 0xa9, 0xd0, 0xf3, 0x35, 0x56, 0x8b};

const unsigned char shift[8] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};

unsigned char newpc[16][48];
//no_init unsigned char newsi[8][64][4];
//code unsigned char ***newsi;
unsigned char nul;



void deskey(unsigned char *temp,unsigned char key[16][8]);
void des(unsigned char *plain,unsigned char key_6[16][8],unsigned char mode,unsigned char *ciphertext);

/*
  DES 测试
*/
/*
main()
{
     unsigned char i;
     memcpy(text,"012345678",8);     //text<-密码种子
     deskey(text,key);              //key<-生成密钥
     memcpy(detext,"My_god !",8);   //detext<-待加密明文
     des(detext,key,EN_DES,text);   //text<-生成密文
     memcpy(detext,"00000000",8);   //清除明文以便于测试
     des(text,key,DE_DES,detext);   //detext<-解密后的明文
     i=10;

}
*/

/*
  64bit 3 DES 快速算法
  mode=EN_DES 为加密运算
  plain 中为8bytes的待加密明文,key_6为密钥,
  ciphertext 为加密后的密文

  mode=DE_DES 为解密运算
  plain 中为8bytes的待密文,key_6为密钥,
  ciphertext 为解密后的明文   、
  当OSC=18.432MHz时,约需41ms(加密和解密的时间基本相同)
*/

void des(unsigned char *plain,unsigned char key_6[16][8],unsigned char mode,unsigned char *ciphertext)
{
    unsigned char i,j,k,m,*s1,r0_6[8];
    unsigned char textbit[65];
    unsigned char tranx[65];

    k = 0;
    for(i=0;i<8;++i){
        m = plain[i];
        for(j=0;j<8;++j) textbit[++k] = m & shift[j] && 1;
    }

    for(i=0;i<65;++i) tranx[i] = textbit[i];
    for(i=1;i<65;++i) textbit[i] = tranx[ip[i]];

    for(i=0;i<16;++i){
        for(j=1;j<33;++j) tranx[j] = *(textbit+32+j);
        r0_6[0] = textbit[37];
        r0_6[1] = textbit[41];
        r0_6[2] = textbit[45];
        r0_6[3] = textbit[49];
        r0_6[4] = textbit[53];
        r0_6[5] = textbit[57];
        r0_6[6] = textbit[61];
        r0_6[7] = textbit[33];
        k = textbit[32];
        textbit[32] = textbit[64];
        for(j=0;j<5;++j){
            m = *(shift+2+j);
            if(*(textbit+32+j)) r0_6[0] |= m;
            if(*(textbit+36+j)) r0_6[1] |= m;
            if(*(textbit+40+j)) r0_6[2] |= m;
            if(*(textbit+44+j)) r0_6[3] |= m;
            if(*(textbit+48+j)) r0_6[4] |= m;
            if(*(textbit+52+j)) r0_6[5] |= m;
            if(*(textbit+56+j)) r0_6[6] |= m;
            if(*(textbit+60+j)) r0_6[7] |= m;
        }
        textbit[32] = k;
        k = 32;
        mode ? (s1 = key_6[i]) : (s1 = key_6[15-i]);
        for(j=0;j<8;++j){
            m = r0_6[j] ^ *(s1++);
//            s2 = newsi[j][m];
//            textbit[++k] = *(++s2);
//            textbit[++k] = *(++s2);
//            textbit[++k] = *(++s2);
//            textbit[++k] = *(++s2);
            textbit[++k] = 0x0;
            textbit[++k] = 0x0;
            textbit[++k] = 0x0;
            textbit[++k] = 0x0;


        }
        k=textbit[33]; /* transpose */
        textbit[33]=textbit[48];textbit[48]=textbit[42];textbit[42]=textbit[47];
        textbit[47]=textbit[63];textbit[63]=textbit[36];textbit[36]=textbit[53];
        textbit[53]=textbit[64];textbit[64]=textbit[57];textbit[57]=textbit[51];
        textbit[51]=textbit[56];textbit[56]=textbit[41];textbit[41]=k;
        k=textbit[34];
        textbit[34]=textbit[39];textbit[39]=textbit[60];textbit[60]=textbit[38];
        textbit[38]=textbit[44];textbit[44]=textbit[58];textbit[58]=textbit[45];
        textbit[45]=textbit[37];textbit[37]=textbit[61];textbit[61]=textbit[54];
        textbit[54]=textbit[59];textbit[59]=textbit[62];textbit[62]=textbit[43];
        textbit[43]=textbit[55];textbit[55]=textbit[35];textbit[35]=textbit[52];
        textbit[52]=textbit[46];textbit[46]=textbit[50];textbit[50]=textbit[40];
        textbit[40]=textbit[49];textbit[49]=k;
        for(j=1;j<33;++j) {
            textbit[j+32] ^= textbit[j];
            textbit[j] = tranx[j];
        }
    }

    k = 0;
    s1 = &ciphertext[0];
    for(i=0;i<8;++i){
        *s1 = 0;
        for(j=0;j<8;++j) if(textbit[fp[k++]]) *s1 |= shift[j];
        ++s1;
    }
}

/*
   密钥生成程序
   temp[8]中为64bit(8个bytes)的密码种子
   key为生成的密钥
   当OSC=18.432MHz时,约需48ms
*/
void deskey(unsigned char *temp,unsigned char key[16][8])
{
    unsigned char i,j,k,m,*s;
    unsigned char tempbit[65];
//    xdata unsigned char tempbit[65],tranx[65];

    m = 0;
    for(i=0;i<8;++i){
        k = temp[i];
        for(j=0;j<8;++j) tempbit[++m] = k & shift[j] && 1;
    }
    s = &newpc[0][0];
    for(i=0;i<16;++i){
        for(j=0;j<8;++j){
            key[i][j] = 0;
            for(k=2;k<8;++k) if(tempbit[*(s++)]) key[i][j] |= shift[k];
        }
    }
}

