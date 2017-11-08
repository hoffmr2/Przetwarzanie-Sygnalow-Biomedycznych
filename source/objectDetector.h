
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
  void FindObjects();
  void FindCountours();
  void FindImageSize();
  inline cv::Mat GetObject() const { return object_; }
  inline cv::Mat GetReference() const { return reference_; }

  static void DrawHeightData(cv::Mat& orginal_image, double height);


private:

  static const int height = 297;//mm
  int row, col;
  
  cv::Mat edged_;
  cv::Mat object_;
  cv::Mat reference_;
  std::vector<std::vector<cv::Point> > contours_;
  const cv::Size gausian_filter_size_;
  const double gausian_filter_standard_deviation = 1.0;
};

#endif // OBJECT_DETECTOR_H
