/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** RemoteDriver.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"
#include <sstream>
#include <stduuid/uuid.h>
#include <string>

namespace gengine::interface::component {

class RemoteDriver : public gengine::Component<RemoteDriver> {
public:
    // Constructor - Generates a new UUID upon object creation
    RemoteDriver();

    // Copy constructor
    RemoteDriver(const RemoteDriver &other);

    // Assignment operator
    RemoteDriver &operator=(const RemoteDriver &other);

    // Overloading the == operator to compare based on UUID
    bool operator==(const RemoteDriver &other) const;

    // Getter for the UUID as a string (hexadecimal format)
    std::string getUUIDString() const;

    // Getter for the raw UUID bytes (for network transmission)
    const uuids::uuid &getUUIDBytes() const;

    bool operator<(const RemoteDriver &other) const {
        return false;
    }

private:
    uuids::uuid m_uuid;

    void generateUUID();
};
} // namespace gengine::interface::component

namespace std {
template <>
struct hash<gengine::interface::component::RemoteDriver> {
    std::size_t operator()(const gengine::interface::component::RemoteDriver &driver) const {
        const uuids::uuid &uuid = driver.getUUIDBytes();
        std::size_t hash_value = 0;
        auto bytes = uuid.as_bytes();
        for (const auto byte : bytes)
            hash_value ^= std::hash<uint8_t>{}((uint8_t)byte) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
        return hash_value;
    }
};
} // namespace std
