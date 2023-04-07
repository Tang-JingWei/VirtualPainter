#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace std;
using namespace cv;

extern int paint_enable;  //画笔使能
extern int threshold_enbale; //双阈值图显示使能

extern vector<vector<int>> myPoints;
extern int myBlue, myGreen, myRed; //混合颜色分量
extern int inkSize; //墨汁大小
extern int minArea;


void Painter();


