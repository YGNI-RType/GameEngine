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
    return uuids::to_string(m_uuid);
}

// Getter for the raw UUID bytes (for network transmission)
const uuids::uuid &RemoteDriver::getUUIDBytes() const {
    return m_uuid;
}

void RemoteDriver::generateUUID() {
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size>{};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::mt19937 generator(seq);
    uuids::uuid_random_generator gen{generator};

    uuids::uuid_random_generator uuidG(gen);
    m_uuid = uuidG();
}
} // namespace gengine::interface::component