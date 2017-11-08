#include "objectDetector.h"
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int, char**)
{
  objectDetector object_detector;
 
 // VideoCapture cap(0); // open the default camera
 // if (!cap.isOpened())  // check if we succeeded
 //   return -1;

  namedWindow("human height", 1);

  // main loop:
  for (;;)
  {
    Mat frame, grey;
    frame = cv::imread("../../../res/test.jpg"); // get a new frame from camera
    cv::resize(frame,frame, cv::Size(400, 300));
    cvtColor(frame, grey, cv::COLOR_BGR2GRAY);
    object_detector.Preprocessing(grey);
    object_detector.FindObjects();
    objectDetector::DrawHeightData(frame, 1.78);
   

    cv::imshow("human height", frame);
    cvMoveWindow("human height", 0, 0);
    cv::imshow("Human", object_detector.GetObject());
    cvMoveWindow("Human", frame.cols, 0);
    cv::imshow("Reference", object_detector.GetReference());
    cvMoveWindow("Reference", 3 * frame.cols / 2, 0);

    //object_detector.FindImageSize(object_detector.GetReference());
    object_detector.FindImageSize();

    if (waitKey(30) >= 0) break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}


