#include <random>
#include <string>

#include "../include/todo_app/uid_generator.hpp"

namespace fv_todo {
	static std::random_device rand_dev;
	static std::mt19937 generator(rand_dev());
	static std::uniform_int_distribution<> distrib(0, 15);

	std::string generate_uid() {
		std::string uid{""};
		for (int i=0; i<16; ++i) {
			uid += std::to_string(distrib(generator));
		}
		return uid;
	}
}
