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
		if (std::cin.fail() || ret > 100)
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

bool get_input_data(std::vector<std::string>& files, int& thr)
{
	std::cout << "Input image comparison threshold in %: \n";
	thr = get_digit("Input threshold must be digit and in range 0 - 100\n");
	std::cout << "Count of images: ";
	int img_count = get_digit("Images count must be digit and positive\n");
	if (img_count < 2)
		return false;
	files.reserve(img_count);
	std::cout << "Input image filenames: \n";
	std::string filename;
	for (size_t i = 0; i < img_count; ++i)
	{
		std::cin >> filename;
		if (std::cin.good())
			files.push_back(filename);
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	return true;
}

int main()
{
	std::vector<std::string> filenames;
	int thr = 0;
	if (!get_input_data(filenames, thr))
	{
		std::cout << "Wrong input values\n";
		return 0;
	}
	// divide by 100 because of percentage
	ImageComparator img_comparator(thr / 100.0);
	img_comparator.compare(filenames);
	img_comparator.print_comparison_table();
	system("pause");
	return 0;
}
