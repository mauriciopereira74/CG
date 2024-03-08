#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "../include/point.h"
#include "../include/world.h"
#include "../include/tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

World world;
float alphaCamera = 0, betaCamera = 0, radiusCamera = 10;
float pxCamera = 0, pyCamera = 0, pzCamera = 0;
bool explorerMode = false;
int timebase = 0, frames = 0;


void showFPS(){
	frames++;
    int fps;
    int time = glutGet(GLUT_ELAPSED_TIME);

    if (time - timebase > 1000){
        fps = frames*1000.0 / (time-timebase);
        timebase = time; frames = 0;
        char title[20];
        sprintf(title, "CG@G8 | %d FPS", fps);
        glutSetWindowTitle(title);
    }
}


void showAxis(){
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	
	// Y axis in green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	
	// Z axis in blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);

	glColor3f(255.0f, 255.0f, 255.0f);
		
	glEnd();
}


void changeSize(int w, int h){

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	Projection projection = world.camera.projection;

	gluPerspective(projection.fov ,ratio, projection.near, projection.far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void){
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	Camera camera = world.camera;
	glLoadIdentity();

	// Modo explorador desativado
	if(explorerMode == false){
		gluLookAt(camera.position.x, camera.position.y, camera.position.z,
	        camera.lookAt.x, camera.lookAt.y, camera.lookAt.z,
	        camera.up.x, camera.up.y, camera.up.z);
	}
	else{
		gluLookAt(pxCamera, pyCamera, pzCamera, 
	        	  0, 0, 0,
	        	  camera.up.x, camera.up.y, camera.up.z);
	}

	// axis drawing
	showAxis();

	// geometric transformations

	// drawing instructions
	Group group = world.group;
	vector<VBO> vbos = group.vbos;
	for(int i=0; i < vbos.size(); i++){
		vbos[i].draw();
	}

	showFPS();

	//  End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int x, int y){
	if(explorerMode == true){
		if(c == 'c'){
			explorerMode = false;
		}
		else if (c == '-'){
			radiusCamera += 1;

			pxCamera = radiusCamera * cos (betaCamera) * sin (alphaCamera);
			pyCamera = radiusCamera * sin (betaCamera);
			pzCamera = radiusCamera * cos (betaCamera) * cos (alphaCamera);
		}
		else if (c == '+'){
			radiusCamera -= 1;

			pxCamera = radiusCamera * cos (betaCamera) * sin (alphaCamera);
			pyCamera = radiusCamera * sin (betaCamera);
			pzCamera = radiusCamera * cos (betaCamera) * cos (alphaCamera);
		}
	}
	else{
		if(c == 'c'){
			explorerMode = true;
		}
	}

	glutPostRedisplay();
}


void processSpecialKeys(int key, int x, int y){	
	if (explorerMode == true){
		if (key == GLUT_KEY_LEFT){
			alphaCamera -= M_PI / 20;

			pxCamera = radiusCamera * cos (betaCamera) * sin (alphaCamera);
			pyCamera = radiusCamera * sin (betaCamera);
			pzCamera = radiusCamera * cos (betaCamera) * cos (alphaCamera);
		}
		else if (key == GLUT_KEY_RIGHT){
			alphaCamera += M_PI / 20;

			pxCamera = radiusCamera * cos (betaCamera) * sin (alphaCamera);
			pyCamera = radiusCamera * sin (betaCamera);
			pzCamera = radiusCamera * cos (betaCamera) * cos (alphaCamera);
		}
		else if (key == GLUT_KEY_UP){
			betaCamera += M_PI / 20;

			if (betaCamera > M_PI / 2) betaCamera = M_PI / 2;

			pxCamera = radiusCamera * cos (betaCamera) * sin (alphaCamera);
			pyCamera = radiusCamera * sin (betaCamera);
			pzCamera = radiusCamera * cos (betaCamera) * cos (alphaCamera);
		}
		else if (key == GLUT_KEY_DOWN){
			betaCamera -= M_PI / 20;

			if (betaCamera < -M_PI / 2) betaCamera = -M_PI / 2;

			pxCamera = radiusCamera * cos (betaCamera) * sin (alphaCamera);
			pyCamera = radiusCamera * sin (betaCamera);
			pzCamera = radiusCamera * cos (betaCamera) * cos (alphaCamera);
		}

		glutPostRedisplay();
	}
}


int main(int argc, char **argv) {
	// init GLUT and the window
	world = World(argv[1]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(world.window.width, world.window.height);
    glutCreateWindow("CG@DI-UM");
		
	// Required callback registry 
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
	// registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

	// init GLEW
	#ifndef __APPLE__
	    glewInit();
	#endif

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);

	world.loadGroup();
	timebase = glutGet(GLUT_ELAPSED_TIME);
	
	// GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
