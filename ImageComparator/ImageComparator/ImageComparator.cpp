#include "ImageComparator.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

ImageComparator::ImageComparator(int comparison_threshold)
{
	detector = cv::ORB::create(comparison_threshold);
	matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
}

double ImageComparator::compare_images(const cv::Mat& first, const cv::Mat& second)
{
	using namespace cv;
	std::vector<KeyPoint> keypoints_first_img, keypoints_second_img;
	Mat descr_first, descr_second;
	detector->detectAndCompute(first, noArray(), keypoints_first_img, descr_first);
	detector->detectAndCompute(second, noArray(), keypoints_second_img, descr_second);
	
	std::vector< std::vector<DMatch> > knn_matches;
	matcher->knnMatch(descr_first, descr_second, knn_matches, number_of_good_matches);

	std::vector<DMatch> good_matches;
	size_t knn_matches_size = knn_matches.size();
	for (size_t i = 0; i < knn_matches_size; i++)
	{
		if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
		{
			good_matches.push_back(knn_matches[i][0]);
		}
	}
	return good_matches.size() / static_cast<double>(knn_matches_size) * 100;
}

void ImageComparator::compare(const std::vector<std::string>& filenames)
{
	size_t pos = 0;
	size_t files_count = filenames.size();
	while (pos <= files_count - 1)
	{
		auto first_filename = filenames[pos];
		cv::Mat first = cv::imread(first_filename);
		if (first.empty())
		{
			std::cout << "Can't read image: " << first_filename << std::endl;
			break;
		}
		for (size_t cur_pos = pos + 1; cur_pos != files_count; ++cur_pos)
		{
			auto second_filename = filenames[cur_pos];
			cv::Mat second = cv::imread(second_filename);
			if (second.empty())
			{
				std::cout << "Can't read image: " << second_filename << std::endl;
				continue;
			}
			else
			{
				double diff = compare_images(first, second);
				images_comparison_table.emplace(std::make_pair(first_filename, second_filename), diff);
			}
		}
		++pos;
	}
}

void ImageComparator::print_comparison_table() const
{
	for (const auto& [images, value] : images_comparison_table)
	{
		std::cout << images.first << " and " << images.second << " are " << value << "% similar to each other\n";
	}
}
