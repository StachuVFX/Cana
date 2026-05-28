//
//  Main.cpp
//  Cana
//
//  Created by Stachu on 16.12.2025.
//

/*
    Conventions:
 - dimensions:
    * unified (signed float, [-1, 1], relative to screen center)
    * direct (unsinged float or int, relative to top-left corner)
 - drawTriangle versions:
    * 1. Lines from one vertex to all points on the opposite side - missing points towards the side edge
    * 2. Lines between two sides, simultanous (starting from one vertex, ending at the other vertices at the same time) - inefficient
    * 3. Only horizontal lines, phased (starting from top vertex, ending at bottom vertex, 2 phases divided by the middle vertex) - efficient
    * 4. Using straight line relative equations and comparisons - probably inefficient
 
    Possible optimizations:
 - implement timing to test solution speed
 - inline functions
 - change arguments to references
 
    Bugs:
 - triangle drawing is very inaccurate (still after a day of debugging)
 
    TODO:
 - finish fixing the triangle bug
 - move fov to main
 - 2D and 3D objects
 - add blured/sampled versions of screen functions
 - add float (blured/sampled) versions of drawing functions
 - try making Cana handle everything
 - move enums to classes (one day)
 - create Cana_Event class (one day)
 - optimize drawing functions (one day)
 - set drawing reference ([-1, 1]) to lower dimension (maybe)
 
    DONE:
 - made rendering functions more accurate (aka more *floaty*)
 - optimizd rendering functions a little
 - created a math file for function defines
 - other minor fixes
*/

//  System Includes
#include <iostream>
#include <thread>

//  SDL Includes (not needed anymore - all in Cana.h)

//  Custom Includes
#include "Cana.h"

//  Defines
#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 900
#define DRAW_WIDTH 360
#define DRAW_HEIGHT 225

//  Structs

//  Function declarations

//  Variable declarations

//  Main function
int main(int argc, char* argv[]) {
/* Startup */
    Cana cana("Cana Test", "0.1.2", "name.stachu.Cana");
    /* Screen and renderer */
    cana.createWindow("Cana Test", SCREEN_WIDTH, SCREEN_HEIGHT, WindowType_Fullscreen);
    Cana_Renderer renderer = cana.createRenderer(DRAW_WIDTH, DRAW_HEIGHT);
    
/* Game setup */
    /* Colors */
    Cana_Color color = cana.mapColors();
    
/* Game loop */
    while (cana.running) {
        /* Sleep in case of memory leaks lol */
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
    /* Events */
        cana.checkEvents();
        
    /* Rendering */
        /* Prepare for drawing */
        cana.drawingStart();
        
        /* Only draw here */
        renderer.clear(color.gray);
        
        // Box 1
        Cana_Vec3 point1(-4.0f, -2.5f, 3.5f);
        Cana_Vec3 point2(-2.0f, -2.5f, 3.5f);
        Cana_Vec3 point3(-2.0f, -0.5f, 3.5f);
        Cana_Vec3 point4(-4.0f, -0.5f, 3.5f);
        Cana_Vec3 point5(-4.0f, -2.5f, 5.5f);
        Cana_Vec3 point6(-2.0f, -2.5f, 5.5f);
        Cana_Vec3 point7(-2.0f, -0.5f, 5.5f);
        Cana_Vec3 point8(-4.0f, -0.5f, 5.5f);
        
        // triangles
        renderer.drawTriangle_3D(point5, point7, point6, color.yellow);
        renderer.drawTriangle_3D(point7, point5, point8, color.yellow);
        
        renderer.drawTriangle_3D(point1, point8, point5, color.magenta);
        renderer.drawTriangle_3D(point8, point1, point4, color.magenta);
        
        renderer.drawTriangle_3D(point1, point6, point2, color.cyan);
        renderer.drawTriangle_3D(point6, point1, point5, color.cyan);
        //
        renderer.drawTriangle_3D(point2, point7, point6, color.red);
        renderer.drawTriangle_3D(point7, point2, point3, color.red);
        
        renderer.drawTriangle_3D(point4, point7, point3, color.green);
        renderer.drawTriangle_3D(point7, point4, point8, color.green);
        
        renderer.drawTriangle_3D(point1, point3, point2, color.blue);
        renderer.drawTriangle_3D(point3, point1, point4, color.blue);
        
        // lines
//        renderer.drawLine_3D(point1, point2, color.black);
//        renderer.drawLine_3D(point2, point3, color.black);
//        renderer.drawLine_3D(point3, point4, color.black);
//        renderer.drawLine_3D(point4, point1, color.black);
//
//        renderer.drawLine_3D(point5, point6, color.black);
//        renderer.drawLine_3D(point6, point7, color.black);
//        renderer.drawLine_3D(point7, point8, color.black);
//        renderer.drawLine_3D(point8, point5, color.black);
//
//        renderer.drawLine_3D(point1, point5, color.black);
//        renderer.drawLine_3D(point2, point6, color.black);
//        renderer.drawLine_3D(point3, point7, color.black);
//        renderer.drawLine_3D(point4, point8, color.black);
        
        // points
        renderer.drawPoint_3D(point1, 0.001f, color.white);
        renderer.drawPoint_3D(point2, 0.001f, color.white);
        renderer.drawPoint_3D(point3, 0.001f, color.white);
        renderer.drawPoint_3D(point4, 0.001f, color.white);
        renderer.drawPoint_3D(point5, 0.001f, color.white);
        renderer.drawPoint_3D(point6, 0.001f, color.white);
        renderer.drawPoint_3D(point7, 0.001f, color.white);
        renderer.drawPoint_3D(point8, 0.001f, color.white);
        
        // Box 2
        Cana_Vec3 point21( 4.0f,  2.5f, 3.5f);
        Cana_Vec3 point22( 2.0f,  2.5f, 3.5f);
        Cana_Vec3 point23( 2.0f,  0.5f, 3.5f);
        Cana_Vec3 point24( 4.0f,  0.5f, 3.5f);
        Cana_Vec3 point25( 4.0f,  2.5f, 5.5f);
        Cana_Vec3 point26( 2.0f,  2.5f, 5.5f);
        Cana_Vec3 point27( 2.0f,  0.5f, 5.5f);
        Cana_Vec3 point28( 4.0f,  0.5f, 5.5f);
        
        // triangles
        renderer.drawTriangle_3D(point25, point26, point27, color.yellow);
        renderer.drawTriangle_3D(point27, point28, point25, color.yellow);
        
        renderer.drawTriangle_3D(point21, point25, point28, color.magenta);
        renderer.drawTriangle_3D(point28, point24, point21, color.magenta);
        
        renderer.drawTriangle_3D(point21, point22, point26, color.cyan);
        renderer.drawTriangle_3D(point26, point25, point21, color.cyan);
        //
        renderer.drawTriangle_3D(point22, point26, point27, color.red);
        renderer.drawTriangle_3D(point27, point23, point22, color.red);
        
        renderer.drawTriangle_3D(point24, point23, point27, color.green);
        renderer.drawTriangle_3D(point27, point28, point24, color.green);
        
        renderer.drawTriangle_3D(point21, point22, point23, color.blue);
        renderer.drawTriangle_3D(point23, point24, point21, color.blue);
        
        // lines
//        renderer.drawLine_3D(point21, point22, color.black);
//        renderer.drawLine_3D(point22, point23, color.black);
//        renderer.drawLine_3D(point23, point24, color.black);
//        renderer.drawLine_3D(point24, point21, color.black);
//
//        renderer.drawLine_3D(point25, point26, color.black);
//        renderer.drawLine_3D(point26, point27, color.black);
//        renderer.drawLine_3D(point27, point28, color.black);
//        renderer.drawLine_3D(point28, point25, color.black);
//
//        renderer.drawLine_3D(point21, point25, color.black);
//        renderer.drawLine_3D(point22, point26, color.black);
//        renderer.drawLine_3D(point23, point27, color.black);
//        renderer.drawLine_3D(point24, point28, color.black);
        
        // points
        renderer.drawPoint_3D(point21, 0.001f, color.white);
        renderer.drawPoint_3D(point22, 0.001f, color.white);
        renderer.drawPoint_3D(point23, 0.001f, color.white);
        renderer.drawPoint_3D(point24, 0.001f, color.white);
        renderer.drawPoint_3D(point25, 0.001f, color.white);
        renderer.drawPoint_3D(point26, 0.001f, color.white);
        renderer.drawPoint_3D(point27, 0.001f, color.white);
        renderer.drawPoint_3D(point28, 0.001f, color.white);
        
        /* Stop drawing */
        cana.drawingFinish();

    /* Swapping buffers */
        cana.scale();
        cana.swap();
    }
    
/* Shutdown */
    cana.quit();
}
