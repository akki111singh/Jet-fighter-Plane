# Jet-fighter-Plane
 A 3D OpenGL 3.0  game
 
# Prerequisites
   OpenGL 3.0
   
 # How to run
    mkdir build
    cd build
    cmake ..
    make
    ./graphics_asgn1
   
## 3D WORLD
    1.One of the important primary objects in the world will be the fighter airplane, which
      the player will be guiding through the land and sea obstacles located beneath to the
      final checkpost to mark the obstacle course “completed”. The plane will have the
      capability to hover(not move but stay in the air), rise upwards and go downwards, go
      forward, turn left and right, tilt left and right and then of course, shoot missiles and
      drop bombs.
      
    2. Airplane dashboard. This will be displayed on the game screen in the bottom left
    corner. The dashboard must display the speed, current altitude and fuel remaining.
    This need not be textual but can be pictorial(like fuel bar or something). Zero fuel or
    zero altitude(hitting the ground) will result in crashing.
    
    3. The obstacle course will be divided into multiple checkpoints. The plane will be
    guided towards a checkpoint with the help of a shiny red arrow, pointing to the
    checkpoint just beneath it. This arrow must be visible from far far away even if the
    actual checkpoint isn’t visible. Upon achieving that checkpoint the arrow will be
    updated according to the succeeding checkpoint. This arrow will help the player
    navigate through the obstacle course.
    
    4.Enemy cannons will be located on ground at each checkpoint attacking the player
    airplane. The fighter plane needs to destroy those enemy hideouts using missiles
    and bombs in order to mark that checkpoint completed and get the direction for next
    checkpoint.
    
    5.Random rings of smoke in the air, passing the airplane through which will guarantee
    bonus points for the player.
    Fuel ups on the way will guarantee that player has the opportunity to refill his tank for
    the long battle ahead.
    
    6.Volcanoes upon the islands beneath, a complete NO-FLYING-ZONE for the player.
    The game will end as soon as the airplane comes too close to the proximity of a
    volcano.
    
    7.Shooting enemy parachutes flying in the air is another way to earn some health.Missiles installed in the
    airplane could be used to shoot the flying targets ahead.
    
  # Controls
    Left Click: Shoot missiles;
    Right Click: Shoot Bombs;
    Up Arrow: increase Speed;
    Down Arrow: Decrease Speed;
    W: move up
    D: move down
    A: move left
    D: move right
    Q: tilt left
    E: tilt right
    Space: stunt
    
# Camera views:
    • Plane view: This is a view from the plane’s position where only a part of the world in front is
    visible. In other words, in this view, we see what the plane sees, as if we were the plane.

    • Top View: This is a top-down view, as if we were looking vertically downwards from a
    position in the sky. This gives a clear picture of the path.
    
    • Tower view: Here, the camera is sitting on a tower, to the side of the plane of playing,
    observing it at an angle.• Follow-cam view: This is a view of the plane and the region in front of it from a location
    behind and above it, as if the camera is following the plane.
    
    • Helicopter-cam view: Here, the camera is movable with the mouse in an intuitive manner.
    Clicking and dragging should change the look angle, the up vector should remain up
    always,and the scroll wheel will move the camera closer or farther away from the scene.up
    vector should remain up always, and the scroll wheel will move the camera closer or farther
    away from the scene.
    
    PRESS 1,2,3,4,5 to change the camera views Respectively.
