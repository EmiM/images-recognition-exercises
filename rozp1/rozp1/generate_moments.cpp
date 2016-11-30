#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <set>

using namespace cv;
using namespace std;

int const max_BINARY_value = 255;
int threshold_value = 0;
int threshold_type = 0;

string get_filename(int number, int person, int number_repetition) {
	string filename = "data/digit";
	filename += to_string(number);
	if (person < 10) {
		filename += "_0";
	}
	else {
		filename += "_";
	}
	filename += to_string(person);
	filename += "_0";
	filename += to_string(number_repetition);
	filename += ".jpg";
	return filename;
}

vector<pair<Mat, int>> get_images() {
	vector<pair<Mat, int>> images_numbers;

	for (int number = 0; number <= 9; number++) {
		for (int person = 0; person <= 20; person++) {
			for (int number_rep = 0; number_rep <= 9; number_rep++) {
				string filename = get_filename(number, person, number_rep);

				Mat binary_img;
				Mat inverted_img;
				Mat src = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
				if (!src.data) {
					cout << filename << endl;
					continue;
				}
				// binary
				threshold(src, binary_img, threshold_value, max_BINARY_value, THRESH_BINARY + THRESH_OTSU);

				// invert
				threshold(binary_img, inverted_img, threshold_value, max_BINARY_value, THRESH_BINARY_INV);

				images_numbers.push_back(make_pair(inverted_img, number));

			}
		}
	}
	return images_numbers;
}

int main(int argc, char** argv)
{
	ofstream features;
	Mat binary_img;
	Mat inverted_img;

	vector<pair<Mat, int>> images_numbers = get_images();

	for (const pair<Mat, int> &image: images_numbers) {
		//namedWindow("inverted", CV_WINDOW_AUTOSIZE);
		//imshow("inverted", image.first);
		//break;
		Moments mm = moments(image.first);
		double hum[7];
		HuMoments(mm, hum);

		for (int h = 0; h < 7; h++) {
			cout << hum[h] << endl;
		}

		// ograniczyæ wyniki po przecinku
		// zapisaæ do pliku (31 dla ka¿dej linii)
		features.open("features_output.txt", fstream::app);
		features << image.second << " ";
		int h;
		for (h = 0; h < 7; h++) {
			features << h + 1 << ":" << hum[h] << " ";
		}

		features << ++h << ":" << mm.m00 << " ";
		features << ++h << ":" << mm.m01 << " ";
		features << ++h << ":" << mm.m02 << " ";
		features << ++h << ":" << mm.m03 << " ";
		features << ++h << ":" << mm.m10 << " ";
		features << ++h << ":" << mm.m11 << " ";
		features << ++h << ":" << mm.m12 << " ";
		features << ++h << ":" << mm.m20 << " ";
		features << ++h << ":" << mm.m21 << " ";
		features << ++h << ":" << mm.m30 << " ";
		features << ++h << ":" << mm.mu02 << " ";
		features << ++h << ":" << mm.mu03 << " ";
		features << ++h << ":" << mm.mu11 << " ";
		features << ++h << ":" << mm.mu12 << " ";
		features << ++h << ":" << mm.mu20 << " ";
		features << ++h << ":" << mm.mu21 << " ";
		features << ++h << ":" << mm.mu30 << " ";

		features << ++h << ":" << mm.nu02 << " ";
		features << ++h << ":" << mm.nu03 << " ";
		features << ++h << ":" << mm.nu11 << " ";
		features << ++h << ":" << mm.nu12 << " ";
		features << ++h << ":" << mm.nu20 << " ";
		features << ++h << ":" << mm.nu21 << " ";
		features << ++h << ":" << mm.nu30 << " ";

		features << "\n";
		features.close();

	}

	/*Mat src = imread("digits00_0.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if (!src.data) {
		std::cout << "OPS" << std::endl;
		return 0;
	}*/

	// binary
	//threshold(src, binary_img, threshold_value, max_BINARY_value, THRESH_BINARY + THRESH_OTSU);

	// invert
	//threshold(binary_img, inverted_img, threshold_value, max_BINARY_value, THRESH_BINARY_INV);

	// count moments
	/*Moments mm = moments(inverted_img);

	// humoment
	double hum[7];
	HuMoments(mm, hum);

	for (int h = 0; h < 7; h++) {
		cout << hum[h] << endl;
	}

	// ograniczyæ wyniki po przecinku
	// zapisaæ do pliku (31 dla ka¿dej linii)
	features.open("features_output.txt");
	features << "1 ";
	int h;
	for (h = 0; h < 7; h++) {
		features << h + 1 << ":" << hum[h] << " ";
	}
	
	features << ++h << ":" << mm.m00 << " ";
	features << ++h << ":" << mm.m01 << " ";
	features << ++h << ":" << mm.m02 << " ";
	features << ++h << ":" << mm.m03 << " ";
	features << ++h << ":" << mm.m10 << " ";
	features << ++h << ":" << mm.m11 << " ";
	features << ++h << ":" << mm.m12 << " ";
	features << ++h << ":" << mm.m20 << " ";
	features << ++h << ":" << mm.m21 << " ";
	features << ++h << ":" << mm.m30 << " ";
	features << ++h << ":" << mm.mu02 << " ";
	features << ++h << ":" << mm.mu03 << " ";
	features << ++h << ":" << mm.mu11 << " ";
	features << ++h << ":" << mm.mu12 << " ";
	features << ++h << ":" << mm.mu20 << " ";
	features << ++h << ":" << mm.mu21 << " ";
	features << ++h << ":" << mm.mu30 << " ";

	features << ++h << ":" << mm.nu02 << " ";
	features << ++h << ":" << mm.nu03 << " ";
	features << ++h << ":" << mm.nu11 << " ";
	features << ++h << ":" << mm.nu12 << " ";
	features << ++h << ":" << mm.nu20 << " ";
	features << ++h << ":" << mm.nu21 << " ";
	features << ++h << ":" << mm.nu30 << " ";

	features << "\n";
	features.close();*/

	/*namedWindow("binary", CV_WINDOW_AUTOSIZE);
	namedWindow("original", CV_WINDOW_AUTOSIZE);
	namedWindow("inverted", CV_WINDOW_AUTOSIZE);
	imshow("binary", binary_img);
	imshow("original", src);
	imshow("inverted", inverted_img);*/
	waitKey(0);

	return 0;
}