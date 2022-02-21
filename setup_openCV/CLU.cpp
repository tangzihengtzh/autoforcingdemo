#include "CLU.h"
#include<iostream>
#include<math.h>
#include<vector>
#include<numeric>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;


double clu::variance(vector<int> sample)
{	//此函数用于计算一组整数样本的方差
	int sum = accumulate(sample.begin(), sample.end(), 0);
	double main = sum / sample.size();
	double vari = 0;
	for (int i = 0; i < sample.size(); i++)
	{
		vari += (sample[i] - main) * (sample[i] - main);
	}
	return vari;
}

// 重载+号以拼接两个vector
template <typename T>
vector<T>& operator +(vector<T>& v1, vector<T>& v2)
{
	v1.insert(v1.end(), v2.begin(), v2.end());
	return v1;
}

template <typename T>
vector<T> MergeVecInt(vector<T> v1, vector<T>v2)
{
	return v1 + v2;
}

vector<int> clu::CreateSample(int x, int y, int k, Mat gry)
{
	int edge = 10;
	if (x>gry.cols-edge-1 || x<edge+1 || y<edge+1|| y>gry.rows- edge - 1)
	{
		cout << "靠近边缘，无法采样\n";
		vector<int>nu = { -1 };
		return nu;
	}
	vector<int> sample = {};
	if (k==0)
	{
		return MergeVecInt(
			MergeVecInt(
				CreateSample(x, y, 1, gry), 
				CreateSample(x, y, 2, gry)
			), 
			CreateSample(x, y, 3, gry)
		);
	}
	else if (k==1)
	{
		for (int i = -edge; i <= edge; i++)
		{
			sample.push_back(abs((int)gry.at<uchar>(y, x + i) - (int)gry.at<uchar>(y, x + i + 1)));
		}
	}
	else if (k==2)
	{
		for (int i = -edge; i <= edge; i++)
		{
			sample.push_back(abs((int)gry.at<uchar>(y + i, x) - (int)gry.at<uchar>(y + i + 1, x)));
		}
	}
	else if (k==3)
	{
		for (int i = -edge; i <= edge; i++)
		{
			sample.push_back(abs((int)gry.at<uchar>(y + i, x + i) - (int)gry.at<uchar>(y + i + 1, x + i + 1)));
		}
	}
	return sample;
}

