// Reference: https://github.com/klavinslab/enviro/blob/master/examples/multiuser/src/guy.h

#ifndef __ROBOT2_AGENT__H
#define __ROBOT2_AGENT__H 

#include "enviro.h"

using namespace enviro;

class robotController2 : public Process, public AgentInterface {

    public:
    robotController2() : Process(), AgentInterface(), v(0), omega(0) {}

    void init() {
        //! reset robot position
        watch("reset_position", [this](Event e) {
            teleport(500, 200, -3.14 / 2);
        });
        //! watch events to support robot move
        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "ArrowUp" ) {
                  v = v_m;              
            } else if ( k == "ArrowDown" ) {
                  v = -v_m;  
            } else if ( k == "ArrowLeft" ) {
                  omega = -omega_m;
            } else if ( k == "ArrowRight" ) {
                  omega = omega_m;
            }
        });        
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "ArrowUp" || k == "ArrowDown" ) {
                  v = 0;               
            } else if ( k == "ArrowLeft" ) {
                  omega = 0;
            } else if ( k == "ArrowRight" ) {
                  omega = 0;
            } 
        });
    }
    void start() {}
    void update() {
        track_velocity(v,omega,10,400);
    }
    void stop() {}
    double v, omega;
    double const v_m = 30, omega_m = 1;
};

class robot : public Agent {
    public:
    robot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    robotController2 c;
};

DECLARE_INTERFACE(robot)

#endif