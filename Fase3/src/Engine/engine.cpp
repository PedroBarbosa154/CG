#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "utils/model.h"
#include "utils/group.h"
#include "utils/fpsCamera.h"
#include "utils/staticCamera.h"
#include "utils/parser.h"

#define XMLFILESFOLDER "../../filesXML/"
#define FPS_CAMERA_CFG_FILE "../../cfg/fpsCamera.cfg"
#define STATIC_CAMERA_CFG_FILE "../../cfg/staticCamera.cfg"

using namespace std;

// * Global variables * //

// Vector with all objects
vector<Group> groups_vector = {};

// Presentation options
GLenum gl_mode = GL_LINE;
GLenum gl_face = GL_FRONT_AND_BACK;

// Camera values
fpsCamera* fps_camera;
staticCamera* static_camera;
int camera_mode = 0; // 0 -> static   1 -> fps
int draw_axis = 0;

// FPS counter variables
int timebase;
float elapsed_frames;


// * Functions declarations * //

void changeSize(int w, int h);
void renderScene(void);
void reactRegularKeys(unsigned char key, int x, int y);
void processMouseMotion(int xx, int yy);
void processMouseButtons(int button, int state, int xx, int yy);
void drawAxis(void);
void drawGroup(Group g);
void engineHelpMenu();


// * Glut Functions * //

// Reshape function
void changeSize(int w, int h) {

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
	gluPerspective(45.0f ,ratio, 1.0f ,500.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

// Display function
void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	if (camera_mode == 1) {
    	gluLookAt(fps_camera->getEyeX(), fps_camera->getEyeY(), fps_camera->getEyeZ(),
		      	fps_camera->getCenterX(), fps_camera->getCenterY(), fps_camera->getCenterZ(),
			  	0.0f,1.0f,0.0f);
	}
	else if (camera_mode == 0) {
		gluLookAt(static_camera->getEyeX(), static_camera->getEyeY(), static_camera->getEyeZ(),
		      	0.0f, 0.0f, 0.0f,
			  	0.0f,1.0f,0.0f);
	}
	glPolygonMode(gl_face, gl_mode);

	// FPS counter
	elapsed_frames++;
	float time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		float fps = elapsed_frames * 1000.0 / (time-timebase);
		timebase = time;
		elapsed_frames = 0;
		string title = "CG - FASE 3 (" + to_string((int)fps) + " FPS)";
		glutSetWindowTitle(title.c_str());
	}
	
	// put drawing instructions here
	// Draw axis
	if (draw_axis) drawAxis();

	// Draw groups
    for (Group g : groups_vector) {
		drawGroup(g);
	}

	// End of frame
	glutSwapBuffers();
}


// * Mouse and Keyboard Functions * //

// Function to react to events from regular keys
void reactRegularKeys(unsigned char key, int xx, int yy) {
	switch (key) {
        case 'a':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;
        case 'd':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;
		case 'w':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;
		case 's':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;
		case 'q':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;
		case 'e':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;

		case 't':
			if (gl_mode == GL_FILL) gl_mode = GL_LINE;
			else if (gl_mode == GL_LINE) gl_mode = GL_POINT;
			else if (gl_mode == GL_POINT) gl_mode = GL_FILL;

			glPolygonMode(gl_face,gl_mode);
			break;
		case '1':
			camera_mode = 0;
			break;
		case '2':
			camera_mode = 1;
			break;
		case 'l':
			camera_mode ? fps_camera->loadCamera(FPS_CAMERA_CFG_FILE) : static_camera->loadCamera(STATIC_CAMERA_CFG_FILE);
			break;
		case 'p':
			camera_mode ? fps_camera->saveCamera(FPS_CAMERA_CFG_FILE) : static_camera->saveCamera(STATIC_CAMERA_CFG_FILE);
			break;
		case 27:
			exit(0);
			break;
	}

	glutPostRedisplay();
}

// Function to process mouse motion
void processMouseMotion(int xx, int yy) {
	if (camera_mode) {
		fps_camera->processMouseMotion(xx, yy);
		glutPostRedisplay();
	}
}

// Function to process mouse buttons
void processMouseButtons(int button, int state, int xx, int yy) {
	if (camera_mode) {
		fps_camera->processMouseButtons(button, state, xx, yy);
		glutPostRedisplay();
	}
}


// * Draw Functions * //

// Function to draw xyz axis
void drawAxis(void) {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glEnd();
}

// Function to draw a single group
void drawGroup(Group g) {

	// Set the model view matrix as current, just for safety
	glMatrixMode(GL_MODELVIEW);

	// Push matrix on beggining
	glPushMatrix();

	// Trying to get transformations from group
	vector<Transformation*> ts = g.getTransformations();
	for (Transformation* t : ts) {
		Translate* t_t = dynamic_cast<Translate*>(t);
		if (t_t) {
			glTranslatef(t_t->getX(), t_t->getY(), t_t->getZ());
			continue;
		}

		DynamicTranslate* t_dt = dynamic_cast<DynamicTranslate*>(t);
		if (t_dt) {
			t_dt->renderCatmullRomCurve();
			t_dt->applyTransformations();
			continue;
		}

		Rotate* t_r = dynamic_cast<Rotate*>(t);
		if (t_r) {
			glRotatef(t_r->getAngle(), t_r->getAxisX(), t_r->getAxisY(), t_r->getAxisZ());
			continue;
		}

		DynamicRotate* t_dr = dynamic_cast<DynamicRotate*>(t);
		if (t_dr) {
			t_dr->applyTransformation();
			continue;
		}

		Scale* t_s = dynamic_cast<Scale*>(t);
		if (t_s) {
			glScalef(t_s->getX(), t_s->getY(), t_s->getZ());
			continue;
		}
	}

	// Trying to get color from group
	Color* cl = g.getColor();
	glColor3f(cl->getR(), cl->getG(), cl->getB());

	// Drawing models in this group
	vector<Model> models = g.getModels();
	for (Model model : models) {
		glBindBuffer(GL_ARRAY_BUFFER, model.getVBOInd());
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, model.getVerticeCount());
	}

	// Drawing groups in this group
	vector<Group> groups = g.getGroups();
	for (Group group : groups) {
		drawGroup(group);
	}

	// Popping matrix after drawing all objects in this group
	glPopMatrix();
}


// * Print Functions * //

// Function to print help menu
void engineHelpMenu() {
	std::cout << "┌─────────────────────────ENGINE HELP─────────────────────────┐" << endl;
	std::cout << "│    Usage: ./engine [XML FILE]                               │" << endl;
	std::cout << "│    Displays all primitives loaded from XML FILE             │" << endl;
	std::cout << "│                                                             │" << endl;
	std::cout << "│    FPS camera options                                       │" << endl;
	std::cout << "│    › Use w,a,s,d to navigate in space                       │" << endl;
	std::cout << "│    › Click and drag left mouse to turn camera horizontally  │" << endl;
	std::cout << "│    › Click and drag right mouse to turn camera vertically   │" << endl;
	std::cout << "│    › Use q and e to move camera up and down                 │" << endl;
	std::cout << "│                                                             │" << endl;
	std::cout << "│    Static camera options                                    │" << endl;
	std::cout << "│    › a : Moves camera to the left                           │" << endl;
	std::cout << "│    › d : Moves camera to the right                          │" << endl;
	std::cout << "│    › w : Moves camera up                                    │" << endl;
	std::cout << "│    › s : Moves camera down                                  │" << endl;
	std::cout << "│    › e : Zoom in                                            │" << endl;
	std::cout << "│    › q : Zoom out                                           │" << endl;
	std::cout << "│                                                             │" << endl;
	std::cout << "│    Scene options                                            │" << endl;
	std::cout << "│    › l : Load saved camera settings                         │" << endl;
	std::cout << "│    › p : Save camera settings                               │" << endl;
	std::cout << "│    › t : Cycle between drawing modes                        │" << endl;
	std::cout << "│    › 1 : Sets camera to static mode                         │" << endl;
	std::cout << "│    › 2 : Sets camera to fps mode                            │" << endl;
	std::cout << "│                                                             │" << endl;
	std::cout << "│    Press ESC at any time to exit program                    │" << endl;
	std::cout << "└─────────────────────────────────────────────────────────────┘" << endl;
}


// * MAIN * //

int main(int argc, char **argv) {

	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		engineHelpMenu();
	}
    else if (argc == 2) {
		// init GLUT and the window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
		glutInitWindowPosition(0,0);
		glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
		glutCreateWindow("CG - FASE 3");
		glEnableClientState(GL_VERTEX_ARRAY);

		// init GLEW
		#ifndef __APPLE__
		glewInit();
		#endif

		// Required callback registry
		glutDisplayFunc(renderScene);
		glutReshapeFunc(changeSize);
		glutIdleFunc(renderScene);

		// put here the registration of the keyboard and mouse callbacks
		glutKeyboardFunc(reactRegularKeys);
		glutMouseFunc(processMouseButtons);
		glutMotionFunc(processMouseMotion);

		//  OpenGL settings
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		// load XML file
        string xmlFileString = argv[1];
    	xmlFileString = XMLFILESFOLDER + xmlFileString;
		if (loadXMLFile(xmlFileString, &groups_vector) == 0) {
			std::cout << "Error reading XML File!\n";
			return 0;
		}

		// init fps camera
		fps_camera = new fpsCamera(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), FPS_CAMERA_CFG_FILE);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT)/2);

		// init static camera
		static_camera = new staticCamera(STATIC_CAMERA_CFG_FILE);

		// init FPS counter
		timebase = glutGet(GLUT_ELAPSED_TIME);

		// enter GLUT's main cycle
		glutMainLoop();
    }
	else {
		std::cout << "Invalid input!\n";
	}

	return 1;
}
