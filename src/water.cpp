#include "water.h"
#include "main.h"
Water::Water(float x, float y, color_t color) {
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
            -10000, -3.0f, -10000,
            -10000, -3.0f, 10000,
             10000, -3.0f, 10000,
             10000, -3.0f, 10000,
            -10000, -3.0f, -10000,
             10000, -3.0f, -10000,

    };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_skyblue, GL_FILL);
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    GLfloat vertex_buffer_data1[90009];
    int i=-500;
    int offset_i;
    int offset_j;
    while(i<=500) {
      for (int j = -500; j <= 500 ; j+=16) {
          offset_i=((i+500)/16)*450 ;
          offset_j=((j+500)/16)*9;
          vertex_buffer_data1[offset_i + offset_j + 0] = i;
          vertex_buffer_data1[offset_i + offset_j + 1] = -2.5;
          vertex_buffer_data1[offset_i + offset_j + 2] = j;

          vertex_buffer_data1[offset_i + offset_j + 3] = i;
          vertex_buffer_data1[offset_i + offset_j + 4] = -2.5;
          vertex_buffer_data1[offset_i + offset_j + 5] = j+16;

          vertex_buffer_data1[offset_i + offset_j + 6] = i+16;
          vertex_buffer_data1[offset_i + offset_j + 7] = -2.5;
          vertex_buffer_data1[offset_i + offset_j + 8] = j;
      }
      i=i+16;
  }
  this->object2 = create3DObject(GL_TRIANGLES, 2500 * 3, vertex_buffer_data1, COLOR_deepskyblue, GL_FILL);
}


void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model = rotate * Matrices.model * translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
   draw3DObject(this->object);
   draw3DObject(this->object2);

}

void Water::tick() {}

void Water::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
