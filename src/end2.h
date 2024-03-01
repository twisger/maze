#ifndef __END2_AGENT__H
#define __END2_AGENT__H 

#include "enviro.h"

using namespace enviro;

class end2Controller : public Process, public AgentInterface {

    public:
    end2Controller() : Process(), AgentInterface() {}

    void init() {
        //! emit event to change text to notify player win.
        notice_collisions_with("Robot2", [&](Event &e) {
            remove_agent(id());
            emit(Event("change_text",{{"text", "Player 2(red) win!"}}  ));
            emit(Event("has_winner"));
        });
    }
    void start() {}
    void update() {}
    void stop() {}

};

class end2 : public Agent {
    public:
    end2(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    end2Controller c;
};

DECLARE_INTERFACE(end2)

#endif