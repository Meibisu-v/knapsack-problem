#include <cstdlib>

int getRandomInt() {
	return (rand() << 16) | rand();
}

long long getRandomLong() {
	return (getRandomInt() * (1LL << 32)) | getRandomInt();
}

int getRandomInt(int l, int r) {
	return l + (getRandomInt() % (r - l + 1));
}

long long getRandomLong(long long l, long long r) {
	return l + (getRandomLong() % (r - l + 1));
}
