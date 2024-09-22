#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

struct unit_load {
    unit_load(const double& wei, const double& pri) {
        weight = wei;
        price = pri;
    }
    double weight;
    double price;
};

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

        for (int i = 0; i < quantity; ++i) {
            unit_load ul(weight, price);
            b_.push_back(ul);
        }
    }

    auto& get() {
        return b_;
    }

    auto get_wcon() {
        return wcon_;
    }

private:
    int ncon_;      //Количество контейнеров
    double wcon_;   //Максимальный вес контейнера
    std::vector<unit_load> b_;
    std::vector<std::vector<double>> c_;
};

bool compareItemsByValue(const unit_load& item1, const unit_load& item2) { //rename
    return item1.price > item2.price;
}

int main() {
    std::string line;
    container cont;
    std::ifstream file("input_test.txt");

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
    }
    file.close();

    std::sort(cont.get().begin(), cont.get().end(), compareItemsByValue);

    std::vector<std::vector<double>> T_(cont.get().size() + 1, std::vector<double>(1000, 0));

    for (int i = 1; i <= cont.get().size(); i++) {
        for (int w = 0; w < 1000; w++) {
            if (w < cont.get()[i - 1].weight) {
                T_[i][w] = T_[i - 1][w];
            }
            else {
                T_[i][w] = std::max(T_[i - 1][w], T_[i - 1][w - cont.get()[i - 1].weight] + cont.get()[i - 1].price);
            }
        }
    }

    std::cout << T_[cont.get().size()][cont.get_wcon() - 1];
	return 0;
}