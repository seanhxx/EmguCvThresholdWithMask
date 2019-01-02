using System;
using System.IO;
using System.Drawing;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using EmguCvThresholdWithMask;
using Emgu.CV;
using Emgu.CV.CvEnum;
using Emgu.CV.Structure;

namespace TestCSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            string path = Path.Combine(typeof(Program).Assembly.CodeBase.Replace("file:///", "").Replace("/", "\\"), "..");
            string fileName = args.Length > 0 ? args[0] : string.Empty;
            if (!string.IsNullOrEmpty(fileName))
            {
                var inputMat = CvInvoke.Imread(fileName);
                var grayMat = new Mat();
                CvInvoke.CvtColor(inputMat, grayMat, ColorConversion.Bgr2Gray);

                Mat mask = new Mat(grayMat.Rows, grayMat.Cols, DepthType.Cv8U, 1);
                CvInvoke.Rectangle(mask, new Rectangle(200, 200, 200, 200), new MCvScalar(255), -1);

                Mat threshMat = new Mat();
                var thValue = ThresholdMasked.Threshold(grayMat, ref threshMat, 0, 255, ThresholdType.Otsu | ThresholdType.Binary, mask);

                Console.WriteLine("threshold value: {0}", thValue);
                var fi = new FileInfo(fileName);
                grayMat.Save(Path.Combine(path, "outputGray" + fi.Name));
                threshMat.Save(Path.Combine(path, "outputThreshold" + fi.Name));

                Console.ReadKey();
            }

        }
    }
}
