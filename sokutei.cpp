#include<opencv2\opencv.hpp>
using namespace cv;
#include"sokutei.h"
#include <math.h>
#include <iostream>
using namespace std;

double position(int  sx,int  sy)
{
	double f=0.018;
	double Y=-8;
	double H=2105;//水平線の位置
	double y=0.0156/3264;
	double x=0.0235/4912;
	double A=atan2((H-1632)*y,f);
	double B=atan2((sy-12)*y,f);//12＝写真内での水平線の中心から海面までのピクセル数
	double C=A-B;
	double Z=Y/tan(C);
	double X=x*sx*Z/f;
	double distance=sqrt(Z*Z+X*X);
	cout << distance << endl;
	return distance;
}
