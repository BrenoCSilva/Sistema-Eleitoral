#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <chrono>


class Data {
public:

    Data(const std::string& dataStr);

    std::string paraString(const std::string& formato = "%d/%m/%Y") const;

    const std::chrono::system_clock::time_point& getTimePoint() const;

private:
    std::chrono::system_clock::time_point m_time_point;
};


#endif