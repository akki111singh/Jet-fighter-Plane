#include "rock.h"
#include "main.h"

color_t color_brown={46,1,1};
color_t color_brown2={102,51,0};

Rock::Rock(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    float vertex_buffer_data[1800];
    float vertex_buffer_data2[1800];
    float vertex_buffer_data3[1800];
    float vertex_buffer_data4[1800];

    float angle = 0;
    int offset=0;
    float ang = 2*M_PI/100;

    for(int i=0;i<100;++i){
        offset=9*i;
        vertex_buffer_data[offset+0]=0.0;
        vertex_buffer_data[offset+2]=0.0;
        vertex_buffer_data[offset+1]=0.7  ;

        vertex_buffer_data[offset+3]=0.5*cos(angle);
        vertex_buffer_data[offset+5]=0.5*sin(angle);
        vertex_buffer_data[offset+4]=-0.1;

        vertex_buffer_data[offset+6]=0.5*cos(angle+ang);
        vertex_buffer_data[offset+8]=0.5*sin(angle+ang);
        vertex_buffer_data[offset+7]=-0.1;

        angle+=ang;

    }

        for(int i=0;i<100;++i){
            offset=9*i;
            vertex_buffer_data2[offset+0]=0.0;
            vertex_buffer_data2[offset+2]=0.0;
            vertex_buffer_data2[offset+1]=0.7;

            vertex_buffer_data2[offset+3]=0.5*cos(angle);
            vertex_buffer_data2[offset+5]=0.5*sin(angle);
            vertex_buffer_data2[offset+4]=-0.1;

            vertex_buffer_data2[offset+6]=0.5*cos(angle+ang);
            vertex_buffer_data2[offset+8]=0.5*sin(angle+ang);
            vertex_buffer_data2[offset+7]=-0.1;

            angle+=ang;

        }

        for(int i=0;i<100;++i){
            offset=9*i;
            vertex_buffer_data3[offset+0]=0.0f;
            vertex_buffer_data3[offset+2]=0.0f;
            vertex_buffer_data3[offset+1]=0.5f;

            vertex_buffer_data3[offset+3]=float(0.5*cos(angle));
            vertex_buffer_data3[offset+5]=float(0.8*sin(angle));
            vertex_buffer_data3[offset+4]=-0.1f;

            vertex_buffer_data3[offset+6]=float(0.5*cos(angle+ang));
            vertex_buffer_data3[offset+8]=float(0.8*sin(angle+ang));
            vertex_buffer_data3[offset+7]=-0.1f ;

            angle+=ang;

        }

        for(int i=0;i<100;++i){
            offset=9*i;
            vertex_buffer_data4[offset+0]=0.0f;
            vertex_buffer_data4[offset+2]=0.0f;
            vertex_buffer_data4[offset+1]=0.1f;

            vertex_buffer_data4[offset+3]=float(0.7*cos(angle));
            vertex_buffer_data4[offset+5]=float(1*sin(angle));
            vertex_buffer_data4[offset+4]=-0.1f;

            vertex_buffer_data4[offset+6]=float(0.7*cos(angle+ang));
            vertex_buffer_data4[offset+8]=float(1*sin(angle+ang));
            vertex_buffer_data4[offset+7]=-0.1f ;

            angle+=ang;

        }


    this->object = create3DObject(GL_TRIANGLES,100*3, vertex_buffer_data, COLOR_volcano, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES,100*3, vertex_buffer_data2, COLOR_fire, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES,100*3, vertex_buffer_data3, color_brown, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES,100*3, vertex_buffer_data4, COLOR_GREEN, GL_FILL);

}

void Rock::draw(glm::mat4 VP) {
//    for (this->rotation = 0; this->rotation<180; this->rotation+=2){
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object3);
        draw3DObject(this->object);
        draw3DObject(this->object2);
        draw3DObject(this->object4);

//    }
}

void Rock::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Rock::tick() {
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
bool Rock::no_flying_zone(point p,sphere s) {
  float distance =     sqrt((p.x - s.x) * (p.x - s.x) +
                           (p.y - s.y) * (p.y - s.y) +
                           (p.z - s.z) * (p.z - s.z));
  return distance < 2;
}
