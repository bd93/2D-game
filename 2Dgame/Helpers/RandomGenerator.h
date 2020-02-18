#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <functional>


class RandomGenerator
{
public:
	RandomGenerator() = delete;
	static float GetFloat(float min, float max)
	{
		float random = min + ((float)rand() / (float)RAND_MAX) * (max-min);
		return random;
	}
	static int GetInt(int min, int max)
	{
		int random = min + rand() % (max-min);
		return random;
	}
};


#endif // !RANDOMGENERATOR_H