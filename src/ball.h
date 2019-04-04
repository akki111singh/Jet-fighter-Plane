#include "main.h"

#ifndef BALL_H
#define BALL_H
#define GLM_ENABLE_EXPERIMENTAL

class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::mat4 rot_matrix;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    void Roll(int angle);
    void Pitch(int angle);
    void Yaw(int angle);
    void Move_forward(float x,float y,float z);
    bool plane_hit(point p,sphere s);
    float roll;
    float health=100;
    int score=0;
    int total_checkpoints=10;
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

#endif // BALL_H
