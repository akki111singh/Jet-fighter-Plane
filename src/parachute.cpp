#include "parachute.h"
#include "main.h"
Parachute::Parachute(float x, float y, float z,color_t color) {
  this->position = glm::vec3(x, y, z);
    float angle=0;
    float ang = 2*M_PI/100;
    int offset=0;
    GLfloat vertex_buffer_data[1800];

    int n = 100;
    for(int i=0;i<100;++i){
        offset=9*i;
        vertex_buffer_data[offset+0]=0.0;
        vertex_buffer_data[offset+2]=0.0;
        vertex_buffer_data[offset+1]=0.8;

        vertex_buffer_data[offset+3]=0.4*cos(angle);
        vertex_buffer_data[offset+5]=0.4*sin(angle);
        vertex_buffer_data[offset+4]=0.2;

        vertex_buffer_data[offset+6]=0.4*cos(angle+ang);
        vertex_buffer_data[offset+8]=0.4*sin(angle+ang);
        vertex_buffer_data[offset+7]=0.2;

        angle+=ang;

    }
    static const float vertex_buffer_data1[]={
      0,0.2,0,
      -0.2,0.2,0,
      0,-0.4,0,

      0,0.2,0,
      0.2,0.2,0,
      0,-0.4,0,
    };

    static const float vertex_buffer_data3[] = {
          -0.13,-0.4,-0.13, // triangle 1 : begin
          -0.13,-0.4, 0.13,
          -0.13, -0.15, 0.13, // triangle 1 : end
           0.13, -0.15,-0.13, // triangle 2 : begin
          -0.13,-0.4,-0.13,
          -0.13, -0.15,-0.13, // triangle 2 : end
           0.13,-0.4, 0.13,
         -0.13,-0.4,-0.13,
          0.13,-0.4,-0.13,
          0.13, -0.15,-0.13,
          0.13,-0.4,-0.13,
          -0.13,-0.4,-0.13,
          -0.13,-0.4,-0.13,
          -0.13, -0.15, 0.13,
          -0.13, -0.15,-0.13,
          0.13,-0.4, 0.13,
          -0.13,-0.4, 0.13,
          -0.13,-0.4,-0.13,
          -0.13, -0.15, 0.13,
          -0.13,-0.4, 0.13,
          0.13,-0.4, 0.13,
          0.13, -0.15, 0.13,
          0.13,-0.4,-0.13,
          0.13, -0.15,-0.13,
          0.13,-0.4,-0.13,
          0.13, -0.15, 0.13,
          0.13,-0.4, 0.13,
          0.13, -0.15, 0.13,
          0.13, -0.15,-0.13,
          -0.13, -0.15,-0.13,
          0.13, -0.15, 0.13,
          -0.13, -0.15,-0.13,
          -0.13, -0.15, 0.13,
          0.13, -0.15, 0.13,
          -0.13, -0.15, 0.13,
          0.13,-0.4, 0.13
    };
    this->object =  create3DObject(GL_TRIANGLES,100*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES,2*3, vertex_buffer_data1, COLOR_BLACK, GL_LINE);
  //  this->object2 = create3DObject(GL_TRIANGLES,12*3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES,12*3, vertex_buffer_data3, COLOR_BLACK, GL_FILL);

}

void Parachute::draw(glm::mat4 VP) {

        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(-0.15, 1, 0));

        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object3);
        draw3DObject(this->object1);
        draw3DObject(this->object);
      //  draw3DObject(this->object2);

}

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Parachute::tick() {
}

bool Parachute::check_parachute_ring_collision(point p,sphere s) {
  float distance =     sqrt((p.x - s.x) * (p.x - s.x) +
                           (p.y - s.y) * (p.y - s.y) +
                           (p.z - s.z) * (p.z - s.z));
  return distance < 0.5;
}
