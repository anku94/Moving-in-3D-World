#ifndef block_H
#define block_H

#include "headerFiles.h"

class GLObjects{
	public:	
	int choice;
	int dir;
	GLuint textureId;          //The id of the texture
	GLfloat posMatrix[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};

	GLObjects(){
		choice=0; /* 0 for noObject ; 1 for Coins ; 2 for life ; 3 for  ; 4 for normal blocks ; 5 for obstacle ; 6 for teleport */
		dir=1;  /* 1 for right/up/forward  2 for left/down/backward*/
	}

	~GLObjects(){
	}

	void draw(){
		switch(choice){
			case 1:
				glColor3f(0.57f, 1.0f, 0.31f);
				break;
			case 2:
				glColor3f(1.0f, 0.5f, 0.88f);
				break;
	}
		glutSolidSphere(0.5,100,100);
	}
};
#endif
