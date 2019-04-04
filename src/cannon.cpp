#include "cannon.h"
#include "main.h"


Cannon::Cannon(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.6;
    int n=100;
    int r=0.5;
    float vertex_buffer_data[1800];
    float vertex_buffer_data1[1800];

    float angle = 0;
    int offset=0;
    float ang = 2*M_PI/100;

    for(int i=0;i<100;++i){
        offset=9*i;
        vertex_buffer_data[offset+0]=0.0f;
        vertex_buffer_data[offset+2]=0.0f;
        vertex_buffer_data[offset+1]=0.5f;

        vertex_buffer_data[offset+3]=float(2*cos(angle));
        vertex_buffer_data[offset+5]=float(3*sin(angle));
        vertex_buffer_data[offset+4]=-0.1f;

        vertex_buffer_data[offset+6]=float(2*cos(angle+ang));
        vertex_buffer_data[offset+8]=float(3*sin(angle+ang));
        vertex_buffer_data[offset+7]=-0.1f ;

        angle+=ang;

    }

    for(int i=0;i<100;i++){
     offset=18*i;
     vertex_buffer_data1[offset+0]=float(0.3*cos(angle));
     vertex_buffer_data1[offset+2]=float(0.2*sin(angle));
     vertex_buffer_data1[offset+1]=0.1f;

     vertex_buffer_data1[offset+3]=float(0.3*cos(angle));
     vertex_buffer_data1[offset+5]=float(0.2*sin(angle));
     vertex_buffer_data1[offset+4]=1.5f;

     vertex_buffer_data1[offset+6]=float(0.3*cos(angle+ang));
     vertex_buffer_data1[offset+8]=float(0.2*sin(angle+ang));
     vertex_buffer_data1[offset+7]=0.1f;

     vertex_buffer_data1[offset+9]=float(0.3*cos(angle+ang));
     vertex_buffer_data1[offset+11]=float(0.2*sin(angle+ang));
     vertex_buffer_data1[offset+10]=0.1f;

     vertex_buffer_data1[offset+12]=float(0.3*cos(angle+ang));
     vertex_buffer_data1[offset+14]=float(0.2*sin(angle+ang));
     vertex_buffer_data1[offset+13]=1.5f;

     vertex_buffer_data1[18*i+15]=float(0.3*cos(angle));
     vertex_buffer_data1[18*i+17]=float(0.2*sin(angle));
     vertex_buffer_data1[18*i+16]=1.5f;

     angle+=ang;

 }



      this->object = create3DObject(GL_TRIANGLES,3*n,vertex_buffer_data,COLOR_GREEN, GL_FILL);
      this->object2 = create3DObject(GL_TRIANGLES,3*200,vertex_buffer_data1,COLOR_BLACK, GL_FILL);


}

void Cannon::draw(glm::mat4 VP) {
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));

        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
        draw3DObject(this->object2);

//    }
}

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
bool Cannon::check_cannon_bullet_collision(point p,sphere s) {
  float distance =     sqrt((p.x - s.x) * (p.x - s.x) +
                           (p.y - s.y) * (p.y - s.y) +
                           (p.z - s.z) * (p.z - s.z));
  return distance < 0.8;
}
