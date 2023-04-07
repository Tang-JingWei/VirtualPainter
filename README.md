# 项目名称
基于OpenCv的虚拟画笔
VirtualPainter

# 项目简介
《基于OpenCv的虚拟画笔》是一个需要使用到摄像头的虚拟画笔应用。

使用的规则很简单：
1、寻找一个粉笔大小并有特征颜色的小物体。
2、将物体置于摄像头前，随后调整“跟踪条”窗口的H、S、V的值，使得“双阈值化”窗口只出现小物体的白色小方块。
3、然后点按一次空格键，就可以看到墨水了；再次点按空格则是关闭画笔。点按‘2’则是清除画布。


## 相关图片
![image](https://gitee.com/JingWei1234/virtual-painter/raw/master/image/hello.png)
![image](https://gitee.com/JingWei1234/virtual-painter/raw/master/image/1-未双阈值.png)
![image](https://gitee.com/JingWei1234/virtual-painter/raw/master/image/2-双阈值化.png)
![image](https://gitee.com/JingWei1234/virtual-painter/raw/master/image/3-高斯模糊处理.png)
![image](https://gitee.com/JingWei1234/virtual-painter/raw/master/image/4-canny边缘检测.png)
![image](https://gitee.com/JingWei1234/virtual-painter/raw/master/image/5-膨胀处理.png)
![image](https://gitee.com/JingWei1234/virtual-painter/raw/master/image/6-轮廓筛选、曲线拟合.png)