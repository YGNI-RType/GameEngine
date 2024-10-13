/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** RemoteDriver.cpp
*/

#include "GEngine/interface/components/RemoteDriver.hpp"

namespace gengine::interface::component {

RemoteDriver::RemoteDriver() {
    generateUUID();
}

// Copy constructor
RemoteDriver::RemoteDriver(const RemoteDriver &other) {
    m_uuid = other.getUUIDBytes();
}

// Assignment operator
RemoteDriver &RemoteDriver::operator=(const RemoteDriver &other) {
    if (this != &other)
        m_uuid = other.getUUIDBytes();
    return *this;
}

// Overloading the == operator to compare based on UUID
bool RemoteDriver::operator==(const RemoteDriver &other) const {
    return m_uuid == other.getUUIDBytes();
}

// Getter for the UUID as a string (hexadecimal format)
std::string RemoteDriver::getUUIDString() const {
    return boost::uuids::to_string(m_uuid);
}

// Getter for the raw UUID bytes (for network transmission)
const boost::uuids::uuid &RemoteDriver::getUUIDBytes() const {
    return m_uuid;
}

void RemoteDriver::generateUUID() {
    boost::uuids::random_generator generator;
    m_uuid = generator();
}
} // namespace gengine::interface::component