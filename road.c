#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


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
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -1.0);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glEnd();
    
// Check if cat parts are touching the wheel
    if (wheelActive &&
        (wheelPosition >= bx - bw && wheelPosition <= bx + bw) &&
        (wheelRotation >= 270.0f && wheelRotation <= 360.0f)) {
        printf("GAME OVER. PRESS ENTER TO PLAY AGAIN\n");
        wheelActive = false;
        hydrantActive = false;
        return;
    }
    
    
    // Set the color for the moving dashes on the road
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the moving dashes on the road
    glBegin(GL_QUADS);
    for (float x = -0.8f + roadPosition; x < 0.8f; x += 0.2f) {
        glVertex2f(x, -0.42f);
        glVertex2f(x, -0.44f);
        glVertex2f(x + 0.1f, -0.44f);
        glVertex2f(x + 0.1f, -0.42f);
    }
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

    // Draw the outer rubber part of the wheel
    glColor3f(1.0f, 0.0f, 0.0f);
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
    glColor3f(1.0f, 1.0f, 1.0f);
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








// Set the color for the fire hydrant



if (hydrantActive) {
    glPushMatrix();
    glTranslatef(hydrantPosition, -0.42f, 0.0f);  // Adjust the y-coordinate for the fire hydrant

    // Draw the fire hydrant
    glColor3f(0.0f, 1.0f, 1.0f);

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

    // Draw the base of the fire hydrant
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.0f);
    glVertex2f(-0.05f, -0.1f);
    glVertex2f(0.05f, -0.1f);
    glVertex2f(0.05f, 0.0f);
    glEnd();

    glPopMatrix();
}
if (hydrantActive) {
        score += 5;
    }




    


    
    //Tail
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_QUAD_STRIP);
    glVertex2f(bx, ty+ catJumpHeight);
    glVertex2f(bx, ty+ catJumpHeight + th);
    ty += ts * 2;
    glVertex2f(bx - ts, ty+ catJumpHeight);
    glVertex2f(bx - ts, ty + th+ catJumpHeight);
    ty += ts * 1;
    glVertex2f(bx - ts * 2, ty+ catJumpHeight);
    glVertex2f(bx - ts * 2, ty + th+ catJumpHeight);
    ty += ts * 2;
    glVertex2f(bx - ts * 3, ty+ catJumpHeight);
    glVertex2f(bx - ts * 3, ty + th+ catJumpHeight);
    ty += ts * 3;
    glVertex2f(bx - ts * 4, ty+ catJumpHeight);
    glVertex2f(bx - ts * 4, ty + th+ catJumpHeight);
    glEnd();
    
   // Dark grey color for the entire cat shape
		glBegin(GL_POLYGON);
	    /* glColor3f(0.2, 0.2, 0.2);  // Dark grey color
	    glVertex2f(bx, by - 0.75);
	    glVertex2f(bx, by + round - 0.75);
	    glVertex2f(bx + bw, by + round - 0.75);
	    glVertex2f(bx + bw, by - 0.75);

	    // Reduce the height to half (divide by 2)
	    glVertex2f(bx + bw, (by - bh / 4) - 0.75);
	    glVertex2f(bx + bw - round, (by - bh / 4) - 0.75);
	    glVertex2f(bx + round, (by - bh / 4 - round) - 0.75);
	    glVertex2f(bx + round, (by - bh / 4) - 0.75); */
	    
	    glColor3f(0.2, 0.2, 0.2); // Dark grey color
	glVertex2f(bx, by - 0.75 + catJumpHeight);
	glVertex2f(bx, by + round - 0.75 + catJumpHeight);
	glVertex2f(bx + bw, by + round - 0.75 + catJumpHeight);
	glVertex2f(bx + bw, by - 0.75 + catJumpHeight);
	glVertex2f(bx + bw, (by - bh / 4) - 0.75 + catJumpHeight);
	glVertex2f(bx + bw - round, (by - bh / 4) - 0.75 + catJumpHeight);
	glVertex2f(bx + round, (by - bh / 4 - round) - 0.75 + catJumpHeight);
	glVertex2f(bx + round, (by - bh / 4) - 0.75 + catJumpHeight);

	glEnd();


	// Light grey color for the inner rectangular polygon with rounded edges
	
	glBegin(GL_POLYGON);
	glColor3f(0.35, 0.35, 0.35); // Light grey color
	float innerRound = round * 0.8;  // Adjust the inner round value to make it smaller than the outer round value
	glVertex2f(bx + round, by - 0.75+ catJumpHeight);
	glVertex2f(bx + round, (by - bh / 4 - round) - 0.75+ catJumpHeight);
	glVertex2f(bx + bw - round, (by - bh / 4 - round) - 0.75+ catJumpHeight);
	glVertex2f(bx + bw - round, by - 0.75+ catJumpHeight);
	glVertex2f(bx + bw - innerRound, by - 0.75+ catJumpHeight);
	glVertex2f(bx + bw - innerRound, (by - bh / 4 - innerRound) - 0.75+ catJumpHeight);
	glVertex2f(bx + innerRound, (by - bh / 4 - innerRound) - 0.75+ catJumpHeight);
	glVertex2f(bx + innerRound, by - 0.75+ catJumpHeight);
	glEnd();	


    // Four paws
    float fr = 0.02;
    float fx = bx + bw -0.23;
    float fy = by - bh - fr;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.6, 0.6, 0.6);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy+ catJumpHeight + fr * sin(i));
    }
    glEnd();

    fx -= bw-0.26;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.6, 0.6, 0.6);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i)+ catJumpHeight);
    }
    glEnd();

    fx = fx + bw * 0.8;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.6, 0.6, 0.6);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i)+ catJumpHeight);
    }
    glEnd();

    fx = (fx * 0.6)-0.05;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.6, 0.6, 0.6);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i)+ catJumpHeight);
    }
    glEnd();
    
    // Face
    fx = bx + bw;
    fy = by - bh * 0.8;
    fr = 0.07;

    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i)+ catJumpHeight);
    }
    glEnd();

    // Ear
    float ew = fr * 0.9;
    glBegin(GL_TRIANGLES);

    // Right ear
    glVertex2f(fx, fy+ catJumpHeight);
    glVertex2f(fx + ew, fy+ catJumpHeight);
    glVertex2f(fx + ew, fy + catJumpHeight+ ew * 2);

    // Left ear
    glVertex2f(fx, fy+ catJumpHeight);
    glVertex2f(fx - ew, fy+ catJumpHeight);
    glVertex2f(fx - ew, fy + catJumpHeight+ ew * 2);
    glEnd();

    // Left eye
    fr = 0.01;
    fx -= fr * 2.5;
    //fy += 0.05; // Move up by 0.25
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + catJumpHeight+ fr * sin(i));
    }
    glEnd();

    // Gleam
    fr = 0.0025;

    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx - fr * 2 + fr * cos(i), fy + catJumpHeight+ fr * 2 + fr * sin(i));
    }
    glEnd();

    // Right eye
    fr = 0.01;
    fx += fr * 4.5;
    //fy += 0.05; // Move up by 0.25
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx - fr * cos(i), fy + catJumpHeight+ fr * sin(i));
    }
    glEnd();

    // Gleam
    fr = 0.0025;
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx - fr * 2 + fr * cos(i), fy + catJumpHeight+ fr * 2 + fr * sin(i));
    }
    glEnd();

    // Nose
    fr = 0.005;  // Radius of the nose
    fx = bx + bw;
    //fy *= 0.9;
    fy -= 0.0000001;
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx - fr * cos(i), fy + catJumpHeight+ fr * sin(i));
    }
    glEnd();

    /*Mouth*/
    //fy *= 0.8;
    fy -= 0.04; // Reduce the space between mouth and eyes by adjusting fy
    float mw = 5;  // Mouth width measured in nose widths
    float mh = 2;  // Mouth height measured in nose widths

    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glVertex2f(fx - fr * mw, fy + catJumpHeight+ fr * mh);
    glVertex2f(fx - fr * mw, fy+ catJumpHeight);
    glVertex2f(fx, fy+ catJumpHeight);
    glVertex2f(fx, fy + catJumpHeight+ fr * mh);
    glVertex2f(fx, fy+ catJumpHeight);
    glVertex2f(fx + fr * mw, fy+ catJumpHeight);
    glVertex2f(fx + fr * mw, fy+ catJumpHeight + fr * mh);
    glEnd();

    fr *= 1.4;
    glColor3f(1, 0.6, 0.6);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + mw * 1.2 * fr - fr * cos(i), fy + catJumpHeight+ fr * sin(i) + fr * mh);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx - mw * 1.2 * fr - fr * cos(i), fy+ catJumpHeight + fr * sin(i) + fr * mh);
    }
    glEnd();


	

// Draw the scoreboard
   // Display the score using OpenGL functions
    // You can choose the position and other properties of the text based on your preferences.
    // Example code to display the score at the top-left corner of the window:
    char scoreString[100]; // Adjust the size according to your needs

    snprintf(scoreString, sizeof(scoreString), "Score: %d", score);
    glColor3f(1.0f, 1.0f, 1.0f); // Set text color to white
    glRasterPos2f(-0.65f, 0.65f); // Position the text at the top-left corner
    int len = strlen(scoreString);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreString[i]);
    }
        

if (wheelActive &&
        (wheelPosition >= bx - bw && wheelPosition <= bx + bw) &&
        (wheelRotation >= 270.0f && wheelRotation <= 360.0f)) {
        printf("GAME OVER. PRESS ENTER TO PLAY AGAIN\n");
        wheelActive = false;
        hydrantActive = false;
        return;
    }

    // Check if cat parts are touching the fire hydrant
    if (hydrantActive &&
        ((bx >= hydrantPosition - 0.03f && bx <= hydrantPosition + 0.03f) ||
         (bx + bw >= hydrantPosition - 0.03f && bx + bw <= hydrantPosition + 0.03f))) {
        if (by - 0.75 + catJumpHeight <= 0.2f ||
            (by - bh / 4 - round) - 0.75 + catJumpHeight <= 0.2f) {
            score += 5;
            hydrantActive = false;
        }
    }

    // Draw the fire hydrant if it's active
    if (hydrantActive) {
        glPushMatrix();
        glTranslatef(hydrantPosition, -0.42f, 0.0f);

        // Draw the fire hydrant
        // ...

        glPopMatrix();
    }

    // ...

    // Update the time since the last fire hydrant appeared
    timeSinceHydrant += elapsedTime;

    // Generate a new fire hydrant after a certain time interval
    if (!hydrantActive && timeSinceHydrant >= 3000) {
        hydrantActive = true;
        hydrantPosition = 1.0f;
        timeSinceHydrant = 0;
    }

    glFlush();
    glutSwapBuffers();
}


   

void update(int value) {
    // Update the position of the wheel
    wheelPosition += wheelSpeed;

    // Wrap the wheel position when it reaches the left edge
    if (wheelPosition < -1.2f)
        wheelPosition = 1.0f;

    // Update the rotation angle of the wheel
    wheelRotation += wheelRotationSpeed;

    // Wrap the wheel rotation when it completes a full rotation
    if (wheelRotation > 360.0f)
        wheelRotation -= 360.0f;

    // Update the position of the dashes
    roadPosition -= dashSpeed;

    // Wrap the dashes around when they reach the left edge of the road
    if (roadPosition < -0.2f)
        roadPosition = 0.0f;

    // Update the position of the fire hydrant if it is active
    if (hydrantActive) {
        hydrantPosition += hydrantSpeed;

        // Deactivate the fire hydrant if it moves beyond the left edge
        if (hydrantPosition < -1.2f) {
            hydrantActive = false;
        }
    }

    // Activate the fire hydrant after a 5-second delay
    if (elapsedTime >= 5000 && !hydrantActive) {
        hydrantActive = true;
        hydrantPosition = 1.0f;
    }

    elapsedTime += 16; // Update elapsed time

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}



void specialKeyPressed(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            // Jump the cat by adjusting the catJumpHeight
            catJumpHeight = 0.6f;
            break;
        // Add more cases for other arrow keys if needed
    }
}

void specialKeyReleased(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            // Reset the catJumpHeight when the up arrow key is released
            catJumpHeight = 0.0f;
            break;
        // Add more cases for other arrow keys if needed
    }
}

void makeHydrantReappear(int value) {
    hydrantActive = true; // Make the fire hydrant reappear
    // You can add additional logic here to control the position of the fire hydrant when it reappears.
} 


void catTouchesFireHydrant() {



    // Check if the distance between the cat and the fire hydrant is less than a threshold value (you need to define this value).
    // You can calculate the distance between two points using the distance formula: sqrt((x2 - x1)^2 + (y2 - y1)^2).
    // If the cat touches the fire hydrant, perform the following actions:
    if (fabs(wheelPosition - hydrantPosition) < threshold) { // Replace 'threshold' with your chosen value.
        hydrantActive = false; // Make the fire hydrant disappear
        score += 5; // Add 5 points to the score
        // Add a delay here if you want the fire hydrant to reappear after a certain time.
        // You can use the 'glutTimerFunc' function to achieve this.

        // Example: If you want the fire hydrant to reappear after 2000 milliseconds (2 seconds)
        
        int reappearDelay = 2000;
        glutTimerFunc(reappearDelay, makeHydrantReappear, 0);
    }
}







int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Obstacle Animation");

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	// Register the keyboard callback functions
    glutSpecialFunc(specialKeyPressed);
    glutSpecialUpFunc(specialKeyReleased);

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}




