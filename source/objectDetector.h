
#ifndef OBJECT_DETECTOR_H
#define OBJECT_DETECTOR_H

#include <opencv2/opencv.hpp>


class objectDetector
{
public:
  objectDetector();
  ~objectDetector();

  cv::Mat Preprocessing(cv::Mat& grey_scale_frame) const;

private:

  const cv::Size gausian_filter_size_;
  static const int gausian_filter_standard_deviation = 2;
};

#endif // OBJECT_DETECTOR_H
