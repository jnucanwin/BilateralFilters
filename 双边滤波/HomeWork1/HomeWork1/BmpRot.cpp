#include <stdio.h>  
#include "BmpRot.h"  
#include "stdlib.h"  
#include "math.h"  
#include <iostream>  
#define PI 3.14159//Բ���ʺ궨��  
#define LENGTH_NAME_BMP 30//bmpͼƬ�ļ�������󳤶�  
using namespace std;
BITMAPFILEHEADER strHead;
RGBQUAD strPla[256], strPla1[256];//256ɫ��ɫ��  
BITMAPINFOHEADER strInfo, strInfo1;
void showBmpHead(BITMAPFILEHEADER pBmpHead) {
	cout << "λͼ�ļ�ͷ:" << endl;
	cout << "�ļ���С:" << pBmpHead.bfSize << endl;
	cout << "������_1:" << pBmpHead.bfReserved1 << endl;
	cout << "������_2:" << pBmpHead.bfReserved2 << endl;
	cout << "ʵ��λͼ���ݵ�ƫ���ֽ���:" << pBmpHead.bfOffBits << endl << endl;
}
void showBmpInforHead(tagBITMAPINFOHEADER pBmpInforHead) {
	cout << "λͼ��Ϣͷ:" << endl;
	cout << "�ṹ��ĳ���:" << pBmpInforHead.biSize << endl;
	cout << "λͼ��:" << pBmpInforHead.biWidth << endl;
	cout << "λͼ��:" << pBmpInforHead.biHeight << endl;
	cout << "biPlanesƽ����:" << pBmpInforHead.biPlanes << endl;
	cout << "biBitCount������ɫλ��:" << pBmpInforHead.biBitCount << endl;
	cout << "ѹ����ʽ:" << pBmpInforHead.biCompression << endl;
	cout << "biSizeImageʵ��λͼ����ռ�õ��ֽ���:" << pBmpInforHead.biSizeImage << endl;
	cout << "X����ֱ���:" << pBmpInforHead.biXPelsPerMeter << endl;
	cout << "Y����ֱ���:" << pBmpInforHead.biYPelsPerMeter << endl;
	cout << "ʹ�õ���ɫ��:" << pBmpInforHead.biClrUsed << endl;
	cout << "��Ҫ��ɫ��:" << pBmpInforHead.biClrImportant << endl;
}
int main() {
	char strFile[LENGTH_NAME_BMP], strFile1[LENGTH_NAME_BMP] = "1.bmp",strFileOut[LENGTH_NAME_BMP];//bmp�ļ���
	IMAGEDATA *imagedata = NULL;//��̬����洢ԭͼƬ��������Ϣ�Ķ�ά����  
	int width, height;//ͼƬ�Ŀ�Ⱥ͸߶�  
	cout << "��������Ҫ��ȡ���ļ���:" << endl;
	cin >> strFile;
	FILE *fpi, *fpw;
	fpi = fopen(strFile, "rb");
	if (fpi != NULL) {
		WORD bfType;
		fread(&bfType, 1, sizeof(WORD), fpi);
		if (0x4d42 != bfType)
		{
			cout << "the file is not a bmp file!" << endl;
			return NULL;
		}
		fread(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpi);
		fread(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpi);
		showBmpInforHead(strInfo);
		if (strInfo.biClrUsed != 256) {
			printf("�εΣ�ͼ�������⣡������������������������");
			int a;
			cin >> a;
		}
		for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
		{
			fread((char *)&(strPla[nCounti].rgbBlue), 1, sizeof(BYTE), fpi);
			fread((char *)&(strPla[nCounti].rgbGreen), 1, sizeof(BYTE), fpi);
			fread((char *)&(strPla[nCounti].rgbRed), 1, sizeof(BYTE), fpi);
			fread((char *)&(strPla[nCounti].rgbReserved), 1, sizeof(BYTE), fpi);
		}
		printf("ԭʼ��ɫ�壺\n");
		for (unsigned int nCounti = 0; nCounti <10; nCounti++)
		{

			printf("%d  %d  %d %d \n", strPla[nCounti].rgbBlue, strPla[nCounti].rgbGreen, strPla[nCounti].rgbRed, strPla[nCounti].rgbReserved);
		}
		printf("************************\n"); 
//////////////////////////////////////////////////////
		/*for (unsigned int nCounti = 0; nCounti < strInfo.biClrUsed; nCounti++)
		{

			printf("%d  %d  %d %d \n", strPla[nCounti].rgbBlue, strPla[nCounti].rgbGreen, strPla[nCounti].rgbRed, strPla[nCounti].rgbReserved);
		}

/////////////////////////////////////////////////////////////////
		/*��ɫ�廯Ϊ�Ҷ�*/
		double clor = 0;
		for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
		{
			clor = (0.2989   *   strPla[nCounti].rgbRed + 0.5870   *   strPla[nCounti].rgbGreen + 0.1140   *   strPla[nCounti].rgbBlue);
			if (clor - (int)clor >= 0.5)

				strPla[nCounti].rgbBlue = (0.2989   *   strPla[nCounti].rgbRed + 0.5870   *   strPla[nCounti].rgbGreen + 0.1140   *   strPla[nCounti].rgbBlue) + 1;
			else
				strPla[nCounti].rgbBlue = (0.2989   *   strPla[nCounti].rgbRed + 0.5870   *   strPla[nCounti].rgbGreen + 0.1140   *   strPla[nCounti].rgbBlue);
			strPla[nCounti].rgbBlue = strPla[nCounti].rgbBlue;
			strPla[nCounti].rgbGreen = strPla[nCounti].rgbBlue;
			strPla[nCounti].rgbRed = strPla[nCounti].rgbBlue;

		}
		
/////////////////////////////////////////////////////////////////////////////


		width = strInfo.biWidth;
		height = strInfo.biHeight;
		width = (width + 3) / 4 * 4;//����Ϊ��׼ֵ
		imagedata = (IMAGEDATA*)malloc(width * height * sizeof(IMAGEDATA));

		for (int i = 0; i < height; ++i){
			for (int j = 0; j < width; ++j){
				(*(imagedata + i *  width + j)).blue = 0;
				//(*(imagedata + i * width + j)).green = 0;  
				//(*(imagedata + i *  width + j)).red = 0;  
			}
		}

		fread(imagedata, sizeof(struct tagIMAGEDATA) * width, height, fpi);
		/*ͼ�����ݻ�Ϊ��׼*/
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				(*(imagedata + i *  width + j)).blue = strPla[(*(imagedata + i *  width + j)).blue].rgbBlue;

			}
		}
		/*��ɫ�廯Ϊ��׼ֵ*/
		for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
		{
			strPla[nCounti].rgbBlue = nCounti;
			strPla[nCounti].rgbBlue = strPla[nCounti].rgbBlue;
			strPla[nCounti].rgbGreen = strPla[nCounti].rgbBlue;
			strPla[nCounti].rgbRed = strPla[nCounti].rgbBlue;
			//printf("%d  %d  %d  \n", strPla[nCounti].rgbBlue, strPla[nCounti].rgbGreen, strPla[nCounti].rgbRed);
		}
		printf("ת�����ɫ�壺\n");
		for (unsigned int nCounti = 0; nCounti <10; nCounti++)
		{

			printf("%d  %d  %d %d \n", strPla[nCounti].rgbBlue, strPla[nCounti].rgbGreen, strPla[nCounti].rgbRed, strPla[nCounti].rgbReserved);
		}
		printf("************************\n");
		fclose(fpi);

	}
	else
	{
		cout << "file open error!" << endl;
		return NULL;
	}



	int num = 0;
	IMAGEDATA **befor;
	befor = new IMAGEDATA *[height];
	for (int i = 0; i < height; i++)
		befor[i] = new IMAGEDATA[width];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			befor[i][j].blue = imagedata[num].blue;
			num++;
		}
	}
	for (int i = 0; i <10; i++) {
		for (int j = 0; j < 10; j++) {

			printf("%d  ", befor[i][j].blue);
		}
		printf("\n");
	}
	IMAGEDATA **after;
	after = new IMAGEDATA *[height];
	for (int i = 0; i < height; i++)
		after[i] = new IMAGEDATA[width];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			after[i][j].blue = befor[i][j].blue;
			num++;
		}
	}
	IMAGEDATA *after1 = new IMAGEDATA[height*width];
	//////////////////////////////////////////////////////////////////////
	/*����ͼ����*/
	int size = 3;
	cout << "������ģ���С��";
	cin >> size;

	int **window;
	double **sub_goss_core = new double *[size];
	for (int i = 0; i < size; i++)
		sub_goss_core[i] = new double[size];

	


	window = new int *[size];
	for (int i = 0; i < size; i++)
		window[i] = new int[size];


	int x, sigma1, sigma2;
	cout << "����������sigmaֵ��";
	cin >> sigma1 >> sigma2;
	sub_goss_core=GussCore(sub_goss_core, size, sigma1, sigma2);
	int x_,y_;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			
			for (int ii = 0; ii < size; ii++) {
				for (int jj = 0; jj < size; jj++) {
					x_ = i + ii - size / 2;
					y_ = j + jj - size / 2;
					if (x_ < 0)
						x_ = i + ii;
					if (y_ < 0)
						y_ = j + jj;
					if (x_ >= height)
						x_ = i + ii-size;
					if (y_ >= width)
						y_ = j + jj-size;
					window[ii][jj] = befor[x_][y_].blue;
					



				}
			}
			x = bilateralFilter(window, size, sigma1,sigma2, sub_goss_core);//˫���˲�����
			after[i][j].blue =x;
		}
	}


	for (int i = 0; i < size; i++) {
		delete[]window[i];
		delete[]sub_goss_core[i];
	}
	window = NULL;
	sub_goss_core = NULL;


	printf("************************\n");
	for (int i = 0; i <10; i++) {
		for (int j = 0; j < 10; j++) {

			printf("%d  ", after[i][j].blue);
		}
		printf("\n");
	}
//////////////////////////////////////////////////////////////////////////////////////////
	
	num = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			after1[num].blue = after[i][j].blue;
			num++;
		}
	}

//////////////////////////////////////////////////////////////////////
	//����bmpͼƬ  

	printf("\n���������ͼ������:");
	
	
	cin >> strFileOut;
	if ((fpw = fopen(strFileOut, "wb")) == NULL)
	{
		cout << "create the bmp file error!" << endl;
		return NULL;
	}
	WORD bfType_w = 0x4d42;
	fwrite(&bfType_w, 1, sizeof(WORD), fpw);
	//fpw +=2;  
	fwrite(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpw);
	strInfo.biWidth = width;
	strInfo.biHeight = height;

	fwrite(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpw);
	//�����ɫ������  
	for (unsigned int nCounti = 0; nCounti < strInfo.biClrUsed; nCounti++)
	{
		fwrite(&strPla[nCounti].rgbBlue, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbGreen, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbRed, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbReserved, 1, sizeof(BYTE), fpw);

	}
	/*if (strInfo.biClrUsed == 256) {
		for (unsigned int nCounti = 0; nCounti < strInfo.biClrUsed; nCounti++)
		{
			fwrite(&strPla[nCounti].rgbBlue, 1, sizeof(BYTE), fpw);
			fwrite(&strPla[nCounti].rgbGreen, 1, sizeof(BYTE), fpw);
			fwrite(&strPla[nCounti].rgbRed, 1, sizeof(BYTE), fpw);
			fwrite(&strPla[nCounti].rgbReserved, 1, sizeof(BYTE), fpw);

		}
	}
	else {
		printf("ͷ�ļ�����������һ���ο�.bmp�ļ�:\n");
		fpi = fopen(strFile1, "rb");
		if (fpi != NULL) {
			WORD bfType;
			fread(&bfType, 1, sizeof(WORD), fpi);
			if (0x4d42 != bfType)
			{
				cout << "the file is not a bmp file!" << endl;
				return NULL;
			}
			fread(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpi);
			fread(&strInfo1, 1, sizeof(tagBITMAPINFOHEADER), fpi);

			for (unsigned int nCounti = 0; nCounti < strInfo1.biClrUsed; nCounti++)
			{
				fread((char *)&(strPla1[nCounti].rgbBlue), 1, sizeof(BYTE), fpi);
				fread((char *)&(strPla1[nCounti].rgbGreen), 1, sizeof(BYTE), fpi);
				fread((char *)&(strPla1[nCounti].rgbRed), 1, sizeof(BYTE), fpi);
				fread((char *)&(strPla1[nCounti].rgbReserved), 1, sizeof(BYTE), fpi);
			}
		}
		for (unsigned int nCounti = 0; nCounti < strInfo1.biClrUsed; nCounti++)
		{
			fwrite(&strPla1[nCounti].rgbBlue, 1, sizeof(BYTE), fpw);
			fwrite(&strPla1[nCounti].rgbGreen, 1, sizeof(BYTE), fpw);
			fwrite(&strPla1[nCounti].rgbRed, 1, sizeof(BYTE), fpw);
			fwrite(&strPla1[nCounti].rgbReserved, 1, sizeof(BYTE), fpw);
		}
	}*/
	//������������  
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			fwrite(&((*(after1 + i * width + j)).blue), 1, sizeof(BYTE), fpw);
			
		}
	}
	fclose(fpw);

	//�ͷ��ڴ�  
	delete[] imagedata;

}