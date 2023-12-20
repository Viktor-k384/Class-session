// Кухарский Виктор Станиславович
// ЗКИ22-07Б
// Практическая работа 1 «введение в объектно-ориентированное программирование».
// Вариант 9.
// Разработать программу, формирующую программный объект на основании его описания в виде текстовой строки.
// Объект, свойства: Учебные занятия: дата, название аудитории (строка в характерном формате),имя преподавателя(строка).

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <clocale>

// Структура для хранения данных об учебном занятии.
struct ClassSession {
    std::string date;
    std::string classroom;
    std::string teacher;

    ClassSession(const std::string& dt, const std::string& cls, const std::string& tch)
        : date(dt), classroom(cls), teacher(tch) {}
};

// Функция для чтения учебного занятия из строки.
ClassSession parseLine(const std::string& str) {
    std::istringstream iss(str);
    std::string date, classroom, teacher;

    iss >> date;
    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\"');
    std::getline(iss, classroom, '\"');
    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\"');
    std::getline(iss, teacher, '\"');

    return ClassSession(date, classroom, teacher);
}

int main() {
    setlocale(LC_ALL, "rus");

    std::ifstream file("session.txt");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            ClassSession session = parseLine(line);

            std::cout << "Дата занятия: " << session.date
                << ", Аудитория: " << session.classroom
                << ", Преподаватель: " << session.teacher << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Невозможно открыть файл." << std::endl;
    }

    return 0;
}