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
    frame = cv::imread("C:/Users/MHofffmann/Documents/Repos/Przetwarzanie-Sygnalow-Biomedycznych/res/test.jpg"); // get a new frame from camera
    cv::resize(frame,frame, cv::Size(400, 300));
    cvtColor(frame, grey, cv::COLOR_BGR2GRAY);
    object_detector.Preprocessing(grey);
    object_detector.FindCountours();
    auto contours = object_detector.GetContours();

    cv::Mat contourImage(frame.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Scalar colors[3];
    colors[0] = cv::Scalar(255, 0, 0);
    colors[1] = cv::Scalar(0, 255, 0);
    colors[2] = cv::Scalar(0, 0, 255);
    for (size_t idx = 0; idx < contours.size(); idx++) {
      cv::drawContours(contourImage, contours, idx, colors[0], CV_FILLED);
    }

    cv::imshow("human height", frame);
    cvMoveWindow("human height", 0, 0);
    cv::imshow("Contours", contourImage);
    cvMoveWindow("Contours", 200, 0);
    if (waitKey(30) >= 0) break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}


