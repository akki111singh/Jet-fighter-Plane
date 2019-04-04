#include "main.h"

#ifndef Water_H
#define Water_H


class Water {
public:
    Water() {};
    Water(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP), set_position(float x, float y) , tick();
    // void set_position(float x, float y);
    // void tick();
    double speed;
    float rotation;
private:
    VAO *object;
    VAO *object2;

};

#endif // Water_H
