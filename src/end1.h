#ifndef __END1_AGENT__H
#define __END1_AGENT__H 

#include "enviro.h"

using namespace enviro;

class end1Controller : public Process, public AgentInterface {

    public:
    end1Controller() : Process(), AgentInterface() {}

    void init() {
        //! emit event to change text to notify player win.
        notice_collisions_with("Robot", [&](Event &e) {
            remove_agent(id());
            emit(Event("change_text",{{"text", "Player 1(green) win!"}}  ));
            emit(Event("has_winner"));
        });
    }
    void start() {}
    void update() {}
    void stop() {}
};

class end1 : public Agent {
    public:
    end1(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    end1Controller c;
};

DECLARE_INTERFACE(end1)

#endif