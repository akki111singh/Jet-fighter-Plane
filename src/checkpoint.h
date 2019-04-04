#include "main.h"

#ifndef Checkpoint_H
#define Checkpoint_H


class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool check_plane_ring_collision(point p, sphere s);
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // BALL_H
