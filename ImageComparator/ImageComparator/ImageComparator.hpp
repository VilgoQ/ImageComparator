#pragma once
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>

class ImageComparator
{
	using table_t = std::map< std::pair< std::string, std::string >, double >;
public:
	ImageComparator(const std::vector<std::string>& filenames_, int thr);
	
	/*
	@brief - Walking through images, compares and adding to images_comparison_table
	*/
	void build_comparison_table();

	/*
	@brief - Printing images_comparison_table with format
	*/
	void print_comparison_table();

protected:

	/*
	@brief - Comparing images with SURF
	@output - percentage value
	*/
	double compare_images(const cv::Mat& first, const cv::Mat& second);

private:
	cv::Ptr<cv::xfeatures2d::SURF> detector;
	cv::Ptr<cv::DescriptorMatcher> matcher;
	table_t images_comparison_table;
	std::vector<std::string> filenames;
	const float ratio_thresh = 0.7f;
	int comparison_threshold = 0;
};