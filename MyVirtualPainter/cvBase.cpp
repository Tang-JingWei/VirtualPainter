#include "VirtualPainter.h"
#include "cvBase.h"

int H_min = 0,   H_max = 141;
int S_min = 113,  S_max = 223;
int V_min = 158,  V_max = 199;

//Ĭ������2.0
float resizeNum = 1.5;

void TrackBar(Mat& image)
{
	namedWindow("������", WINDOW_FREERATIO);

	createTrackbar("H��Сֵ:", "������", &H_min, 180);
	createTrackbar("S��Сֵ:", "������", &S_min, 255);
	createTrackbar("V��Сֵ:", "������", &V_min, 255);
	createTrackbar("H���ֵ:", "������", &H_max, 180);
	createTrackbar("S���ֵ:", "������", &S_max, 255);
	createTrackbar("V���ֵ:", "������", &V_max, 255);

	createTrackbar("��ɫ������", "������", &myBlue, 255);
	createTrackbar("��ɫ������", "������", &myGreen, 255);
	createTrackbar("��ɫ������", "������", &myRed, 255);

	createTrackbar("ī֭��С��", "������", &inkSize, 25);

	createTrackbar("������(ԽСԽ����)", "������", &minArea, 300);
}


/*
	����������
*/
void Keys_Scan()
{
	int key = waitKey(1);
	if (key == '1') {
		cout << "==> �˳�����(1)" << endl;
		exit(0);
	}
	else if (key == '2') {
		cout << "==> �������(2)" << endl;
		myPoints.clear();
	}
	else if (key == '3') {
		
	}
	else if (key == ' ') {
		if (paint_enable == 1)
		{
			paint_enable = 0;
			cout << "==> �رջ���( )" << endl;
		}
		else
		{
			paint_enable = 1;
			cout << "==> ��������( )" << endl;
		}
	}
}

/*
	����¼����
*/
void MouseCallBack(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_MOUSEWHEEL) //�����¼�
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
	������ʾ
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
