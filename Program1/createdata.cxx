#include <cstdio>
#include <iostream>
#include <random>
#include <string>

#include "json.hpp"

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Usage: %s numSamples arraySize\n", argv[0]);
		return EXIT_FAILURE;
	}

	unsigned int numSamples = 0, arraySize = 0;
	if (sscanf(argv[1], "%u", &numSamples) != 1 || sscanf(argv[2], "%u", &arraySize) != 1) {
		printf("numSamples and arraySize must be positive integers\n");
		return EXIT_FAILURE;
	}

	// C++11 random number tutorial: https://gist.github.com/PhDP/5289449
	// Seed random number generator
	std::mt19937_64 rng(time(0));
	// Create uniform distribution
	std::uniform_int_distribution<int> unif(
		std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	nlohmann::json samples;
	samples["metadata"]["numSamples"] = numSamples;
	samples["metadata"]["arraySize"] = arraySize;
	unsigned int totalZeros = (int) floor(log10((double) numSamples)) + 1;
	for (unsigned int sample = 1; sample <= numSamples; sample++) {
		int sampleZeros =  (int) floor(log10((double) sample)) + 1;
		std::string sampleNum = std::string(totalZeros - sampleZeros, '0').append(std::to_string(sample));
		nlohmann::json result;
		// On size_t usage here: https://stackoverflow.com/questions/131803/unsigned-int-vs-size-t
		for (size_t i = 0; i < arraySize; i++) {
				// Add random integer to array
				result.push_back(unif(rng));
		}
		samples["Sample" + sampleNum] = result;
	}
	std::cout << samples.dump(2) << std::endl;
	return EXIT_SUCCESS;
}