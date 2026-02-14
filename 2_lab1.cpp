#include <iostream>
#include <string>
#include <vector>

class Watch {
private:
    int day;
    int month;
    int year;
    int hours;
    int minutes;
    std::string dayOfWeek;

public:
    
    Watch() : day(1), month(1), year(2026), hours(0), minutes(0), dayOfWeek("четверг") {}

    Watch(int d, int m, int y, int h, int min, std::string dw) {
        day = d;
        month = m;
        year = y;
        hours = h;
        minutes = min;
        dayOfWeek = dw;
    }

    Watch(const Watch& other) {
        day = other.day;
        month = other.month;
        year = other.year;
        hours = other.hours;
        minutes = other.minutes;
        dayOfWeek = other.dayOfWeek;
    }

    ~Watch() {
        std::cout << "деструктор вызван" << std::endl;
    }

    int getDay() const { 
        return day; 
    }
    int getMonth() const { 
        return month; 
    }
    int getYear() const { 
        return year; 
    }
    int getHours() const { 
        return hours; 
    }
    int getMinutes() const { 
        return minutes; 
    }
    std::string getDayOfWeek() const { 
        return dayOfWeek; 
    }

    void setDayOfWeek(std::string dw) {
        std::vector<std::string> validDays = {
            "понедельник", "вторник", "среда", "четверг", "пятница", "суббота", "воскресенье"
        };
        bool isValid = false;
        for (const auto& d : validDays) {
            if (dw == d) {
                isValid = true;
                break;
            }
        }
        if (isValid) {
            dayOfWeek = dw;
        }
        else {
            std::cout << "некорректный день недели" << std::endl;
        }
    }

    void printInfo() const {
        std::cout << "дата: " << (day < 10 ? "0" : "") << day << "."
            << (month < 10 ? "0" : "") << month << "." << year << std::endl;
        std::cout << "время: " << (hours < 10 ? "0" : "") << hours << ":"
            << (minutes < 10 ? "0" : "") << minutes << std::endl;
        std::cout << "день недели: " << dayOfWeek << std::endl;
    }
 
    void addMinutes(int x) {
        minutes += x;

        while (minutes >= 60) {
            minutes -= 60;
            hours++;
        }

        while (hours >= 24) {
            hours -= 24;
            day++;
        }

        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        while (day > daysInMonth[month - 1]) {
            day -= daysInMonth[month - 1];
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }
};

int main() {

    Watch myWatch(28, 2, 2026, 23, 30, "понедельник");

    std::cout << "текущие данные" << std::endl;
    myWatch.printInfo();

    std::cout << "\nдобавить 45 минут" << std::endl;
    myWatch.addMinutes(45); 
    myWatch.printInfo();

    std::cout << "\nошибки ввода: " << std::endl;
    myWatch.setDayOfWeek("не понедельник");

    return 0;
}