#include "stdafx.h"
// �� �Ʒ��� ��� ���� �߰�
#include "Core.h"
#include "object.h"


//------��������
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> size{ 0.1f, 0.5f };
std::uniform_real_distribution<float> cr{ 0.f, 1.f };

//------��������


///------ �Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMotion(int x, int y);
//	button (��ư �Ķ����): GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
//	state(���� �Ķ����) : GLUT_UP, GLUT_DOWN
//	x, y : �����쿡�� ���콺����ġ


GLvoid mouseWheel(int button, int dir, int x, int y);

void update_world();
void game_loop();
void init_world();

GLuint loadCubeMap(vector<string> faces);
///------ �Լ�
void main(int argc, char** argv)
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);//--- glut �ʱ�ȭ
	glutInitWindowPosition(100, 0);//--- �������� ��ġ ����
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);//--- ���÷��� ��� ����
	glutInitWindowSize(1600, 800);//--- �������� ũ�� ����
	glutCreateWindow("PM_Game");//--- ������ ���� (������ �̸�)
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) //--- glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}

	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	//glEnable(GL_MULTISAMPLE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glutSetCursor(GLUT_CURSOR_NONE);

	
	


	//--- ������ ����ϰ� �ݹ��Լ� ����
	glutDisplayFunc(drawScene);//--- ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape);//--- �ٽ� �׸��� �ݹ��Լ� ����
	
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutIdleFunc(game_loop);	// --- ���� ���� ������ �⺻ �޼��� ����
	glutMouseWheelFunc(mouseWheel);
	



	Core::Instance()->Init();//��ü �ʱ�ȭ
	glutMainLoop();//--- �̺�Ʈ ó�� ����
}

void game_loop()
{
	Core::Instance()->Progress();
}
GLvoid drawScene()
{
	
	Core::Instance()->Render();
	
}
GLvoid mouseWheel(int button, int dir, int x, int y)
{
	Core::Instance()->mouse_wheel(button, dir, x, y);
	glutPostRedisplay();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glutPostRedisplay();
}
GLvoid MouseMotion(int x, int y) {
	Core::Instance()->mouse_motion(x, y);
	glutPostRedisplay();
}
GLvoid Mouse(int button, int state, int x, int y) {
	Core::Instance()->Mouse(button, state, x, y);
	glutPostRedisplay();
}


