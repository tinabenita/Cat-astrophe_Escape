#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Global variables
float wheelPosition = 1.0f; // Current position of the wheel on the road
float wheelSpeed = -0.01f; // Speed of the wheel movement
float roadPosition = 0.0f; // Current position of dashes on the road
float dashSpeed = 0.01f; // Speed of the moving dashes
float wheelRotation = 0.0f; // Current rotation angle of the wheel
float wheelRotationSpeed = -1.0f; // Speed of the wheel rotation
float hydrantPosition = 1.0f; // Current position of the fire hydrant
float hydrantSpeed = -0.01f; // Speed of the fire hydrant movement
bool wheelActive = true; // Flag indicating if the wheel is active
bool hydrantActive = false; // Flag indicating if the fire hydrant is active
int elapsedTime = 0; // Elapsed time in milliseconds
float catJumpHeight = 0.0f;
int score = 0; 
char scoreString[100]; // Adjust the size according to your needs
double threshold = 0.1; // Adjust the value according to your needs
int timeSinceHydrant = 0;
int windowWidth = 800;
int windowHeight = 600;
bool isGameOver = false;
// Number of stars
#define NUM_STARS 100

// RGB values for VIBGYOR colors

int colorIndex = 0;     // Current color index

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
	float exitxL = -0.5;  // Example value for exitxL
    float exityL = 0.5;   // Example value for exityL
    float exityU = -0.5;  // Example value for exityU
    
    float bx = (exitxL * 0.5)-0.35;  // Half the length along the x-axis
    float by = exityL+0.09;
    float w = 0.014;
    float step = (exityL - exityU) / 5.0;
    float bh = step * 5.0;
    float bw = bh * 0.80952 * 0.5;  // Half the length along the x-axis
    float round = 0.024;

    float th = 0.05;
    float ts = 0.01;
    float ty = by - bh * 0.8;
    
   
	
	    // Background
	glBegin(GL_QUADS);

	// Bottom-left corner (purple)
	glColor3f(0.2, 0.0, 0.2);
	glVertex2f(-1.0, -1.0);

	// Top-left corner (purple)
	glColor3f(0.2, 0.0, 0.2);
	glVertex2f(-1.0, 1.0);

	// Top-right corner (black)
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(1.0, 1.0);

	// Bottom-right corner (black)
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(1.0, -1.0);

	glEnd();
	
	
        // Set the color for the wheel
    glPushMatrix();
    glTranslatef(wheelPosition, -0.32f, 0.0f);  // Adjust the y-coordinate for the wheel
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

    // Draw the wheel as a circle with spokes
    int numSpokes = 12;
    float radius = 0.08f;  // Modify this value to change the radius of the wheel
    float spokeWidth = 0.01f;
    float spokeAngle = 360.0f / numSpokes;

    // Draw the body the wheel
    glColor3f(0.75f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (float angle = 0.0f; angle <= 360.0f; angle += 10.0f) {
        float theta = angle * 3.14159f / 180.0f;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    
    // Draw the spokes
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < numSpokes; i++) {
        float angle = i * spokeAngle;
        float theta = angle * 3.14159f / 180.0f;
        float x1 = (radius - spokeWidth) * cos(theta);
        float y1 = (radius - spokeWidth) * sin(theta);
        float x2 = (radius + spokeWidth) * cos(theta);
        float y2 = (radius + spokeWidth) * sin(theta);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();

    glPopMatrix();

	/*
	
	// Set the color for the fire hydrant

	if (hydrantActive) 
	{
	    glPushMatrix();
	    glTranslatef(hydrantPosition, -0.42f, 0.0f);  // Adjust the y-coordinate for the fire hydrant

	    // Draw the fire hydrant
	    glColor3f(0.0f, 0.75f, 0.75f);

	    // Draw the main body of the fire hydrant
	    glBegin(GL_QUADS);
	    glVertex2f(-0.03f, 0.0f);
	    glVertex2f(-0.03f, 0.2f);
	    glVertex2f(0.03f, 0.2f);
	    glVertex2f(0.03f, 0.0f);
	    glEnd();

	    // Draw the top part of the fire hydrant
	    glBegin(GL_TRIANGLE_FAN);
	    glVertex2f(0.0f, 0.3f);
	    for (float angle = 0.0f; angle <= 360.0f; angle += 10.0f) {
		float theta = angle * 3.14159f / 180.0f;
		float x = 0.03f * cos(theta);
		float y = 0.3f + 0.03f * sin(theta);
		glVertex2f(x, y);
	    }
	    glEnd();
	    // Draw the nozzle of the fire hydrant
	    glColor3f(0.0f, 0.0f, 1.0f);
	    glBegin(GL_QUADS);
	    glVertex2f(-0.02f, 0.2f);
	    glVertex2f(-0.02f, 0.3f);
	    glVertex2f(0.02f, 0.3f);
	    glVertex2f(0.02f, 0.2f);
	    glEnd();

	    

	    glPopMatrix();
	}
	
	*/
	    glFlush();
    glutSwapBuffers();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 1000);
    glutCreateWindow("test");

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	// Register the keyboard callback functions
    //glutSpecialFunc(specialKeyPressed);
    //glutSpecialUpFunc(specialKeyReleased);
    //glPointSize(1.0);

    //initStars();

    glutDisplayFunc(display);
    //glutReshapeFunc(reshape);
    //glutTimerFunc(0, timer, 0);
    //glutTimerFunc(0, update, 0);
    //glutTimerFunc(95, updateColor, 0);
    glutMainLoop();
    return 0;
}



