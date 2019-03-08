typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

//λͼ�ļ�ͷ����;  
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������  
//Ҫ�Ǽ��˵Ļ���������ȷ��ȡ�ļ���Ϣ��  
typedef struct  tagBITMAPFILEHEADER {
	//WORD bfType;//�ļ����ͣ�������0x424D�����ַ���BM��  
	DWORD bfSize;//�ļ���С  
	WORD bfReserved1;//������  
	WORD bfReserved2;//������  
	DWORD bfOffBits;//���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���  
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;//��Ϣͷ��С  
	LONG biWidth;//ͼ����  
	LONG biHeight;//ͼ��߶�  
	WORD biPlanes;//λƽ����������Ϊ1  
	WORD biBitCount;//ÿ����λ��  
	DWORD  biCompression; //ѹ������  
	DWORD  biSizeImage; //ѹ��ͼ���С�ֽ���  
	LONG  biXPelsPerMeter; //ˮƽ�ֱ���  
	LONG  biYPelsPerMeter; //��ֱ�ֱ���  
	DWORD  biClrUsed; //λͼʵ���õ���ɫ����  
	DWORD  biClrImportant; //��λͼ����Ҫ��ɫ����  
}BITMAPINFOHEADER; //λͼ��Ϣͷ����  

typedef struct tagRGBQUAD {
	BYTE rgbBlue; //����ɫ����ɫ����  
	BYTE rgbGreen; //����ɫ����ɫ����  
	BYTE rgbRed; //����ɫ�ĺ�ɫ����  
	BYTE rgbReserved; //����ֵ  
}RGBQUAD;//��ɫ�嶨��  

		 //������Ϣ  
typedef struct tagIMAGEDATA
{
	BYTE blue;
	//BYTE green;  
	//BYTE red;  
}IMAGEDATA;
int  bilateralFilter(int **img, int ksize, double sigma_d, double sigma_g, double **gussGore);
double   ** GussCore(double **sub_goss_core, int ksize, int  sigma_d, int  sigma_g);