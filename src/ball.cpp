#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.02;
    this->roll=0;
    this->pitch=0;
    this->yaw=0;
    this->rot_matrix=glm::mat4(1.0f);

    float hl = 2 * 0.5f;
    float a = 0.0f;
    int numSteps=100;
    int radius=1;
    int i=0;
    float step = 2*3.14 /numSteps;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float vertex_buffer_data[1800];
    float vertex_buffer_data1[1800];
    float vertex_buffer_data4[1800];

    float angle = 0;
     int offset=0;
     float ang = 2*M_PI/100;

     for(int i=0;i<100;i++){
         offset=9*i;
         vertex_buffer_data[offset+0]=0.0;
         vertex_buffer_data[offset+1]=0.0;
         vertex_buffer_data[offset+2]=-0.2;

         vertex_buffer_data[offset+3]=0.3*cos(angle);
         vertex_buffer_data[offset+4]=0.3*sin(angle);
         vertex_buffer_data[offset+5]=0.1;

         vertex_buffer_data[offset+6]=0.3*cos(angle+ang);
         vertex_buffer_data[offset+7]=0.3*sin(angle+ang);
         vertex_buffer_data[offset+8]=0.1;

         angle+=ang;

     }


          for(int i=0;i<100;i++){
              offset=9*i;
              vertex_buffer_data4[offset+0]=0.0;
              vertex_buffer_data4[offset+1]=0.0;
              vertex_buffer_data4[offset+2]=0.0;

              vertex_buffer_data4[offset+3]=0.31*cos(angle);
              vertex_buffer_data4[offset+4]=0.31*sin(angle);
              vertex_buffer_data4[offset+5]=1.6;

              vertex_buffer_data4[offset+6]=0.31*cos(angle+ang);
              vertex_buffer_data4[offset+7]=0.31*sin(angle+ang);
              vertex_buffer_data4[offset+8]=1.6;

              angle+=ang;


          }
     for(int i=0;i<100;i++){
      offset=18*i;
      vertex_buffer_data1[offset+0]=0.3*cos(angle);
      vertex_buffer_data1[offset+1]=0.3*sin(angle);
      vertex_buffer_data1[offset+2]=0.1;

      vertex_buffer_data1[offset+3]=0.3*cos(angle);
      vertex_buffer_data1[offset+4]=0.3*sin(angle);
      vertex_buffer_data1[offset+5]=1.5;

      vertex_buffer_data1[offset+6]=0.3*cos(angle+ang);
      vertex_buffer_data1[offset+7]=0.3*sin(angle+ang);
      vertex_buffer_data1[offset+8]=0.1;

      vertex_buffer_data1[offset+9]=0.3*cos(angle+ang);
      vertex_buffer_data1[offset+10]=0.3*sin(angle+ang);
      vertex_buffer_data1[offset+11]=0.1;

      vertex_buffer_data1[offset+12]=0.3*cos(angle+ang);
      vertex_buffer_data1[offset+13]=0.3*sin(angle+ang);
      vertex_buffer_data1[offset+14]=1.5;

      vertex_buffer_data1[18*i+15]=0.3*cos(angle);
      vertex_buffer_data1[18*i+16]=0.3*sin(angle);
      vertex_buffer_data1[18*i+17]=1.5;

      angle+=ang;

  }
  GLfloat vertex_buffer_data2[]={
        0.28, 0.15, 0.4,
        0.28, 0.15, 0.8,
        2, 0.15, 1,

        -0.28, 0.15, 0.4,
        -0.28, 0.15, 0.8,
        -2, 0.15, 1,

        0.1, 0.15, 1.2,
        0.1, 0.15, 1.6,
        1, 0.15, 1.8,

        -0.1, 0.15, 1.2,
        -0.1, 0.15, 1.6,
        -1, 0.15, 1.8,



    };

    this->object = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data1, COLOR_light_red, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_YELLOW , GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data4, COLOR_YELLOW , GL_FILL);


}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);     // glTranslatef

    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->rot_matrix);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);


}

void Ball::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::Roll(int angle) {
  glm::mat4 rotate=glm::rotate((angle/ 180.0f),glm::vec3(this->rot_matrix[2][0],this->rot_matrix[2][1],this->rot_matrix[2][2]));
  this->rot_matrix=rotate*this->rot_matrix;
}
void Ball::Pitch(int angle) {
  glm::mat4 rotate=glm::rotate((angle/ 180.0f),glm::vec3(this->rot_matrix[0][0],this->rot_matrix[0][1],this->rot_matrix[0][2]));
  this->rot_matrix=rotate*this->rot_matrix;
}
void Ball::Yaw(int angle) {
  glm::mat4 rotate=glm::rotate((angle/ 180.0f),glm::vec3(this->rot_matrix[1][0],this->rot_matrix[1][1],this->rot_matrix[1][2]));
  this->rot_matrix=rotate*this->rot_matrix;
}



void Ball::tick() {
     this->position.x += -this->rot_matrix[2][0]*this->speed;
     this->position.y += -this->rot_matrix[2][1]*this->speed;
     this->position.z += -this->rot_matrix[2][2]*this->speed;

}

bool Ball::plane_hit(point p,sphere s) {
  float distance = sqrt((p.x - s.x) * (p.x - s.x) +
                           (p.y - s.y) * (p.y - s.y) +
                           (p.z - s.z) * (p.z - s.z));
  return distance < 0.7;
}
