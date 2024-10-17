/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** ClientEventPublisher.cpp
*/

// #include "GEngine/interface/network/systems/ClientEventPublisher.hpp"

template <class... Events>
gengine::interface::network::system::ClientEventPublisher<Events...>::ClientEventPublisher()
    : m_client(Network::NET::getClient())
    , m_msg(true, Network::CL_EVENT) {
}

template <class... Events>
void gengine::interface::network::system::ClientEventPublisher<Events...>::init(void) {
    this->template subscribeToEvent<gengine::system::event::StartEngine>(&ClientEventPublisher::onStartEngine);
    this->template subscribeToEvent<gengine::system::event::MainLoop>(&ClientEventPublisher::onMainLoop);
    (dynamicSubscribe<Events>(), ...);
    auto &eventManager = Network::NET::getEventManager();
    eventManager.registerCallback<int>(Network::Event::CT_OnServerReady, [this](int) -> void {
        std::lock_guard<std::mutex> lock(m_netMutex);
        m_ready = true;
    });
}

template <class... Events>
void gengine::interface::network::system::ClientEventPublisher<Events...>::onStartEngine(
    gengine::system::event::StartEngine &e) {
    m_msg.setAck(true);
    m_msg.appendData<std::uint64_t>(0);
    m_eventCount = 0;
}

template <class... Events>
void gengine::interface::network::system::ClientEventPublisher<Events...>::onMainLoop(
    gengine::system::event::MainLoop &e) {
    if (!m_ready)
        return;

    m_msg.writeData(m_eventCount, sizeof(Network::UDPG_NetChannelHeader), 0, false);
    m_client.pushData(m_msg);
    m_msg.clear(true);

    m_msg.appendData<std::uint64_t>(0);
    m_eventCount = 0;
}

template <class... Events>
template <typename T>
void gengine::interface::network::system::ClientEventPublisher<Events...>::dynamicSubscribe(void) {
    m_events.insert(std::make_pair(std::type_index(typeid(T)), m_id));
    this->template subscribeToEvent<T>([this](T &event) -> void {
        if (m_eventCount > m_maxEventToSend)
            return;

        m_msg.appendData<std::uint64_t>(m_events.find(std::type_index(typeid(T)))->second);
        m_msg.appendData<T>(event);
        m_eventCount++;
    });
    m_id++;
}
