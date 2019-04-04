#include "checkpoint.h"
#include "main.h"

Checkpoint::Checkpoint(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    float rot = 2*3.141/100;
    float angle = 0;
    int i=0;
    GLfloat vertex_buffer_data[200*9];

    while(i<18*100){

            if(i%18==2 || i%18==5 || i%18==8 || i%18==11 || i%18==14 || i%18==17)
            vertex_buffer_data[i] = 0;

            else if(i%18==15 || i%18==0)
            vertex_buffer_data[i] = 2*cos(angle);


            else if(i%18==3)
              vertex_buffer_data[i] = 2.2*cos(angle);

            else if(i%18==4)
              vertex_buffer_data[i] = 2.2*sin(angle);


            else if(i%18==16 || i%18 ==1)
              vertex_buffer_data[i] = 2*sin(angle);


          else if(i%18==6 || i%18==9 || i%18==12 )
              vertex_buffer_data[i] = 2.2*cos(angle+rot);


          else if(i%18==12 )
              vertex_buffer_data[i] = 2*cos(angle+rot);


            else if(i%18==7 || i%18==10 || i%18==13)
              vertex_buffer_data[i] = 2.2*sin(angle+rot);

              else if(i%18==13)
                vertex_buffer_data[i] = 2*sin(angle+rot);


            angle+=rot;
            i++;
        }


    this->object = create3DObject(GL_TRIANGLES,3*100, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Checkpoint::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Checkpoint::tick() {

}
bool Checkpoint::check_plane_ring_collision(point p,sphere s) {
  float distance = sqrt((p.x - s.x) * (p.x - s.x) +
                           (p.y - s.y) * (p.y - s.y) +
                           (p.z - s.z) * (p.z - s.z));
  return distance < 2;
}
