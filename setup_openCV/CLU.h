#include<iostream>
#include<math.h>
#include<vector>
#include<numeric>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class clu
{
public:
	static double variance(vector<int> sample);//计算方差
	static vector<int> CreateSample(int x, int y, int k, Mat gry);//采样并做差分，k代表采用方式，1横向，2纵向，3斜向,0三个方向混合
private:

};



