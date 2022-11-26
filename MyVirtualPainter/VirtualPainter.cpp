#include "VirtualPainter.h"
#include "cvBase.h"

//墨汁大小 默认 <10>大小
int inkSize = 15;

//混合颜色分量，默认 <红色>画笔
int myBlue = 0, myGreen = 0, myRed = 255; 

//按键控制
int paint_enable = 0; //画笔使能
int threshold_enbale = 1; //双阈值图显示使能

//颜色阈值
vector<vector<int>> useColors{ {46,107,92,180,255,255}	//blue
							  ,{0,138,67,58,255,255} };	//red

//寻找到的色块的点
vector<vector<int>> myPoints;

//橡皮擦
vector<vector<int>> erasePoints;

//寻找颜色
void findColors(Mat img)
{
	Mat imgHSV, imgBlur, imgCanny, imgDilate, imgCopy = img.clone();
	Mat mask; //双阈值化图像
	Mat kernel; 
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//1、双阈值化范围标量
	//Scalar lower(useColors[i][0], useColors[i][1], useColors[i][2]); //下界
	//Scalar upper(useColors[i][3], useColors[i][4], useColors[i][5]); //上界
	Scalar lower(H_min, S_min, V_min); //下界
	Scalar upper(H_max, S_max, V_max); //上界

	//2、将<RGB>图像转换到<HSV>空间
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	//3、获得双阈值化的图像 mask
	inRange(imgHSV, lower, upper, mask);

	//4、高斯模糊（去噪）
	GaussianBlur(mask, imgBlur, Size(3,3), 0, 0);

	//5、Canny算法进行边缘提取
	Canny(imgBlur, imgCanny, 100, 110);

	//6、构造结构元素用来进行图像膨胀处理
	kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilate, kernel);

	//7、轮廓提取 Suzuki85算法
	findContours(imgDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//drawContours(img, contours, -1, Scalar(0, 0, 255), 2);

	//8、轮廓筛选
	vector<vector<Point>> approxCurve(contours.size()); //近似曲线
	for (int j = 0; j < contours.size(); j++)
	{
		//cout << "面积为：" << contourArea(contours[j]) << endl;
		if (contourArea(contours[j]) >= 200)
		{
			double contourLength = arcLength(contours[j], 1); //第 j 个轮廓的长度
			approxPolyDP(contours[j], approxCurve[j], 0.03 * contourLength, 1); //Douglas-Peucker算法
			drawContours(imgCopy, approxCurve, j, Scalar(0, 255, 255), 2);
			Rect bounding = boundingRect(approxCurve[j]);	// 获得包含第 j 个轮廓的最小矩形
			rectangle(imgCopy, bounding, Scalar(0,0,255), 3);

			myPoints.push_back({ bounding.x + bounding.width / 2, bounding.y});
		}
	}

	//imshow("高斯模糊", imgBlur);
	//imshow("Canny边缘检测", imgCanny);
	//imshow("膨胀", imgDilate);
	//imshow("形状", img);
	//imshow("轮廓筛选", imgCopy);
	//imshow("最小矩形包含", imgCopy);
}

//画图
void Canva(Mat& img)
{
	for (int i = 0; i < myPoints.size(); i++)
	{
		circle(img, Point(myPoints[i][0], myPoints[i][1]), inkSize, Scalar(myBlue, myGreen, myRed), FILLED);
	}

}

//总入口函数
void Painter()
{
	VideoCapture camera(0);  //创建并且获取本地摄像机对象
	Mat frame, frameResize, frameforTrackHSV;

	namedWindow("画笔效果");
	TrackBar(frameforTrackHSV);
	setMouseCallback("画笔效果", MouseCallBack, (void*)(&frame)); //捕捉鼠标事件

	while (true)
	{
		camera.read(frameResize);

		flip(frameResize, frameResize, 1); //图像镜像对称
		
		resize(frameResize, frame, Size(), resizeNum, resizeNum, INTER_LINEAR); //缩放
		
		//寻找阈值
		cvtColor(frame, frameforTrackHSV, COLOR_BGR2HSV);
		inRange(frameforTrackHSV, Scalar(H_min, S_min, V_min), Scalar(H_max, S_max, V_max), frameforTrackHSV);
		
		putText(frameforTrackHSV, "Use The Threshold Bar (H S V)", Point(0, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 2);
		putText(frameforTrackHSV, "To Track The Color You Are Interested......", Point(0, 75), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 2);
		imshow("双阈值化", frameforTrackHSV);
		
		if (paint_enable == 1)
		{
			findColors(frame); //找色块
		}

		Canva(frame);	//画圆圈

		SetTips(frame); //加提示
		imshow("画笔效果", frame);
		
		Keys_Scan();
	}
}


/*
	橡皮擦
*/
void ErasePaint()
{

}
