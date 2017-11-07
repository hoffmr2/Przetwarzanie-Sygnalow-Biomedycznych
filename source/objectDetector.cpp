#include "objectDetector.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

objectDetector::objectDetector()
  :
    gausian_filter_size_(7,7),
    edged_()
{
}


objectDetector::~objectDetector()
{
}

cv::Mat objectDetector::Preprocessing(cv::Mat& grey_scale_frame)
{
  cv::Mat edged;
  cv::GaussianBlur(grey_scale_frame, grey_scale_frame, gausian_filter_size_, gausian_filter_standard_deviation);
  cv::Canny(grey_scale_frame, grey_scale_frame, 100, 200);
  cv::dilate(grey_scale_frame, grey_scale_frame, cv::MORPH_CROSS);
  cv::erode(grey_scale_frame, edged, cv::MORPH_CROSS);

  edged.copyTo(edged_);
  return edged;
}

void objectDetector::FindObjects()
{
  FindCountours();

  cv::Mat contour_image(edged_.size(), CV_8UC3, cv::Scalar(0, 0, 0));
  cv::Scalar color = cv::Scalar(255, 0, 0);
 
  for (size_t idx = 0; idx < contours_.size(); ++idx) 
  {
    cv::drawContours(contour_image, contours_, idx, color, CV_FILLED);
  }

  object_ = contour_image(cv::Range(0, contour_image.rows), cv::Range(0, contour_image.cols / 2));
  reference_ = contour_image(cv::Range(0, contour_image.rows), cv::Range(contour_image.cols / 2, contour_image.cols));
}

void objectDetector::FindCountours()
{
  /* check if we had ekstract edges */
  assert(edged_.empty() == false);

  auto contourOutput = edged_.clone();
  cv::findContours(contourOutput, contours_, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
}
