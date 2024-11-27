#include "stdafx.h"
// 요 아래에 헤더 파일 추가

#include "KeyManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "Core.h"
#include "Model.h"
#include "TimeManager.h"
#include "TextureLoadManager.h"
#include "Shader.h"
#include "ShaderManager.h"

//------전역변수
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> size{ 0.1f, 0.5f };
std::uniform_real_distribution<float> cr{ 0.f, 1.f };

//------전역변수

//bool firstMouse = true;
//float lastX = 400, lastY = 400;


//CameraManager* g_camera = nullptr;
//
//float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
//	// positions   // texCoords
//	-1.0f,  1.0f,  0.0f, 1.0f,
//	-1.0f, -1.0f,  0.0f, 0.0f,
//	 1.0f, -1.0f,  1.0f, 0.0f,
//
//	-1.0f,  1.0f,  0.0f, 1.0f,
//	 1.0f, -1.0f,  1.0f, 0.0f,
//	 1.0f,  1.0f,  1.0f, 1.0f
//};
//// positions all containers
//glm::vec3 cubePositions[] = {
//	glm::vec3(0.0f,  0.0f,  0.0f),
//	glm::vec3(2.0f,  5.0f, -15.0f),
//	glm::vec3(-1.5f, -2.2f, -2.5f),
//	glm::vec3(-3.8f, -2.0f, -12.3f),
//	glm::vec3(2.4f, -0.4f, -3.5f),
//	glm::vec3(-1.7f,  3.0f, -7.5f),
//	glm::vec3(1.3f, -2.0f, -2.5f),
//	glm::vec3(1.5f,  2.0f, -2.5f),
//	glm::vec3(1.5f,  0.2f, -1.5f),
//	glm::vec3(-1.3f,  1.0f, -1.5f)
//};
//// positions of the point lights
//glm::vec3 pointLightPositions[] = {
//	glm::vec3(0.7f,  0.2f,  2.0f),
//	glm::vec3(2.3f, -3.3f, -4.0f),
//	glm::vec3(-4.0f,  2.0f, -12.0f),
//	glm::vec3(0.0f,  0.0f, -3.0f)
//};
//
//float skyboxVertices[] = {
//	// positions          
//	-1.0f,  1.0f, -1.0f,
//	-1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//	 1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//
//	-1.0f, -1.0f,  1.0f,
//	-1.0f, -1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f,  1.0f,
//	-1.0f, -1.0f,  1.0f,
//
//	 1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//
//	-1.0f, -1.0f,  1.0f,
//	-1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f, -1.0f,  1.0f,
//	-1.0f, -1.0f,  1.0f,
//
//	-1.0f,  1.0f, -1.0f,
//	 1.0f,  1.0f, -1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	-1.0f,  1.0f,  1.0f,
//	-1.0f,  1.0f, -1.0f,
//
//	-1.0f, -1.0f, -1.0f,
//	-1.0f, -1.0f,  1.0f,
//	 1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//	-1.0f, -1.0f,  1.0f,
//	 1.0f, -1.0f,  1.0f
//};
//vector<std::string> faces
//{
//	"resources/skybox/right.png",
//	"resources/skybox/left.png",
//	"resources/skybox/top.png",
//	"resources/skybox/bottom.png",
//	"resources/skybox/front.png",
//	"resources/skybox/back.png"
//};
//// first, configure the cube's VAO (and VBO)
//unsigned int VBO, cubeVAO,cubeVBO;
//unsigned int lightCubeVAO;
//unsigned int quadVAO, quadVBO;
//unsigned int planeVAO, planeVBO;
//unsigned int skyboxVAO, skyboxVBO;
//GLuint fbo;
//GLuint rbo;
//GLuint screenTextureColorBuffer;
//
//
////Shader stencilShader;
////Shader stencilSingleColorShader;
////Shader lightCubeShader;
////Shader ModelShader;
////Shader shader;
////Shader screenShader;
////Shader skyboxShader;
////Shader cubeMapShader;
//
//Model ourModel;
//Model ourCube;
//Model ourPlane;
//
//Model ourPyramid;
//
//Model ourSphere;
//
//glm::mat4 space_ship_model(1.0f);
//glm::vec3 pointLightColor(0.8,0.8,0.8);
//bool rotation_light = false;
//bool light_on = true;
///------ 함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMotion(int x, int y);
//	button (버튼 파라미터): GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
//	state(상태 파라미터) : GLUT_UP, GLUT_DOWN
//	x, y : 윈도우에서 마우스의위치


GLvoid mouseWheel(int button, int dir, int x, int y);

void update_world();
void game_loop();
void init_world();
GLuint loadCubeMap(vector<string> faces);
///------ 함수
void main(int argc, char** argv)
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);//--- glut 초기화
	glutInitWindowPosition(100, 0);//--- 윈도우의 위치 지정
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);//--- 디스플레이 모드 설정
	glutInitWindowSize(1600, 800);//--- 윈도우의 크기 지정
	glutCreateWindow("Example21");//--- 윈도우 생성 (윈도우 이름)
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) //--- glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}

	
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glutSetCursor(GLUT_CURSOR_NONE);

	
	


	//--- 윈도우 출력하고 콜백함수 설정
	glutDisplayFunc(drawScene);//--- 출력 콜백함수의 지정
	glutReshapeFunc(Reshape);//--- 다시 그리기 콜백함수 지정
	
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutIdleFunc(game_loop);	// --- 게임 루프 돌리는 기본 메세지 루프
	glutMouseWheelFunc(mouseWheel);
	



	Core::Instance()->Init();//전체 초기화
	glutMainLoop();//--- 이벤트 처리 시작
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
	if (dir > 0)
	{
		//g_camera->ProcessMouseScroll(1.0f);//fovy값변경
	}
	else
	{
		//g_camera->ProcessMouseScroll(-1.0f);//fovy값변경
	}
	glutPostRedisplay();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glutPostRedisplay();
}
GLvoid MouseMotion(int x, int y) {
	Core::Instance()->mouse_motion(x, y);
}
GLvoid Mouse(int button, int state, int x, int y) {
	Core::Instance()->Mouse(button, state, x, y);
}


