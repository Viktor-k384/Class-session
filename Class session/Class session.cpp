#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <clocale>
#include <vector>
#include <regex>

// Класс для хранения данных об учебном занятии
class ClassSession {
private:
    std::string date_;
    std::string classroom_;
    std::string teacher_;

public:
    ClassSession(const std::string& date, const std::string& classroom, const std::string& teacher)
        : date_(date), classroom_(classroom), teacher_(teacher) {}

    const std::string& GetDate() const { return date_; }
    const std::string& GetClassroom() const { return classroom_; }
    const std::string& GetTeacher() const { return teacher_; }

    // Проверка корректности формата даты
    static void ValidateDateFormat(const std::string& date) {
        std::regex date_pattern(R"(^\d{4}\.\d{2}\.\d{2}$)");
        if (!std::regex_match(date, date_pattern)) {
            throw std::invalid_argument("Формат даты не соответствует шаблону ГГГГ.ММ.ДД");
        }
    }

    // Разбор строки на составляющие класса
    static ClassSession ParseLine(const std::string& line) {
        std::istringstream iss(line);
        std::string date, classroom, teacher;
        char quote;

        iss >> date;
        ValidateDateFormat(date);

        iss >> quote; // Считываем символ, ожидаем кавычку
        if (quote != '\"') {
            throw std::invalid_argument("Название аудитории должно начинаться с кавычки.");
        }

        if (!std::getline(iss, classroom, '\"')) {
            throw std::invalid_argument("Неправильный формат аудитории, отсутствует закрывающая кавычка.");
        }

        iss >> quote; // Считываем символ, снова ожидаем кавычку
        if (quote != '\"') {
            throw std::invalid_argument("Имя преподавателя должно быть в кавычках.");
        }

        if (!std::getline(iss, teacher, '\"')) {
            throw std::invalid_argument("Неправильный формат ФИО преподавателя, отсутствует закрывающая кавычка.");
        }

        // Проверяем наличие лишних символов после закрывающей кавычки ФИО преподавателя
        std::string remainder;
        std::getline(iss, remainder);
        if (!remainder.empty() && remainder.find_first_not_of(" \t") != std::string::npos) {
            throw std::invalid_argument("Лишние символы после ФИО преподавателя.");
        }

        return ClassSession(date, classroom, teacher);
    }
};

// Класс для считывания данных об учебных занятиях из файла
class FileReader {
public:
    static std::vector<ClassSession> ReadSessionsFromFile(const std::string& file_name) {
        std::ifstream file(file_name);
        if (!file.is_open()) {
            throw std::runtime_error("Невозможно открыть файл: " + file_name);
        }

        std::vector<ClassSession> sessions;
        std::string line;
        while (std::getline(file, line)) {
            try {
                sessions.push_back(ClassSession::ParseLine(line));
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Ошибка при разборе строки: " << line << " — " << e.what() << std::endl;
            }
        }

        file.close();
        return sessions;
    }
};

// Функция для вывода данных о занятии
void PrintSession(const ClassSession& session) {
    std::cout << "Дата занятия: " << session.GetDate()
        << ", Аудитория: " << session.GetClassroom()
        << ", Преподаватель: " << session.GetTeacher() << std::endl;
}

// Точка входа в программу
int main() {
    setlocale(LC_ALL, "Russian");

    try {
        const std::string file_name = "session.txt";
        auto sessions = FileReader::ReadSessionsFromFile(file_name);
        for (const auto& session : sessions) {
            PrintSession(session);
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
    }

    return 0;
}