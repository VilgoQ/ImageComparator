#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>

using table_t = std::map< std::pair< std::string, std::string >, size_t >;
static int thr = 0;

void get_input_data(std::vector<std::string>& files)
{
	bool ok = false;
	std::cout << "Input image threshold value: \n";
	while (!ok)
	{
		std::cin >> thr;
		if (std::cin.fail() || thr < 0)
		{
			std::cout << "Input threshold must be digit and positive\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			ok = true;
			std::cin.ignore();
		}
	}
	std::string filename;
	std::cout << "Count of images: ";
	size_t img_count = 0;
	std::cin >> img_count;
	std::cout << "Input image filenames: \n";
	for (size_t i = 0; i < img_count; ++i)
	{
		std::cin >> filename;
		if (std::cin.good())
			files.emplace_back(filename);
		else
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}
}

size_t compare_images(cv::Mat& first, cv::Mat& second)
{
	return 0;
}

table_t build_comparison_table(const std::vector<std::string>& filenames)
{
	table_t compared_table;
	size_t pos = 0;
	while (pos <= filenames.size() - 1)
	{
		auto first_filename = filenames[pos];
		cv::Mat first = cv::imread(first_filename);
		if (first.empty())
		{
			std::cout << "Can't read image" << first_filename << std::endl;
			break;
		}
		for (size_t cur_pos = pos + 1; cur_pos != filenames.size(); ++ cur_pos)
		{
			auto second_filename = filenames[cur_pos];
			cv::Mat second = cv::imread(second_filename);
			if (second.empty())
			{
				std::cout << "Can't read image" << second_filename << std::endl;
				break;
			}
			else
			{
				size_t diff = compare_images(first, second);
				compared_table.emplace(std::make_pair(first_filename, second_filename), diff);
			}
		}
		++pos;
	}
	return compared_table;
}

int main()
{
	std::vector<std::string> filenames;
	get_input_data(filenames);
	if (filenames.size() < 2)
	{
		std::cout << "Not enough images to compare\n";
		return 0;
	}
	table_t table = build_comparison_table(filenames);
	return 0;
}
