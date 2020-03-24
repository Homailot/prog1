#include<random>

int randomInt(int high, int low) {
	return (rand() % (high - low + 1)) + low;
}

int trueMod(int n, int divisor) {
	int result = n % divisor;

	if (result < 0) {
		return result + divisor;
	}
	return result;
}