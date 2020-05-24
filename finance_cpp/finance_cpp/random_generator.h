


class RandomGenerator {
public:
	RandomGenerator(unsigned int seed);
	int randint();

private:
	unsigned int seed;
	unsigned int mod = 0x7fffffff;
};