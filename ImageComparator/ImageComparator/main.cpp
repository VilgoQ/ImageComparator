#include "ImageComparator.hpp"
#include <iostream>
#include <vector>

void get_input_data(std::vector<std::string>& files, int& thr)
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
