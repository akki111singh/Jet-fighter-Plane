#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;


    static const GLfloat vertex_buffer_data[] = {

      -0.1, 0,-0.1,
      -0.1, 0,0.1,
       0, -0.1, 0,

      -0.1, 0,0.1,
       0.1, 0,0.1,
       0, -0.1, 0,

       0.1, 0,0.1,
       0.1, 0,-0.1,
       0, -0.1, 0,

       0.1, 0,-0.1,
      -0.1, 0,-0.1,
       0, -0.1, 0,
      };


     static const GLfloat vertex_buffer_data1[] = {

       -0.1, 0,-0.1,
       -0.1, 0,0.1,
       0, 0.1, 0,

        -0.1, 0,0.1,
        0.1, 0,0.1,
        0, 0.1, 0,

        0.1, 0,0.1,
        0.1, 0,-0.1,
        0, 0.1, 0,

        0.1, 0,-0.1,
        -0.1, 0,-0.1,
        0, 0.1, 0,
       };

    this->object = create3DObject(GL_TRIANGLES,4*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES,4*3, vertex_buffer_data1, COLOR_RED, GL_FILL);

}

void Bomb::draw(glm::mat4 VP) {

        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180), glm::vec3(0, 1, 0));

        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
        draw3DObject(this->object1);

}

void Bomb::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick() {
  this->position.y-=0.05;
}
bool Bomb::bomb_hit(point p,sphere s) {
  float distance = sqrt((p.x - s.x) * (p.x - s.x) +
                           (p.y - s.y) * (p.y - s.y) +
                           (p.z - s.z) * (p.z - s.z));
  return distance < 1;
}
