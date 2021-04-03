#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using table_t = std::map< std::pair< std::string, std::string >, size_t >;

void get_input_data(int& thr, std::vector<std::string>& files)
{
	bool ok = false;
	while (!ok)
	{
		std::cin >> thr;
		if (std::cin.fail())
		{
			std::cout << "Input threshold must be digit\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			ok = true;
	}
	std::string filename;
	std::cout << "Input image filenames: \n";
	while (std::cin.get() != 27)
	{
		std::cin >> filename;
		files.emplace_back(filename);
	}
}

size_t compare_images(const cv::Mat& first, const cv::Mat& second)
{
	return 0;
}

table_t build_comparison_table(const std::vector<std::string>& filenames)
{
	table_t compared_table;
	size_t pos = 0;
	if (filenames.size() > 2)
	{
		while (pos != filenames.size() - 1)
		{
			auto first_filename = filenames[pos];
			cv::Mat first = cv::imread(first_filename);
			if (first.empty())
			{
				std::cout << "Can't read image" << first_filename << std::endl;
				continue;
			}
			for (size_t cur_pos = pos + 1; cur_pos != filenames.size(); ++ cur_pos)
			{
				auto second_filename = filenames[cur_pos];
				cv::Mat second = cv::imread(second_filename);
				if (second.empty())
				{
					std::cout << "Can't read image" << second_filename << std::endl;
					continue;
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
	else
	{
		auto first = filenames[0];
		auto second = filenames[1];
		cv::Mat first_img = cv::imread(first);
		cv::Mat second_img = cv::imread(second);
		if (first_img.empty() || second_img.empty())
		{
			std::cout << ("Can't read one of the images\n");
			return compared_table;
		}
		size_t diff = compare_images(first_img, second_img);
		compared_table.emplace(std::make_pair(first, second), diff);
		return compared_table;
	}
}

int main()
{
	int comparison_threshold = 0;
	std::vector<std::string> filenames;
	get_input_data(comparison_threshold, filenames);
	if (filenames.size() < 2)
	{
		std::cout << "Not enough images to compare\n";
		return 0;
	}
	table_t table = build_comparison_table(filenames);
	return 0;
}