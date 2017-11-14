#include "objectDetector.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

objectDetector::objectDetector()
  : 
    gausian_filter_size_(7, 7), row_top_(0), col_top_(0), row_bottom_(0), col_bottom_(0),
    edged_()
{
}

objectDetector::~objectDetector()
{
	// empty
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

void objectDetector::FindHumanSize()
{
  assert(object_.empty() == false);
  auto end = false;

  for (int i = 0; i < object_.rows && (!end); i++)
    for (int j = 0; j < object_.cols && (!end); j++)
    {
      cv::Vec3b colour = object_.at<cv::Vec3b>(i, j);
      if (colour.val[0] == 255)
      {
        row_top_human = i; col_top_human_ = j;
        end = true;
      }
    }

  auto human_height_pixel = object_.rows - row_top_human;
  human_height_ = static_cast<double>(human_height_pixel) * A4_height_ / static_cast<double>(reference_object_height_);

}

void objectDetector::FindImageSize()
{ 
  assert(reference_.empty() == false);
  auto end = false;

  for (int i = 0; i < reference_.rows && (!end); i++)
    for (int j = 0; j < reference_.cols && (!end); j++)
    {
      cv::Vec3b colour = reference_.at<cv::Vec3b>(i, j);
      if(colour.val[0] == 255)
      {
        row_top_ = i; col_top_ = j;
        end = true;
      }
    }

  end = false;
  for (int i = reference_.rows - reference_.rows / 5; i >= 0 && (!end); i--)
    for (int j = reference_.cols - 1; j >= 0 && (!end); j--)
    {
      cv::Vec3b colour = reference_.at<cv::Vec3b>(i, j);
      if (colour.val[0] == 255)
      {
        row_bottom_ = i; col_bottom_ = j;
        end = true;
      }
    }

  reference_object_height_ = row_bottom_ - row_top_;

}

double objectDetector::GetHumanHeight()
{
  FindImageSize();
  FindHumanSize();
  return human_height_;
}

void objectDetector::DrawHeightData(cv::Mat& orginal_image, double height)
{
  // draw height  
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2) << "Height: " <<height;
  std::string height_data = ss.str();
  auto origin = cv::Point(orginal_image.cols * 0.55, orginal_image.rows * 0.1);
  auto font_scale = 2;
  auto font_colour = cv::Scalar(0,0,0);
  cv::putText(orginal_image, height_data, origin, cv::FONT_HERSHEY_PLAIN, font_scale, font_colour);  

  // Draw half line
  auto begin_point = cv::Point(orginal_image.cols / 2, 0);
  auto end_point = cv::Point(orginal_image.cols / 2, orginal_image.rows);
  cv::line(orginal_image, begin_point, end_point, cv::Scalar(0, 0, 255));
}

