#ifndef humanoid_H
#define humanoid_H

#include "camera.h"
#include "block.h"
#include "md2model.h"

MD2Model* _model;

class GLobject{
	virtual void Draw(){
		return;
	}
};

class GLHumanoid{

	public:
	GLfloat torso[16]={1,0,0,0,0,1,0,0,0,0,1,0,4,-3.0,4,1};
	GLfloat neck[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,1.75,0,1};
	GLfloat lShoulder[16]={1,0,0,0,0,1,0,0,0,0,1,0,1.25,1.25,0,1};
	GLfloat lElbow[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-0.75,0,1};
	GLfloat lWrist[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-0.75,0,1};
	GLfloat rShoulder[16]={1,0,0,0,0,1,0,0,0,0,1,0,-1.25,1.25,0,1};
	GLfloat rElbow[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-0.75,0,1};
	GLfloat rWrist[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-0.75,0,1};
	GLfloat lBottom[16]={1,0,0,0,0,1,0,0,0,0,1,0,0.75,-1.75,0,1};
	GLfloat lKnee[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-0.75,0,1};
	GLfloat lAnkle[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-0.75,0,1};
	GLfloat rBottom[16]={1,0,0,0,0,1,0,0,0,0,1,0,-0.75,-1.75,0,1};
	GLfloat rKnee[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-0.75,0,1};
	GLfloat rAnkle[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-0.75,0,1};
	GLfloat tempMatrix1[16];
	GLfloat tempMatrix2[16];
	GLfloat aheadOfTorso[16];
	char legStates[2];    
	char armStates[2];
	int score;
	float torsoXAngle;
	float torsoYAngle;
	float torsoZAngle;

	float legAngles[2];
	float armAngles[2];
	float armSpeed[2];
	float legSpeed[2];
	float roboSpeed;

	float direction;      /* -1 for +Z ; 1 for -Z    */
	float rotateAngle;
	int jumpFlag;			/*if 1 jump*/
	int drownFlag;              /*if 1 drown*/
	int state; /*0 stand ; 1 run */
	float currHeight;
	float jumpHeight;
	float jumpDir;
	float jumpSpeed;
	float currZ;
	float prevZ;
	float ground;
	int collisionFlag;
	int currentX,currentZ;
	GLCamera c1,c2,c3,c4;
	bool seize;
	time_t timer;
	int health;

	GLHumanoid(){
		health=10;
		score=0;
		state=0;
		seize=false;
		currentX=0;
		currentZ=0;
		collisionFlag=0;
		ground=-8.4;
		armAngles[LEFT] = 0.0;
		armAngles[RIGHT] = 0.0;
		legAngles[LEFT] = 0;
		legAngles[RIGHT] = 0;

		armStates[LEFT] = FORWARD_STATE;
		armStates[RIGHT] = BACKWARD_STATE;

		legStates[LEFT] = BACKWARD_STATE;
		legStates[RIGHT] = FORWARD_STATE;

		armSpeed[LEFT]=0;
		legSpeed[LEFT]=0;
		armSpeed[RIGHT]=0;
		legSpeed[RIGHT]=0;
		roboSpeed=1.0;
		direction=1;
		rotateAngle=10.0;
		currHeight=0.0;
		jumpHeight=7.0;
		jumpDir=1.0;
		jumpSpeed=1.0;
		currZ=0.0;
		prevZ=0.0;
		torsoXAngle=0.0;
		torsoYAngle=0.0;
		torsoZAngle=0.0;
		drownFlag=0;
		collisionFlag=0;

	}

	~GLHumanoid(){
		//	delete [] neck,lShoulder,rShoulder,torso,lElbow,rElbow,lWrist,rWrist,lKnee,rKnee,lAnkle,rAnkle,lBottom,rBottom;
	}

	void setCamc1(){
		glPushMatrix();
		glLoadMatrixf(torso);
		glMultMatrixf(neck);
		glTranslatef(0.0,0.85, 0.0f);
		glTranslatef(0.0f,0.4f, 0.25f);

		glPushMatrix();
		glTranslatef(0.0f,3.0f,20.0f);
		glGetFloatv (GL_MODELVIEW_MATRIX, tempMatrix1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f,0.0f,0.0f);
		glGetFloatv (GL_MODELVIEW_MATRIX, tempMatrix2);
		glPopMatrix();

		glPopMatrix();
		c1.set(tempMatrix2[12],tempMatrix2[13],tempMatrix2[14],tempMatrix1[12],tempMatrix1[13],tempMatrix1[14],0.0,1.0,0.0);

	}

	void setCamc2(){
		glPushMatrix();
		glLoadMatrixf(torso);
		glTranslatef(0.0f,0.0f,-20.0f);
		glGetFloatv (GL_MODELVIEW_MATRIX, tempMatrix1);
		glPopMatrix();
		c2.set(tempMatrix1[12],tempMatrix1[13],tempMatrix1[14],torso[12],torso[13],torso[14],0.0,1.0,0.0);
	}

	void setCamc3(){
		glPushMatrix();
		glLoadMatrixf(torso);
		glTranslatef(-20.0f,0.0f,0.0f);
		glGetFloatv (GL_MODELVIEW_MATRIX, tempMatrix1);
		glPopMatrix();
		c3.set(tempMatrix1[12],tempMatrix1[13],tempMatrix1[14],torso[12],torso[13],torso[14],0.0,1.0,0.0);
	}

	void draw(){
		glPushMatrix();
		//Body
		
		glPushMatrix();
		glLoadMatrixf(torso);
		glTranslatef(0.0f,0.0f,4.0f);
		glGetFloatv (GL_MODELVIEW_MATRIX, aheadOfTorso);
		glPopMatrix();

		glMultMatrixf(torso);
		// torso
		
		glPushMatrix();
		glColor3f(0.0f, 1.0f, 0.0f);
		glScalef(2,3,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		//neck
		glPushMatrix();
		glMultMatrixf(neck);

		glPushMatrix();
		glColor3f(1.0f, 1.0f, 0.0f);
		glScalef(0.5f,0.5f,0.5f);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		//head
		glPushMatrix();
		glTranslatef(0.0,0.85, 0.0f);

		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(1.2,1.2,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		//Nose
		glPushMatrix();
		glTranslatef(0.0f,0.0f, 0.25f);
		glColor3f(0.5f, 0.0f, 0.0f);
		glScalef(.2,.2,.2);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		//Mouth
		glPushMatrix();
		glTranslatef(0.0f,-0.4f, 0.25f);
		glColor3f(0.5f, 0.0f, 1.0f);
		glScalef(.4,.2,.2);
		glutSolidCube(1.0);
		glPopMatrix();
		//eyes

		glPushMatrix();
		glTranslatef(0.0f,0.4f, 0.25f);

		//left eye
		glPushMatrix();
		glTranslatef(0.3f,0.0f, 0.0f);
		glColor3f(0.5f, 0.0f, 1.0f);
		glScalef(.2,.2,.2);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();


		//right eye
		glPushMatrix();
		glTranslatef(-0.3f,0.0f, 0.0f);
		glColor3f(0.5f, 0.0f, 1.0f);
		glScalef(.2,.2,.2);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		glPopMatrix();

		glPopMatrix();


		glPopMatrix();	
/*------------------------------------------------------------------------------------------*/
		//left-shoulder
		glPushMatrix();
		glMultMatrixf(lShoulder);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();
		
		//arm 

		glPushMatrix();
		glTranslatef(0.5,-0.25, 0.0f);

		glPushMatrix();
		glColor3f(0.0f, 0.5f, 0.2f);
		glScalef(0.5,1,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		//elbow
		glMultMatrixf(lElbow);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		//fore-arm
		glPushMatrix();
		glTranslatef(0,-0.75, 0.0f);

		glPushMatrix();
		glColor3f(1.0f, 0.5f, 0.2f);
		glScalef(.5,1,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		//wrist
		glMultMatrixf(lWrist);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		//palm
		glPushMatrix();
		glTranslatef(0,-0.2, 0.0f);

		glPushMatrix();
		glColor3f(1.0f, 0.5f, 0.6f);
		glScalef(.8,.4,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		glPopMatrix();

		glPopMatrix();

		glPopMatrix();

		glPopMatrix();
/*-----------------------------------------------------*/
		//right-shoulder
		glPushMatrix();
		glMultMatrixf(rShoulder);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();
		
		//arm 
		glPushMatrix();
		glTranslatef(-0.5,-0.25, 0.0f);

		glPushMatrix();
		glColor3f(0.0f, 0.5f, 0.2f);
		glScalef(0.5,1,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		//elbow
		glMultMatrixf(rElbow);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		//fore-arm
		glPushMatrix();
		glTranslatef(0,-0.75, 0.0f);

		glPushMatrix();
		glColor3f(1.0f, 0.5f, 0.2f);
		glScalef(.5,1,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		//wrist
		glMultMatrixf(rWrist);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		//palm
		glPushMatrix();
		glTranslatef(0,-0.2, 0.0f);

		glPushMatrix();
		glColor3f(1.0f, 0.5f, 0.6f);
		glScalef(.8,.4,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		glPopMatrix();

		glPopMatrix();

		glPopMatrix();

		glPopMatrix();
/*---------------------------------------------------------------------------------------------------*/
		//left-leg

		glPushMatrix();
		glMultMatrixf(lBottom);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		
		
		//leg 
		glPushMatrix();
		glTranslatef(0.0,-0.75, 0.0f);

		glPushMatrix();
		glColor3f(0.0f, 0.5f, 0.2f);
		glScalef(0.5,1,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		//knee
		glMultMatrixf(lKnee);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		//fore-leg
		glPushMatrix();
		glTranslatef(0,-0.75, 0.0f);

		glPushMatrix();
		glColor3f(1.0f, 0.5f, 0.2f);
		glScalef(.5,1,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		//ankle
		glMultMatrixf(lAnkle);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		//foot
		glPushMatrix();
		glTranslatef(0,-0.45, 0.5f);

		glPushMatrix();
		glColor3f(1.0f, 0.5f, 0.6f);
		glScalef(.8,.4,1);
		glutSolidCube(1.0);
		glPopMatrix();

		glPopMatrix();

		glPopMatrix();

		glPopMatrix();

		glPopMatrix();
/*---------------------------------------------------------------------------------------------------*/
		//right-leg

		glPushMatrix();
		glMultMatrixf(rBottom);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);

		glutSolidSphere(0.5,100,100);
		glPopMatrix();
		
		//leg 
		glPushMatrix();
		glTranslatef(0.0,-0.75, 0.0f);

		glPushMatrix();
		glColor3f(0.0f, 0.5f, 0.2f);
		glScalef(0.5,1,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		//knee
		glMultMatrixf(rKnee);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		//fore-leg
		glPushMatrix();
		glTranslatef(0,-0.75, 0.0f);

		glPushMatrix();
		glColor3f(1.0f, 0.5f, 0.2f);
		glScalef(.5,1,0.5);
		glutSolidCube(1.0);
		glPopMatrix();

		//Ankle
		glMultMatrixf(rAnkle);
		glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.0f);
		glScalef(0.5,0.5,0.5);
		glutSolidSphere(0.5,100,100);
		glPopMatrix();

		//foot
		glPushMatrix();
		glTranslatef(0,-0.45, 0.5f);

		glPushMatrix();
		glColor3f(1.0f, 0.5f, 0.6f);
		glScalef(.8,.4,1.0);
		glutSolidCube(1.0);
		glPopMatrix();

		glPopMatrix();

		glPopMatrix();

		glPopMatrix();

		glPopMatrix();
/*--------------------------------------------------------------------------------------------*/
		glPopMatrix();
	}

	void move(){
		if(collisionFlag!=3){
			glPushMatrix();
			glLoadMatrixf(torso);
			glTranslatef(0.0f,0.0f,DEG2RAD(15)*direction*roboSpeed);
			glGetFloatv (GL_MODELVIEW_MATRIX, torso);
			glPopMatrix();
		}else if(collisionFlag==3){
			if(direction==-1){
				glPushMatrix();
				glLoadMatrixf(torso);
				glTranslatef(0.0f,0.0f,DEG2RAD(15)*direction*roboSpeed);
				glGetFloatv (GL_MODELVIEW_MATRIX, torso);
				glPopMatrix();
			}
		}
	}

	void rotate(){
		glPushMatrix();
		glLoadMatrixf(torso);
		glRotatef(rotateAngle,0.0f,1.0f,0.0f);
		glGetFloatv (GL_MODELVIEW_MATRIX, torso);
		glPopMatrix();
	}

	void jump(){
		printf("y of jump %f\n",torso[13]);
		if(jumpHeight==currHeight){
			jumpDir=-1.0;
		}
		currHeight+=jumpSpeed*jumpDir;
		glPushMatrix();
		glLoadMatrixf(torso);
		glTranslatef(0.0f,jumpDir*jumpSpeed,currZ-prevZ);
		prevZ=currZ;
		glGetFloatv (GL_MODELVIEW_MATRIX, torso);
		glPopMatrix();

		if(ground>=torso[13]-5.4&&jumpDir==-1.0){
			printf("hello\n");
			jumpHeight=7.0;
			jumpFlag=0;
			torso[13]=ground+5.4;
			if(state==1){
				_model->setAnimation("run");
			}else if(state==0){
				_model->setAnimation("stand");
			}
			roboSpeed=state;
		}
		move();
	}

	void drown(){
		roboSpeed=4.0;
		if(ground>=torso[13]-5.4){
			drownFlag==0;
			torso[13]=ground+5.4;
			gameFlag=1;
			roboSpeed=0.0;
		}
		glPushMatrix();
		glLoadMatrixf(torso);
		glTranslatef(0.0f,-3.0,0.0);
		glGetFloatv (GL_MODELVIEW_MATRIX, torso);
		glPopMatrix();
		move();
		move();
	}

};

#endif
