#include "main.h"

#ifndef Cannon_H
#define Cannon_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bool check_cannon_bullet_collision(point p,sphere s);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
};


#endif //Cannon_H
