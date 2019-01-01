#pragma once

#include "ThresholdWithMask.h"
#include "opencv2/core/cvdef.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Emgu::CV;

namespace EmguCvThresholdWithMask {
	public ref class ThresholdMasked
	{
	protected:
		!ThresholdMasked();

	public:
		ThresholdMasked();
		~ThresholdMasked();

		double Threshold(Emgu::CV::Mat ^src, Emgu::CV::Mat ^% dst, 
			double thresh, double maxval, Emgu::CV::CvEnum::ThresholdType type, Emgu::CV::Mat ^mask);
	};
}
