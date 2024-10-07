/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Base.cpp
*/

#include "exceptions/Base.hpp"

namespace gengine {
Exception::Exception(const std::string &message, const char *file, int line, const char *color)
    : m_message(message)
    , m_file(file)
    , m_line(line)
    , m_color(color) {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    m_timestamp = std::ctime(&time_t_now);
    m_timestamp.pop_back(); // Remove newline character
}

const char *Exception::what() const noexcept {
    std::ostringstream oss;
    oss << std::endl
        << m_color << "=== " << colors::E_RESET << "GEngine Exception" << m_color << " ===" << colors::E_RESET
        << std::endl // Separator
        << "Type: " << getType() << colors::E_RESET << std::endl
        << "Msg: " << m_message << colors::E_RESET << std::endl
        << "File: " << m_file << ", Line: " << m_line << colors::E_RESET << std::endl
        << "Time: " << m_timestamp << colors::E_RESET << std::endl
        << m_color << "=========================" << colors::E_RESET;
    m_formattedMessage = oss.str();
    return m_formattedMessage.c_str();
}

FatalException::FatalException(const std::string &message, const char *file, int line)
    : Exception(message, file, line, colors::E_RED) {
}

const char *FatalException::getType() const noexcept {
    return "Fatal Error";
}

ErrorException::ErrorException(const std::string &message, const char *file, int line)
    : Exception(message, file, line, colors::E_RED) {
}

const char *ErrorException::getType() const noexcept {
    return "Error";
}

WarningException::WarningException(const std::string &message, const char *file, int line)
    : Exception(message, file, line, colors::E_YELLOW) {
}

const char *WarningException::getType() const noexcept {
    return "Warning";
}

InfoException::InfoException(const std::string &message, const char *file, int line)
    : Exception(message, file, line, colors::E_BLUE) {
}

const char *InfoException::getType() const noexcept {
    return "Info";
}
} // namespace gengine
