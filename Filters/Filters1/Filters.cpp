#include "Filters.h"

template<class T>
T clamp(T v, int max, int min)
{
	if (v > max)
		return max;
	else if (v < min)
		return min;
	return v;
}

QImage Invert_filter::calculateNewImagePixMap(const QImage& photo, int radius)
{
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++)
	{
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = photo.pixelColor(x, y);
			photo_color.setRgb(255 - photo_color.red(), 255 - photo_color.green(), 255 - photo_color.blue());
			result_Image.setPixelColor(x, y, photo_color);
		}
	}
	return result_Image;
}

QImage Matrix_filter::calculateNewImagePixMap(const QImage& photo, int radius)
{
	QImage result_Image(photo);

	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{

			QColor photo_color = calculateNewPixColor(photo, x, y, radius);
			result_Image.setPixelColor(x, y, photo_color);
		}
	return result_Image;
}

QColor Matrix_filter::calculateNewPixColor(QImage photo, int x, int y, int radius)
{
	int returnR = 0;
	int returnG = 0;// результирующие компоненты цвета
	int returnB = 0;
	int size = 2 * radius + 1; // диаметр, 1 прибавляем, так как мы стоим в центре квадратной матрицы и не учитываем центральный элемент, от которого ведем отсчет 

	for (int i = -radius; i <= radius; i++)
	{
		for (int j = -radius; j <= radius; j++)
		{
			int ind = (i + radius) * size + j + radius;
			QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0),  // j
				clamp<int>(y + i, photo.height() - 1, 0));
			returnR += color.red() * vector[ind];
			returnG += color.green() * vector[ind];
			returnB += color.blue() * vector[ind];
		}
	}
	return QColor(clamp<int>(returnR, 255, 0), clamp<int>(returnG, 255, 0), clamp<int>(returnB, 255, 0));
}

void Gaussian_blur_filter::createGaussianVector(int radius, int sigma)
{
	const unsigned int size = 2 * radius + 1;
	float norm = 0;
	vector = new float[size * size];
	for (int i = -radius; i <= radius; i++)
		for (int j = -radius; j <= radius; j++)
		{
			int idx = (i + radius) * size + (j + radius);
			vector[idx] = exp(-(i * i + j * j) / (sigma * sigma));
			norm += vector[idx];
		}
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			vector[i * size + j] /= norm;
}

QColor GrayScaleFilter::calculateNewPixelColor(QImage photo, int x, int y, int radius)
{
	QColor color = photo.pixelColor(x, y);
	float Intensity = 0.36 * color.red() + 0.53 * color.green() + 0.11 * color.blue();
	color.setRgb(Intensity, Intensity, Intensity);
	return color;
}

QImage GrayScaleFilter::calculateNewImagePixMap(const QImage& photo, int radius)
{
	QImage result_Image(photo);

	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{

			QColor photo_color = calculateNewPixelColor(photo, x, y, radius);
			result_Image.setPixelColor(x, y, photo_color);
		}
	return result_Image;
}

QColor Sepia::calculateNewPixelColor(QImage photo, int x, int y, int radius)
{
	QColor color = photo.pixelColor(x, y);
	float Intensity = 0.36 * color.red() + 0.53 * color.green() + 0.11 * color.blue();
	float k = 12.5;
	color.setRgb(clamp<int>(Intensity + 2 * k, 255, 0), clamp<int>(Intensity + 0.5 * k, 255, 0), clamp<int>(Intensity - 1 * k, 255, 0));
	return color;
}

QImage Sepia::calculateNewImagePixMap(const QImage& photo, int radius)
{
	QImage result_Image(photo);

	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{

			QColor photo_color = calculateNewPixelColor(photo, x, y, radius);
			result_Image.setPixelColor(x, y, photo_color);
		}
	return result_Image;
}

QColor Brightness::calculateNewPixelColor(QImage photo, int x, int y, int radius)
{
	QColor color = photo.pixelColor(x, y);
	int c = 20;
	color.setRgb(clamp<int>(color.red() + c, 255, 0), clamp<int>(color.green() + c, 255, 0), clamp<int>(color.blue() + c, 255, 0));
	return color;
}

QImage Brightness::calculateNewImagePixMap(const QImage& photo, int radius)
{
	QImage result_Image(photo);

	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{

			QColor photo_color = calculateNewPixelColor(photo, x, y, radius);
			result_Image.setPixelColor(x, y, photo_color);
		}
	return result_Image;
}

QColor Shift::calculateNewPixelColor(QImage photo, int x, int y, int radius)
{
	if (x + 200 >= photo.width())
	{
		return QColor(0, 0, 0);
	}
	QColor color = photo.pixelColor(x + 200, y);
	return color;
}

QImage Shift::calculateNewImagePixMap(const QImage& photo, int radius)
{
	QImage result_Image(photo);

	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = calculateNewPixelColor(photo, x, y, radius);
			result_Image.setPixelColor(x, y, photo_color);
		}
	return result_Image;
}

QColor Wave_Filter::calculateNewPixelColor(QImage photo, int x, int y, int radius)
{
	const double PI = 3.141592653589793;
	if (x + 20 * sin((2 * PI * y) / 60) >= photo.width() && x + 20 * sin((2 * PI * y) / 60) <= 0)
		return photo.pixelColor(x, y);
	QColor color = photo.pixelColor(x + 20*sin((2* PI * y)/60), y);
	return color;
}

QImage Wave_Filter::calculateNewImagePixMap(const QImage& photo, int radius)
{
	QImage result_Image(photo);

	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = calculateNewPixelColor(photo, x, y, radius);
			result_Image.setPixelColor(x, y, photo_color);
		}
	return result_Image;
}