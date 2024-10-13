/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** RemoteDriver.hpp
*/

#pragma once

#include "GEngine/libdev/Component.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string>
#include <sstream>

namespace gengine::interface::component {

    class RemoteDriver: public gengine::Component<RemoteDriver> {
    public:
        // Constructor - Generates a new UUID upon object creation
        RemoteDriver() {
            generateUUID();
        }

        // Copy constructor
        RemoteDriver(const RemoteDriver& other) {
            m_uuid = other.getUUIDBytes();
        }

        // Assignment operator
        RemoteDriver& operator=(const RemoteDriver& other) {
            if (this != &other) {
                m_uuid = other.getUUIDBytes();
            }
            return *this;
        }

        // Overloading the == operator to compare based on UUID
        bool operator==(const RemoteDriver& other) const {
            return m_uuid == other.getUUIDBytes();
        }

        // Getter for the UUID as a string (hexadecimal format)
        std::string getUUIDString() const {
            return boost::uuids::to_string(m_uuid);
        }

        // Getter for the raw UUID bytes (for network transmission)
        const boost::uuids::uuid& getUUIDBytes() const {
            return m_uuid;
        }

    private:
        boost::uuids::uuid m_uuid;

        // Method to generate a random UUID using Boost
        void generateUUID() {
            boost::uuids::random_generator generator;
            m_uuid = generator();
        }
    };
}

namespace std {
    template <>
    struct hash<gengine::interface::component::RemoteDriver> {
        std::size_t operator()(const gengine::interface::component::RemoteDriver& driver) const {
            const boost::uuids::uuid& uuid = driver.getUUIDBytes();
            std::size_t hash_value = 0;
            for (auto byte : uuid) {
                hash_value ^= std::hash<uint8_t>{}(byte) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
            }
            return hash_value;
        }
    };
}
