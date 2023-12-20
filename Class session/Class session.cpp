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

// Функция чтения данных сессии из строки.
ClassSession ParseLine(const std::string& str) {
    std::istringstream iss(str);
    std::string date, classroom, teacher;

    iss >> date;
    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\"');
    std::getline(iss, classroom, '\"');
    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\"');
    std::getline(iss, teacher, '\"');

    return ClassSession(date, classroom, teacher);
}

// Функция вывода данных сессии.
void PrintSession(const ClassSession& session) {
    std::cout << "Дата занятия: " << session.date
        << ", Аудитория: " << session.classroom
        << ", Преподаватель: " << session.teacher << std::endl;
}

// Основная функция для обработки файла сессии.
void ProcessSessionFile(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            ClassSession session = ParseLine(line);
            PrintSession(session);
        }
        file.close();
    }
    else {
        std::cerr << "Невозможно открыть файл." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    const std::string file_name = "session.txt";
    ProcessSessionFile(file_name);

    return 0;
}
