#include <gtest/gtest.h>
#include "Class session.cpp"

// Тестирование корректной строки.
TEST(ClassSessionTest, ParseCorrectLine) {
	std::string input = "2023.01.01 \"101\" \"Иванов И.И.\"";
	ClassSession session = ClassSession::ParseLine(input);
	EXPECT_EQ("2023.01.01", session.GetDate());
	EXPECT_EQ("101", session.GetClassroom());
	EXPECT_EQ("Иванов И.И.", session.GetTeacher());
}

// Тестирование некорректной даты.
TEST(ClassSessionTest, ParseIncorrectDateFormat) {
	std::string input = "01/01/2023 \"101\" \"Иванов И.И.\"";
	EXPECT_ANY_THROW(ClassSession::ParseLine(input));
}

// Тестирование отсутствующих кавычек у аудитории.
TEST(ClassSessionTest, ParseMissingQuotesClassroom) {
	std::string input = "2023.01.01 101 \"Иванов И.И.\"";
	EXPECT_ANY_THROW(ClassSession::ParseLine(input));
}

// Тестирование отсутствующих кавычек у ФИО преподавателя.
TEST(ClassSessionTest, ParseMissingQuotesTeacher) {
	std::string input = "2023.01.01 \"101\" Иванов И.И.";
	EXPECT_ANY_THROW(ClassSession::ParseLine(input));
}

// Тестирование лишних символов.
TEST(ClassSessionTest, ParseExtraCharacters) {
	std::string input = "2023.01.01 \"101\" \"Иванов И.И.\" extra";
	EXPECT_ANY_THROW(ClassSession::ParseLine(input));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}