/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** cvar
*/

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

namespace CVar {

// Templating may result issues on convar indexing
class ConVar {
public:
    enum flag {
        NONE = 0x00,
        CHEAT = 0x01,    // used only when cheat enabled
        CMD = 0x02,      // only in cmd (starting the software)
        ROM = 0x04,      // nobody can change the value
        SETUP = 0x08,    // Commands that are in setup, use callbacks
        SYSTEM = 0x10,   // System commands
        TRANSMIT = 0x20, // Server commands, needs to trasmit to the server
        SELF = 0x40      // Client commands, based on self process
    };

public:
    ConVar(const std::string &name, const std::string &value, short flags, const std::string &description = "");
    ~ConVar() = default;

    const std::string &getRawValue(void) const {
        return m_value;
    }
    const int getIntValue(void) const {
        return m_intValue;
    }
    const std::string &getDescription(void) const {
        return m_description;
    }

    const short getFlags(void) const {
        return m_flags;
    }
    void setValue(const std::string &value, bool isUserInput = false);

private:
    static std::unordered_map<std::string, ConVar *> &getAllCommands() {
        static std::unordered_map<std::string, ConVar *> instance = {};
        return instance;
    }

    static std::unordered_map<std::string, ConVar *> &getPublicCommands() {
        static std::unordered_map<std::string, ConVar *> instance = {};
        return instance;
    }

private:
    std::string m_value;
    std::string m_description;
    int m_intValue;
    short m_flags;
    // std::function<void(void)> m_callback; // only used on system commands
};

extern ConVar sv_cheats;

} // namespace CVar
