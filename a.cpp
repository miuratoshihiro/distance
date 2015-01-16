#include<opencv2\opencv.hpp>
using namespace cv;
#include"sokutei.h"

int main()
{
	Mat img0 = imread("camera/ogasawaramaru2.jpg");
	namedWindow("trck0");
	char    str[500];
	sprintf(str,"camera/trck000000.JPG");
	Mat img = imread(str);
	namedWindow("trck");
	int xmin = 0, ymin = 0;
	long long sqsum_min = LLONG_MAX;
	uchar * data = img.data;
	uchar * data0 = img0.data;
	Size sz;
	sz.width = 1200;
	sz.height = 800;
	Mat img2;
	for(int y = 0; y< img.rows-img0.rows; y++)
	{
		for(int x = 0; x < img.cols- img0.cols; x++)
		{
			long long sqsum =0;
			for(int u = 0; u <  img0.cols; u++)
			{
				for(int v = 0; v < img0.rows; v++)
				{
					int r, g, b;
					r =data[3*(x+u)+img.cols*(y+v)*3+2];
					g =data[3*(x+u)+img.cols*(y+v)*3+1];
					b =data[3*(x+u)+img.cols*(y+v)*3];
					int r0, g0, b0;
					r0=data0[3*u+img0.cols*v*3+2];
					g0=data0[3*u+img0.cols*v*3+1];
					b0=data0[3*u+img0.cols*v*3];

					sqsum+= (r-r0) *(r-r0);
					sqsum+= (g-g0) *(g-g0);
					sqsum+= (b-b0) *(b-b0);
				}
			}
			if (sqsum < sqsum_min)
			{
				sqsum_min = sqsum;
				xmin = x;
				ymin = y;
			}
		}
	}
	Point p0;
	p0.x=xmin;
	p0.y=ymin;
	Point p1;
	p1.x=xmin+img0.cols;
	p1.y=ymin+img0.rows;
	rectangle(img,p0,p1,Scalar(200,100,255));
	resize(img,img2,sz);
	FILE *D;
	D = fopen("kyori.txt", "w");
	int px=img.cols/2;//画像の中心
	int py=img.rows/2;
	int tx= xmin+img0.cols/2; //テンプレート画像の中心
	int ty= ymin+img0.rows/2;
	int sx=tx-px;//画像の中心からテンプレートの中心までの距離
	int sy=py-ty;
	printf("%d\n",tx);
	printf("%d\n",ty);
	double RD= position(sx,sy);
	fprintf(D,"%f \n",RD);
	fclose(D);
	imshow("trck0", img0);
	imshow("trck", img2);
	cvWaitKey(0);
