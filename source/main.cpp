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
    cap >> frame;
   // frame = cv::imread("../../../res/test5.jpg"); // get a new frame from camera
   // cv::resize(frame,frame, cv::Size(frame.cols / 7, frame.rows / 7));
    cvtColor(frame, grey, cv::COLOR_BGR2GRAY);
    object_detector.Preprocessing(grey);
    object_detector.FindObjects();
    auto human_height = object_detector.GetHumanHeight();
    objectDetector::DrawHeightData(frame, human_height);
   

    cv::imshow("human height", frame);
    cvMoveWindow("human height", 0, 0);
    cv::imshow("Human", object_detector.GetObject());
    cvMoveWindow("Human", frame.cols, 0);
    cv::imshow("Reference", object_detector.GetReference());
    cvMoveWindow("Reference", 3 * frame.cols / 2, 0);

    if (waitKey(30) >= 0) break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}


