#include "objectDetector.h"
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int, char**)
{
  objectDetector object_detector;
 
  VideoCapture cap(0); // open the default camera
  if (!cap.isOpened())  // check if we succeeded
    return -1;

  namedWindow("human height", 1);

  // main loop:
  for (;;)
  {
    Mat frame, grey;
    cap >> frame; // get a new frame from camera

    cvtColor(frame, grey, cv::COLOR_BGR2GRAY);
    imshow("human height", object_detector.Preprocessing(grey));
    if (waitKey(30) >= 0) break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}


