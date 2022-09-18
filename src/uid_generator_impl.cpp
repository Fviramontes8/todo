#include <random>
#include <string>
#include <sstream>

#include "../include/todo_app/uid_generator.hpp"

namespace fv_todo {
	static std::random_device rand_dev;
	static std::mt19937 generator(rand_dev());
	static std::uniform_int_distribution<> distrib(0, 15);

	std::string generate_uid() {
		std::stringstream int_hex_stream;
		for (int i=0; i<16; ++i) {
			int generated_int = distrib(generator);
			int_hex_stream << std::hex << generated_int;
		}
		return int_hex_stream.str();
	}
}
