#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>

void readCoefficients(const std::string& filename, double& a, double& b, double& c) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        throw std::runtime_error("Не удалось открыть файл для чтения.");
    }

    inputFile >> a >> b >> c;

    // Проверка на корректность ввода
    if (inputFile.fail() || inputFile.peek() != EOF) {
        throw std::runtime_error("Некорректные входные данные в файле.");
    }

    inputFile.close();
}

void solveQuadratic(double a, double b, double c, double& root1, double& root2, bool& hasRoots) {
    if (a == 0) {
        throw std::runtime_error("Коэффициент 'a' не может быть равен нулю.");
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        root1 = (-b + std::sqrt(discriminant)) / (2 * a);
        root2 = (-b - std::sqrt(discriminant)) / (2 * a);
        hasRoots = true;
    } else if (discriminant == 0) {
        root1 = root2 = -b / (2 * a);
        hasRoots = true;
    } else {
        hasRoots = false; // Корней нет
    }
}

void writeRoots(const std::string& filename, double root1, double root2, bool hasRoots) {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        throw std::runtime_error("Не удалось открыть файл для записи.");
    }

    if (hasRoots) {
        outputFile << "Корни квадратного уравнения: " << root1 << ", " << root2 << std::endl;
    } else {
        outputFile << "Нет действительных корней." << std::endl;
    }

    outputFile.close();
}

int main() {
    try {
        double a, b, c;
        readCoefficients("/home/masha/CLionProjects/допса/lab1/input.txt", a, b, c);

        double root1, root2;
        bool hasRoots;
        solveQuadratic(a, b, c, root1, root2, hasRoots);

        writeRoots("output.txt", root1, root2, hasRoots);

        std::cout << "Решение завершено. Проверьте файл output.txt." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
