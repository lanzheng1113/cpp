
//depends on glew32.lib freeglut.lib

#include <string>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/freeglut.h>
#include <math.h>
#include "shader.h"

#define PI 3.14159265
using namespace std;


void userInit();
void reshape(int w,int h);
void display( void );
void keyboardAction( unsigned char key, int x, int y );
void drawFourLine(float side,int level);
void prepareData();

//global variables
struct ShaderData {
GLuint vboId;           // vertex buffer object
GLuint vaoId;           // vertex array object
GLuint programId;       // shader program id
GLuint projMatLocId;    // projection matrix location id
GLuint viewMatLocId;    // view matrix location id
GLuint modelMatLocId;   // model matrix location id
glm::mat4 projMatrix;   // Store the projection matrix
glm::mat4 viewMatrix;   // Store the view matrix
glm::mat4 modelMatrix;  // Store the model matrix
}shader;

std::vector< glm::vec4 > vertexVec;
float prevX = 0.0f,prevY =0.0f;
int angle = 0;

float side = 3.0f;
int level = 6;



int main( int argc, char **argv )
{
	glutInit(&argc, argv);

    glutInitDisplayMode( GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "Koch Snow demo" );

    glewInit();
    userInit();
	glutReshapeFunc(reshape);
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboardAction );
    glutMainLoop();
    return 0;
}
//custom initialization
void userInit()
{
	 glClearColor( 0.0, 0.0, 0.0, 0.0 );
	 //initialize vertex data
     prepareData();
	 //create vertex array object
	 glGenVertexArrays(1,&shader.vaoId);
	 glBindVertexArray(shader.vaoId);
	 //create vertex buffer object
	 glGenBuffers(1,&shader.vboId);
	 glBindBuffer(GL_ARRAY_BUFFER, shader.vboId);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*vertexVec.size(), &vertexVec[0], GL_STATIC_DRAW);
	 glBindBuffer(GL_ARRAY_BUFFER,0);
	 //create shader
	std::vector<GLuint> idVector;
	idVector.push_back(Shader::createShader(GL_VERTEX_SHADER,"resources/vertex.glsl"));
	idVector.push_back(Shader::createShader(GL_FRAGMENT_SHADER,"resources/frag.glsl"));
	shader.programId = Shader::createProgram(idVector);
	//get matrix location
	shader.projMatLocId  = glGetUniformLocation(shader.programId, "projectionMatrix");
    shader.viewMatLocId  = glGetUniformLocation(shader.programId, "viewMatrix");
    shader.modelMatLocId = glGetUniformLocation(shader.programId, "modelMatrix");
    //set default value
    shader.viewMatrix = glm::mat4(1.0);
    shader.projMatrix =  glm::ortho(-1.0,1.0,-1.0,1.0);
    shader.modelMatrix = glm::mat4(1.0);

}
//adjust window size
void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	//set projection matrix
	glUseProgram(shader.programId);
	if (w <= h) {
         shader.projMatrix = glm::ortho(-5.0,5.0,
        		 -5.0*(GLfloat)h/(GLfloat)w,5.0*(GLfloat)h/(GLfloat)w);
	}
	else {
		shader.projMatrix = glm::ortho(-5.0*(GLfloat)w/(GLfloat)h,
				5.0*(GLfloat)w/(GLfloat)h,-5.0,5.0);
	}
	//send projection matrix to shader
	glUniformMatrix4fv(shader.projMatLocId, 1,
	    	        GL_FALSE, glm::value_ptr(shader.projMatrix));
	//send view matrix to shader
	glUniformMatrix4fv(shader.viewMatLocId, 1,
	    		        GL_FALSE, glm::value_ptr(shader.viewMatrix));
	glUseProgram(0);
}
//render callback
void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT);
	glUseProgram(shader.programId);
    glm::vec3 center = glm::vec3(side/2.0,-side/(2.0*sqrt(3.0)),0.0);
    shader.modelMatrix = glm::mat4(1.0);
     //scale at center
    shader.modelMatrix = glm::translate(shader.modelMatrix,glm::vec3(-center.x,-center.y,0.0));
    shader.modelMatrix = glm::scale(shader.modelMatrix,glm::vec3(5.0,5.0,1.0));
    shader.modelMatrix = glm::translate(shader.modelMatrix,glm::vec3(center.x,center.y,0.0));
    //put the snow's center to origin
    shader.modelMatrix = glm::translate(shader.modelMatrix,glm::vec3(-center.x,-center.y,0.0));
    glUniformMatrix4fv(shader.modelMatLocId, 1,
    		GL_FALSE, glm::value_ptr(shader.modelMatrix));
    //send data to shader
	glBindBuffer(GL_ARRAY_BUFFER,shader.vboId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,0);
   // draw line loop using vertex
	glDrawArrays(GL_LINE_LOOP, 0, vertexVec.size());

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glUseProgram(0);
	glDisableVertexAttribArray(0);
	glutSwapBuffers();
}
//keyboard callback
void keyboardAction( unsigned char key, int x, int y )
{
    switch( key )
	{
		case 033:  // Escape key
			exit( EXIT_SUCCESS );
			break;
    }
}
void drawFourLine(float side,int level)
{
	if (level == 0)
	{
		  prevX = prevX + (side/3)*cos(angle*PI / 180.0);
		  prevY = prevY + (side/3)*sin(angle*PI / 180.0);
		  vertexVec.push_back(glm::vec4(prevX,prevY,0,1));
	}
	else
	{
		drawFourLine(side/3,level-1);
		angle += 60;
		drawFourLine(side/3,level-1);
		 angle += -120;
		 drawFourLine(side/3,level-1);
		 angle += 60;
		 drawFourLine(side/3,level-1);
	}
}
//prepare snow data
void prepareData()
{

    float originX = 0,originY =0;
    vertexVec.push_back(glm::vec4(originX,originY,0,1));
    for(int i=0;i< 3;i++)
    {
    	drawFourLine(side,level);
         angle += -120;
    }
}

