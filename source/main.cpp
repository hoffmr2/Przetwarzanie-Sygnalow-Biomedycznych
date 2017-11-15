#include "objectDetector.h"
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int, char**)
{
  objectDetector object_detector;
  bool external_camera = true;
 
  VideoCapture cap(1); // open the external camera
  if (!cap.isOpened())  // check if we succeeded
  {
	  external_camera = false;
	  cap = VideoCapture(0); // open default camera
  }
  if (!cap.isOpened())
    return -1;

  namedWindow("human height", 1);

  // main loop:
  for (;;)
  {
    Mat frame, grey;
    cap >> frame;

	if (external_camera == true)
	{
		cv::rotate(frame, frame, ROTATE_180);
	}
    cvtColor(frame, grey, cv::COLOR_BGR2GRAY);
    object_detector.Preprocessing(grey);
    object_detector.FindObjects();
    auto human_height = object_detector.GetHumanHeight();
    objectDetector::DrawHeightData(frame, human_height);
   

    cv::imshow("human height", frame);
    cvMoveWindow("human height", 0, 0);

    if (waitKey(30) >= 0) break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}


