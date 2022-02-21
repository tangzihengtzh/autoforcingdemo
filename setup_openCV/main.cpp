#include<opencv2/opencv.hpp>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include"CLU.h"
#include<vector>

using namespace cv;
using namespace std;

int Xpoint = 0, Ypoint = 0;

Mat src;
Mat gry;
bool down = false;
Point prept = Point(-1, -1);
Point curpt = Point(-1, -1);


template <typename T>
void PrintVec(vector<T> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

Mat CutC = imread("cut1", 1);
Mat CutG;
int index = 0;
void on_mouse(int event, int x, int y, int flags, void* ustc)
{
	if (event == CV_EVENT_LBUTTONDOWN)    //按下
	{
		prept = Point(x, y);
		cout << "当前点击坐标：";
		cout << x << "," << y << endl;
		Xpoint = x; Ypoint = y;
		//cout << "灰度值:" << (int)gry.at<uchar>(Ypoint, Xpoint) << endl;

		//cout << "灰度值:" << (int)CutC.at<uchar>(Ypoint, Xpoint) << endl;

		string CutI = "cut";
		int max = -1;
		for (int i = 1; i <= 5; i++)
		{
			CutI = "cut" + to_string(i) + ".jpg";
			CutC = imread(CutI, 1);
			//cvtColor(CutC, CutG, COLOR_BGR2GRAY);
			//cout << clu::variance(clu::CreateSample(Xpoint, Ypoint, 0, CutG));
			if (max< clu::variance(clu::CreateSample(Xpoint, Ypoint, 0, CutC)))
			{
				max = clu::variance(clu::CreateSample(Xpoint, Ypoint, 0, CutC));
				index = i;
			}
		}
		src = imread("cut" + to_string(index) + ".jpg", 1);
		imshow("原彩色图", src);
		down = true;
	}
}

int main()
{
	src = imread("cut1.jpg", 1);

	imshow("原彩色图", src);
	
	cvSetMouseCallback("原彩色图", on_mouse, 0);//关键内置函数，用以实现获取鼠标点击位置坐标

	cvtColor(src, gry, COLOR_BGR2GRAY);
	//imshow("灰度图", gry);
	//cvSetMouseCallback("灰度图", on_mouse, 0);
	cvSetMouseCallback("原彩色图", on_mouse, 0);

	//cout <<"灰度值:"<< (int)gry.at<uchar>(Ypoint, Xpoint);//此语句用于获取指定像素灰度,参数1为垂直坐标，参数2为水平坐标

	//cvDestroyAllWindows();
	cvWaitKey(0);
	return 0;
}



