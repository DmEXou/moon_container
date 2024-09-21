#include <iostream>
#include <fstream>
#include <string>
//#include <sstream>
#include <vector>

class container {
public:
    void container_parser_begin(const std::string& str) {
        int dot = str.find(',');
        ncon_ = std::stoi(str.substr(0,dot));
        wcon_ = std::stod(str.substr(dot + 1, str.length() - dot));
    }
    void container_parser_remains(const std::string& str) {
        int dot_begin = str.find(',');
        int dot_end = str.rfind(',');
        int quantity = std::stoi(str.substr(0, dot_begin));
        double weight = std::stod(str.substr(dot_begin + 1, dot_end));
        double price = std::stod(str.substr(dot_end + 1, str.length() - dot_end));
        std::cout << std::endl;
    }
private:
    int ncon_;      //Количество контейнеров
    double wcon_;   //Максимальный вес контейнера
    std::vector<std::tuple <int, double, double>> a_;
};

int main() {
    std::string line;
    container cont;
    std::ifstream file("input.txt");

    if (!file) {
        std::cout << "file opening failed!\n";
        return 1;
    }
    int counter = 0;
    
    while (std::getline(file, line)) {
        if (counter == 0) {
            cont.container_parser_begin(line);
        }
        else {
            cont.container_parser_remains(line);
        }
        ++counter;
        //std::cout << line << std::endl;
    }

    file.close();
	return 0;
}