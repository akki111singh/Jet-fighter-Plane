#include "bullet2.h"
#include "main.h"

Bullet2::Bullet2(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.15;
    this->iden=glm::mat4(1.0f);

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
        this->object1 = create3DObject(GL_TRIANGLES,4*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);

    }

void Bullet2::draw(glm::mat4 VP) {
  glm::vec3 a = glm::normalize(this->dir_vector);
  glm::vec3 b = glm::normalize(glm::cross(this->dir_vector,glm::vec3(1,1,1)));
  glm::vec3 c = glm::normalize(glm::cross(b,a));

    int i=0;
  while(i<3){
        this->iden[0][i] =  c[i];
        this->iden[1][i] =  b[i];
        this->iden[2][i] = -a[i];
      i++;
    }
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));

        Matrices.model *= (translate * rotate)*this->iden;
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
        draw3DObject(this->object1);

}

void Bullet2::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bullet2::tick() {
  this->position.x+=this->iden[2][0]*this->speed;
  this->position.y+=this->iden[2][1]*this->speed;
  this->position.z+=this->iden[2][2]*this->speed;

}
