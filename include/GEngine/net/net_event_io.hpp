/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** net_event_io
*/

#pragma once
namespace Network::Event {
class IO {
protected:
    int m_pipe[2];

public:
    IO();
    IO(const IO &other);
    virtual ~IO();

    void writeUpdate(void);
    void readUpdate(void);

    int getIncommingPipe(void) const {
        return m_pipe[0];
    }
};
} // namespace Network::Event
