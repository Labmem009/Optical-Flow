#include "opencv2/opencv.hpp"  
#include <iostream>  
using namespace cv;
using namespace std;

//�˶������⺯��
Mat MoveDetect(Mat temp, Mat frame);

int main(int argc, char** argv)
{

	//VideoCapture video("video.avi");//����VideoCapture��video  

	Mat frame;//�洢֡  
	Mat temp;//�洢ǰһ֡ͼ��  
	Mat result;//�洢���ͼ��  

	temp= imread("C:/Users/Administrator/Desktop/p9.png");
	frame= imread("C:/Users/Administrator/Desktop/p10.png");
	result = MoveDetect(temp, frame);
	imshow("result", result);
	cvWaitKey(0);
	return 0;
}
Mat MoveDetect(Mat temp, Mat frame)
{
	Mat result = frame.clone();
	//1.��background��frameתΪ�Ҷ�ͼ  
	Mat gray1, gray2;
	cvtColor(temp, gray1, CV_BGR2GRAY);
	cvtColor(frame, gray2, CV_BGR2GRAY);
	//2.��background��frame����  
	Mat diff;
	absdiff(gray1, gray2, diff);
	imshow("diff", diff);
	//3.�Բ�ֵͼdiff_thresh������ֵ������  
	Mat diff_thresh;
	threshold(diff, diff_thresh, 10, 255, CV_THRESH_BINARY);
	imshow("diff_thresh", diff_thresh);

	GaussianBlur(diff_thresh, diff_thresh, Size(3, 3), 0, 0);

	//4.��ʴ  
	Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(5, 5));
	erode(diff_thresh, diff_thresh, kernel_erode);
	//imshow("erode", diff_thresh);
	//5.����  
	dilate(diff_thresh, diff_thresh, kernel_dilate);
	imshow("dilate", diff_thresh);
	//6.������������������  
	vector<vector<Point>> contours;
	findContours(diff_thresh, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//drawContours(result, contours, -1, Scalar(0, 0, 255), 2);//��result�ϻ�������  
	//7.��������Ӿ���  
	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(contours[i]);
		rectangle(result, boundRect[i], Scalar(0, 255, 0), 2);//��result�ϻ�������Ӿ���  
	}
	return result;//����result  
}
