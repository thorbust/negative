#include "ppm.h"
#include "image.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define LOG(x) std::cout << x << std::endl;

float * imaging::ReadPPM(const char * filename, int * w, int * h) {
	// PPM header data
	std::string type;
	int width;
	int height;
	unsigned int intensity;
	
	std::ifstream file_stream;
	
	file_stream.open(filename, std::ios_base::binary);

	if (!file_stream.is_open()) throw("Cannot open file");

	file_stream >> type 
				>> width 
				>> height 
				>> intensity;

	file_stream.get();

	*w = width;
	*h = height;

	int size = 3 * width * height; // Size of float array 3 X w X h 3 rgb values

	unsigned char* buffer = new unsigned char[size];

	float* floatArray = new float[size];

	if (type.compare("P6") != 0) throw("Cannot read file. Must be P6");
	if (intensity > 255) throw("Cannot read file. Color intensity must be up to 255");

	
	//file_stream.read(reinterpret_cast<char *>(floatArray), size);

	file_stream.read(reinterpret_cast<char *>(buffer), size);


	file_stream.close();

	std::cout << "the entire file content is in memory \n";

	for (int i = 0; i < size; i++) {
		floatArray[i] = (float)buffer[i];
		floatArray[i] /= 255.f;
	}


	return floatArray;
}

bool imaging::WritePPM(const float * data, int w, int h, const char * filename)
{
	try
	{
		// Setting up the header of PPM file. 
		std::ofstream file_stream(filename, std::ios_base::binary);
		file_stream << "P6\n";
		file_stream << w << "\n";
		file_stream << h << "\n";
		file_stream << "255\n";

		// Write buffer data to the given file.

		std::cout << "enter" << std::endl;
		// PPM file data as a char type
		/*float * farr = new float[3 * w*h];
		for (int i = 0; i < 3*w*h; i++)
		{
			farr[i] = data[i];
		}

		unsigned char* ppm_data = new unsigned char[3 * w*h]; 

		for (int i = 0; i < 3 * w*h; i++) {
			unsigned char c = (unsigned char)(farr[i]);
			file_stream.write((char*)&c, sizeof(c));
		}*/
		

		//ppm_data[0] = (unsigned char)data[0];

		//unsigned char* ppm_data = new unsigned char[3 * w*h];

		for (int i = 0; i < 3*w*h; i++) {
			unsigned char c = (unsigned char)(data[i] * 255);
			if (i < 10) {
				LOG((int)c);
			}
			file_stream.write((char*)&c, sizeof(c));
		}
		
		file_stream.close();

		return true;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return false;
}