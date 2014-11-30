
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "maze.h"

using namespace std;


bool initMaze(int argc, char **argv );
void displayMaze();
void drawCell(int i,int j);
void drawCellBorder(int i,int j);
void userInit();
void reshape(int w,int h);
void display( void );
void keyboardAction( unsigned char key, int x, int y );
void moveStep(int id);
//全局变量
Maze g_maze;
bool g_bsuccess;
bool g_bFinished;
bool g_bPause;
pair<list<Pos2D>,list<Pos2D>> g_resultPair;
int g_mazeSize = 220;
Pos2D g_curPos;

int main( int argc, char **argv )
{
	if(!initMaze(argc, argv ))
	{
		std::cerr<<"Initialize Maze failed."<<std::endl;
		return 0;
	}
	glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "2D Maze Demo-CSDN wangdingqiaoit" );

    glewInit();
    userInit();
	glutReshapeFunc(reshape);
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboardAction );
	glutTimerFunc(800,moveStep,1);
    glutMainLoop();
    return 0;
}
//自定义初始化函数
void userInit()
{
	 glClearColor( 0.0f, 0.2f, 0.1f, 0.0f );
	 g_bPause = true;
}
//定时函数
void moveStep(int id)
{
	static bool first = true;
	static std::list<Pos2D>::iterator it;
	if(g_bPause)
	{
		glutTimerFunc(800,moveStep,1);
		return;
	}
	if(first)
	{
		g_bsuccess = g_maze.getoutOfMaze3(g_resultPair);
		it = g_resultPair.second.begin();
		first = false;
		g_bFinished = false;
	}
	if(it != g_resultPair.second.end())
	{
		g_curPos = *it++;
		glutPostRedisplay();
		glutTimerFunc(800,moveStep,1);
	}
	else
	{
		g_bFinished = true;
		glutPostRedisplay();
	}
}
void drawCellBorder(int i,int j)
{
	int cell_width  = g_mazeSize / g_maze.colCnt;
	int cell_height = g_mazeSize / g_maze.rowCnt;
	//绘制边界虚框
	glPushMatrix();
		glBegin(GL_LINE_STRIP);
			glVertex2i(j*cell_width,-i*cell_height);
			glVertex2i(j*cell_width,-(i+1)*cell_height);
			glVertex2i((j+1)*cell_width,-(i+1)*cell_height);
			glVertex2i((j+1)*cell_width,-i*cell_height);
			glVertex2i(j*cell_width,-i*cell_height);
			glVertex2i(j*cell_width,-i*cell_height);
		glEnd();
	glPopMatrix();
}
void drawCell(int i,int j)
{
	int cell_width  = g_mazeSize / g_maze.colCnt;
	int cell_height = g_mazeSize / g_maze.rowCnt;
	int xPos = (2*j+1)*cell_width/2;
	int yPos = -(2*i+1)*cell_height/2;
	int offset = 1;
	glPushMatrix();
	    glTranslatef(xPos,yPos,0.0f);
	    glScalef(cell_width-offset,cell_height-offset,1.0);
	    glutSolidCube(1.0);
	glPopMatrix();
}
void displayMaze()
{
	for(int i =0;i<g_maze.rowCnt;++i)
		for(int j=0;j<g_maze.colCnt;j++)
		{
			char ch = g_maze.cellArray[i*g_maze.colCnt+j].content;
			switch(ch)
			{
				case Maze::BLOCKED_CONTENT:
					glColor3f(0.5f,0.25f,0.0f); //非通道
					break;
				case Maze::EXIT_CONTENT:	//出口
				    glColor3f(1.0f,1.0f,0.0f);
					break;
				default:
					glColor3f(1.0f,1.0f,1.0f); //入口、已经访问点、通道
					break;
			}
			//绘制单元格
			drawCell(i,j);
			//绘制边界虚框
			glColor3f(0.0f,0.0f,0.8f);
			drawCellBorder(i,j);
		}
	//绘制当前位置
	int i = g_curPos.row,j = g_curPos.col;
	glColor3f(0.0f,1.0f,0.0f);
	drawCell(i,j);
   //绘制入口点
	i = g_maze.startPos.row,j = g_maze.startPos.col;
	glColor3f(1.0f,0.0f,0.0f);
	drawCell(i,j);
	//结束时绘制整个路径
	if(g_bFinished && g_bsuccess)
	{
		g_resultPair.first.pop_front();
		g_resultPair.first.pop_back();
		glColor3f(0.0f,1.0f,1.0f);
		for(Pos2D& pos : g_resultPair.first)
		{
			i = pos.row,j = pos.col;
			drawCell(i,j);
		}
	}
}
//绘制回调函数
void display( void )
{
    glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	    glTranslatef(-g_mazeSize/2.0,g_mazeSize/2.0,0.0);
		displayMaze();
	glPopMatrix();
	glutSwapBuffers();
}
//调整窗口大小回调函数
void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-g_mazeSize/2, g_mazeSize/2,
		-g_mazeSize/2*(GLfloat)h/(GLfloat)w,g_mazeSize/2*(GLfloat)h/(GLfloat)w,-1,1);
    else
		glOrtho(-g_mazeSize/2*(GLfloat)w/(GLfloat)h,
		g_mazeSize/2*(GLfloat)w/(GLfloat)h, -g_mazeSize/2,g_mazeSize/2,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//键盘按键回调函数
void keyboardAction( unsigned char key, int x, int y )
{
    switch( key )
	{
		case 033:  // Escape key
			exit( EXIT_SUCCESS );
			break;
		case 32:
			g_bPause = !g_bPause;
			break;
    }
}
//初始化迷宫
bool initMaze(int argc, char **argv )
{
	string mapFileName;
	if (argc == 2)
	{
		mapFileName = string(argv[1]);
	}
	else
	{
		std::cout<<"input maze map file name: "<<std::endl;
		std::cin >> mapFileName;
	}
	ifstream mapStream;
	mapStream.open(mapFileName.c_str());
	if(!mapStream)
	{
		std::cerr<<" Could not open stream "<<mapFileName<<" for reading."<<std::endl;
		return false;
	}
	g_maze.initializeMap(mapStream);
	g_curPos = g_maze.startPos;
	return true;
}
