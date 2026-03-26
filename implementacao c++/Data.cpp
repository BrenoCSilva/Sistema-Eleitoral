#include "Data.hpp" 
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <ctime>


Data::Data(const std::string& dataStr){
    
    std::tm tm = {};
    std::stringstream ss(dataStr);
    ss >> std::get_time(&tm, "%d/%m/%Y");

    if (ss.fail()) {
        throw std::runtime_error("Erro de parse: a data '" + dataStr + "' nao esta no formato dd/mm/yyyy.");
    }

    std::time_t tempo_t = std::mktime(&tm);
    if (tempo_t == -1) {
        throw std::runtime_error("Erro de conversao: data invalida.");
    }
    
    this->m_time_point = std::chrono::system_clock::from_time_t(tempo_t); 
}

std::string Data::paraString(const std::string& formato) const {
    
    std::time_t tempo_t = std::chrono::system_clock::to_time_t(this->m_time_point);
    std::tm tm_local = *std::localtime(&tempo_t); 

    std::stringstream ss;
    ss << std::put_time(&tm_local, formato.c_str());
    
    return ss.str();
}

const std::chrono::system_clock::time_point& Data::getTimePoint() const {
    return this->m_time_point;
}