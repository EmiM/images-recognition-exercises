#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstdio>
#include <set>

using namespace cv;
using namespace std;

/// Global variables
char* rotate_window = "Rotate window";
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
	//rot_mat = getRotationMatrix2D(center, angle, scale);
	//warpAffine(src, src_rotated, rot_mat, src_rotated.size());
	imshow(rotate_window, src_rotated);
}

int main(int argc, char** argv)
{
	/// Load the image
	src = imread("digits00_rotated.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if (!src.data) {
		std::cout << "OPS" << std::endl;
		return 0;
	}

	vector<double> averages( src.rows );
	for (int x = 0; x < src.rows; x++) {
		double row_sum = 0;
		for (int y = 0; y<src.cols; y++) {
			row_sum += src.at<uchar>(x, y);  // uchar, bo 256

		}
		double row_average = row_sum / src.rows;
		averages[x] = row_average;
	}
	set<int> row_indexes;

	int pixels_to_make_white = 5;
	for (int line = 0; line < 20; line++) {  // we have 20 dark lines on the picture so we need to find 20 min values
		auto found_it = min_element(averages.begin(), averages.end());// search through the all averages for the min value (dark line)
		row_indexes.insert(found_it - averages.begin());  // saving row index for later cutting the image
		auto left_bound = max(averages.begin(), found_it - pixels_to_make_white);
		auto right_bound = min(found_it + pixels_to_make_white, averages.end());

		fill(left_bound, right_bound, 255); // make pixels around found min value white to ignore close black pixels 
	}

	// cut horizontal images
	vector<Rect> horizontal_bars_rects;
	for (auto it = row_indexes.begin(), it2 = ++row_indexes.begin(); ; ++++it, ++++it2) {
		//Rect horizontalBar(src.cols, *it2 - *it);
		Rect bar{0, *it, src.cols, *it2 - *it};
		horizontal_bars_rects.push_back(bar);
		//Mat cropped(src, bar);
		//namedWindow(to_string(*it), CV_WINDOW_NORMAL);
		//imshow(to_string(*it), cropped);
		if (it2 == --row_indexes.end()) {
			break;
		}
	}

	// find averages but for vertical lines for each horizontal bar:
	vector<double> vertical_averages(src.rows);
	for (auto it = horizontal_bars_rects.begin(); it < horizontal_bars_rects.end(); it++) {
		for (int x = 0; x < src.rows; x++) {
			double row_sum = 0;
			for (int y = 0; y < src.cols; y++) {
				row_sum += src.at<uchar>(x, y);  // uchar, bo 256

			}
			double row_average = row_sum / src.rows;
			averages[x] = row_average;
		}
	}

	
	// cutting horizontal bars to separate numbers
	for (auto it = horizontal_bars_rects.begin(); it < horizontal_bars_rects.end(); it++) {
		for (int i = 0; i < 11; i++) { // 11 dark lines between numbers in each bar
			//min_element();
		}
	}


	// ----- ROTATE ------
	/// Set the dst image the same type and size as src
	//src_rotated = Mat::zeros(src.rows, src.cols, src.type());
	//src.copyTo(src_rotated);

	/** Rotating the image */
	/// Compute a rotation matrix with respect to the center of the image
	//center = Point(src_rotated.cols / 2, src_rotated.rows / 2);

	/// Show what you got
	//namedWindow(rotate_window, CV_WINDOW_AUTOSIZE);
	//createTrackbar("Rotating", rotate_window, &degree, max_degree, rotateImage);
	//imshow(rotate_window, src_rotated);
	// ------- END ROTATE
	/// Wait until user exits the program
	waitKey(0);
	getchar();
	return 0;
}
