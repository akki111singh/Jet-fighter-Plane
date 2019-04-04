#include "main.h"

#ifndef Parachute_H
#define Parachute_H
#define GLM_ENABLE_EXPERIMENTAL

class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z,color_t color);
    bool check_parachute_ring_collision(point p,sphere s);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;

private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // Parachute_H
