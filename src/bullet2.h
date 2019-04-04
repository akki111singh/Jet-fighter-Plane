#include "main.h"

#ifndef Bullet2_H
#define Bullet2_H
#define GLM_ENABLE_EXPERIMENTAL

class Bullet2 {
public:
    Bullet2() {}
    Bullet2(float x, float y, float z);
    glm::vec3 position;
    glm::vec3 dir_vector;
    glm::mat4 iden;
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

#endif // Bullet2_H
