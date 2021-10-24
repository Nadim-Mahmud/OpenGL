#include<windows.h>
#include <GL/glut.h>
#include<bits/stdc++.h>

using namespace std;

#define MAX_HEIGHT 720
#define MAX_WIDTH 1280


void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);	// Set display window colour to white

	glMatrixMode(GL_PROJECTION);		// Set projection parameters
	gluOrtho2D(0.0, 1280.0, 0.0, 720.0);
}



float x,y,i;
float PI=3.1416;

void circle(float x, float y, GLfloat radius, bool color){
    int i;
    int triangleAmount =100;
    GLfloat twicePi = 2.0 * PI;

    glBegin(GL_TRIANGLE_FAN);
    if(!color){
        glColor3ub(238, 139, 21);
    }
    else{
        glColor3ub(255, 255, 255);
    }

    twicePi = 2.0 * PI;


    glVertex2f(x, y);
    for(i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i *  twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }

    glEnd();
}


void bringWindows(int x1, int y1, int height, int width, int row, int column,  int night){

    int i, j, stx, sty;

    float distx = (float)width/((float)column*2.0 + 1.0);
    float disty = (float)height/((float)row*2.0 + 1.0);
    float window_length = min(distx, disty);

    glColor3f(1.0, 1.0, 1.0);
    for(i = 1; i <= column; i++){
        for(j = 1; j <= row; j++){

            if(night){
                int radom = rand()%2;
                if(radom){
                    glColor3f(1.0, 1.0, 1.0);
                }
                else{
                    glColor3f(0.0, 0.0, 0.0);
                }
            }

            stx = x1 + window_length + window_length*(i-1)*2;
            sty = y1 + window_length + window_length*(j-1)*2;

            glBegin(GL_QUADS);

                glVertex2i(stx, sty);
                glVertex2i(stx+window_length, sty);
                glVertex2i(stx+window_length, sty+window_length);
                glVertex2i(stx, sty+window_length);

            glEnd();

        }
    }

}


/**
    (x1, y1) bottom left location
    height = building height
    width = building width
    row = number of window in row
    column = number of window in column
    night = is night
*/

void houseBuilding(int x1, int y1, int height, int width, int row, int column,  int night){

    int l = 1, r = 1, u = 1, d = 1;
    int right_loc = x1+width;
    int upper_loc = y1+height;

	// outer box
	if(night){
        glColor3f(1.0, 1.0, 1.0);
	}
	else{
        glColor3f(0.0, 0.0, 0.0);
	}


	glBegin(GL_QUADS);

		glVertex2i(x1, y1);
		glVertex2i(right_loc, y1);
		glVertex2i(right_loc, upper_loc);
		glVertex2i(x1, upper_loc);

	glEnd();

	//inner box
	if(night){
        glColor3f(61.0/255.0, 55.0/255.0, 46.0/255.0);
	}
	else{
        glColor3f(178.0/255.0, 208/255.0, 180/255.0);
	}

	glBegin(GL_QUADS);

        glVertex2i(x1+r, y1+u);
		glVertex2i(right_loc-r, y1+u);
		glVertex2i(right_loc-r, upper_loc-u);
		glVertex2i(x1+r, upper_loc-u);

	glEnd();

    bringWindows(x1, y1, height, width, row, column, night);

}



void road(int height, int night){

    // main road
    if(night){
        glColor3ub(65, 72, 77);
    }
    else{
        glColor3ub(99, 108, 115);
    }

    glBegin(GL_QUADS);

        glVertex2i(0, 0);
		glVertex2i(1280, 0);
		glVertex2i(1280, height);
		glVertex2i(0, height);

	glEnd();


	// white striped segment of stripe count

    if(night){
        glColor3ub(255, 255, 255);
    }
    else{
        glColor3ub(255, 255, 255);
    }

    int  stripe_count = 4;
    double mid = height/2.0;
    double stripe_width = 20.0;
    double segment = (double)MAX_WIDTH/(double)(stripe_count*2+1);

	for(int i = 0; i<4; i++){

        glBegin(GL_QUADS);

            glVertex2i(segment + 2*i*segment, mid-stripe_width);
            glVertex2i(2*segment + 2*i*segment, mid-stripe_width);
            glVertex2i(2*segment + 2*i*segment, mid+stripe_width);
            glVertex2i(segment + 2*i*segment, mid+stripe_width);

        glEnd();
	}
}

void back_ground(int start_y, int height, int night){

    if(night){
        glColor3ub(94, 95, 98);
    }
    else{
        glColor3ub(116, 117, 122);
    }

    glBegin(GL_QUADS);

        glVertex2i(0, start_y);
		glVertex2i(1280, start_y);
		glVertex2i(1280, start_y+height);
		glVertex2i(0, start_y+height);

	glEnd();
}


void sky(int start_y, int night){

    if(night){
        glColor3ub(0, 0, 102);
    }
    else{
        glColor3ub(255, 255, 153);
    }

    glBegin(GL_QUADS);

        glVertex2i(0, start_y);
		glVertex2i(1280, start_y);
		glVertex2i(1280, 720);
		glVertex2i(0, 720);

	glEnd();
}


void drawShapes(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear display window

	//Set colour to black
	glColor3f(0.0, 0.0, 0.0);
	//Adjust the point size
	glPointSize(5.0);
	//Set colour to red
	glColor3f(178.0/255.0, 208/255.0, 180/255.0);

	// Draw an outlined triangle

	int night = 1;
    int road_height = 220;
    int bg_height = 70;
    int bg_mid = road_height + bg_height/2;


	sky(road_height + bg_height, night);
    back_ground(road_height, bg_height, night);
    road(road_height, night);

    houseBuilding(0, bg_mid, 300, 160, 6, 3, night);


    //glClearColor(0.0, 0.0, 0.0, 0.0);
    //glClear(GL_COLOR_BUFFER_BIT ) ;

	//circle(640, 360, 50, 0);
	//circle(670, 370, 50, 1);


    glutSwapBuffers();
	glFlush();	// Process all OpenGL routines
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);						// Initalise GLUT
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);	// Set display mode

	glutInitWindowPosition(50, 100);		// Set window position
	glutInitWindowSize(1280, 720);					// Set window size
	glutCreateWindow("An Example OpenGL Program");	// Create display window
	init();							// Execute initialisation procedure
	glutDisplayFunc(drawShapes);		// Send graphics to display window
	glutMainLoop();					// Display everything and wait

	return 0;
}

