#include "stdafx.h"

#include "EmguCvThresholdWithMask.h"

namespace EmguCvThresholdWithMask {
	ThresholdMasked::ThresholdMasked() {}
	ThresholdMasked::~ThresholdMasked() {}
	ThresholdMasked::!ThresholdMasked() {
		GC::Collect();
	}

	double ThresholdMasked::Threshold(Emgu::CV::Mat ^ src, Emgu::CV::Mat ^% dst, 
		double thresh, double maxval, Emgu::CV::CvEnum::ThresholdType type, Emgu::CV::Mat ^ mask)
	{
		if (src->NumberOfChannels != 1) {
			throw gcnew System::Exception("The channel of src mat should be 1!");
		}
		if (src->Depth != Emgu::CV::CvEnum::DepthType::Cv8U) {
			throw gcnew System::Exception("The depth type of src mat should be Cv8U!");
		}
		if (mask != nullptr) {
			if (mask->NumberOfChannels != 1) {
				throw gcnew System::Exception("The channel of src mat should be 1!");
			}
			if (mask->Depth != Emgu::CV::CvEnum::DepthType::Cv8U) {
				throw gcnew System::Exception("The depth type of src mat should be Cv8U!");
			}
		}

		int srcWidth = src->Width;
		int srcHeight = src->Height;

		cli::array<System::Byte>^ srcMatData = gcnew cli::array<System::Byte>(srcWidth*srcHeight);
		src->CopyTo(srcMatData);
		pin_ptr<System::Byte> pSrcMatData = &srcMatData[0];
		unsigned char* pbySrcMatData = pSrcMatData;
		unsigned char* srcCvMatData = reinterpret_cast<unsigned char*>(pbySrcMatData);
		cv::Mat1b* srcCvMat = new cv::Mat1b(src->Rows, src->Cols, srcCvMatData);

		cv::Mat1b* maskCvMat;
		if (mask != nullptr) 
		{
			cli::array<System::Byte>^ maskMatData = gcnew cli::array<System::Byte>(srcWidth*srcHeight);
			mask->CopyTo(maskMatData);
			pin_ptr<System::Byte> pMaskMatData = &maskMatData[0];
			unsigned char* pbyMaskMatData = pMaskMatData;
			unsigned char* maskCvMatData = reinterpret_cast<unsigned char*>(pbyMaskMatData);
			maskCvMat = new cv::Mat1b(mask->Rows, mask->Cols, maskCvMatData);
		}
		else
		{
			maskCvMat = new cv::Mat1b();
		}

		cv::Mat1b* dstCvMat = new cv::Mat1b(dst->Rows, dst->Cols);
		double cvth_value = ThresholdWithMask::threshold_with_mask(*srcCvMat, *dstCvMat, thresh, maxval, (int)type, *maskCvMat);

		//Convert cv::Mat to Emgu::CV::Mat
		IplImage* dstCvIplImage = new IplImage(*dstCvMat);
		Emgu::CV::Image<Emgu::CV::Structure::Gray, Byte>^ dstImage = gcnew Emgu::CV::Image<Emgu::CV::Structure::Gray, Byte>(src->Width, src->Height);

		System::IntPtr iplImageIntPtr(dstCvIplImage);
		System::IntPtr imageIntPtr(dstImage->Ptr.ToPointer());
		System::IntPtr nullIntPtr(nullptr);
		Emgu::CV::CvInvoke::cvCopy(iplImageIntPtr, imageIntPtr, nullIntPtr);
		dst = dstImage->Mat;

		return cvth_value;
	}
}
