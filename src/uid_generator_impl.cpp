#include <random>
#include <string>
#include <sstream>

#include "../include/todo_app/uid_generator.hpp"

namespace fv_todo {
	static std::random_device rand_dev;
	static std::mt19937 generator(rand_dev());
	static std::uniform_int_distribution<> distrib(0, 15);

	unsigned long long generate_uid() {
		unsigned long long uid = 0;
		for (int i=0; i<16; ++i) {
			int generated_int = distrib(generator);
			uid = uid | generated_int;
			uid <<= 1;
		}
		return uid;
	}
}
