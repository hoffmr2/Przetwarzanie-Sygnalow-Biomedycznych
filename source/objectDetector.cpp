#include "objectDetector.h"



objectDetector::objectDetector()
  :
    gausian_filter_size_(7,7)
{
}


objectDetector::~objectDetector()
{
}

cv::Mat objectDetector::Preprocessing(cv::Mat& grey_scale_frame) const
{
  cv::Mat edged;

  cv::GaussianBlur(grey_scale_frame, grey_scale_frame, gausian_filter_size_, gausian_filter_standard_deviation);
  cv::Canny(grey_scale_frame, grey_scale_frame, 50, 150);
  cv::dilate(grey_scale_frame, grey_scale_frame, cv::MORPH_RECT);
  cv::erode(grey_scale_frame, edged, cv::MORPH_RECT);

  return edged;
}
