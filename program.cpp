#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    std::string s;
    std::ifstream file("input.txt");

    if (!file) {
        std::cout << "file opening failed!\n";
        return EXIT_FAILURE;
    }
    while (std::getline(file, s)) {
        std::cout << s << std::endl;
    }

    file.close();
	return 0;
}