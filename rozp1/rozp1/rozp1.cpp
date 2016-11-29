#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstdio>
#include <set>

using namespace cv;
using namespace std;

/// Global variables
/*char* rotate_window = "Rotate window";
const double scale = 1;
double angle = 0.0;
Point center;
Point2f srcTri[3];
//Mat rot_mat(2, 3, CV_32FC1);
Mat src, src_rotated;
int degree = 0;
int max_degree = 360;

void rotateImage(int, void*) {
	angle = -degree;
	imshow(rotate_window, src_rotated);
}

void imgrotate(cv::Mat& src, double angle, cv::Mat& dst) {
	cv::Point2f ptCp(src.cols*0.5, src.rows*0.5);
	cv::Mat M = cv::getRotationMatrix2D(ptCp, angle, 1.0);
	cv::warpAffine(src, dst, M, src.size(), cv::INTER_CUBIC); //Nearest is too rough, 
}

vector<double> count_averages(int rows, int cols, Mat img) {
	vector<double> averages(rows);
	for (int x = 0; x < rows; x++) {
		double row_sum = 0;
		for (int y = 0; y < cols; y++) {
			row_sum += img.at<uchar>(x, y);  // uchar, bo 256

		}
		double row_average = row_sum / rows;
		averages[x] = row_average;
	}
	return averages;
}

set<int> get_darkest_lines_indexes(int lines_amount, vector<double> averages, int pixels_to_make_white) {
	set<int> row_indexes;
	for (int line = 0; line < lines_amount; line++) {  // we have 20 dark lines on the picture so we need to find 20 min values
		auto found_it = min_element(averages.begin(), averages.end());// search through the all averages for the min value (dark line)
		row_indexes.insert(found_it - averages.begin());  // saving row index for later cutting the image
		auto left_bound = max(averages.begin(), found_it - pixels_to_make_white);
		auto right_bound = min(found_it + pixels_to_make_white, averages.end());

		fill(left_bound, right_bound, 255); // make pixels around found min value white to ignore close black pixels 
	}
	return row_indexes;
}

vector<Mat> get_cropped_images(set<int> darkest_line_indexes, bool show_in_window) {
	vector<Mat> cropped_images;
	for (auto it = darkest_line_indexes.begin(), it2 = ++darkest_line_indexes.begin(); ; ++++it, ++++it2) {
		//Rect horizontalBar(src.cols, *it2 - *it);
		Rect bar(0, *it, src.cols, *it2 - *it);
		Mat cropped(src, bar);
		cropped_images.push_back(cropped);  // collect all Mats because we need to crop them either

		if (show_in_window) {
			namedWindow(to_string(*it), CV_WINDOW_NORMAL);
			imshow(to_string(*it), cropped);
		}

		if (it2 == --darkest_line_indexes.end()) {
			break;
		}
	}
	return cropped_images;
}*/

/*int main(int argc, char** argv)
{
	/// Load the image
	src = imread("digits00_rotated.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if (!src.data) {
		std::cout << "OPS" << std::endl;
		return 0;
	}

	// count averages for each row in main image
	vector<double> averages = count_averages(src.rows, src.cols, src);


	set<int> row_indexes = get_darkest_lines_indexes(20, averages, 5);

	// cut horizontal images
	vector<Mat> horizontal_bars = get_cropped_images(row_indexes, false);

	// find averages but for vertical lines for each horizontal bar:
	int counter = 1;
	for (auto it = horizontal_bars.begin(); it < horizontal_bars.end(); it++) {
		imwrite("digits00_" + to_string(counter) + ".jpg", *it);
		counter++;
	}

	// ------- END ROTATE
	/// Wait until user exits the program
	//waitKey(0);
	//getchar();
	return 0;
}*/

