#include "main.h"

#ifndef Bomb_H
#define Bomb_H
#define GLM_ENABLE_EXPERIMENTAL

class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z);
    glm::vec3 position;
    glm::vec3 dir_vector;
    glm::mat4 iden;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    bool bomb_hit(point p,sphere s);
    void tick();
    double speed;

private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;


};

#endif // Bomb_H
