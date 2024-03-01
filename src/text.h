#ifndef __TEXT_AGENT__H
#define __TEXT_AGENT__H 

#include "enviro.h"

using namespace enviro;

class textController : public Process, public AgentInterface {

    public:
    textController() : Process(), AgentInterface() {}

    void init() {
        // watch event for change text
        watch("change_text", [this](Event e) {
            if (!hasWinner) {
                label(e.value()["text"], 15, 15);
            }
        });
        // when already has winner, lock text
        watch("has_winner", [this](Event e) {
            hasWinner = true;
        });
        watch("reset_position", [this](Event e) {
            hasWinner = false;
        });
    }
    void start() {}
    void update() {}
    void stop() {}
    private:
    bool hasWinner;
};

class text : public Agent {
    public:
    text(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    textController c;
};

DECLARE_INTERFACE(text)

#endif