#include "headerFiles.h"
int windowWidth;
int windowHeight;

void renderBitmapString(float x, float y, void *font,char *string){
	char *c;
	glRasterPos2f(x, y);
	for (c=string; *c != '\0'; c++){
		glutBitmapCharacter(font, *c);
	}
}

void setOrthographicProjection(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0,windowWidth, 0,windowHeight);
	glScalef(1, -1, 1);
	glTranslatef(0, -windowHeight, 0);
	glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection(){
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void showText(int health,int score){
	char hel[50],scr[50];
	hel[0]='H';
	hel[1]='e';
	hel[2]='a';
	hel[3]='l';
	hel[4]='t';
	hel[5]='h';
	hel[6]=' ';
	hel[7]=' ';
	sprintf(scr,"Score %d ",score);
	for(int i=0;i<health;i++){
	hel[8+i]='|';
	}
	hel[8+health]='\0';
	glColor3f(0.0f,1.0f,1.0f);
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(30,30,GLUT_BITMAP_TIMES_ROMAN_24,"Arrow keys for camera");
	renderBitmapString(400,30,GLUT_BITMAP_TIMES_ROMAN_24,hel);
	renderBitmapString(800,30,GLUT_BITMAP_TIMES_ROMAN_24,scr);
	renderBitmapString(1200,30,GLUT_BITMAP_TIMES_ROMAN_24,"Esc - Quit");
	glPopMatrix();
	resetPerspectiveProjection();
}

void showWon(){
        FILE * logoFile = fopen("won", "r");
        char *line = NULL;
        int i = 300; 
        size_t len = 0;
        ssize_t read;

        //fscanf(l, "%[^\n]s", temp);
        glColor3f(0.0f, 1.0f, 1.0f);
        setOrthographicProjection();
        glPushMatrix();
        glLoadIdentity();
        while ((read = getline(&line, &len, logoFile)) != -1) {
                renderBitmapString(100, i, GLUT_BITMAP_9_BY_15, line);
                i+=10;
        }
        glPopMatrix();
        resetPerspectiveProjection();
}

void showLost(){
        FILE * logoFile = fopen("lost", "r");
        char *line = NULL;
        int i = 300; 
        size_t len = 0;
        ssize_t read;

        glColor3f(0.0f, 1.0f, 1.0f);
        setOrthographicProjection();
        glPushMatrix();
        glLoadIdentity();
        while ((read = getline(&line, &len, logoFile)) != -1) {
                renderBitmapString(115, i, GLUT_BITMAP_9_BY_15, line);
                i+=10;
        }
        glPopMatrix();
        resetPerspectiveProjection();
}
