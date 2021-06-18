#include <iostream>
#define QUARTER(size)  (size_t) (size/4)

using namespace std;

// new comment
// new comment with other branch

template< class T>
class AverageBuffer
{
private:
	T* buffer;
	const size_t size;
	size_t nextPos = 0;
	size_t droppedElementsCount = 0;
	double droppedElementsAvg = 0; // using double and not T, T might be int for example.
	double currentAvg = 0;
	bool isEmpty = true;

	// helper functions
	size_t windowSize() const
	{
		size_t count = droppedElementsCount > 0 ? size : nextPos;
		if (count == 0 && !isEmpty)
		{
			count = size;
		}
		return count;
	}

	size_t addOne(int pos) const // using circular array
	{
		return (pos + 1) % size;
	}

	int lastPos(int pos) const
	{
		return pos - 1;
	}

	double getWeightedAverage(double avgFirst, size_t countFirst, double avgSecond, size_t countSecond) const
	{
		if (countSecond + countSecond == 0)
			return 0;

		double firstPart = (avgFirst / (countFirst + countSecond))*countFirst;
		double secondPart = (avgSecond / (countFirst + countSecond))*countSecond;
		return firstPart + secondPart;
	}

public:
	AverageBuffer(size_t size) : buffer(new T[size]), size(size) {}

	~AverageBuffer()
	{
		delete[]buffer;
	}

	AverageBuffer(const AverageBuffer& other) = delete;
	const AverageBuffer& operator=(const AverageBuffer& other) = delete;

	void addSample(T value)
	{
		size_t count = windowSize();
		if (isEmpty)
		{
			isEmpty = !isEmpty;
		}
		if (count == size) // in that case the oldest sample will be extracted from the buffer
		{
			droppedElementsAvg = getWeightedAverage(droppedElementsAvg, droppedElementsCount, buffer[nextPos], 1); // calc the dropped elements avg
			currentAvg = currentAvg - (buffer[nextPos] / count) + (value / count); // calc the buffer elements avg
			droppedElementsCount++;
		}
		else
		{
			currentAvg = getWeightedAverage(currentAvg, count, value, 1);
		}
		buffer[nextPos] = value;
		nextPos = addOne(nextPos);
	}

	double getAverage() const
	{
		return currentAvg;
	}

	double getAverageForever() const
	{
		size_t count = windowSize();
		return getWeightedAverage(droppedElementsAvg, droppedElementsCount, currentAvg, count);
	}

	double getUpperQuarterAverage() const
	{
		double UpperQuarterAvg = 0;
		size_t count = windowSize();
		int currIndex = lastPos(nextPos);
		count = QUARTER(count);
		for (int i = 0; i < count; i++)
		{
			if (currIndex < 0)
				currIndex += size;
			UpperQuarterAvg += ((double)buffer[currIndex] / count);
			currIndex = lastPos(currIndex);

		}
		return UpperQuarterAvg;
	}


	double getLowerQuarterAverage() const
	{
		double lowerQuarterAvg = 0;
		size_t count = windowSize();
		int currIndex = count < size ? 0 : nextPos;
		count = QUARTER(count);
		for (int i = 0; i < count; i++)
		{
			lowerQuarterAvg += ((double)buffer[currIndex] / count);
			currIndex = addOne(currIndex);
		}
		return lowerQuarterAvg;
	}

	void clear()
	{
		nextPos = droppedElementsCount = droppedElementsAvg = currentAvg = 0;
		isEmpty = true;
	}
};
