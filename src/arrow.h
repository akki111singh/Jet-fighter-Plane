#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
    glm::vec3 position;
    glm::vec3 direction_vector;
    float rotation;
    glm::mat4 iden;
    void draw(glm::mat4 VP, glm::vec3 pos);
    void set_position(float x, float y, float z);
    void tick(glm::vec3);
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // BALL_H
