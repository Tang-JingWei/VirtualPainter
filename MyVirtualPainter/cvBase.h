#pragma once

extern int H_min, H_max;
extern int S_min, S_max;
extern int V_min, V_max;
extern float resizeNum;


void TrackBar(Mat& image);
void Keys_Scan();
void MouseCallBack(int event, int x, int y, int flags, void* userdata);
void SetTips(Mat& img);
