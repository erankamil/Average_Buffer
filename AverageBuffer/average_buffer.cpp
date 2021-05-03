#include "average_buffer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include <fstream>

using namespace std::chrono_literals;


int main()
{
	AverageBuffer<float> avgBuf(100);
	ofstream  myfile;
	myfile.open("output.txt");

	std::srand(0);
	for (int i = 0; i < 200; i++)
	{
		// Generate rand number (between 0-100)
		float randNum = 100 * ((float)std::rand() / RAND_MAX);

		// Adding new sample to the buffer
		avgBuf.addSample(randNum);

		myfile << "i = " << i << std::endl;
		myfile << "randNum = " << randNum << std::endl;
		myfile << "getAverage = " << avgBuf.getAverage() << std::endl;
		myfile << "getAverageForever = " << avgBuf.getAverageForever() << std::endl;
		myfile << "getUpperQuarterAverage = " << avgBuf.getUpperQuarterAverage() << std::endl;
		myfile << "getLowerQuarterAverage = " << avgBuf.getLowerQuarterAverage() << std::endl;
		std::this_thread::sleep_for(1ms);
	}

	// Clearing the buffer content and parameters
	avgBuf.clear();

	return 0;
}
