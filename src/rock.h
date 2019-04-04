#include "main.h"

#ifndef ROCK_H
#define ROCK_H


class Rock {
public:
    Rock() {}
    Rock(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bool no_flying_zone(point p,sphere s);
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;

};


#endif //ROCK_H
