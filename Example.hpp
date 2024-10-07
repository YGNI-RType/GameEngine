template <typename T>
struct Life : public gengine::Component {
    T life;
    Life(T &life_unit)
        : life(life_unit) {
    }
    Life(T &&life_unit)
        : life(life_unit) {
    }

    Life<T> &operator++(void) {
        life++;
        return *this;
    }
};

struct StartSystem : public gengine::System<StartSystem> {
    void init(void) override {
        subscribeToEvent<gengine::system::event::StartEngine>(&StartSystem::onStart);
    }

    void onStart(gengine::system::event::StartEngine &e) {
        spawnEntity(Life<int>(1));
        publishEvent(gengine::system::event::MainLoop());
    }
};

struct AddSystem : public gengine::System<AddSystem, Life<int>> {
    void init(void) override {
        subscribeToEvent<gengine::system::event::MainLoop>(&AddSystem::onMainLoop);
    }

    void onMainLoop(gengine::system::event::MainLoop &event) {
        auto &lifes = getComponent<Life<int>>();
        for (auto &[entity, life] : lifes) {
            life.life++;
            std::cout << life.life << std::endl;
            if (life.life == 10)
                publishEvent(gengine::system::event::StopMainLoop());
        }
    }
};
