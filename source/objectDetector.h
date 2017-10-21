
#ifndef OBJECT_DETECTOR_H
#define OBJECT_DETECTOR_H

#include <opencv2/opencv.hpp>

class objectDetector
{
public:
  objectDetector();
  ~objectDetector();

  inline std::vector<std::vector<cv::Point> > GetContours() const { return contours_;}

  cv::Mat Preprocessing(cv::Mat& grey_scale_frame);
  void FindCountours();

private:

  cv::Mat edged_;
  std::vector<std::vector<cv::Point> > contours_;
  const cv::Size gausian_filter_size_;
  static const int gausian_filter_standard_deviation = 2;
};

#endif // OBJECT_DETECTOR_H
