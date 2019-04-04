#include "fuel.h"
#include "main.h"

Fuel::Fuel(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->gravity = -0.002f;
    speed = 0.0f;

    static const GLfloat vertex_buffer_data[] = {
            -0.5, 0.9, -0.13,
            -0.5, 0.9, 0.13,
            -0.5, 1.2, 0.13,
             0.5, 1.2, -0.13,
            -0.5, 0.9, -0.13,
            -0.5, 1.2, -0.13,
             0.5, 0.9, 0.13,
            -0.5, 0.9, -0.13,
             0.5, 0.9, -0.13,
             0.5, 1.2, -0.13,
             0.5, 0.9, -0.13,
            -0.5, 0.9, -0.13,
            -0.5, 0.9, -0.13,
            -0.5, 1.2, 0.13,
            -0.5, 1.2, -0.13,
             0.5, 0.9, 0.13,
            -0.5, 0.9, 0.13,
            -0.5, 0.9, -0.13,
            -0.5, 1.2, 0.13,
            -0.5, 0.9, 0.13,
             0.5, 0.9, 0.13,
             0.5, 1.2, 0.13,
             0.5, 0.9, -0.13,
             0.5, 1.2, -0.13,
             0.5, 0.9, -0.13,
             0.5, 1.2, 0.13,
             0.5, 0.9, 0.13,
             0.5, 1.2, 0.13,
             0.5, 1.2, -0.13,
            -0.5, 1.2, -0.13,
             0.5, 1.2, 0.13,
            -0.5, 1.2, -0.13,
            -0.5, 1.2, 0.13,
             0.5, 1.2, 0.13,
            -0.5, 1.2, 0.13,
             0.5, 0.9, 0.13
    };


    static const GLfloat vertex_buffer_data2[] = {
            -0.13, 0.6, -0.13,
            -0.13, 0.6, 0.13,
            -0.13,1.6, 0.13,
            0.13, 1.6, -0.13,
            -0.13, 0.6, -0.13,
            -0.13,1.6, -0.13,
            0.13, 0.6, 0.13,
            -0.13, 0.6, -0.13,
            0.13, 0.6, -0.13,
            0.13,1.6, -0.13,
            0.13, 0.6, -0.13,
            -0.13, 0.6, -0.13,
            -0.13, 0.6, -0.13,
            -0.13,1.6, 0.13,
            -0.13,1.6, -0.13,
            0.13, 0.6, 0.13,
            -0.13, 0.6, 0.13,
            -0.13, 0.6, -0.13,
            -0.13,1.6, 0.13,
            -0.13, 0.6, 0.13,
            0.13, 0.6, 0.13,
            0.13,1.6, 0.13,
            0.13, 0.6, -0.13,
            0.13,1.6, -0.13,
            0.13, 0.6, -0.13,
            0.13,1.6, 0.13,
            0.13, 0.6, 0.13,
            0.13,1.6, 0.13,
            0.13,1.6, -0.13,
            -0.13,1.6, -0.13,
            0.13,1.6, 0.13,
            -0.13,1.6, -0.13,
            -0.13,1.6, 0.13,
            0.13,1.6, 0.13,
            -0.13,1.6, 0.13,
            0.13, 0.6, 0.13
    };


    this->object = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data2, color, GL_FILL);
}

void Fuel::draw(glm::mat4 VP) {
    this->rotation += 2.5f;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}


void Fuel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Fuel::tick() {

}
bool Fuel::get_fuel(point p,sphere s) {
  float distance =     sqrt((p.x - s.x) * (p.x - s.x) +
                           (p.y - s.y) * (p.y - s.y) +
                           (p.z - s.z) * (p.z - s.z));
  return distance < 1.5;
}
