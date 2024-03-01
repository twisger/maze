#ifndef __WALL1_AGENT__H
#define __WALL1_AGENT__H 

#include "enviro.h"

using namespace enviro;
//! vertical wall of maze
class wall1Controller : public Process, public AgentInterface {

    public:
    wall1Controller() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class wall1 : public Agent {
    public:
    wall1(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    wall1Controller c;
};

DECLARE_INTERFACE(wall1)

#endif