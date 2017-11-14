
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
  void FindHumanSize();
  void FindImageSize();
  double GetHumanHeight();
  inline cv::Mat GetObject() const { return object_; }
  inline cv::Mat GetReference() const { return reference_; }

  static void DrawHeightData(cv::Mat& orginal_image, double height);


private:
  const double A4_height_ = 29.7;//cm
  cv::Mat edged_;
  cv::Mat object_;
  cv::Mat reference_;
  std::vector<std::vector<cv::Point> > contours_;
  const cv::Size gausian_filter_size_;
  int row_top_;
  int col_top_;
  int row_bottom_;
  int col_bottom_;
  int row_top_human;
  int col_top_human_;
  int reference_object_height_;
  double human_height_;
  static const int gausian_filter_standard_deviation = 1.5;
};

#endif // OBJECT_DETECTOR_H
