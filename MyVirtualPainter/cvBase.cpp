#include "VirtualPainter.h"
#include "cvBase.h"

int H_min = 0,   H_max = 141;
int S_min = 113,  S_max = 223;
int V_min = 158,  V_max = 199;

//默认缩放2.0
float resizeNum = 1.5;

void TrackBar(Mat& image)
{
	namedWindow("跟踪条", WINDOW_FREERATIO);

	createTrackbar("H最小值:", "跟踪条", &H_min, 180);
	createTrackbar("S最小值:", "跟踪条", &S_min, 255);
	createTrackbar("V最小值:", "跟踪条", &V_min, 255);
	createTrackbar("H最大值:", "跟踪条", &H_max, 180);
	createTrackbar("S最大值:", "跟踪条", &S_max, 255);
	createTrackbar("V最大值:", "跟踪条", &V_max, 255);

	createTrackbar("蓝色分量：", "跟踪条", &myBlue, 255);
	createTrackbar("绿色分量：", "跟踪条", &myGreen, 255);
	createTrackbar("红色分量：", "跟踪条", &myRed, 255);

	createTrackbar("墨汁大小：", "跟踪条", &inkSize, 25);

	createTrackbar("灵敏度(越小越灵敏)", "跟踪条", &minArea, 300);
}


/*
	键盘输入检测
*/
void Keys_Scan()
{
	int key = waitKey(1);
	if (key == '1') {
		cout << "==> 退出程序(1)" << endl;
		exit(0);
	}
	else if (key == '2') {
		cout << "==> 清除画布(2)" << endl;
		myPoints.clear();
	}
	else if (key == '3') {
		
	}
	else if (key == ' ') {
		if (paint_enable == 1)
		{
			paint_enable = 0;
			cout << "==> 关闭画笔( )" << endl;
		}
		else
		{
			paint_enable = 1;
			cout << "==> 开启画笔( )" << endl;
		}
	}
}

/*
	鼠标事件检测
*/
void MouseCallBack(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_MOUSEWHEEL) //滚轮事件
	{
		if (getMouseWheelDelta(flags) > 0) {
			resizeNum += 0.05;
			resizeNum = (resizeNum >= 3 ? 3 : resizeNum);
		}
		else if (getMouseWheelDelta(flags) < 0) {
			resizeNum -= 0.05;
			resizeNum = (resizeNum >= 0.2 ? resizeNum : 0.2);
		}
	}
}

/*
	设置提示
*/
void SetTips(Mat& img)
{
	putText(img, "PojectName: Virtual Painter", Point(10, 25), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 200, 200), 4);
	putText(img, "Author: TangJW", Point(10, 65), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 200, 200), 4);
	putText(img, "Use Manual:", Point(10, 110), FONT_HERSHEY_DUPLEX, 1, Scalar(200, 100, 0), 2);
	putText(img, "1 - close('1')", Point(10, 160), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 200), 2);
	putText(img, "2 - clear canva('2')", Point(10, 210), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 200), 2);
	putText(img, "3 - stop paint('blankspace')", Point(10, 260), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 200), 2);
	putText(img, "4 - use mousewheel to resize the canva", Point(10, 310), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 200), 2);
}
