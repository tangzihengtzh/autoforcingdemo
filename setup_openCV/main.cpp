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
	if (event == CV_EVENT_LBUTTONDOWN)    //����
	{
		prept = Point(x, y);
		cout << "��ǰ������꣺";
		cout << x << "," << y << endl;
		Xpoint = x; Ypoint = y;
		//cout << "�Ҷ�ֵ:" << (int)gry.at<uchar>(Ypoint, Xpoint) << endl;

		//cout << "�Ҷ�ֵ:" << (int)CutC.at<uchar>(Ypoint, Xpoint) << endl;

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
		imshow("ԭ��ɫͼ", src);
		down = true;
	}
}

int main()
{
	src = imread("cut1.jpg", 1);

	imshow("ԭ��ɫͼ", src);
	
	cvSetMouseCallback("ԭ��ɫͼ", on_mouse, 0);//�ؼ����ú���������ʵ�ֻ�ȡ�����λ������

	cvtColor(src, gry, COLOR_BGR2GRAY);
	//imshow("�Ҷ�ͼ", gry);
	//cvSetMouseCallback("�Ҷ�ͼ", on_mouse, 0);
	cvSetMouseCallback("ԭ��ɫͼ", on_mouse, 0);

	//cout <<"�Ҷ�ֵ:"<< (int)gry.at<uchar>(Ypoint, Xpoint);//��������ڻ�ȡָ�����ػҶ�,����1Ϊ��ֱ���꣬����2Ϊˮƽ����

	//cvDestroyAllWindows();
	cvWaitKey(0);
	return 0;
}



