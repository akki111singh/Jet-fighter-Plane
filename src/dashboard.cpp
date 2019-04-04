#include "dashboard.h"
#include "main.h"
#include "ball.h"

Dashboard::Dashboard(float x, float y, float z,float angle,float speed,float fuel,color_t color_fuel,color_t color_speed,color_t color_alt) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->num=2;
    float a = -0.25;
    float b = 0;

      float theta;
      float r=1;
      int n=100;
      float delta = (2 * (3.141592)) / n;
      theta = delta;
      GLfloat g_vertex_buffer_data[9 * n];
      g_vertex_buffer_data[0] = g_vertex_buffer_data[1] = g_vertex_buffer_data[2] = 0.0f;
      for(int i = 0; i < 9 * n; i++)
      {
          if(i % 9 == 0 || i % 9 == 1 || i % 9 == 2 || i % 9 == 5 || i % 9 == 8)
              g_vertex_buffer_data[i] = 0.0f;
          else if(i % 9 == 3)
              g_vertex_buffer_data[i] = r * cos(theta - delta);
          else if(i % 9 == 4)
              g_vertex_buffer_data[i] = r * sin(theta - delta);
          else if(i % 9 == 6)
              g_vertex_buffer_data[i] = r * cos(theta);
          else
              g_vertex_buffer_data[i] = r * sin(theta), theta += delta;
      }

      this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, COLOR_BLACK, GL_FILL);

      GLfloat vertex_buffer_data2[]={
          -0.3,0.5,0,
          -0.3 ,-0.1,0,
          0.2,-0.1,0,

          -0.3,0.5,0,
          0.2,0.5,0,
          0.2,-0.1,0,

        };
        GLfloat vertex_buffer_data4[]={

            0.3,0.4,0,
            0.3 ,-0.2,0,
            0.7,-0.2,0,

            0.3,0.4,0,
            0.7,0.4,0,
            0.7,-0.2,0,


          };
          GLfloat vertex_buffer_data5[]={

              -0.8,0.4,0,
              -0.8 ,-0.2,0,
              -0.4,-0.2,0,

              -0.8,0.4,0,
              -0.4,0.4,0,
              -0.4,-0.2,0,
            };

            float g_vertex_buffer_data2[9 * n];
            float ang=0;
            float rot_ang= 2 * M_PI / 100;
            for(int i=0;i<100;i++){
              int offset=i*9;
              g_vertex_buffer_data2[offset] = float(0.0f * cos(ang));
              g_vertex_buffer_data2[offset + 2]  = 0.0f;
              g_vertex_buffer_data2[offset + 1]  = float(-0.6f+0.0f * sin(ang));
              g_vertex_buffer_data2[offset + 3]  = float(0.4f * cos(ang));
              g_vertex_buffer_data2[offset + 5]  = 0.0f;
              g_vertex_buffer_data2[offset + 4]  = float(-0.6f+0.4f * sin(ang));
              g_vertex_buffer_data2[offset + 6]  = float(0.4f * cos(ang + rot_ang));
              g_vertex_buffer_data2[offset + 8]  = 0.0f;
              g_vertex_buffer_data2[offset + 7]  = float(-0.6f+0.4f * sin(ang + rot_ang));

              ang += rot_ang;

      };




    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, color_speed, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, color_alt, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, color_fuel, GL_FILL);
    this->object8 = create3DObject(GL_TRIANGLES, 100*3, g_vertex_buffer_data2, color_fuel, GL_FILL);

    GLfloat speed_bar[]={
           float(a*cos(-speed*3)-b*sin(-speed*3)),float(a*sin(-speed*3)+b*cos(-speed*3)),0,
           -0.1,-0.1,0,
           -0.05,-0.1,0,
      };
    GLfloat altitude_bar[]={
        float(a*cos(-angle/10)+0.6-b*sin(-angle/10)),float(a*sin(-angle/10)+b*cos(-angle/10)),0,
        -0.1+0.6,-0.1,0,
        -0.05+0.6,-0.1,0,
        };

    GLfloat fuel_bar[]={
            float(a*cos(fuel/10)-0.5-b*sin(fuel/10)),float(a*sin(fuel/10)+b*cos(fuel/10)),0,
               -0.1-0.5,-0.1,0,
               -0.05-0.5,-0.1,0,
          };


      this->object3 = create3DObject(GL_TRIANGLES,1*3, speed_bar, COLOR_BLACK, GL_FILL);
      this->object6 = create3DObject(GL_TRIANGLES,1*3, altitude_bar, COLOR_BLACK, GL_FILL);
      this->object7 = create3DObject(GL_TRIANGLES,1*3, fuel_bar, COLOR_BLACK, GL_FILL);

}

void Dashboard::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);

    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object7);

}


void Dashboard::draw2(glm::mat4 VP,float fuel) {
  GLfloat compass[]={
    float(-0.05*cos(2*M_PI*fuel)),float(-0.05*sin(2*M_PI*fuel))-0.6f,0,
    float(+0.05*cos(2*M_PI*fuel)),float(+0.05*sin(2*M_PI*fuel))-0.6f,0,
    float(0.25*sin(2*M_PI*fuel)),float(-0.25*cos(2*M_PI*fuel))-0.6f,0,

    };
  GLfloat compass2[]={
      float(-0.05*cos(-2*M_PI*fuel)),float(0.05*sin(-2*M_PI*fuel))-0.6f,0,
      float(+0.05*cos(-2*M_PI*fuel)),float(-0.05*sin(-2*M_PI*fuel))-0.6f,0,
      float(0.25*sin(-2*M_PI*fuel)),float(+0.25*cos(-2*M_PI*fuel))-0.6f,0,
      };

   this->object9 = create3DObject(GL_TRIANGLES, 1*3, compass, COLOR_BLACK, GL_FILL);
   this->object10 = create3DObject(GL_TRIANGLES, 1*3, compass2, COLOR_RED, GL_FILL);

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);

    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object8);
    draw3DObject(this->object9);
    draw3DObject(this->object10);
}

void Dashboard::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, 0);
}


void Dashboard::tick(){
}
