#include <stdio.h>
#include <iostream>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int g_switch_value = 100;
CvPoint A1, A2;

IplImage *img = 0;
IplImage *final = 0;


void switch_on_function(int step){
	final = cvCloneImage(img);
	final = cvCreateImage(cvSize(img->width*(step*0.1), img->height*(step*0.1)), 
						img->depth, img->nChannels);
	cvResize(img, final, 1);	
	cvNamedWindow("Final", CV_WINDOW_AUTOSIZE);
	cvShowImage("Final", final);
}
void switch_off_function(){
	final = cvCloneImage(img);
	cvShowImage("Final", final);
}
void switch_callback(int position){
	if(0 == position){
		switch_off_function();
	}else{
		switch_on_function(position);
	}
}

void my_mouse_callback(int event, int x, int y, int flags, void *param);

void drawTarget(IplImage* img, int x, int y, int radius){
	cvCircle(img,cvPoint(x, y),radius,CV_RGB(250,0,0),1,8);
    cvLine(img, cvPoint(x-radius/2, y-radius/2), cvPoint(x+radius/2, y+radius/2),CV_RGB(250,0,0),1,8);
    cvLine(img, cvPoint(x-radius/2, y+radius/2), cvPoint(x+radius/2, y-radius/2),CV_RGB(250,0,0),1,8);
}


int main(int argc, char **argv){

	img = cvLoadImage(argv[1], 1);

	assert(img != 0);



	cvNamedWindow(argv[1], 1);	
	//cvSetMouseCallback(argv[1], my_mouse_callback, (void*)img);
	/*cvCreateTrackbar(
		"Size"
		,argv[1]
		,&g_switch_value
		,200
		,switch_callback
	);*/

		size_t b;
	while(1){

		cvShowImage(argv[1], img);
		b = cvWaitKey(500);
		if (b != -1)
			cout<<b<<endl;
		if (1048603 == b){
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
			drawTarget(imag, x, y, 10);
			A1.x = x, A1.y = y;
			break;
		}
		case CV_EVENT_LBUTTONUP:{
			A2.x = x, A2.y = y;
			cout<<"Rect: "<<A1.x<<" "<<A1.y<<"   "<<A2.x<<" "<<A2.y << endl;
			break;
		}
	}
}
