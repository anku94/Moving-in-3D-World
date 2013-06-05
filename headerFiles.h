#ifndef headerFiles_H
#define headerFiles_H

#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <assert.h>
#include <fstream>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// constants for arm and leg movement states
const int BACKWARD_STATE = 0;
const int FORWARD_STATE  = 1;

// index constants for accessing arm and leg array data
const int LEFT  = 0;
const int RIGHT = 1;
int gameFlag=0;  /* 0 going on ; 1 game over ; 2 game completed*/
GLuint _texWall,_textureId1,_textureId2,_textureId3,_textureId4,_textureId5,_textureId6,_textureId7,_textureId8,_textureId9,_texSky,_texPalace,_texWater; //The id of the texture

#endif
