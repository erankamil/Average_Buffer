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
	// - Create a buffer of 100 samples (sliding window) that will calculate
	//   'Average', 'Average-forever', 'Upper Quarter Average' and 'Lower Quarter Average'.
	//   Note: Buffer size can vary.
	// - Every time a new sample enters the buffer the oldest sample will be extracted
	//   from the buffer (if the buffer is full).
	// - 'Average' is the average of the 100 samples that are currently in the buffer (if buffer size is currently 100).
	// - 'Average-forever' is the average of all samples from the beginning of the run.
	// - 'Upper Quarter Average' is the average of the newest 25 samples (if buffer size is currently 100).
	// - 'Lower Quarter Average' is the average of the oldest 25 samples (if buffer size is currently 100).
	//    For example, if the buffer size is 8 and the last samples are [10,40,30,44,20,50,35,55]:
	//      'Upper Quarter Average' is the average of [35,55] (the newest two samples).
	//      'Lower Quarter Average' is the average of [10,40] (the oldest two samples).


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
