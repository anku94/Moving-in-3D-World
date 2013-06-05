#ifndef camera_H
#define camera_H
#include "headerFiles.h"

class GLCamera{

	public:
	float eyeX;
	float eyeY;
	float eyeZ;
	float refX;
	float refY;
	float refZ;
	float upX;
	float upY;
	float upZ;

	GLCamera(){
	}
	
	void set(float eX,float eY,float eZ,float rX,float rY,float rZ,float uX,float uY,float uZ){
		eyeX=eX;
		eyeY=eY;
		eyeZ=eZ;
		refX=rX;
		refY=rY;
		refZ=rZ;
		upX=uX;
		upY=uY;
		upZ=uZ;		
	}
	
	~GLCamera(){
	}

	void lookAt(){
		gluLookAt(eyeX,eyeY,eyeZ,refX,refY,refZ,upX,upY,upZ);
	}
};
#endif
