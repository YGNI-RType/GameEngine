/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** Base.hpp
*/

#pragma once

#include <chrono>
#include <ctime>
#include <cxxabi.h>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <typeinfo>
#include <cxxabi.h>

namespace gengine::colors {
    static const char* const E_RED = "\033[31m";
    static const char* const E_YELLOW = "\033[33m";
    static const char* const E_BLUE = "\033[34m";
    static const char* const E_RESET = "\033[0m";
    static const char* const E_UNDERLINE = "\033[4m";
}

#define THROW_ERROR(msg) throw gengine::ErrorException(msg, __FILE__, __LINE__)
#define THROW_FATAL(msg) throw gengine::FatalException(msg, __FILE__, __LINE__)
#define THROW_WARNING(msg) throw gengine::WarningException(msg, __FILE__, __LINE__)
#define THROW_INFO(msg) throw gengine::InfoException(msg, __FILE__, __LINE__)

#define READABLE_TYPE_NAME(type) \
    ([]() -> std::string { \
        int status = 0; \
        char* demangled = abi::__cxa_demangle(typeid(type).name(), nullptr, nullptr, &status); \
        std::string result(demangled); \
        free(demangled); \
        return result; \
    }())

namespace gengine {

/**
 * @brief Base class for all exceptions in GEngine.
 */
class Exception : public std::exception {
public:
    /**
     * @brief Constructs an Exception.
     * @param message The error message.
     * @param file The source file where the exception occurred.
     * @param line The line number where the exception occurred.
     * @param color The color code for displaying the exception.
     */
    Exception(const std::string& message, const char* file, int line, const char* color);

    /**
     * @brief Returns a formatted error message.
     * @return Formatted error message as a C-style string.
     */
    virtual const char* what() const noexcept override;

protected:
    /**
     * @brief Returns the type of the exception.
     * @return Type of the exception as a C-style string.
     */
    virtual const char* getType() const noexcept = 0;

    std::string m_message;       ///< Error message
    const char* m_file;          ///< Source file name
    int m_line;                  ///< Line number
    std::string m_timestamp;     ///< Timestamp of the exception
    mutable std::string m_formattedMessage; ///< Formatted message
    const char* m_color;         ///< Color code for the message
};

/**
 * @brief Exception for fatal errors.
 */
class FatalException : public Exception {
public:
    /**
     * @brief Constructs a FatalException.
     * @param message The error message.
     * @param file The source file where the exception occurred.
     * @param line The line number where the exception occurred.
     */
    FatalException(const std::string& message, const char* file, int line);

protected:
    virtual const char* getType() const noexcept override;
};

/**
 * @brief Exception for errors.
 */
class ErrorException : public Exception {
public:
    /**
     * @brief Constructs an ErrorException.
     * @param message The error message.
     * @param file The source file where the exception occurred.
     * @param line The line number where the exception occurred.
     */
    ErrorException(const std::string& message, const char* file, int line);

protected:
    virtual const char* getType() const noexcept override;
};

/**
 * @brief Exception for warnings.
 */
class WarningException : public Exception {
public:
    /**
     * @brief Constructs a WarningException.
     * @param message The warning message.
     * @param file The source file where the exception occurred.
     * @param line The line number where the exception occurred.
     */
    WarningException(const std::string& message, const char* file, int line);

protected:
    virtual const char* getType() const noexcept override;
};

/**
 * @brief Exception for informational messages.
 */
class InfoException : public Exception {
public:
    /**
     * @brief Constructs an InfoException.
     * @param message The informational message.
     * @param file The source file where the exception occurred.
     * @param line The line number where the exception occurred.
     */
    InfoException(const std::string& message, const char* file, int line);

protected:
    virtual const char* getType() const noexcept override;
};

} // namespace gengine
