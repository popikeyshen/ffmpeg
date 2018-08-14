#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("frame",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        //cvtColor(frame, frame, COLOR_BGR2GRAY);
        //GaussianBlur(frame, frane, Size(7,7), 1.5, 1.5);
        //Canny(frame, frame, 0, 30, 3);
        imshow("frame", frame);
	
	// dummy pipe - send frame to sout
	for (size_t i = 0; i < frame.dataend - frame.datastart; i++) 
	{
           std::cout << frame.data[i];   
	} 

        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
