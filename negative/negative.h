#pragma once

#include <iostream>

#include "image.h"
#include "ppm.h"
#include "cli.h"

#define IMAGE_SIZE width * height

using namespace imaging;

// Fill a Color array with raw data read from an image file
//
// \param color is the color array, which consists of red, green, blue values
// \param data is the float values of raw data read from the image file
// \param width is the image width
// \param height is the image height
//
// \return an array of type Color filled with color values
Color* FillColorFromRawData(Color* color, float* data, int width, int height);

// Calculates the value of a pixel to it's negative to a given Color array
//
// \param color is the color array to apply the filter
// \param width is the image width
// \param height is the image height
//
// \return an array of type Color with it's negative values
Color* ApplyNegativeFilter(Color* color, int width, int height);