#include "main.h"

#ifndef Bullet_H
#define Bullet_H
#define GLM_ENABLE_EXPERIMENTAL

class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y, float z, color_t color);
    glm::vec3 position;


    glm::mat4 rot_matrix;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void move( float x);
    void Roll(int angle);
    void Pitch(int angle);
    void Yaw(int angle);
    void Move_forward(float x,float y,float z);
    float roll;
    float pitch;
    float yaw;
    double speed;
    float fuel=100;

private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;


};

#endif // Bullet_H
