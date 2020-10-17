#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>

using std::cout;
using std::endl;

const auto a = 0.0;
const auto b = 3.0;

auto random(const double min, const double max) -> double {
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

auto f(const double x, const bool choice) -> double {
    if (choice == 0) {
        return -sqrt(x) * sin(x);
    }
    else if (choice == 1) {
        return f(x, 0) * sin(5 * x);
    }
}

auto Annealing(const bool choice) -> std::vector<std::pair<double, double>> {
    std::vector<std::pair<double, double>> result;
    auto x_min = random(a, b);
    auto t_max = 10000.0, t_min = 0.01;
    while (t_max > t_min) {
        auto x_i = random(a, b);
        auto difference = f(x_i, choice) - f(x_min, choice);
        auto probability = 0.0;
        if (difference <= 0) {
            x_min = x_i;
            probability = 1;
        }
        else {
            auto temp = random(0, 1);
            probability = exp(-difference / t_max);
            if (temp < probability) {
                x_min = x_i;
            }
        }
        result.emplace_back(t_max, x_min);
        t_max *= 0.95;
    }
    return result;
}

void Print(const std::vector<std::pair<double, double>>& table, const bool choice) {
    cout << std::string(44, '-') << endl;
    cout << "|" << std::setw(4) << std::left << "N";
    cout << "|" << std::setw(11) << std::left << "T";
    cout << "|" << std::setw(11) << std::left << "x";
    cout << "|" << std::setw(13) << std::left << "f(x)";
    cout << '|' << endl;
    cout << std::string(44, '-') << endl;
    for (size_t i = 0; i < table.size(); i++) {
        cout << "|";
        cout << std::setw(4) << std::left << i + 1;
        cout << '|' << std::setw(11) << std::left << table[i].first;
        cout << '|' << std::setw(11) << std::left << table[i].second;
        cout << '|' << std::setw(13) << std::left << f(table[i].second, choice);
        cout << '|' << endl;
    }
    cout << std::string(44, '-') << endl;
    cout << "Result: " << "Xmin = " << table[table.size() - 1].second << " Fmin = " << f(table[table.size() - 1].second, choice) << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Алгоритм имитации отжига" << endl;
    cout << "Вариант №3:" << endl << endl;
    cout << "Функция -sqrt(x) * sin(x) для интервала [0, 3]" << endl;
    Print(Annealing(0), 0);
    cout << endl << endl << "Функция -sqrt(x) * sin(x) * sin(5 * x) для интервала [0, 3]" << endl;
    Print(Annealing(1), 1);

    return 0;
}
