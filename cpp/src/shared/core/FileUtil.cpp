#include "FileUtil.h"

std::string readFile(const char* fileName) {
	std::ifstream t(fileName);

	if (t.fail())
		return std::string();

	std::string source;
	t.seekg(0, std::ios::end);
	source.reserve(unsigned int(t.tellg()));
	t.seekg(0, int(std::ios::beg));

	source.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	return source;
}
