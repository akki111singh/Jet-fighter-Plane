  #include "main.h"
  #include "timer.h"
  #include "ball.h"
  #include "water.h"
  #include "dashboard.h"
  #include "checkpoint.h"
  #include "bullet.h"
  #include "rock.h"
  #include "cannon.h"
  #include "arrow.h"
  #include "bullet2.h"
  #include "time.h"
  #include "parachute.h"
  #include "bomb.h"
  #include "fuel.h"
  using namespace std;

  GLMatrices Matrices;
  GLMatrices Matrices2;

  GLuint     programID;
  GLFWwindow *window;


  bool shoot =false;
  bool check=false;
  Ball ball1;
  Water water;
  vector <Rock> rock;
  Arrow arrow;
  vector <Cannon> cannon;
  vector <Bullet2> bullet2;
  vector <Checkpoint> checkpt;
  vector <Parachute> parachute;
  vector <Bomb> bomb;
  vector <Fuel> fuel,health;
  Dashboard dashboard;
  sphere R1;
  sphere P1,C1,V1,B2,F1;
  point Plane,B1,b;
  glm:: vec3 compass;
  bool roll;
  int count=0;

  time_t seconds;
  time_t seconds2;
  time_t seconds4;
  time_t seconds5;

time_t seconds3=time(NULL);
  vector <Bullet> bullet;
  color_t color_fuel=COLOR_GREEN;
  color_t color_speed=COLOR_GREEN;
  color_t color_alt=COLOR_GREEN;
  int view=1;
  int flag=0;
  float camera_x,camera_y,camera_z;
  float target_x,target_y,target_z;
  float up_x,up_y,up_z;

  float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
  float camera_rotation_angle = 0;

  Timer t60(1.0 / 60);



  /* Render the scene with openGL */
  /* Edit this function according to your assignment */
  void draw() {
      // clear the color and depth in the frame buffer
      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // use the loaded shader program
      // Don't change unless you know what you are doing
      glUseProgram (programID);

      // Eye - Location of camera. Don't change unless you are sure!!
//TOP VIEW

        if(view==1)
        {
          camera_x=ball1.position.x;
          camera_y=ball1.position.y;
          camera_z=ball1.position.z-0.5;

          target_x=ball1.position.x-10*ball1.rot_matrix[2][0];
          target_y=ball1.position.y-10*ball1.rot_matrix[2][1];
          target_z=ball1.position.z-10*ball1.rot_matrix[2][2];

          up_x=ball1.rot_matrix[1][0];
          up_y=ball1.rot_matrix[1][1];
          up_z=ball1.rot_matrix[1][2];
        }
        if(view==2)
        {
          camera_x=ball1.position.x;
          camera_y=50;
          camera_z=ball1.position.z;

          target_x=ball1.position.x;
          target_y=ball1.position.y;
          target_z=ball1.position.z;

          up_x=-ball1.rot_matrix[2][0];
          up_y=-ball1.rot_matrix[2][1];
          up_z=-ball1.rot_matrix[2][2];
        }
        if(view==3)
        {
          camera_x=10;
          camera_y=10;
          camera_z=0;

          target_x=ball1.position.x;
          target_y=ball1.position.y;
          target_z=ball1.position.z;

          up_x=0;
          up_y=1;
          up_z=0;
        }
        if(view==4)
        {
          camera_x=ball1.position.x+10*ball1.rot_matrix[2][0]+2*ball1.rot_matrix[1][0];
          camera_y=ball1.position.y+10*ball1.rot_matrix[2][1]+2*ball1.rot_matrix[1][1];
          camera_z=ball1.position.z+10*ball1.rot_matrix[2][2]+2*ball1.rot_matrix[1][2];

          target_x=ball1.position.x-ball1.rot_matrix[2][0];
          target_y=ball1.position.y-ball1.rot_matrix[2][1];
          target_z=ball1.position.z-ball1.rot_matrix[2][2];

          up_x=ball1.rot_matrix[1][0];
          up_y=ball1.rot_matrix[1][1];
          up_z=ball1.rot_matrix[1][2];
        }

        glm::vec3 eye (camera_x,camera_y,camera_z);
        glm::vec3 target (target_x,target_y,target_z);
        glm::vec3 up (up_x,up_y,up_z);


      // Compute Camera matrix (view)
      Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
      glm::mat4 VP = Matrices.projection * Matrices.view;

      glm::vec3 eye1 ( 0,0,0.4 );
      glm::vec3 target1 (0, 0, 0);
      glm::vec3 up1 (0, 1, 0);

      Matrices2.view = glm::lookAt( eye1, target1, up1);
      glm::mat4 VP1 = Matrices2.projection * Matrices2.view;


      glm::mat4 MVP;  // MVP = Projection * View * Model

      // Scene render
      water.draw(VP);
      ball1.draw(VP);

      for(int i=0;i<rock.size();i++)
      rock[i].draw(VP);

      for(int i=0;i<checkpt.size();i++)
        checkpt[i].draw(VP);

        if(!bullet.empty())
        for(int i=0;i<bullet.size();i++)
          bullet[i].draw(VP);

      if(!cannon.empty())
      cannon[0].draw(VP);

      if(!bomb.empty())
      bomb[0].draw(VP);

      dashboard.draw(VP1);

      if(ball1.rot_matrix[2][0]>0)
      dashboard.draw2(VP1,ball1.rot_matrix[2][2]);
      else
      dashboard.draw2(VP1,-ball1.rot_matrix[2][2]);



      glm::vec3 arrow_pos = ball1.position;
      arrow_pos.y+=1;

      arrow.draw(VP, arrow_pos);

      if(!bullet2.empty()){
      for(int i=0;i<bullet2.size();i++)
        bullet2[i].draw(VP);
      }

      for(int i=0;i<parachute.size();i++)
        parachute[i].draw(VP);

      for(int i=0;i<fuel.size();i++)
        fuel[i].draw(VP);

        if(!health.empty()){
        for(int i=0;i<health.size();i++)
          health[i].draw(VP);
        }
  }

  void tick_input(GLFWwindow *window) {
      int a  = glfwGetKey(window, GLFW_KEY_A);
      int d = glfwGetKey(window, GLFW_KEY_D);
      int q  = glfwGetKey(window, GLFW_KEY_Q);
      int e = glfwGetKey(window, GLFW_KEY_E);
      int w  = glfwGetKey(window, GLFW_KEY_W);
      int s = glfwGetKey(window, GLFW_KEY_S);
      int speedup = glfwGetKey(window, GLFW_KEY_UP);
      int speeddown = glfwGetKey(window, GLFW_KEY_DOWN);
      int stunt = glfwGetKey(window, GLFW_KEY_SPACE);

      int bult = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
      int bmb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

      int camera1 = glfwGetKey(window, GLFW_KEY_1);
      int camera2 = glfwGetKey(window, GLFW_KEY_2);
      int camera3 = glfwGetKey(window, GLFW_KEY_3);
      int camera4 = glfwGetKey(window, GLFW_KEY_4);
      int camera5 = glfwGetKey(window, GLFW_KEY_5);
      int bult2 = glfwGetKey(window, GLFW_KEY_6);


      if (q) {
        ball1.Roll(1);
      }
      if(e){
        ball1.Roll(-1);
      }
      if (a) {
        ball1.Yaw(1);
        check=false;
      }
      if(d){
        ball1.Yaw(-1);
        check=true;
      }
      if (w) {
        ball1.Pitch(1);
      }
      if(s){
        ball1.Pitch(-1);
      }

      if(speedup){
        if(ball1.speed < 0.95)
        ball1.speed+=0.003;

      ball1.fuel+=0.01;
      }

      if(speeddown){
        if(ball1.speed > 0.02)
        ball1.speed-=0.003;
      }
      if(camera1) view=1;
      if(camera2) view=2;
      if(camera3) view=3;
      if(camera4) view=4;
      if(camera5) view=0;

      if(bult){
        seconds4=time(NULL);
        seconds5=seconds4-seconds3;

        if(seconds5 > 0.2){
        seconds3=time(NULL);
        bullet.push_back(Bullet(ball1.position.x,ball1.position.y,ball1.position.z,COLOR_RED));
        bullet[bullet.size()-1].rot_matrix = ball1.rot_matrix;

      }
    }
      if(bmb)
      {
        if(bomb.empty()){
          bomb.push_back(Bomb(ball1.position.x,ball1.position.y-0.5,ball1.position.z));
        }
      }
      if(stunt){
        roll=true;
      }



}
  void tick_elements() {

      if(roll==true){
        ball1.Roll(2.0f);
        count++;
      }
      if(count==550){
        roll=false;
        count=0;
      }

      Plane.x=ball1.position.x;
      Plane.y=ball1.position.y;
      Plane.z=ball1.position.z;

      if(!bullet2.empty()){
        B2.x=bullet2[0].position.x;
        B2.y=bullet2[0].position.y;
        B2.z=bullet2[0].position.z;
      }

      if(!bullet2.empty())
      if(ball1.plane_hit(Plane,B2)){
        ball1.health-=2.5;
      }


      if(!bomb.empty() and bomb[0].position.y < -3){
        bomb.erase(bomb.begin());
      }
      if(!bomb.empty())
      bomb[0].tick();

    //  cout<<bomb.size()<<endl;


      for(int i=0;i<checkpt.size();i++){
        R1.x=checkpt[i].position.x;
        R1.y=checkpt[i].position.y;
        R1.z=checkpt[i].position.z;

        if(checkpt[i].check_plane_ring_collision(Plane,R1)){
          ball1.score+=100;
          checkpt.erase(checkpt.begin()+i);
          float x=rand()%100-rand()%30;
          float y=rand()%2;
          float z=rand()%100-rand()%30;
          checkpt.push_back(Checkpoint(x,y,z));
        }
      }


      C1.x=cannon[0].position.x;
      C1.y=cannon[0].position.y+1;
      C1.z=cannon[0].position.z;


      if(!bomb.empty()){
        b.x=bomb[0].position.x;
        b.y=bomb[0].position.y;
        b.z=bomb[0].position.z;
      }

      if(!bomb.empty() and bomb[0].bomb_hit(b,C1)){
        float x=rand()%100-rand()%30;
        float y=-3.0f;
        float z=rand()%100-rand()%30;
        cannon.push_back(Cannon(x,y,z));
        cannon.erase(cannon.begin());
        bullet2.erase(bullet2.begin());
      }

      for(int i=0;i<rock.size();i++){

        V1.x=rock[i].position.x;
        V1.y=rock[i].position.y+2;
        V1.z=rock[i].position.z;

        if(rock[i].no_flying_zone(Plane,V1)){
          ball1.health-=0.2;
        }
      }


      for(int i=0;i<fuel.size();i++){
        F1.x=fuel[i].position.x;
        F1.y=fuel[i].position.y;
        F1.z=fuel[i].position.z;

        if(fuel[i].get_fuel(Plane,F1)){
            ball1.fuel-=5;
            fuel.erase(fuel.begin()+i);

            float x=rand()%50-rand()%50;
            float y=rand()%5-rand()%2;
            float z=rand()%100-rand()%30;
            fuel.push_back(Fuel(x,y,z,COLOR_YELLOW));

        }

      }

      if(!health.empty()){
      for(int i=0;i<fuel.size();i++){
        F1.x=health[i].position.x;
        F1.y=health[i].position.y;
        F1.z=health[i].position.z;

        if(health[i].get_fuel(Plane,F1)){
            ball1.health+=5;
            health.erase(health.begin()+i);
        }

      }
    }




      if(!bullet.empty()){
        for(int i=0;i<bullet.size();i++){
        B1.x=bullet[i].position.x;
        B1.y=bullet[i].position.y;
        B1.z=bullet[i].position.z;


  //  cout<<B1.x<<" "<<B1.y<<" "<<B1.z<<endl;
      for(int i=0;i<parachute.size();i++){
          P1.x=parachute[i].position.x;
          P1.y=parachute[i].position.y;
          P1.z=parachute[i].position.z;


          if(parachute[i].check_parachute_ring_collision(B1,P1)){
              float l = parachute[i].position.x;
              float m = parachute[i].position.y;
              float n = parachute[i].position.z;

              ball1.score+=20;
              parachute.erase(parachute.begin()+i);

              health.push_back(Fuel(l,m,n,COLOR_GREEN));
              float x=rand()%20-rand()%20;
              float y=10.0f;
              float z=ball1.position.z-rand()%20;
              int c = rand()%5;
              if(c==1)parachute.push_back(Parachute(x,y,z,COLOR_parachute));
              if(c==2)parachute.push_back(Parachute(x,y,z,COLOR_parachute1));
              if(c==3)parachute.push_back(Parachute(x,y,z,COLOR_parachute2));
              if(c==4)parachute.push_back(Parachute(x,y,z,COLOR_parachute3));
              if(c==4)parachute.push_back(Parachute(x,y,z,COLOR_parachute4));
            }

        }

        if(cannon[0].check_cannon_bullet_collision(B1,C1)){
          ball1.total_checkpoints--;
          float x=rand()%100-rand()%30;
          float y=-3.0f;
          float z=rand()%100-rand()%30;
          cannon.push_back(Cannon(x,y,z));
          cannon.erase(cannon.begin());
          bullet2.erase(bullet2.begin());
      }
      }
    }


      ball1.tick();

      if(bullet2.empty()){
      seconds=time(NULL);
      bullet2.push_back(Bullet2(cannon[0].position.x,cannon[0].position.y+0.8 ,cannon[0].position.z));
    }
      seconds2=time(NULL);

      if(seconds2-seconds >=8){
        bullet2.erase(bullet2.begin());
      }

      if(!bullet2.empty())
      for(int i=0;i<bullet2.size();i++)
          bullet2[i].tick();

      for(int i=0;i<parachute.size();i++)
        parachute[i].tick();

      for(int i=0;i<parachute.size();i++){
        if(parachute[i].position.y < -3){
          float x=rand()%20-rand()%20;
          float y=10.0f;
          float z=ball1.position.z-rand()%20;
          int c = rand()%5;
          if(c==1)parachute.push_back(Parachute(x,y,z,COLOR_parachute));
          if(c==2)parachute.push_back(Parachute(x,y,z,COLOR_parachute1));
          if(c==3)parachute.push_back(Parachute(x,y,z,COLOR_parachute2));
          if(c==4)parachute.push_back(Parachute(x,y,z,COLOR_parachute3));
          if(c==4)parachute.push_back(Parachute(x,y,z,COLOR_parachute4));

          parachute.erase(parachute.begin()+i);
      }

}




      float x1 = ball1.position.x;
      float y1 = ball1.position.y;
      float z1 = ball1.position.z;

      float x2 = cannon[0].position.x;
      float y2 = cannon[0].position.y;
      float z2 = cannon[0].position.z;





      float den=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));

      arrow.direction_vector.x=(x2-x1)/den;
      arrow.direction_vector.y=(y2-y1)/den;
      arrow.direction_vector.z=(z2-z1)/den;

      if(!bullet2.empty()){
        for(int i=0;i<bullet2.size();i++)
        bullet2[i].dir_vector=(arrow.direction_vector);
      }


      if(!bullet.empty()){
        for(int i=0;i<bullet.size();i++){
      if(abs(ball1.position.z-bullet[i].position.z > 50) || ball1.position.y < -3.5)
      bullet.erase(bullet.begin());
      }
      }



      if(!bullet.empty()){
      for(int i=0;i<bullet.size();i++)
      bullet[i].move(ball1.speed);
      }

      ball1.fuel+=0.004;

      if(ball1.position.y > 27.704)
        ball1.position.y=27.704;

      if(ball1.speed > 0.95)
        ball1.speed=0.95;




      if(ball1.position.y < -4.8)
        ball1.position.y=-4.8;


      if(ball1.position.y > -4.7 and ball1.position.y  < 8)
      dashboard = Dashboard(-3,-2,0,ball1.position.y,ball1.speed,ball1.fuel,color_fuel,color_speed,COLOR_GREEN);

      if(ball1.position.y > 8 and ball1.position.y  < 17.7)
      dashboard = Dashboard(-3,-2,0,ball1.position.y,ball1.speed,ball1.fuel,color_fuel,color_speed,COLOR_YELLOW);

      if(ball1.position.y > 17.7 and ball1.position.y  < 27.704)
      dashboard = Dashboard(-3,-2,0,ball1.position.y,ball1.speed,ball1.fuel,color_fuel,color_speed,COLOR_RED);


      if(ball1.position.y < -2 )
      dashboard = Dashboard(-3,-2,0,ball1.position.y,ball1.speed,ball1.fuel,color_fuel,color_speed,COLOR_RED);

      if(ball1.speed < 0.35)
      color_speed=COLOR_GREEN;


      if(ball1.speed > 0.35 and ball1.speed < 0.611)
        color_speed=COLOR_YELLOW;

     if(ball1.speed > 0.611 and ball1.speed < 1)
        color_speed=COLOR_RED;
//100 112 128


      if(ball1.fuel > 127.5){
        ball1.fuel=127.5;
        //game quit
      }
      if(ball1.fuel > 100 and ball1.fuel< 112){
      color_fuel=COLOR_GREEN;
    }


      if(ball1.fuel > 112 and ball1.fuel < 118)
        color_fuel=COLOR_YELLOW;

      if(ball1.fuel > 118 and ball1.fuel < 128)
        color_fuel=COLOR_RED;


    //  camera_rotation_angle += 1;
  }

  /* Initialize the OpenGL rendering properties */
  /* Add all the models to be created here */
  void initGL(GLFWwindow *window, int width, int height) {
      /* Objects should be created before any other gl function and shaders */
      // Create the models

      ball1 = Ball(0,0,0,COLOR_RED);
      water = Water(0,-1, COLOR_BLACK);
      rock.push_back(Rock(0,-3,-30));

      for(int i=0;i<20;i++){
          float x=rand()%80 - rand()%60;
          float z=rand()%100 - rand()%150;
          rock.push_back(Rock(x,-3,z));
        }
      cannon.push_back(Cannon(0,-3,-50));
      arrow = Arrow(ball1.position.x, ball1.position.y, ball1.position.z);
      parachute.push_back(Parachute(1,14,-40,COLOR_parachute));
      parachute.push_back(Parachute(4,5,-100,COLOR_parachute1));
      parachute.push_back(Parachute(6,16,-60,COLOR_parachute2));
      parachute.push_back(Parachute(5,7,-80,COLOR_parachute3));
      parachute.push_back(Parachute(16,18,-110,COLOR_parachute4));
      parachute.push_back(Parachute(-5,9,-70,COLOR_parachute));

      fuel.push_back(Fuel(2,2,-20,COLOR_YELLOW));
      fuel.push_back(Fuel(15,1,-60,COLOR_YELLOW));
      fuel.push_back(Fuel(-15,3,-50,COLOR_YELLOW));

      //bomb.push_back(Bomb(0,0,-30));
  //    parachute.push_back(Parachute(-20,10,-130,COLOR_parachute1));

    //  bullet.push_back(Bullet(-6,-1,0 ,COLOR_RED));

      dashboard = Dashboard(-3,-2,0,ball1.position.y,ball1.speed,ball1.fuel,color_fuel,color_speed,color_alt);
      checkpt.push_back(Checkpoint(0,0,-40));
      checkpt.push_back(Checkpoint(-15,0,-100));
  //    bullet2.push_back(Bullet2(-5,-5,-20));
      // Create and compile our GLSL program from the shaders
      programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
      // Get a handle for our "MVP" uniform
      Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


      reshapeWindow (window, width, height);

      // Background color of the scene
      glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
      glClearDepth (1.0f);

      glEnable (GL_DEPTH_TEST);
      glDepthFunc (GL_LEQUAL);

      cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
      cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
      cout << "VERSION: " << glGetString(GL_VERSION) << endl;
      cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
  }


  int main(int argc, char **argv) {
      srand(time(0));
      int width  = 1000;
      int height = 1000;

      window = initGLFW(width, height);

      initGL (window, width, height);

      /* Draw in loop */
      while (!glfwWindowShouldClose(window)) {
          // Process timers

          if (t60.processTick()) {
              // 60 fps
              // OpenGL Draw commands
              disp_score();
              if(ball1.total_checkpoints<=0){
                cout<<"You Won "<<endl;
                cout <<"Total score "<<ball1.score<<endl;
                break;
              }
              if(ball1.health<=0){
                cout<<"You LOST "<<endl;
                cout<<"Checkpoints remaining "<<ball1.total_checkpoints<<endl;
                cout <<"Total score "<<ball1.score<<endl;
                break;
              }
              if(ball1.position.y < -4){
                cout<<"You LOST"<<endl;
                cout <<"Total score "<<ball1.score<<endl;
                ball1.position.y=-4;
                break;
              }
                if(ball1.fuel > 127.5){
                cout<<"You LOST Fuel box empty"<<endl;
                cout <<"Total score "<<ball1.score<<endl;
                break;
              }



              draw();
              // Swap Frame Buffer in double buffering
              glfwSwapBuffers(window);

              tick_elements();
              tick_input(window);
          }

          // Poll for Keyboard and mouse events
          glfwPollEvents();
      }

      quit(window);
  }

  bool detect_collision(bounding_box_t a, bounding_box_t b) {
      return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
             (abs(a.y - b.y) * 2 < (a.height + b.height));
  }

  void reset_screen() {
      float top    = screen_center_y + 4 / screen_zoom;
      float bottom = screen_center_y - 4 / screen_zoom;
      float left   = screen_center_x - 4 / screen_zoom;
      float right  = screen_center_x + 4 / screen_zoom;
      Matrices.projection = glm::perspective(float(45*M_PI/180), 1.0f, 0.1f, 500.0f);
      Matrices2.projection = glm::ortho(left, right, bottom, top);
  }

void heli_camera(float x, float y){
    if(view == 0) {

      target_x=ball1.position.x-ball1.rot_matrix[2][0];
      target_y=ball1.position.y-ball1.rot_matrix[2][1];
      target_z=ball1.position.z-ball1.rot_matrix[2][2];

      camera_x = ball1.position.x;
      camera_z = ball1.position.z+10;

      camera_x += (x-200)/2;
        if(y<=200){
            camera_y = ball1.position.y;
            camera_y += (200-y)/2;
        }

    up_x=0;
    up_y=1;
    up_z=0;
}
}

void disp_score() {
    string a = "3D WORLD \t|\t Score : ";
    string b = "\t|\t Health: ";
    string c  ="\t|\t Checkpoint_remaining: ";
    std::string i = std::to_string(ball1.score);
    std::string j = std::to_string(int(ball1.health));
    std::string k = std::to_string(int(ball1.total_checkpoints));

    a = a + i + b + j + c + k;
    glfwSetWindowTitle(window, const_cast<char *>(a.c_str()));

}
