#include <math.h>
#include "stdlib.h" 
#include <stdio.h>  
#include "BmpRot.h"  
#include "stdlib.h"  
#include "math.h"  
#include <iostream>  




double   ** GussCore(double **sub_goss_core,int ksize, int  sigma_d, int  sigma_g) {
	double  x2, y2;
	

	int center = ksize / 2;

	for (int i = 0; i < ksize; i++) {
		x2 = pow(i - center, 2);
		for (int j = 0; j < ksize; j++) {
			y2 = pow(j - center, 2);
			sub_goss_core[i][j] = -(x2 + y2) / (2 * sigma_d*sigma_d);
		}
	}
	return sub_goss_core;

}



int  bilateralFilter(int **img, int ksize, double sigma_d,double sigma_g, double **gussGore) {
	int center = ksize / 2;
	//生成高斯核
	/*double **sub_goss_core,x2,y2;
	sub_goss_core = new double *[ksize];
	for (int i = 0; i < ksize; i++)
		sub_goss_core[i] = new double[ksize];



	for (int i = 0; i < ksize; i++) {
		x2 = pow(i - center, 2);
		for (int j = 0; j < ksize; j++) {
			y2 = pow(j - center, 2);
			sub_goss_core[i][j] = -(x2 + y2) / (2 * sigma_d*sigma_d);
		}
	}*/

	//计算值域核

	double **sub_range_core;


	sub_range_core = new double *[ksize];
	for (int i = 0; i < ksize; i++)
		sub_range_core[i] = new double[ksize];
	
	for (int i = 0; i < ksize; i++) {
		for (int j = 0; j < ksize; j++) {
			sub_range_core[i][j] =- pow((img[i][j] - img[center][center]), 2)/(2*sigma_g*sigma_g);
		}
	}
	////////////////////////////////////////////////////////
	double **core;
	double c = 0;
	int  **int_core;
	int_core = new int *[ksize];
	core = new double *[ksize];
	for (int i = 0; i < ksize; i++) {
		core[i] = new double[ksize];
		int_core[i] = new int[ksize];
	}


	for (int i = 0; i < ksize; i++) {
		for (int j = 0; j < ksize; j++) {
			c = exp(sub_range_core[i][j] + sub_range_core[i][j]);
			if (c - (int)c >= 0.5)
				int_core[i][j] = (int)c + 1;
			else
				int_core[i][j] = (int)c + 1;
		}		
	}
	//归一化core
	int  sum = 0;
	for (int i = 0; i < ksize; i++) {
		for (int j = 0; j < ksize; j++) {
			sum += int_core[i][j];
		}
	}
	for (int i = 0; i < ksize; i++) {
		for (int j = 0; j < ksize; j++) {
			core[i][j]= int_core[i][j]/(double)sum;
		//	printf("%f  ", core[i][j]);
		}
		//printf("\n");
	}
	//printf("\********************************************\n");
	for (int i = 0; i < ksize; i++) {
		for (int j = 0; j < ksize; j++) {
			
		//	printf("%d  ", img[i][j]);
		}
		//printf("\n");
	}
	//计算像素灰度值

	double out_gray=0;
	for (int i = 0; i < ksize; i++) {
		for (int j = 0; j < ksize; j++) {
			out_gray = out_gray +img[i][j] * core[i][j];
			//printf("%f ", out_gray);
		}
	}





	for (int i = 0; i < ksize; i++) {
		
		delete[]sub_range_core[i];
		delete[]core[i];
		delete[] int_core[i];
		
	}
	
	sub_range_core = NULL;
	core = NULL;
	int_core = NULL;

	return out_gray;
}

