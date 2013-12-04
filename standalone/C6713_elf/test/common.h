#ifndef _COMMON_H_
#define _COMMON_H_

#define  commom_Restrict(a,b) ((a) = ((a)>=(b))?(a)=(b):(((a)<=-(b))?-(b):(a)))
#define		TRUE       1
#define		FALSE      0
	
#define    	SUCCESS    0
#define    	FAILED     1
typedef union
{
    unsigned int		u32;
	int					i32;
    float       		f32;
	unsigned short		u16[2];
	short				i16[2];
    unsigned char		u8[4];
}Union_byte4;

unsigned short common_crc_calculate(unsigned char *source_dat,int dat_len);
void 	common_i162bytes(short i16,unsigned char *b1,unsigned char *b2);
void 	common_i322bytes(int i32,unsigned char *b1,unsigned char *b2,unsigned char *b3,unsigned char *b4);
void 	common_f322bytes(float f,unsigned char *b1,unsigned char *b2,unsigned char *b3,unsigned char *b4);
void 	common_f642bytes(double f,unsigned char *b1,unsigned char *b2,unsigned char *b3,unsigned char *b4,unsigned char *b5,unsigned char *b6,unsigned char *b7,unsigned char *b8);
void 	common_bytes2i16(unsigned char b1,unsigned char b2,short *i16);
void 	common_bytes2i32(unsigned char b1,unsigned char b2,unsigned char b3,unsigned char b4,int *i32);
void 	common_bytes2f32(unsigned char b1,unsigned char b2,unsigned char b3,unsigned char b4,float *f32);
void 	common_bytes2f64(unsigned char b1,unsigned char b2,unsigned char b3,unsigned char b4,unsigned char b5,unsigned char b6,unsigned char b7,unsigned char b8,double *f64);
int 	common_b_search_u(float *fx,int len,float x,int max_limit);
int 	common_b_search_d(float *fx,int len,float x,int max_limit);
float 	common_standard_lag1y1d(float *x,float *y,float x0,int len);
float  	common_standard_lag1y2d(float *x_r,int rows,float *x_c,int cols,float *fx,float xr,float xc);
float 	common_atan_c(float y,float x);
float 	common_sign(float x);
Min2MulD   common_Min2Mul(float *t,float *X,float *Y,float *Z,int N);

#endif

