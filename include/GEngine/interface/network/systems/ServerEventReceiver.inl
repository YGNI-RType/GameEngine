/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** RemoteEvent.cpp
*/

template <class... Events>
gengine::interface::network::system::ServerEventReceiver<Events...>::ServerEventReceiver()
    : m_server(Network::NET::getServer()) {}

template <class... Events>
void gengine::interface::network::system::ServerEventReceiver<Events...>::init(void) {
    this->template subscribeToEvent<gengine::system::event::MainLoop>(&ServerEventReceiver::onMainLoop);
    (dynamicPublish<Events>(), ...);
}

template <class... Events>
void gengine::interface::network::system::ServerEventReceiver<Events...>::onMainLoop(gengine::system::event::MainLoop &e) {
    auto &clients = this->template getSystem<gengine::interface::network::system::ServerClientsHandler>();
    Network::UDPMessage msg(true, Network::CL_EVENT);
    size_t readCount = 0;

    for (auto &[id, client] : clients.getClients()) {
        if (client.shouldDelete())
            continue;
        if (!client.getNet()->popIncommingData(msg, readCount))
            continue;

        std::uint64_t nb;
        msg.readContinuousData(nb, readCount);

        for (size_t i = 0; i < nb; i++) {
            std::uint64_t type;
            msg.readContinuousData(type, readCount);
            auto it = m_eventsCallbacks.find(type);
            if (it == m_eventsCallbacks.end())
                throw std::runtime_error("Event type not found");

            auto &[callback, size] = it->second;
            std::vector<Network::byte_t> data(size);

            msg.readData(data.data(), readCount, size);
            readCount += size;
            callback(data.data());
        }
    }
}

template <class... Events>
template <typename T>
void gengine::interface::network::system::ServerEventReceiver<Events...>::dynamicPublish(void) {
    m_eventsCallbacks.insert(std::make_pair(m_id, std::make_pair<std::function<void(void *)>, size_t>(
        [this](void *data) -> void {
            event::RemoteEvent<T> event(*reinterpret_cast<T *>(data));
            this->template publishEvent<event::RemoteEvent<T>>(event);
        },
        sizeof(T))));
    m_id++;
}

