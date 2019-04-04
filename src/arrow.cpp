#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->iden=glm::mat4(1.0f);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
            -0.05, -0.05, -0.33f,
            -0.05, -0.05, 0.33f,
            -0.05, 0.05, 0.33f,

             0.05, 0.05, -0.33f,
            -0.05, -0.05, -0.33f,
            -0.05, 0.05, -0.33f,

             0.05, -0.05, 0.33f,
            -0.05, -0.05, -0.33f,
             0.05, -0.05, -0.33f,

             0.05, 0.05, -0.33f,
             0.05, -0.05, -0.33f,
            -0.05, -0.05, -0.33f,

            -0.05, -0.05, -0.33f,
            -0.05, 0.05, 0.33f,
            -0.05, 0.05, -0.33f,

             0.05, -0.05, 0.33f,
            -0.05, -0.05, 0.33f,
            -0.05, -0.05, -0.33f,

            -0.05, 0.05, 0.33f,
            -0.05, -0.05, 0.33f,
             0.05, -0.05, 0.33f,

             0.05, 0.05, 0.33f,
             0.05, -0.05, -0.33f,
             0.05, 0.05, -0.33f,

             0.05, -0.05, -0.33f,
             0.05, 0.05, 0.33f,
             0.05, -0.05, 0.33f,

             0.05, 0.05, 0.33f,
             0.05, 0.05, -0.33f,
            -0.05, 0.05, -0.33f,

             0.05, 0.05, 0.33f,
            -0.05, 0.05, -0.33f,
            -0.05, 0.05, 0.33f,

            0.05, 0.05, 0.33f,
            -0.05, 0.05, 0.33f,
            0.05, -0.05, 0.33f,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);


    static const float vertex_buffer_data2[] = {
            0.14, 0.14, 0.31,
            -0.14, -0.14, 0.31,
            -0.14, 0.14, 0.31,

            0.14, 0.14, 0.31,
            0.14, -0.14, 0.31,
            -0.14, -0.14, 0.31,

            -0.14, -0.14, 0.31,
            -0.14, 0.14, 0.31,
            0.0, 0.0, 0.6,

            -0.14, -0.14, 0.31,
            0.14, -0.14, 0.31,
            0.0, 0.0, 0.6,

            0.14, -0.14, 0.31,
            0.14, 0.14, 0.31,
            0.0, 0.0, 0.6,

            0.14, 0.14, 0.31,
           -0.14, 0.14, 0.31,
            0.0, 0.0, 0.6,
    };

    this->object2 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data2, COLOR_RED, GL_FILL);

}

void Arrow::draw(glm::mat4 VP, glm::vec3 pos) {

    glm::vec3 a = glm::normalize(-this->direction_vector);
    glm::vec3 b = glm::normalize(glm::cross(-this->direction_vector,glm::vec3(1,1,1)));
    glm::vec3 c = glm::normalize(glm::cross(b,a));

      int i=0;
    while(i<3){
          this->iden[0][i] =  c[i];
          this->iden[1][i] =  b[i];
          this->iden[2][i] = -a[i];
        i++;
      }

    this->position = pos;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));

    Matrices.model *= (translate)*this->iden;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);

}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick(glm::vec3 ballpos) {
    this->position = ballpos;
}
