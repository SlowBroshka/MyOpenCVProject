#include <stdio.h>
#include <iostream>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void my_mouse_callback(int event, int x, int y, int flags, void *param);

void drawTarget(IplImage* img, int x, int y, int radius){
	cvCircle(img,cvPoint(x, y),radius,CV_RGB(250,0,0),1,8);
    cvLine(img, cvPoint(x-radius/2, y-radius/2), cvPoint(x+radius/2, y+radius/2),CV_RGB(250,0,0),1,8);
    cvLine(img, cvPoint(x-radius/2, y+radius/2), cvPoint(x+radius/2, y-radius/2),CV_RGB(250,0,0),1,8);
}

int main(int argc, char **argv){

	IplImage *img = cvLoadImage(argv[1], 1);


	cvNamedWindow(argv[1], 1);	
	cvSetMouseCallback(argv[1], my_mouse_callback, (void*)img);
	
	while(1){

		cvShowImage(argv[1], img);
		if (1048603 == cvWaitKey(33)){
			break;
		}
	}

	cvDestroyWindow(argv[1]);
	cvReleaseImage(&img);
	return 0;

}
void my_mouse_callback(int event, int x, int y, int flags, void *param){
	IplImage *imag = (IplImage*) param;
	switch(event){
		case CV_EVENT_MOUSEMOVE:{
			break;
		}
		case CV_EVENT_LBUTTONDOWN:{
			cout<<x<<" "<<y<<endl;
			drawTarget(imag, x, y, 10);
			break;
		}
		case CV_EVENT_LBUTTONUP:{
			break;
		}
	}
}
