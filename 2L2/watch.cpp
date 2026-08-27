#include <iostream>
#include "watch.h"

watch::watch() : day(1), month(1), year(2026), hours(0), minutes(0) {
    tasks = new std::vector<std::string>();
}

watch::watch(int d, int m, int y, int h, int min, const std::vector<std::string>& t) {
    day = d;
    month = m;
    year = y;
    hours = h;
    minutes = min;
    tasks = new std::vector<std::string>(t);
}

watch::watch(const watch& other) {
    day = other.day;
    month = other.month;
    year = other.year;
    hours = other.hours;
    minutes = other.minutes;
    tasks = new std::vector<std::string>(*(other.tasks));
}

watch::~watch() {
    if (tasks) {
        tasks->clear(); 
        delete tasks;   
    }
    std::cout << "деструктор вызван" << std::endl;
}

watch& watch::operator=(const watch& other) {
    if (this == &other) return *this;

    day = other.day;
    month = other.month;
    year = other.year;
    hours = other.hours;
    minutes = other.minutes;
    delete tasks; 
    tasks = new std::vector<std::string>(*(other.tasks)); 
    return *this;
}

bool watch::is_later(const watch& other) const {
    if (year != other.year) return year > other.year;
    if (month != other.month) return month > other.month;
    if (day != other.day) return day > other.day;
    if (hours != other.hours) return hours > other.hours;
    return minutes > other.minutes;
}

void watch::add_time(int d, int h, int m) {
    minutes += m;
    hours += minutes / 60;
    minutes %= 60;
    hours += h;
    day += (hours / 24) + d;
    hours %= 24;
    
    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    while (true) {
        int dim = days_in_month[month - 1];
        if (day <= dim) break;
        day -= dim;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

void watch::add_task(const std::string& task) {
    for (const auto& t : *tasks) {
        if (t == task) return;
    }
    tasks->push_back(task);
}

watch watch::operator+(const watch& other) const {
    watch result;
    if (this->is_later(other)) {
        result = *this;
    }
    else {
        result = other;
    }

    result.add_time(7, 1, 0);
    result.tasks->clear();

    for (const auto& t : *(this->tasks)) {
        result.add_task(t);
    }
    for (const auto& t : *(other.tasks)) {
        result.add_task(t);
    }
    return result;
}

watch watch::operator/(const watch& other) const {
    watch result;
    if (this->is_later(other)) {
        result = other;
    }
    else {
        result = *this;
    }

    result.add_time(3, 0, 0);
    result.tasks->clear();

    int count1 = this->tasks->empty() ? 0 : rand() % (this->tasks->size() + 1);
    int count2 = other.tasks->empty() ? 0 : rand() % (other.tasks->size() + 1);

    for (int i = 0; i < count1; ++i) {
        result.add_task((*this->tasks)[i]);
    }
    for (int i = 0; i < count2; ++i) {
        result.add_task((*other.tasks)[i]);
    }
    return result;
}

void watch::print_info() const {
    std::cout << "дата: " << (day < 10 ? "0" : "") << day << "."
        << (month < 10 ? "0" : "") << month << "." << year << std::endl;
    std::cout << "время: " << (hours < 10 ? "0" : "") << hours << ":"
        << (minutes < 10 ? "0" : "") << minutes << std::endl;
    std::cout << "вектор дел: ";
    if (tasks->empty()) {
        std::cout << "нет дел";
    }
    else {
        std::cout << "[";
        for (size_t i = 0; i < tasks->size(); ++i) {
            std::cout << (*tasks)[i] << (i == tasks->size() - 1 ? "" : ", ");
        }
        std::cout << "]";
    }
    std::cout << std::endl;

}
