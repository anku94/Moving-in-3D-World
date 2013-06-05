#ifndef block_H
#define block_H

#include "headerFiles.h"
class GLBlocks{

	public:	
	int choice;
	int dir;
	GLuint textureId;          //The id of the texture
	GLfloat posMatrix[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	int sendTo[2];
	int objChoice;  /*1 for coin*/
	int showFlag;

	GLBlocks(){
		choice=0; /* 0 for noblock ; 1 for leftRight ; 2 for forwardBackward ; 3 for upDown ; 4 for normal blocks ; 5 for obstacle ; 6 for teleport ; 7 for destroying Block */
		dir=1;  /* 1 for right/up/forward  2 for left/down/backward*/
		textureId=_textureId1;
		sendTo[0]=0;
		sendTo[1]=0;
		objChoice=0;
		showFlag=0;
	}

	~GLBlocks(){
	}

	void draw(){
		switch(objChoice){
			case 1:
				if(showFlag!=0){
					glPushMatrix();
					glTranslatef(0,3, 0.0f);
					glColor3f(1.0f, 0.7f, 0.3f);
					glutSolidSphere(1,100,100);
					glPopMatrix();
				}
				break;
			case 2:

				glPushMatrix();
				glTranslatef(1.2,2.2, 1.2f);
				glColor3f(0.5f, 0.5f, 0.0f);	
				glutSolidSphere(.5,20,20);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(1.2,2.2, -1.2f);
				glColor3f(0.5f, 0.5f, 0.0f);				
				glutSolidSphere(.5,20,20);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(-1.2,2.2, -1.2f);
				glColor3f(0.5f, 0.5f, 0.0f);				
				glutSolidSphere(.5,20,20);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(-1.2,2.2, 1.2f);
				glColor3f(0.5f, 0.5f, 0.0f);
				glutSolidSphere(.5,20,20);				
				glPopMatrix();

				break;
			case 3:
				if(showFlag!=0){
					glPushMatrix();
					glTranslatef(0,3, 0.0f);
					glColor3f(0.6f, 0.04f, 0.1f);
					glutSolidCube(1);
					glPopMatrix();
				}
				break;
			case 4:
					glPushMatrix();
					glTranslatef(0,10, 0.0f);
					glScalef(4,10,4);
					glColor3f(1.0f, 1.0f, 1.0f);
					glutSolidCube(2);
					glPopMatrix();

				break;
		}

		switch(choice){
			case 1:
				glColor3f(0.57f, 0.5f, 0.31f);
						textureId=_textureId1;
				break;
			case 2:
				glColor3f(0.78f, 0.85f, 0.88f);
						textureId=_textureId2;
				break;
			case 3:
				if(objChoice==2){
					glColor3f(0.2f, 0.32f, 0.36f);
					textureId=_textureId8;
				}else{
					glColor3f(0.2f, 0.32f, 0.36f);
					textureId=_textureId3;
				}
				break;
			case 4:
				glColor3f(0.37f, 0.63f, 0.32f);
						textureId=_textureId4;
				break;
			case 5:
				glColor3f(0.47f, 0.13f, 0.56f);
						textureId=_textureId5;
				break;
			case 6:
				glColor3f(1.0f, 0.3f, 0.6f);
						textureId=_textureId6;
				break;
			case 7:
				glColor3f(0.4f, 0.4f, 1.0f);
					textureId=_textureId7;
				break;

		}	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		/*Top*/
		glBegin(GL_QUADS);

		glNormal3f(0.0, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-2.0f, 2.0f, 2.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(2.0f, 2.0f, 2.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, 2.0f, -2.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-2.0f, 2.0f, -2.0f);

		glEnd();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		
		if(choice==5){
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			//Ground
			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-4.0f, 0.125f, 4.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(4.0f, 0.125f, 4.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(4.0f, 0.125f, -4.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-4.0f, 0.125f, -4.0f);

			glEnd();
		}else{
			glBindTexture(GL_TEXTURE_2D, _textureId9);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glColor3f(0.75f, 0.65f, 0.3f);
		}

		//Bottom
		glBegin(GL_QUADS);

		glNormal3f(0.0, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-2.0f, -2.0f, 2.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(2.0f, -2.0f, 2.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, -2.0f, -2.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-2.0f, -2.0f, -2.0f);
		glEnd();

		//Right
		glBegin(GL_QUADS);
	
		glNormal3f(1.0, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2.0f, -2.0f, 2.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(2.0f, 2.0f, 2.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, 2.0f, -2.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(2.0f, -2.0f, -2.0f);

		glEnd();	

		//Left
		glBegin(GL_QUADS);

		glNormal3f(-1.0, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-2.0f, -2.0f, 2.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-2.0f, 2.0f, 2.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-2.0f, 2.0f, -2.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-2.0f, -2.0f, -2.0f);

		glEnd();	
		//Forward
		glBegin(GL_QUADS);

		glNormal3f(0.0, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-2.0f, 2.0f, 2.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(2.0f, 2.0f, 2.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, -2.0f, 2.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-2.0f, -2.0f, 2.0f);

		glEnd();

		//BackWard
		glBegin(GL_QUADS);

		glNormal3f(0.0, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-2.0f, 2.0f, -2.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(2.0f, 2.0f, -2.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, -2.0f, -2.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-2.0f, -2.0f, -2.0f);

		glEnd();
		glDisable(GL_TEXTURE_2D);
		//		glColor3f(1.0f,0.0f,0.0f);
		//		glutWireCube(4.0);
	}
};
#endif
