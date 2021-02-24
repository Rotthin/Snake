#pragma once
#include <string>
#include <fstream>

namespace rott {
	namespace saving {
		void saveInt(std::string fileName, int value) {
			std::ofstream stream(fileName);
			stream << value;
		}

		int loadInt(std::string fileName) {
			int result;
			std::ifstream stream(fileName);

			if (!stream)
				return 0;

			stream >> result;
			
			return result;
		}
	}
}