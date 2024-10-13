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
        RemoteDriver();

        // Copy constructor
        RemoteDriver(const RemoteDriver& other);

        // Assignment operator
        RemoteDriver& operator=(const RemoteDriver& other);

        // Overloading the == operator to compare based on UUID
        bool operator==(const RemoteDriver& other) const;

        // Getter for the UUID as a string (hexadecimal format)
        std::string getUUIDString() const;

        // Getter for the raw UUID bytes (for network transmission)
        const boost::uuids::uuid& getUUIDBytes() const;
    private:
        boost::uuids::uuid m_uuid;

        // Method to generate a random UUID using Boost
        void generateUUID();
    };
}
