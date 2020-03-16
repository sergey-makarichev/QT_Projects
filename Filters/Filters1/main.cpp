#include <QtCore/QCoreApplication>
#include <QImage>
#include <string>
#include <iostream>
#include "Filters.h"

using namespace std;

int main(int argc, char* argv[])
{
	string s;
	QImage photo;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-p") && (i + 1 < argc)) // strcmp сравнивает символы 2 строк пока не будут найдены различные
			s = argv[i + 1];                          //символы или не будет достигнут конец строки. 0, если строки равны
	}
	photo.load(QString(s.c_str()));
	photo.save("Starting.JPG");

	//Invert_filter* invert = new Invert_filter();
	//QImage InvertImage = invert->calculateNewImagePixMap(photo, 0);
	//InvertImage.save("Invert.JPG");

	//Blur_filter* matrixFilter = new Blur_filter(3);
	//QImage blurImage = matrixFilter->calculateNewImagePixMap(photo, 3);
	//blurImage.save("blurImage.jpg");

	//Gaussian_blur_filter* GaussFilter = new Gaussian_blur_filter();
	//QImage GaussImage = GaussFilter->calculateNewImagePixMap(photo, 3);
	//GaussImage.save("GaussImage.jpg");

	//GrayScaleFilter* grayFilter = new GrayScaleFilter();
	//QImage grayImage = grayFilter->calculateNewImagePixMap(photo, 0);
	//grayImage.save("GrayImage.jpg");

	//Sepia* sepiaFilter = new Sepia();
	//QImage sepiaImage = sepiaFilter->calculateNewImagePixMap(photo, 0);
	//sepiaImage.save("SepiaImage.jpg");

	//Brightness* brightnessFilter = new Brightness();
	//QImage brightnessImage = brightnessFilter->calculateNewImagePixMap(photo, 0);
	//brightnessImage.save("BrightnessImage.jpg");

	//SobelY_filter* SobelYFilter = new SobelY_filter();
	//QImage SobelYImage = SobelYFilter->calculateNewImagePixMap(photo, 1);
	//SobelYImage.save("SobelY_filter.jpg");

	//SobelX_filter* SobelXFilter = new SobelX_filter();
	//QImage SobelXImage = SobelXFilter->calculateNewImagePixMap(photo, 1);
	//SobelXImage.save("SobelX_filter.jpg");

	//Sharpness_Filter1* SharpnessFilter1 = new Sharpness_Filter1();
	//QImage SharpnessImage1 = SharpnessFilter1->calculateNewImagePixMap(photo, 1);
	//SharpnessImage1.save("Sharpness_Filter1.jpg");

	//Shift* ShiftFilter = new Shift();
	//QImage ShiftImage = ShiftFilter->calculateNewImagePixMap(photo, 0);
	//ShiftImage.save("ShiftFilter.jpg");

	MotionBlur_filter* MotionFilter = new MotionBlur_filter(1);
	QImage MotionblurImage = MotionFilter->calculateNewImagePixMap(photo, 1);///
	MotionblurImage.save("MotionblurImage.jpg");

	Wave_Filter* WaveFilter = new Wave_Filter();
	QImage WaveImage = WaveFilter->calculateNewImagePixMap(photo, 1);///
	WaveImage.save("WaveImage.jpg");
	return 0;
}
