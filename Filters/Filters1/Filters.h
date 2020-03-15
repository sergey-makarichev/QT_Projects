#pragma once
#include <QImage>
class Filters
{
public:
	Filters()
	{
	};
	~Filters()
	{
	};
	virtual QImage calculateNewImagePixMap(const QImage& photo, int radius) = 0;
};

class Invert_filter : public Filters
{
public:
	Invert_filter()
	{
	};
	~Invert_filter()
	{
	};
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
};

class GrayScaleFilter :public Filters
{
public:
	GrayScaleFilter() {};
	~GrayScaleFilter() {};
	QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
};

class Sepia : public Filters
{
public:
	Sepia() {};
	~Sepia() {};
	QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
};

class Brightness : public Filters
{
public:
	Brightness() {};
	~Brightness() {};
	QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
};

class Shift : public Filters
{
public:
	Shift() {};
	~Shift() {};
	QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
};

class Matrix_filter : public Filters {
public:
	float* vector;
	int mRadius;
	Matrix_filter(int radius = 1) : mRadius(radius) {}; // vector1
	~Matrix_filter()
	{
	};
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
	QColor calculateNewPixColor(QImage photo, int x, int y, int radius);

};

class Blur_filter : public Matrix_filter
{
public:
	Blur_filter(int radius)
	{
		mRadius = radius;
		int size = 2 * mRadius + 1;
		vector = new float[size * size];
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				vector[i * size + j] = 1.0f / (size * size);
	};
	~Blur_filter()
	{
	};
};

class MotionBlur_filter : public Matrix_filter
{
public:
	MotionBlur_filter(int radius)
	{
		mRadius = radius;
		int size = 2 * mRadius + 1;
		vector = new float[size * size];
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
			{
				if (i == j)
					vector[i * size + j] = 1.0f / (size * size);
				else
					vector[i * size + j] = 0;
			}
	};
	~MotionBlur_filter()
	{
	};
};

class Gaussian_blur_filter :public Matrix_filter
{
public:
	Gaussian_blur_filter()
	{
		createGaussianVector(3, 2);
	}
	~Gaussian_blur_filter()
	{
	};

	void createGaussianVector(int radius, int sigma);
};

class SobelY_filter : public Matrix_filter
{
public:
	SobelY_filter()
	{
		int size = 2 * mRadius + 1;
		vector = new float[size * size];
		vector[0] = -1; vector[1] = -2; vector[2] = -1;
		vector[3] = 0; vector[4] = 0; vector[5] = 0;
		vector[6] = 1; vector[7] = 2; vector[8] = 1;
	};
	~SobelY_filter() {};
};

class SobelX_filter : public Matrix_filter
{
public:
	SobelX_filter()
	{
		int size = 2 * mRadius + 1;
		vector = new float[size * size];
		vector[0] = -1; vector[1] = 0; vector[2] = 1;
		vector[3] = -2; vector[4] = 0; vector[5] = 2;
		vector[6] = -1; vector[7] = 0; vector[8] = 1;
	};
	~SobelX_filter() {};
};

class Sharpness_Filter1 : public Matrix_filter
{
public:
	Sharpness_Filter1()
	{
		int size = 2 * mRadius + 1;
		vector = new float[size * size];
		vector[0] = 0; vector[1] = -1; vector[2] = 0;
		vector[3] = -1; vector[4] = 5; vector[5] = -1;
		vector[6] = 0; vector[7] = -1; vector[8] = 0;
	};
	~Sharpness_Filter1() {};
};

class Sharpness_Filter2 : public Matrix_filter
{
public:
	Sharpness_Filter2()
	{
		int size = 2 * mRadius + 1;
		vector = new float[size * size];
		vector[0] = -1; vector[1] = -1; vector[2] = -1;
		vector[3] = -1; vector[4] = 9; vector[5] = -1;
		vector[6] = -1; vector[7] = -1; vector[8] = -1;
	};
	~Sharpness_Filter2() {};
};
