#include "VirtualPainter.h"
#include "cvBase.h"

//ī֭��С Ĭ�� <10>��С
int inkSize = 15;

//�����ɫ������Ĭ�� <��ɫ>����
int myBlue = 0, myGreen = 0, myRed = 255; 

//��������
int paint_enable = 0; //����ʹ��
int threshold_enbale = 1; //˫��ֵͼ��ʾʹ��

//��ɫ��ֵ
vector<vector<int>> useColors{ {46,107,92,180,255,255}	//blue
							  ,{0,138,67,58,255,255} };	//red

//Ѱ�ҵ���ɫ��ĵ�
vector<vector<int>> myPoints;

//��Ƥ��
vector<vector<int>> erasePoints;

//Ѱ����ɫ
void findColors(Mat img)
{
	Mat imgHSV, imgBlur, imgCanny, imgDilate, imgCopy = img.clone();
	Mat mask; //˫��ֵ��ͼ��
	Mat kernel; 
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//1��˫��ֵ����Χ����
	//Scalar lower(useColors[i][0], useColors[i][1], useColors[i][2]); //�½�
	//Scalar upper(useColors[i][3], useColors[i][4], useColors[i][5]); //�Ͻ�
	Scalar lower(H_min, S_min, V_min); //�½�
	Scalar upper(H_max, S_max, V_max); //�Ͻ�

	//2����<RGB>ͼ��ת����<HSV>�ռ�
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	//3�����˫��ֵ����ͼ�� mask
	inRange(imgHSV, lower, upper, mask);

	//4����˹ģ����ȥ�룩
	GaussianBlur(mask, imgBlur, Size(3,3), 0, 0);

	//5��Canny�㷨���б�Ե��ȡ
	Canny(imgBlur, imgCanny, 100, 110);

	//6������ṹԪ����������ͼ�����ʹ���
	kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilate, kernel);

	//7��������ȡ Suzuki85�㷨
	findContours(imgDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//drawContours(img, contours, -1, Scalar(0, 0, 255), 2);

	//8������ɸѡ
	vector<vector<Point>> approxCurve(contours.size()); //��������
	for (int j = 0; j < contours.size(); j++)
	{
		//cout << "���Ϊ��" << contourArea(contours[j]) << endl;
		if (contourArea(contours[j]) >= 200)
		{
			double contourLength = arcLength(contours[j], 1); //�� j �������ĳ���
			approxPolyDP(contours[j], approxCurve[j], 0.03 * contourLength, 1); //Douglas-Peucker�㷨
			drawContours(imgCopy, approxCurve, j, Scalar(0, 255, 255), 2);
			Rect bounding = boundingRect(approxCurve[j]);	// ��ð����� j ����������С����
			rectangle(imgCopy, bounding, Scalar(0,0,255), 3);

			myPoints.push_back({ bounding.x + bounding.width / 2, bounding.y});
		}
	}

	//imshow("��˹ģ��", imgBlur);
	//imshow("Canny��Ե���", imgCanny);
	//imshow("����", imgDilate);
	//imshow("��״", img);
	//imshow("����ɸѡ", imgCopy);
	//imshow("��С���ΰ���", imgCopy);
}

//��ͼ
void Canva(Mat& img)
{
	for (int i = 0; i < myPoints.size(); i++)
	{
		circle(img, Point(myPoints[i][0], myPoints[i][1]), inkSize, Scalar(myBlue, myGreen, myRed), FILLED);
	}

}

//����ں���
void Painter()
{
	VideoCapture camera(0);  //�������һ�ȡ�������������
	Mat frame, frameResize, frameforTrackHSV;

	namedWindow("����Ч��");
	TrackBar(frameforTrackHSV);
	setMouseCallback("����Ч��", MouseCallBack, (void*)(&frame)); //��׽����¼�

	while (true)
	{
		camera.read(frameResize);

		flip(frameResize, frameResize, 1); //ͼ����Գ�
		
		resize(frameResize, frame, Size(), resizeNum, resizeNum, INTER_LINEAR); //����
		
		//Ѱ����ֵ
		cvtColor(frame, frameforTrackHSV, COLOR_BGR2HSV);
		inRange(frameforTrackHSV, Scalar(H_min, S_min, V_min), Scalar(H_max, S_max, V_max), frameforTrackHSV);
		
		putText(frameforTrackHSV, "Use The Threshold Bar (H S V)", Point(0, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 2);
		putText(frameforTrackHSV, "To Track The Color You Are Interested......", Point(0, 75), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 2);
		imshow("˫��ֵ��", frameforTrackHSV);
		
		if (paint_enable == 1)
		{
			findColors(frame); //��ɫ��
		}

		Canva(frame);	//��ԲȦ

		SetTips(frame); //����ʾ
		imshow("����Ч��", frame);
		
		Keys_Scan();
	}
}


/*
	��Ƥ��
*/
void ErasePaint()
{

}
