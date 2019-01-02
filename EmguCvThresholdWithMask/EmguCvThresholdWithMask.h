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

		static double Threshold(Emgu::CV::Mat ^src, Emgu::CV::Mat ^% dst, 
			double thresh, double maxval, Emgu::CV::CvEnum::ThresholdType type, Emgu::CV::Mat ^mask);

	private:
		static cli::array<System::Byte>^ _srcMatData;
		static cli::array<System::Byte>^ _maskMatData;
		static Emgu::CV::Image<Emgu::CV::Structure::Gray, Byte>^ _dstImage;
	};
}
