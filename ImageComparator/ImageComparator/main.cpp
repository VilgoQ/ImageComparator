#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cassert>
#include <filesystem>
#include <string>
#include <list>

void get_input_data(int& thr, std::list<std::string>& files)
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

int main()
{
	int comparison_threshold = 0;
	std::list<std::string> filenames;
	get_input_data(comparison_threshold, filenames);
	return 0;
}