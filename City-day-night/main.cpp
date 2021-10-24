#include<windows.h>
#include <GL/glut.h>
#include<bits/stdc++.h>

using namespace std;

#define MAX_HEIGHT 720
#define MAX_WIDTH 1280

// ************ ALL GLOBAL VARIABLES *****************

int night = 0;
int road_height = 220;
int bg_height = 70;
int bg_mid = road_height + bg_height/2;

vector<int>random[20];
void randomVectorGeneration(){
    for(int i=0; i<20; i++){
        for(int j=0; j<500; j++){
            random[i].push_back(rand()%2);
        }
    }
}


// *********************** BUILDIN SECTION *****************************

void bringWindows(int x1, int y1, int height, int width, int row, int column,  int night, int id){

    int i, j, stx, sty;

    float distx = (float)width/((float)column*2.0 + 1.0);
    float disty = (float)height/((float)row*2.0 + 1.0);
    float window_length = min(distx, disty);

    glColor3f(1.0, 1.0, 1.0);
    for(i = 1; i <= column; i++){
        for(j = 1; j <= row; j++){

            if(night){
                int radom = (i+j+id)%2;
                if(radom){
                    glColor3ub(255, 255, 153);
                }
                else{
                    glColor3f(0.0, 0.0, 0.0);
                }
            }
            else glColor3f(1.0, 1.0, 1.0);

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


/*
    (x1, y1) bottom left location
    height = building height
    width = building width
    row = number of window in row
    column = number of window in column
    night = is night
*/

void houseBuilding(int x1, int y1, int height, int width, int row, int column,  int night, int id){

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

    bringWindows(x1, y1, height, width, row, column, night, id);

}

void bringAllBuilding(){

    houseBuilding(0, bg_mid, 270, 160, 5, 3, night,1);
    houseBuilding(80, bg_mid, 200, 160, 4, 3, night,2);

    houseBuilding(300, bg_mid, 300, 160, 6, 3, night,3);

    houseBuilding(550, bg_mid, 250, 150, 5, 3, night,4);
    houseBuilding(630, bg_mid, 200, 180, 5, 4, night,5);

    houseBuilding(900, bg_mid, 300, 160, 6, 3, night,6);
    houseBuilding(970, bg_mid, 200, 180, 5, 4, night,7);
}


// ********************** BUILDING END ************************

// ********************** SKY + BG + ROAD Back Ground*********************

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
    double stripe_width = 16.0;
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

// ********************* BG END ***************************


// Set color before calling this
// glColor3ub(0, 0, 102);

void circle(int x, int y, int radious){

   float th;
   glBegin(GL_POLYGON);

   for(int i=0;i<360;i++){
       th=i*(3.1416/180);
       glVertex2f(x+radious*cos(th),y+radious*sin(th));
   }
   glEnd();
}


float counter = 0;
float x = -250;
float y = 70;

void carAnimation(){

    //Bottom Part
    //glLoadIdentity();

    float car_length = 250;
    float car_width = 70;
    float padding_top = car_length/4.0;
    float padding_bottom = car_length/8.0;
    float padding_circle = car_length/6.0;

    counter=counter+0.03;
    x = x+2;
    if(x>1280) x = -40;
    //cout<<x<<endl;
    //glTranslated(counter,y,0.0);
    //glScaled(0.1,0.1,0.0);

    glColor3ub(1, 146, 189);
    //glColor3ub(100, 106, 108);

    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x+car_length, y);
        glVertex2f(x+car_length, y+car_width);
        glVertex2f(x, y+car_width);
    glEnd();

     //Top Part
    glBegin(GL_POLYGON);
        glVertex2f(x+padding_bottom, y+car_width);
        glVertex2f(x+car_length-padding_bottom, y+car_width);
        glVertex2f(x+car_length-padding_top, y+car_width+car_width/2.0);
        glVertex2f(x+padding_top, y+car_width+car_width/2.0);

    glEnd();

    glColor3ub(0, 0, 0);
    circle(x+padding_circle, y,20);
    circle(x+car_length-padding_circle, y, 20);
}

float sun_x = 500;
float sun_y = 600;

void sun(){

    glColor3ub(0, 0, 0);
    circle(sun_x, sun_y, 41);

    glColor3ub(255, 255, 0);
    circle(sun_x, sun_y, 40);
}



// keyboard entry function
void my_keyboard(unsigned char key, int x, int y){

	switch (key) {

		case 'n':
		    night = 1;
			break;

		case 'd':
		    night = 0;
			break;

		case 's':
			 //glutIdleFunc(NULL);
			 break;

	  default:
			break;
	}
}

void drawShapes(void){

	glClear(GL_COLOR_BUFFER_BIT);	// Clear display window

	sky(road_height + bg_height, night);
	sun();
    back_ground(road_height, bg_height, night);
    road(road_height, night);

    bringAllBuilding();


    //glClearColor(0.0, 0.0, 0.0, 0.0);
    //glClear(GL_COLOR_BUFFER_BIT ) ;

	//circle(640, 360, 50, 0);
	//circle(670, 370, 50, 1);
    //circle(100,100,50);

    carAnimation();

    Sleep(1000/60);
    glutSwapBuffers();
	glFlush();	// Process all OpenGL routines
}


void init(void){

	glClearColor(1.0, 1.0, 1.0, 0.0);	// Set display window colour to white

	glMatrixMode(GL_PROJECTION);		// Set projection parameters
    glLoadIdentity();

	gluOrtho2D(0.0, 1280.0, 0.0, 720.0);

    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char* argv[]){

    randomVectorGeneration();
	glutInit(&argc, argv);						// Initalise GLUT
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);	// Set display mode

	glutInitWindowPosition(50, 100);		// Set window position
	glutInitWindowSize(1280, 720);					// Set window size
	glutCreateWindow("Day and Night");	// Create display window
	init();							// Execute initialisation procedure
	glutDisplayFunc(drawShapes);		// Send graphics to display window
	glutIdleFunc(drawShapes);
	glutKeyboardFunc(my_keyboard);
	glutMainLoop();					// Display everything and wait

	return 0;
}

