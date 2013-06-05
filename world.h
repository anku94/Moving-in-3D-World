#ifndef world_H
#define world_H

#include "headerFiles.h"
#include "block.h"

int counter=0;
const int worldLength=70;
const int worldWidth=70;
GLBlocks block[worldLength*worldWidth];
GLBlocks objects[worldLength*worldWidth];

void drawLine(float x1, float y1, float z1, float x2, float y2, float z2){
	glBegin(GL_LINES);
	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glEnd();
}

class GLWorld{

	public :
		int choice;
		float upDown;
		float leftRight;
		float forwardBackward;
		float up;
		float down;
		float normal;
		float center;
		float udIncrement;
		float lrIncrement;
		float fbIncrement;
		float waterIncrement;
		GLuint texWall,textureId1,textureId2,textureId3,textureId4,textureId5,textureId6,textureId7,textureId8,textureId9,texSky,texPalace,texWater; //The id of the texture
	
		GLWorld(){
			normal=-10.4;
			upDown=0.0;
			leftRight=0.0;
			forwardBackward=0.0;
			udIncrement=0.4f;
			lrIncrement=0.6f;
			fbIncrement=0.6f;
			waterIncrement=0.1;
			srand(time(NULL));
			int x,z;
			for(int i=0;i<7;i++){
				for(int j=0;j<7;j++){
					for(int k=0;k<worldLength/7;k++){
						for(int l=0;l<worldWidth/7;l++){
							/* (i*(worldLength/5))+x,(j*(worldWidth/5))+z;     */
							x=(i*(worldLength/7))+k;
							z=(j*(worldWidth/7))+l;  
							block[worldWidth*x+z].posMatrix[12]=4*x;
							block[worldWidth*x+z].posMatrix[14]=4*z;
							block[worldWidth*x+z].posMatrix[13]=normal;
							if(i%2==0 && j%2==0){
								if((j%4==0&&i%4!=0)||(j%4!=0&&i%4==0)){
									if(l%5==2&&k%5==2){
										block[worldWidth*x+z].objChoice=1;
										block[worldWidth*x+z].showFlag=1;
									}else if( ( (l==1||l==9) && (k==2||k==3||k==6||k==7) ) || (k==1||k==9) && (l==2||l==3||l==6||l==7) ){
										block[worldWidth*x+z].objChoice=2;
										block[worldWidth*x+z].showFlag=1;
									}
									block[worldWidth*x+z].choice=3;
								}else{
									if(l%6==2&&k%6==2){
										block[worldWidth*x+z].choice=5;
										block[worldWidth*x+z].posMatrix[13]=normal+1.5;
									}else if(l%6==4&&k%6==4){
										block[worldWidth*x+z].choice=6;
										block[worldWidth*x+z].sendTo[0]=(((2*(i+1))%7)*(worldLength/7)+k%6+1);
										block[worldWidth*x+z].sendTo[1]=(((2*(j+1))%7)*(worldLength/7)+l%6+1);
										if(block[worldWidth*x+z].sendTo[0]>60)
											block[worldWidth*x+z].sendTo[0]=35;
										if(block[worldWidth*x+z].sendTo[1]>60)
											block[worldWidth*x+z].sendTo[1]=35;
									}else if(l%7==6&&k%7==6){
										block[worldWidth*x+z].choice=7;
									}else{
										if(l%6==1&&k%6==1){
											block[worldWidth*x+z].objChoice=1;
											block[worldWidth*x+z].showFlag=1;
										}else if(l%6==3&&k%6==2){
											block[worldWidth*x+z].objChoice=3;
											block[worldWidth*x+z].showFlag=1;
										}
										block[worldWidth*x+z].choice=4;
									}
								}
							}else if(i%2!=0 && j%2==0){
								if(j%4==0)
									block[worldWidth*x+z].dir=1;
								else
									block[worldWidth*x+z].dir=-1;

								if(((l>(worldWidth/35)&&l<4*(worldWidth/35)-1))&&(k>(worldLength/35)&&k<4*(worldLength/35)-1)){
									block[worldWidth*x+z].choice=2;
								}
							}else if(i%2 ==0 && j%2!=0){
								if(i%4==0)
									block[worldWidth*x+z].dir=1;
								else
									block[worldWidth*x+z].dir=-1;
								if(((l>(worldWidth/35)&&l<4*(worldWidth/35)-1))&&(k>(worldLength/35)&&k<4*(worldLength/35)-1)){
									block[worldWidth*x+z].choice=1;
								}
							}else if(i%2 !=0 && j%2!=0){
								if(((l>(worldWidth/35)&&l<4*(worldWidth/35)-1))&&(k>(worldLength/35)&&k<4*(worldLength/35)-1)){
									block[worldWidth*x+z].choice=4;
								}else{
									block[worldWidth*x+z].choice=0;
								}
							}

							if(x>=worldLength-10&&z>=worldWidth-10){
								if(l%6==1&&k%6==1){
									block[worldWidth*x+z].objChoice=4;
									block[worldWidth*x+z].showFlag=1;
								}
							}
						}
					}
				}
			}
		}

		~GLWorld(){
		}

		void draw(){
			int x,z,y;
			glPushMatrix();
			
			for(int i=0;i<5;i++){
				for(int j=0;j<5;j++){
					for(int k=0;k<worldLength/5;k++){
						for(int l=0;l<worldWidth/5;l++){
							/*	(i*(worldLength/5))+x,(j*(worldWidth/5))+z;     */
							x=(i*(worldLength/5))+k;
							z=(j*(worldWidth/5))+l;  
							switch(block[worldWidth*x+z].choice){
								case 0:
									glPushMatrix();
									glLoadMatrixf(block[worldWidth*x+z].posMatrix);
									glTranslatef(0,0,0);
									glGetFloatv (GL_MODELVIEW_MATRIX,block[worldWidth*x+z].posMatrix);
									glPopMatrix();
									
									glPushMatrix();
									glMultMatrixf(block[worldWidth*x+z].posMatrix);
									glPopMatrix();
									break;
								case 1:
									glPushMatrix();
									glLoadMatrixf(block[worldWidth*x+z].posMatrix);
									glTranslatef(lrIncrement*block[worldWidth*x+z].dir,0,0);
									glGetFloatv (GL_MODELVIEW_MATRIX,block[worldWidth*x+z].posMatrix);
									glPopMatrix();

									glPushMatrix();
									glMultMatrixf(block[worldWidth*x+z].posMatrix);
									glColor3f(1.0f,0.0f,0.5f);
									block[worldWidth*x+z].draw();
									glPopMatrix();
									break;
								case 2:
									glPushMatrix();
									glLoadMatrixf(block[worldWidth*x+z].posMatrix);
									glTranslatef(0,0,fbIncrement*block[worldWidth*x+z].dir);
									glGetFloatv (GL_MODELVIEW_MATRIX,block[worldWidth*x+z].posMatrix);
									glPopMatrix();

									glPushMatrix();
									glMultMatrixf(block[worldWidth*x+z].posMatrix);
									glColor3f(0.5f,1.0f,0.5f);
									block[worldWidth*x+z].draw();
									glPopMatrix();
									break;
								case 3:
									glPushMatrix();
									glLoadMatrixf(block[worldWidth*x+z].posMatrix);
									glTranslatef(0,udIncrement,0);
									glGetFloatv (GL_MODELVIEW_MATRIX,block[worldWidth*x+z].posMatrix);
									glPopMatrix();

									glPushMatrix();
									glMultMatrixf(block[worldWidth*x+z].posMatrix);
									glColor3f(0.5f,0.5f,0.5f);
									block[worldWidth*x+z].draw();
									glPopMatrix();
									break;
								case 4:
									glPushMatrix();
									glLoadMatrixf(block[worldWidth*x+z].posMatrix);
									glTranslatef(0,0,0);
									glGetFloatv (GL_MODELVIEW_MATRIX,block[worldWidth*x+z].posMatrix);
									glPopMatrix();

									glPushMatrix();
									glMultMatrixf(block[worldWidth*x+z].posMatrix);
									glColor3f(0.5f,0.0f,0.5f);
									block[worldWidth*x+z].draw();
									glPopMatrix();
									break;
								case 5:
									glPushMatrix();
									glLoadMatrixf(block[worldWidth*x+z].posMatrix);
									glTranslatef(0,0,0);
									glGetFloatv (GL_MODELVIEW_MATRIX,block[worldWidth*x+z].posMatrix);
									glPopMatrix();
									glPushMatrix();
									glMultMatrixf(block[worldWidth*x+z].posMatrix);
									glScalef(.5,4,.5);
									glColor3f(0.5f,1.0f,0.5f);
									block[worldWidth*x+z].draw();
									glPopMatrix();
									break;
								case 6:
									glPushMatrix();
									glLoadMatrixf(block[worldWidth*x+z].posMatrix);
									glTranslatef(0,0,0);
									glGetFloatv (GL_MODELVIEW_MATRIX,block[worldWidth*x+z].posMatrix);
									glPopMatrix();
									
									glPushMatrix();
									glMultMatrixf(block[worldWidth*x+z].posMatrix);
									glColor3f(0.5f,0.0f,0.5f);
									block[worldWidth*x+z].draw();
									glPopMatrix();
									break;
								case 7:
									glPushMatrix();
									glLoadMatrixf(block[worldWidth*x+z].posMatrix);
									glTranslatef(0,0,0);
									glGetFloatv (GL_MODELVIEW_MATRIX,block[worldWidth*x+z].posMatrix);
									glPopMatrix();
									
									glPushMatrix();
									glMultMatrixf(block[worldWidth*x+z].posMatrix);
									glColor3f(0.5f,1.0f,0.0f);
									block[worldWidth*x+z].draw();
									glPopMatrix();
									break;
							}
						}
					}
				}
			}
			glPopMatrix();
/*			//Draw Palace
			glColor3f(0.8f,0.8f,0.8f);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId9);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glPushMatrix();
			glTranslatef(18.0,8.0,1.0);
			glScalef(8.0,8.0,1.0);
			//Start
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-2.5f, 2.5f, -2.5f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-2.5f, -2.5f, -2.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(2.5f, -2.5f, -2.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(2.5f, 2.5f, -2.5f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(1.0,8.0,18.0);
			glScalef(1.0,8.0,8.0);
			//Start
			glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-2.5f, 2.5f, 2.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-2.5f, -2.5f, 2.5f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-2.5f, -2.5f, -2.5f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-2.5f, 2.5f, -2.5f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(18.0,8.0,1.0);
			glScalef(8.0,8.0,1.0);
			//Top
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-2.5f, 2.5f, -2.5f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-2.5f, -2.5f, -2.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(2.5f, -2.5f, -2.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(2.5f, 2.5f, -2.5f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(18.0,8.0,1.0);
			glScalef(8.0,8.0,1.0);
			//Top
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-2.5f, 2.5f, -2.5f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-2.5f, -2.5f, -2.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(2.5f, -2.5f, -2.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(2.5f, 2.5f, -2.5f);
			glEnd();
			glPopMatrix();

			glDisable(GL_TEXTURE_2D);
*/
/*
			//Draw Box texture
*/
			//Bottom
			glPushMatrix();
			glTranslatef(4*35.0f, -60.0f, 4*35.0f);
			glScalef(112.0,1.0,112.0);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texWater);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glColor3f(0.4f, 0.82f, 0.81f);
			glBegin(GL_QUADS);

			glNormal3f(0.0, 1.0f, 0.0f);
			glTexCoord2f(0.0f+waterIncrement, 0.0f-waterIncrement);
			glVertex3f(-2.5f, -2.5f, 2.5f);
			glTexCoord2f(1.0f+waterIncrement, 0.0f-waterIncrement);
			glVertex3f(2.5f, -2.5f, 2.5f);
			glTexCoord2f(1.0f+waterIncrement, 1.0f-waterIncrement);
			glVertex3f(2.5f, -2.5f, -2.5f);
			glTexCoord2f(0.0f+waterIncrement, 1.0f-waterIncrement);
			glVertex3f(-2.5f, -2.5f, -2.5f);
			glEnd();

			glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			//Top
			glPushMatrix();
			glTranslatef(4*35.0f, 400.0f, 4*35.0f);
			glScalef(112.0,1.0,112.0);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texSky);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glColor3f(0.2f, 0.2f, 0.2f);
			glBegin(GL_QUADS);

			glNormal3f(0.0, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-2.5f, -2.5f, 2.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(2.5f, -2.5f, 2.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(2.5f, -2.5f, -2.5f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-2.5f, -2.5f, -2.5f);
			glEnd();

			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
			

			// back
			glPushMatrix();
			glTranslatef(4*35.0f, 160.0f, -6*35.0f);
			glScalef(140.0,160.0,1.0);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texWall);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glColor3f(0.4f, 0.82f, 0.81f);
			glBegin(GL_QUADS);

			glNormal3f(0.0, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-2.5f, 2.5f, -2.5f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-2.5f, -2.5f, -2.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(2.5f, -2.5f, -2.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(2.5f, 2.5f, -2.5f);
			glEnd();

			glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			// left
			glPushMatrix();
			glTranslatef(-6*35.0f, 160.0f, 4*35.0f);
			glScalef(1.0,160.0,140.0);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texWall);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glColor3f(0.4f, 0.82f, 0.81f);
			glBegin(GL_QUADS);

			glNormal3f(-1.0, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-2.5f, 2.5f, 2.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-2.5f, -2.5f, 2.5f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-2.5f, -2.5f, -2.5f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-2.5f, 2.5f, -2.5f);
			glEnd();

			glDisable(GL_TEXTURE_2D);
			glPopMatrix();			
			
			// front
			glPushMatrix();
			glTranslatef(4*35.0f, 160.0f, 14*35.0f);
			glScalef(140.0,160.0,1.0);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texWall);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glColor3f(0.4f, 0.82f, 0.81f);
			glBegin(GL_QUADS);

			glNormal3f(0.0, 0.0f, 1.0f);
			glTexCoord2f(1.0f,1.0f);
			glVertex3f(-2.5f, 2.5f, 2.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-2.5f, -2.5f, 2.5f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(2.5f, -2.5f, 2.5f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(2.5f, 2.5f, 2.5f);
			glEnd();

			glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			// right
			glPushMatrix();
			glTranslatef(14*35.0f, 160.0f, 4*35.0f);
			glScalef(1.0,160.0,140.0);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texWall);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glColor3f(0.4f, 0.82f, 0.81f);
			glBegin(GL_QUADS);

			glNormal3f(1.0, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(2.5f, 2.5f, 2.5f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(2.5f, -2.5f, 2.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(2.5f, -2.5f, -2.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(2.5f, 2.5f, -2.5f);
			glEnd();

			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		}
};
#endif
