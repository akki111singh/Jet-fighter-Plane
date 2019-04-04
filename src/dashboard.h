#include "main.h"
#include "ball.h"
#ifndef Dashboard_H
#define Dashboard_H
#define GLM_ENABLE_EXPERIMENTAL

class Dashboard {
public:
    Dashboard() {}
    Dashboard(float x, float y, float z, float angle,float speed,float fuel,color_t color_fuel,color_t color_speed,color_t color_alt);
    glm::vec3 position;
    float rotation;
    int num;
    void draw(glm::mat4 VP);
    void draw2(glm::mat4 VP,float fuel);
    void set_position(float x, float y,float z);
    void tick();
    void altitute_control();
    double speed;
    float compass_rot=0;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
    VAO *object9;
    VAO *object10;

};

#endif // Dashboard_H
