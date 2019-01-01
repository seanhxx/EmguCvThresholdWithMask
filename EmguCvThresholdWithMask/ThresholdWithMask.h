#pragma once

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

namespace ThresholdWithMask {
	double threshold_with_mask(Mat1b& src, Mat1b& dst, double thresh, double maxval, int type, const Mat1b& mask = Mat1b());
}