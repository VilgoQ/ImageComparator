#include "ImageComparator.hpp"
#include <iostream>
#include <vector>

int get_digit(const std::string& error_msg)
{
	bool ok = false;
	int ret = 0;
	while (!ok)
	{
		std::cin >> ret;
		if (std::cin.fail() || ret < 0)
		{
			std::cout << error_msg;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			ok = true;
			std::cin.ignore();
		}
	}
	return ret;
}

void get_input_data(std::vector<std::string>& files, int& thr)
{
	std::cout << "Input image threshold value: \n";
	thr = get_digit("Input threshold must be digit and positive\n");
	std::cout << "Count of images: ";
	int img_count = get_digit("Images count must be digit and positive\n");
	std::cout << "Input image filenames: \n";
	std::string filename;
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

int main()
{
	std::vector<std::string> filenames;
	int thr = 0;
	get_input_data(filenames, thr);
	if (filenames.size() < 2)
	{
		std::cout << "Not enough images to compare\n";
		return 0;
	}
	ImageComparator img_comparator(filenames, thr);
	img_comparator.build_comparison_table();
	img_comparator.print_comparison_table();
	system("pause");
	return 0;
}
