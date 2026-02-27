#ifndef WATCH_H
#define WATCH_H


#include <string>
#include <vector>
#include <cstdlib>

class watch {
private:
    int day;
    int month;
    int year;
    int hours;
    int minutes;
    std::vector<std::string>* tasks;

public:
    watch();
    watch(int d, int m, int y, int h, int min, const std::vector<std::string>& t);
    watch(const watch& other);

    ~watch();

    watch& operator=(const watch& other);

    watch operator+(const watch& other) const;
    watch operator/(const watch& other) const;

    void print_info() const;
    void add_task(const std::string& task);

private:
    bool is_later(const watch& other) const;
    void add_time(int d, int h, int m);
};

#endif