#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace std;
using namespace cv;

extern int paint_enable;  //����ʹ��
extern int threshold_enbale; //˫��ֵͼ��ʾʹ��

extern vector<vector<int>> myPoints;
extern int myBlue, myGreen, myRed; //�����ɫ����
extern int inkSize; //ī֭��С
extern int minArea;


void Painter();


