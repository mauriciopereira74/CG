#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "../../include/point.h"
#include "../../include/engine/world.h"
#include "../../include/tinyxml2/tinyxml2.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace tinyxml2;
using namespace std;

World world;
int window;
int timebase = 0, frames = 0;
bool axis = true;


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
	glVertex3f(-1500.0f, 0.0f, 0.0f);
	glVertex3f(1500.0f, 0.0f, 0.0f);
	
	// Y axis in green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1500.0f, 0.0f);
	glVertex3f(0.0f, 1500.0f, 0.0f);
	
	// Z axis in blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -1500.0f);
	glVertex3f(0.0f, 0.0f, 1500.0f);

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

	gluPerspective(projection.fov, ratio, projection.near, projection.far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void){
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	Camera camera = world.camera;
	glLoadIdentity();

	gluLookAt(camera.position.x, camera.position.y, camera.position.z,
			  camera.lookAt.x  , camera.lookAt.y  , camera.lookAt.z  ,
			  camera.up.x      , camera.up.y      , camera.up.z       );

	// axis drawing
	if (axis) {
		showAxis();
	}

	// geometric transformations

	// drawing instructions
	world.drawModels();

	showFPS();

	//  End of frame
	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y){
	switch(key){
		case 27: // ESCAPE
			glutDestroyWindow(window);
			exit(0);
			break;
		default:
			world.camera.processNormalKeys(key);
			break;
	}

	glutPostRedisplay();
}

void processMouseMotion(int x, int y){
	world.camera.processMouseMotion(x, y);
}


void menuCamChoice(int choice){
    switch (choice) {
        case 0:
            world.camera.mode = STATIC;
            break;
        case 1:
            world.camera.mode = FPS;
			world.camera.beta = 0;
			world.camera.firstTime = true;
            break;
        default:
            break;
    }
}

void modeChoice(int choice){
	switch (choice) {
		case 0:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 1:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		default:
			break;
	}
}

void menuChoice(int choice) {
	switch (choice) {
		case 0:
			axis = axis ^ 1;
			break;
	}
}


void cameraMenu(){
	int cameraMenu = glutCreateMenu(menuCamChoice);
	glutAddMenuEntry("Static Camera", 0);
	glutAddMenuEntry("FPS Camera", 1);

	int modeMenu = glutCreateMenu(modeChoice);
	glutAddMenuEntry("Lines", 0);
	glutAddMenuEntry("Fill", 1);

	glutCreateMenu(menuChoice);
	glutAddMenuEntry("Toggle axis", 0);

	glutAddSubMenu("Mode", modeMenu);
	glutAddSubMenu("Camera", cameraMenu);
	glutAttachMenu(GLUT_LEFT_BUTTON);
}


int main(int argc, char **argv) {
	if (argc == 1 || (argc == 2 && strcmp(argv[1], "--help") == 0)){
        cout << "-------------------------------------------------HELP-----------------------------------------------" << endl;
        cout << "USAGE: ./engine {FILEPATH}.xml" << endl;
		cout << "note: the filepath must be relative to 'build' folder" << endl;
        cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "OPEN MENU: mouse left button" << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "FPS CAMERA MODE      | MOVE: W, A, S, D      | POINT: MOUSE             | INCREASE SPEED: hold SHIFT" << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;

		return 0;
    }

	// init GLUT and the window
	world = World(argv[1]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(world.window.width, world.window.height);
	window = glutCreateWindow("CG@DI-UM");
		
	// Required callback registry 
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
	// registration of the keyboard callbacks
	glutKeyboardFunc(processNormalKeys);
	glutPassiveMotionFunc(processMouseMotion);

	// init GLEW
	#ifndef __APPLE__
		glewInit();
	#endif

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnableClientState(GL_VERTEX_ARRAY);

	world.loadModels();
	timebase = glutGet(GLUT_ELAPSED_TIME);

	cameraMenu();
	
	// GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
