#ifndef __COORDINATOR_AGENT__H
#define __COORDINATOR_AGENT__H 
#include <vector>
#include "enviro.h"
#include "maze.h"

using namespace enviro;
using namespace std;
using Point = pair<int, int>;


class CoordinatorController : public Process, public AgentInterface {

    public:
    CoordinatorController() : Process(), AgentInterface() {}

    void init() {
        initMaze();
        watch("button_click", [&](Event& e) {
            std::cout << e.value() << "\n";
            e.stop_propagation();
            clearAgents();
            initMaze();
        });
    }
    void start() {}
    void update() {}
    void stop() {}
private:
    vector<int> agent_ids;
    //! wrap add_agent to save id, for remove agent later.
    Agent& addAgent(const std::string name, double x, double y, double theta, const json style) {
        Agent& agent = add_agent(name, x,y, theta,style);
        agent_ids.push_back(agent.get_id());
        return agent;
    }
    //! init maze and add end point, reset position of robot and prompt text
    void initMaze() {
        clearAgents();
        generateMaze();
        emit(Event("reset_position"));
        emit(Event("change_text", {{ "text", "Wait for winner..." }}));
        addAgent("end1", 500, -250, 0, {{ "fill", "lightgreen" }});
        addAgent("end2", -450, -250, 0, {{ "fill", "red" }});
    }
    //! add walls based on the maze generated
    void generateMaze() {
        int rows = 10;
        int cols = 20;
        MazeGenerator maze(rows, cols);
        maze.generateMaze({0, 0});
        maze.print();
        //! top,left corner of maze
        double x = -450;
        double y = -250;

        for (int i= 0; i < rows;i++) {
            // uncomment next line if need exit in maze
            // if (i != rows - 1) {
                // left border
                addAgent("wall1", x - 25, y + i * 50, 0, { {"fill", "gray"}});
                // right border
                addAgent("wall1", x + 50 * cols - 25, y + i * 50, 0, { {"fill", "gray"}});
            // }
        }
        for (int i = 0; i < cols; i++) {
            // top border
            addAgent("wall2", x + i * 50, y - 25, 0, { {"fill", "gray"}});
            // bottom border
            addAgent("wall2", x + i * 50, y + 50 * rows - 25, 0, { {"fill", "gray"}});
        }

        for (int i = 0; i < rows;i++) {
            for (int j = 0; j < cols; j++) {
                int centerX = x + j * 50;
                int centerY = y + i * 50;
                // right wall
                if (!maze.isConnected(make_pair(i, j), make_pair(i, j + 1)) && j + 1 < cols) {
                    addAgent("wall1", centerX + 25, centerY, 0, { {"fill", "gray"}});
                }
                // bottom wall
                if (!maze.isConnected(make_pair(i, j), make_pair(i + 1, j)) && i + 1 < rows) {
                    addAgent("wall2", centerX, centerY + 25, 0, { {"fill", "gray"}});
                }
            }
        }
    }
    //! remove all agents for regenerate
    void clearAgents() {
        for ( int id : agent_ids ) {
            if ( agent_exists(id) ) {
                remove_agent(id);
            }
        }
    }
};

class Coordinator : public Agent {
    public:
    Coordinator(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    CoordinatorController c;
};

DECLARE_INTERFACE(Coordinator)

#endif