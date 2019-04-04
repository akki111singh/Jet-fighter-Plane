#include "main.h"

#ifndef Fuel_H
#define Fuel_H


class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation, gravity;
    void draw(glm::mat4 VP);
    bool get_fuel(point p,sphere s);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    int color;
private:
    VAO *object;
    VAO *object2;
};


#endif //Fuel_H
