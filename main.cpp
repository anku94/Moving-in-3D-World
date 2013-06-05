#include "humanoid.h"
#include "world.h"
#include "imageloader.h"
#include "md2model.h"
#include "text.h"
using namespace std;

// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleKeypress3(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
	
// Global Variables

float box_len = 2.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float tri_z = 0.0f;
float lastX, lastY;
float dX, dY;
float totalRX, totalRY;
float heliX = 0.05, heliY = 0.0f;
float theta = 0.0f;

int blockX,blockZ;    /* position of robot */
int tileX=0,tileZ=0;   /* position of camera */
int upKey=0,downKey=0,leftKey=0,rightKey=0;
int cameraFlag=0;
int cameraNo=2;
int initHeliX=0,initHeliY=0;
int finHeliX=0,finHeliY=0;
int heliZ=0;
int heliFlag=0;
int heliTempX,heliTempY=0;
int lastClick;

GLHumanoid robot;
GLCamera c5,tower1Cam,tower2Cam,tileCam,topCam;
GLWorld world;

void collision(GLHumanoid *robo);


//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void collision(GLHumanoid *robo){
	int tempx,tempz,colX=0,colZ=0,diff;
	time_t end;
	int flagX=0,flagZ=0;
	robo->collisionFlag=0;
	for(int x=0;x<worldLength;x++){
		for(int z=0;z<worldWidth;z++){
			if(block[worldWidth*x+z].choice==0){
				blockX=x;
				blockZ=z;

			}else{
				if((block[x*worldWidth+z].posMatrix[12]+2>=robo->torso[12]&&block[x*worldWidth+z].posMatrix[12]-2<=robo->torso[12])&&(block[x*worldWidth+z].posMatrix[14]+2>=robo->torso[14]&&block[x*worldWidth+z].posMatrix[14]-2<=robo->torso[14])){
					colX=x;
					colZ=z;
					if(robo->currentX!=colX||robo->currentZ!=colZ){
						robo->currentX=colX;
						robo->currentZ=colZ;
						time(&(robo->timer));
					}else{
						time(&(end));
						diff=difftime(end,robo->timer);
						if(diff>5){
							if(block[worldWidth*x+z].choice==7){
								robo->torso[13]-=1;
								robo->ground-=1;
								block[x*worldWidth+z].posMatrix[13]-=1;
								if(diff>8)
									block[worldWidth*x+z].choice=0;
							}
						}
					}

					if(block[x*worldWidth+z].showFlag!=0){
						switch(block[x*worldWidth+z].objChoice){
							case 1:
								block[x*worldWidth+z].showFlag=0;
								robot.score+=1000;
								break;
							case 2:
								if(robo->jumpFlag==0){
									robot.jumpFlag=1;
									robot.currHeight=0.0f;
									robot.jumpDir=1.0f;
									robot.jumpSpeed=1.0f;
									robot.currZ=0.0f;
									robot.prevZ=0.0f;
									_model->setAnimation("jump");
									robot.roboSpeed = 4.0f;
								}
								break;
							case 3:
								block[x*worldWidth+z].showFlag=0;
								robo->health-=1;
								if(robo->health<1){
									gameFlag=1;
									robo->seize=true;
									time(&(robo->timer));
									robo->health=0;
								}
								break;
						}
					}
					float bT,bC,bB,hT,hC,hB;
					bC=block[x*worldWidth+z].posMatrix[13];
					bT=bC+2;
					bB=bC-2;
					hC=robo->torso[13];
					hT=hC+3;
					hB=hC-5;
					if( ( bC>hB ) && ( bB<hB ) ){
						if(block[worldWidth*x+z].choice==5){	
							robo->collisionFlag=3;
							if(diff==3){
								diff=0;
								time(&(robo->timer));
								robo->health-=1;
								if(robo->health<1){
									gameFlag=1;
									robo->seize=true;
									time(&(robo->timer));
									robo->health=0;
								}
							}
						}else{
							robo->collisionFlag=2;
						}
					}else if(((block[x*worldWidth+z].posMatrix[13]+2<=robo->torso[13]+3&&block[x*worldWidth+z].posMatrix[13]+2.0>=robo->torso[13]-5)||(block[x*worldWidth+z].posMatrix[13]-2<=robo->torso[13]+3&&block[x*worldWidth+z].posMatrix[13]-2>=robo->torso[13]-5.0f))&&(block[worldWidth*x+z].choice==5)){
						robo->collisionFlag=3;
						if(diff==3){
							diff=0;
							time(&(robo->timer));
							robo->health-=1;
							if(robo->health<1){
								gameFlag=1;
								time(&(robo->timer));
								robo->seize=true;
								robo->health=0;
							}
						}
					}else{
						if(x>=worldLength-10&&z>=worldWidth-10){
							gameFlag=2;
							robo->seize=true;
							time(&(robo->timer));
						}
						switch(block[worldWidth*x+z].choice){

							case 1:
								robo->torso[12]+=world.lrIncrement*block[worldWidth*x+z].dir;
								robo->ground=-8.4;
								break;
							case 2:
								robo->torso[14]+=world.fbIncrement*block[worldWidth*x+z].dir;
								robo->ground=-8.4;
								break;
							case 3:
								robo->torso[13]+=world.udIncrement;
								robo->ground=-8.4+world.upDown;
								break;
							case 4:
								robo->ground=-8.4;
								break;
							case 5:
								robo->ground=-8.4;
								break;
						}
						if(block[worldWidth*x+z].choice==6){
							printf("check x z %d %d\n",block[worldWidth*x+z].sendTo[0],block[worldWidth*x+z].sendTo[1]);
							robo->torso[12]=block[worldWidth*block[worldWidth*x+z].sendTo[0]+block[worldWidth*x+z].sendTo[1]].posMatrix[12];
							robo->torso[14]=block[worldWidth*block[worldWidth*x+z].sendTo[0]+block[worldWidth*x+z].sendTo[1]].posMatrix[14];
						}
						robo->collisionFlag=1;
					}
				}
			}
		}
	}

	if(robo->collisionFlag!=1&&robo->jumpFlag!=1&&robo->collisionFlag!=3){
		robo->drownFlag=1;
		robo->seize=true;
		robo->jumpFlag=0;
		robo->ground=-65.4f;
		time(&(robo->timer));
	}else if(robo->collisionFlag==2&&robo->jumpFlag==1){
		robo->drownFlag=1;
		robo->seize=true;
		robo->jumpFlag=0;
		robo->ground=-65.4f;
		time(&(robo->timer));
	}
	return;	
}

void spotlight(float x,float y,float z){
	float pos[] = {10, 30, 30, 0};
	float white[] = {1, 1, 1, 1};
	GLfloat lightpos[] ={x, y, z, 1.0};
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glEnable(GL_LIGHT0);
}

void activeFunc(int x, int y){
	float cX, cY;
	cX = 2*(x - windowWidth/2.0)/windowWidth;
	cY = 2*(y - windowHeight/2.0)/windowHeight;
	if(lastClick == GLUT_LEFT_BUTTON){
		dX = cX - lastX;
		dY = cY - lastY;
		totalRX -= totalRX>360?360.0f:0.0f;
		totalRY -= totalRY>360?360.0f:0.0f;
	}
}

int main(int argc, char **argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	windowWidth = w ;
	windowHeight = h ;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0,0);

	glutCreateWindow("------Adventurous 3D World-------");  // Setup the window
	initRendering();
	world.texWater= _texWater; //The id of the texture
	world.textureId1= _textureId1; //The id of the texture
	world.textureId2= _textureId2; //The id of the texture
	world.textureId3= _textureId3; //The id of the texture
	world.textureId4= _textureId4; //The id of the texture
	world.textureId5= _textureId5; //The id of the texture
	world.textureId6= _textureId6; //The id of the texture
	world.textureId7= _textureId7; //The id of the texture
	world.textureId8= _textureId8; //The id of the texture
	world.textureId9= _textureId9; //The id of the texture
	world.texSky= _texWater; //The id of the texture
	world.texPalace= _texPalace; //The id of the texture
	world.texWall= _texWall; //The id of the texture

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutSpecialUpFunc(handleKeypress3);
	glutMouseFunc(handleMouseclick);
	glutMotionFunc(activeFunc);
	glutReshapeFunc(handleResize);
	glutTimerFunc(100, update, 0);
	glutMainLoop();
	return 0;
}

// Function to draw objects on the screen
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	if(cameraNo==1){
		robot.setCamc1();
		robot.c1.lookAt();
	}else if(cameraNo==2){
		robot.setCamc2();
		robot.c2.lookAt();
	}else if(cameraNo==3){
		robot.setCamc3();
		robot.c3.lookAt();
	}else if(cameraNo==4){
		c5.set(robot.torso[12],robot.torso[13],robot.torso[14]+15.0f,robot.torso[12],robot.torso[13],robot.torso[14],0.0f,1.0f,0.0f);
		c5.lookAt();
	}else if(cameraNo==5){
		tower1Cam.set(-130.0,238.0,-130.0,2*worldLength,0.0,2*worldWidth,0.0f,1.0f,0.0f);
		tower1Cam.lookAt();	
	}else if(cameraNo==6){
		tower2Cam.set(2*worldLength,100.0,2*worldWidth,robot.torso[12],robot.torso[13],robot.torso[14],0.0f,1.0f,0.0f);
		tower2Cam.lookAt();	
	}else if(cameraNo==7){
		topCam.set(2*worldLength,360.0,2*worldWidth,2*worldLength,0.0,2*worldWidth,0.0f,0.0f,1.0f);
		topCam.lookAt();
	}else if(cameraNo==8){
		tileCam.set(block[tileX*worldWidth+tileZ].posMatrix[12],block[tileX*worldWidth+tileZ].posMatrix[13]+3,block[tileX*worldWidth+tileZ].posMatrix[14],block[tileX*worldWidth+tileZ].posMatrix[12]+tri_x,block[tileX*worldWidth+tileZ].posMatrix[13]+tri_y,block[tileX*worldWidth+tileZ].posMatrix[14]-10+tri_z,0.0f,1.0f,0.0f);
		tileCam.lookAt();
	}else if(cameraNo==9){
		glTranslatef(tri_x,tri_y,-20+heliZ);
		if(heliFlag==2){
			heliTempX+=90*(finHeliX-initHeliX)/1400;
			heliTempY+=90*(finHeliY-initHeliY)/800;
		}
		heliTempX%=360;
		heliTempY%=360;
		glRotatef(totalRX + 50*dX,0.0f,1.0f,0.0f);
		glRotatef(totalRY + 50*dY,1.0f,0.0f,0.0f);
	}
	if(robot.drownFlag==0&&robot.seize==false)	{
		collision(&robot);
	}
	spotlight(robot.torso[12]+10.0,40.0,robot.torso[14]+10.0);
	showText(robot.health,robot.score);
	if(gameFlag==1)
	showLost();
	else if(gameFlag==2)
	showWon();
	glColor3f(1,0,0);
	drawLine(0,0,0,10,0,0);
	glColor3f(0,1,0);
	drawLine(0,0,0,0,10,0);
	glColor3f(0,0,1);
	drawLine(0,0,0,0,0,10);
	glColor3f(0.5,0,0.5);
	glutSolidCube(1.0);

	glPushMatrix();
	glTranslatef(4*(worldLength),0.0,4*(worldWidth));
	glColor3f(1,0,0);
	drawLine(0,0,0,10,0,0);
	glColor3f(0,1,0);
	drawLine(0,0,0,0,10,0);
	glColor3f(0,0,1);
	drawLine(0,0,0,0,0,10);
	glColor3f(0.5,0.5,0.5);
	glutSolidCube(1.0);
	
	glPopMatrix();
	
	// Draw World
	glPushMatrix();
	world.draw();
	glPopMatrix();

	// Draw Humanoid
	glPushMatrix();
//	robot.draw();
	if(_model!=NULL){
		glPushMatrix();
		glMultMatrixf(robot.torso);
		glTranslatef(0,-0.4,-0.6);
		glRotatef(90.0,0,1,0);
		glRotatef(-90.0,1,0,0);
		_model->draw();
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {
	int diff;
	time_t end;
	if(gameFlag!=0){
		time(&(end));
		diff=difftime(end,robot.timer);
		if(diff>5)
		handleKeypress1(27, 0, 0);
	}
	
	if(_model!=NULL){
		_model->advance(0.2f);
	}
	if(robot.seize==false){
		if(robot.jumpFlag==1)
			robot.jump();
		robot.move();
		if(robot.state!=0)
			robot.score+=10;
		robot.roboSpeed -= 0.1f;
		if(robot.roboSpeed < 0.0f)
			robot.roboSpeed = 0.0f;
	}
	if(robot.seize==true&&robot.state!=3){
		robot.state=3;
		if(_model!=NULL){
			_model->setAnimation("pain");
		}
	}
	if(robot.drownFlag==1)
		robot.drown();
	if(robot.roboSpeed>=0.6&&robot.state==0&&robot.jumpFlag==0){
		robot.state=1;
		if(_model!=NULL){
			_model->setAnimation("run");
		}
	}
	if(robot.roboSpeed<0.6&&robot.state==1&&robot.jumpFlag==0){
		robot.state=0;
		if(_model!=NULL){
			_model->setAnimation("stand");
		}
	}
	if(world.waterIncrement==0.5)
		world.waterIncrement+=0.0;
	world.waterIncrement+=0.01;
	
	if(world.upDown>=4.0f){
		world.udIncrement=-0.4f;
	}else if(world.upDown<=-4.0f){
		world.udIncrement=0.4f;
	}
	world.upDown+=world.udIncrement;
	
	if(world.leftRight>=12.0){
		world.lrIncrement=-0.6;
	}else if(world.leftRight<=-12.0){
		world.lrIncrement=0.6;
	}
	world.leftRight+=world.lrIncrement;

	if(world.forwardBackward>=12.0){
		world.fbIncrement=-0.6;
	}else if(world.forwardBackward<=-12.0f){
		world.fbIncrement=0.6f;
	}
	world.forwardBackward+=world.fbIncrement;

	glutTimerFunc(30, update, 0.0);
}

// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_LIGHTING);        // Enable lighting
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	Image* imgWall = loadBMP("wall.bmp");
	_texWall = loadTexture(imgWall);
	delete imgWall;

	Image* image1 = loadBMP("1.bmp");
	_textureId1 = loadTexture(image1);
	delete image1;

	Image* image2 = loadBMP("2.bmp");
	_textureId2 = loadTexture(image2);
	delete image2;

	Image* image3 = loadBMP("3.bmp");
	_textureId3 = loadTexture(image3);
	delete image3;

	Image* image4 = loadBMP("4.bmp");
	_textureId4 = loadTexture(image4);
	delete image4;

	Image* image5 = loadBMP("5.bmp");
	_textureId5 = loadTexture(image5);
	delete image5;
	
	Image* image6 = loadBMP("6.bmp");
	_textureId6 = loadTexture(image6);
	delete image6;
	
	Image* image7 = loadBMP("7.bmp");
	_textureId7 = loadTexture(image7);
	delete image7;
	
	Image* image8 = loadBMP("8.bmp");
	_textureId8 = loadTexture(image8);
	delete image8;
	
	Image* image9 = loadBMP("9.bmp");
	_textureId9 = loadTexture(image9);
	delete image9;

	Image* imgWater = loadBMP("water.bmp");
	_texWater = loadTexture(imgWater);
	delete imgWater;
	
	Image* imgSky = loadBMP("sky.bmp");
	_texSky = loadTexture(imgSky);
	delete imgSky;
	
	Image* imgPalace = loadBMP("palace.bmp");
	_texPalace = loadTexture(imgPalace);
	delete imgPalace;
	
	_model =MD2Model::load("zombie.md2","zombie.bmp");
	if(_model!=NULL){
		_model->setAnimation("stand");
	}
	GLfloat light1_ambient[] = {0.4, 0.4, 0.4, 1.0};
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0_ambient);
	GLfloat light1_diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat light1_pos[] = {-10.0f, 15.5f, 10.0f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glEnable(GL_LIGHT1);
}

// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		if(gameFlag==1){
			printf("---------------------\n");
			printf("---------------------\n");
			printf("-------You Lose------\n");
			printf("---------------------\n");
			printf("---------------------\n");
		}
		else if(gameFlag==2){
			printf("---------------------\n");
			printf("---------------------\n");
			printf("-------You Win-------\n");
			printf("---------------------\n");
			printf("---------------------\n");
		}
		exit(0);     // escape key is pressed
	}
	if(key==100){
		glPushMatrix();
		glLoadMatrixf(robot.torso);
		glRotatef(20.0f,0.0,1.0,0.0);
		glGetFloatv (GL_MODELVIEW_MATRIX, robot.torso);
		glPopMatrix();
	}
	if(key==99){      /* c */
		if(cameraFlag==1)
			cameraFlag=0;
		else if(cameraFlag==0)
			cameraFlag=1;
	}
	if(key==32||key==106){   /*spc or j*/
		if(robot.jumpFlag==0&&robot.drownFlag==0){
			robot.jumpFlag=1;
			robot.currHeight=0.0f;
			robot.jumpDir=1.0f;
			robot.jumpSpeed=1.0f;
			robot.currZ=0.0f;
			robot.prevZ=0.0f;
			_model->setAnimation("jump");
			robot.roboSpeed = 4.0f;
		}
	}
	if(key==113){              /*   q  */
	    if(cameraFlag==1)
		    tri_x+=1;
    }
    if(key==119){  /*w*/
		if(cameraFlag==1)
			tri_x-=1;
    }
    if(key==97){ 	/*a*/
		if(cameraFlag==1)
			tri_y+=1;
    }
    if(key==115){		/*s*/
		if(cameraFlag==1)
			tri_y-=1;
    }
    if(key==122){		/*z*/
		if(cameraFlag==1)
			tri_z+=1;
    }
    if(key==120){   	/*x*/
		if(cameraFlag==1)
			tri_z-=1;
    }
    if(key==101){   	/*e*/
	    tri_x=0;
	    tri_y=0;
	    tri_z=0;
	    cameraNo%=9;
	    cameraNo++;
    }
}

void handleKeypress2(int key, int x, int y) {

	if (key == GLUT_KEY_LEFT){
		leftKey=1;
		if(robot.drownFlag==0){
			if(cameraFlag==0){
				if(robot.seize==false){
					if(robot.collisionFlag!=3){
						robot.rotateAngle=10.0f;
						robot.rotate();
					}
				}
			}else{
				if(cameraNo==8){
					if(tileX>4)
					tileX-=4;
				}
			}
		}
	}else if (key == GLUT_KEY_RIGHT){
		rightKey=1;
		if(robot.drownFlag==0){
			if(cameraFlag==0){
				if(robot.seize==false){
					if(robot.collisionFlag!=3){
						robot.rotateAngle=-10.0f;
						robot.rotate();
					}
				}
			}else{
				if(cameraNo==8){
					if(tileX<worldLength-4)
					tileX+=4;
				}
			}
		}
	}else if (key == GLUT_KEY_UP){
		upKey=1;
		if(robot.drownFlag==0){
			if(cameraFlag==0){
				if(robot.seize==false){
					robot.rotateAngle=0.0f;
					robot.direction=1.0;
					if(robot.jumpFlag==0){
						if(robot.roboSpeed < 3.0f)
							robot.roboSpeed += 0.5f;
						else
							robot.roboSpeed = 3.0f;

					}else if(robot.jumpFlag==1){
						robot.currZ+=0.3;
					}
				}
			}else{
				if(cameraNo==8){
					if(tileZ>4)
						tileZ-=4;
				}
			}
		}
	}else if (key == GLUT_KEY_DOWN){
		downKey=1;
		if(robot.drownFlag==0){
			if(cameraFlag==0){
				if(robot.seize==false){
					robot.rotateAngle=0.0f;
					robot.direction=1.0;
					if(robot.jumpFlag==0){
						if(robot.roboSpeed > 0.0f){
							robot.roboSpeed -= 0.5f;
						}else{
							robot.roboSpeed = 0.0f;
							if(robot.collisionFlag==3){	
								robot.direction=-1.0;
								robot.roboSpeed = 0.5f;
							}
						}
					}else if(robot.jumpFlag==1){
						robot.currZ-=0.3;
					}
				}
			}else{
				if(cameraNo==8){
					if(tileZ<worldWidth-4)
					tileZ+=4;
				}
			}
		}
	}
}

void handleKeypress3(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT){
		leftKey=-1;
	}else if (key == GLUT_KEY_RIGHT){
		rightKey=-1;
	}else if (key == GLUT_KEY_UP){
		upKey=-1;
	}else if (key == GLUT_KEY_DOWN){
		downKey=-1;
	}
}

void handleMouseclick(int button, int state, int x, int y) {

	printf("HF:: %d\n", heliFlag);
	lastClick = button;
	lastX = 2*(x-windowWidth/2.0)/windowWidth;
	lastY = 2*(y-windowHeight/2.0)/windowHeight;
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_UP){
			totalRX += 50*dX;
			totalRY += 50*dY;
			dX = 0;
			dY = 0;
		}
	}
	if (state == GLUT_DOWN&&heliFlag==0){
		if (button == GLUT_LEFT_BUTTON){
			initHeliX=x;
			initHeliY=y;
			heliFlag=1;
		}else if (button == GLUT_RIGHT_BUTTON){
			theta -= 15.0;
		}
	}else if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		finHeliX = x;
		finHeliY = y;
		heliFlag = 2;
		printf("Helis --> %f %f\n", finHeliX, finHeliY);
	}else if (state == GLUT_UP&&heliFlag==1){
		if (button == GLUT_LEFT_BUTTON){
			finHeliX=x;
			finHeliY=y;
			heliFlag=2;
		}else if (button == GLUT_RIGHT_BUTTON){
			theta -= 15.0;
		}
	}
	if (button==3){
		heliZ+=1;
	}else if (button==4){
		heliZ-=1;
	}
}
