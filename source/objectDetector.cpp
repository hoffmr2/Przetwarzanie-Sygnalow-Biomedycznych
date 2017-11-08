#include "objectDetector.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

double height = 297;//mm
int row, col;

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

void objectDetector::FindImageSize()
{
  int b, x = 0, y = 0, end = 0;
  //unsigned char *input = (unsigned char*)(reference_.data);
  
  for (int i = 0; i < reference_.rows; i++)
    for (int j = 0; j < reference_.cols; j++)
    {
      //b = input[reference_.step * j + i];
      //if (b == 255)
      //{
      //  row = i; col = j;
      //  end = 1;
      //}
      //cv::Point3_<uchar>* p = reference_.ptr<cv::Point3_<uchar> >(i, j);
      //std::cout << static_cast<int>(p->x) << " " << std::endl;
      cv::Scalar intensity = reference_.at<uchar>(i,j);
      int blue = intensity.val[0];
      if((intensity.val[0] || intensity.val[1] || intensity.val[2] || intensity.val[3]) == 1)
        std::cout << intensity << " row: " << i << " col: " << j << std::endl;
      if(blue == 255)
      {
        row = i; col = j;
        end = 1;
      }
      if (end) break;
    }
  std::cout << row << " " << col << " " << std::endl;
}

//void objectDetector::FindImageSize(cv::Mat image)
//{
//  int b, x, y;
//  unsigned char *input = (unsigned char*)(image.data);
//  for (int i = 0; i < image.rows; i++)
//    for (int j = 0; j < image.cols; j++)
//    {
//      b = input[image.step * j + i];
//      y = image.step;
//      if (b == 255)
//      {
//        x = input[image.step * j + i];
//        row = i; col = j;
//        break;
//      }
//    }
//  std::cout << x << " " << y << std::endl;
//  std::cout << row << " " << col << std::endl;
//}
