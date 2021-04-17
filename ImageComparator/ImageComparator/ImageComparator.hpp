#pragma once
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>

class ImageComparator
{
	using table_t = std::map< std::pair< std::string, std::string >, double >;
public:
	ImageComparator(int comparison_threshold);
	
	/*
	@brief - Walking through images, compares and adding to images_comparison_table
	*/
	void compare(const std::vector<std::string>& filenames);

	/*
	@brief - Printing images_comparison_table with format
	*/
	void print_comparison_table() const;

protected:
	/*
	@brief - Comparing images with SURF
	@output - percentage value
	*/
	double compare_images(const cv::Mat& first, const cv::Mat& second);

private:
	cv::Ptr<cv::ORB> detector;
	cv::Ptr<cv::DescriptorMatcher> matcher;
	table_t images_comparison_table;
	const float ratio_thresh = 0.7f;
	const int number_of_good_matches = 2;
};
