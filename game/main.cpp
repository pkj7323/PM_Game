#include "stdafx.h"

#include "CameraManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "TextureLoadManager.h"
#include "ShaderManager.h"
#include "New3D.h"
// 요 아래에 헤더 파일 추가



//------전역변수
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> size{ 0.1f, 0.5f };
std::uniform_real_distribution<float> dis{ -1.f, 1.f };

//------전역변수

bool firstMouse = true;
float lastX = 400, lastY = 400;
float g_speed = 30.0f;
glm::vec3 g_lightPos(0, 0, 5);



New3D* g_flat = nullptr;

CameraManager* g_camera1 = nullptr;

GLuint texture;

GLint lightPosLocation;
GLint lightColorLocation;
GLint objColorLocation;
GLint viewPosLocation;
GLint projectionLocation;
GLint viewLocation;
GLint worldLocation;
GLint useTextureLocation;


float vertices[] = {
	// positions          // normals           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	-0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // bottom right
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
	 0.5f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f  // top left 
};
unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};
unsigned int VBO, VAO, EBO;



///------ 함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMotion(int x, int y);
//	button (버튼 파라미터): GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
//	state(상태 파라미터) : GLUT_UP, GLUT_DOWN
//	x, y : 윈도우에서 마우스의위치
GLvoid TimerFunction(int value);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid mouseWheel(int button, int dir, int x, int y);

void update_world();
void game_loop();
void init_world();
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

	ShaderManager::Instance()->make_ShaderProgram("light_vertex.glsl", "light_fragment.glsl");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glutSetCursor(GLUT_CURSOR_NONE);

	GLuint ID = ShaderManager::Instance()->GetID();
	lightPosLocation = glGetUniformLocation(ID, "lightPos");
	lightColorLocation = glGetUniformLocation(ID, "lightColor");
	objColorLocation = glGetUniformLocation(ID, "objectColor");
	viewPosLocation = glGetUniformLocation(ID, "viewPos");
	projectionLocation = glGetUniformLocation(ID, "projection");
	viewLocation = glGetUniformLocation(ID, "view");
	worldLocation = glGetUniformLocation(ID, "world");
	useTextureLocation = glGetUniformLocation(ID, "useTexture");


	//--- 윈도우 출력하고 콜백함수 설정
	glutDisplayFunc(drawScene);//--- 출력 콜백함수의 지정
	glutReshapeFunc(Reshape);//--- 다시 그리기 콜백함수 지정
	glutKeyboardFunc(Keyboard);//--- 키보드 입력 콜백함수 지정(스페셜 키못받음)
	glutSpecialFunc(SpecialKeyboard);//--- 특수키 입력 콜백함수 지정
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutIdleFunc(game_loop); // --- 게임 루프 돌리는 기본 메세지 루프
	glutMouseWheelFunc(mouseWheel);
	//glutTimerFunc(60, TimerFunction, 1); //---타이머 설정 콜백함수



	init_world();
	glutMainLoop();//--- 이벤트 처리 시작
}

GLvoid Keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'q':
		glutDestroyWindow(glutGetWindow());
		break;
	case 'w':
		g_camera1->ProcessKeyboard(FORWARD, TimeManager::Instance()->GetDeltaTime());
		break;
	case 's':
		g_camera1->ProcessKeyboard(BACKWARD, TimeManager::Instance()->GetDeltaTime());
		break;
	case 'a':
		g_camera1->ProcessKeyboard(LEFT, TimeManager::Instance()->GetDeltaTime());
		break;
	case 'd':
		g_camera1->ProcessKeyboard(RIGHT, TimeManager::Instance()->GetDeltaTime());
		break;

	default:
		break;
		//.....
	}
	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		g_lightPos.y += 0.1f;
		break;
	case GLUT_KEY_DOWN:
		g_lightPos.y -= 0.1f;
		break;
	case GLUT_KEY_LEFT:
		g_lightPos.x -= 0.1f;
		break;
	case GLUT_KEY_RIGHT:
		g_lightPos.x += 0.1f;
		break;
	case GLUT_KEY_F1:
		g_lightPos.z += 0.1f;
		break;
	case GLUT_KEY_F2:
		g_lightPos.z -= 0.1f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void init_world()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//카메라 초기화
	{
		g_camera1 = new CameraManager;
		g_camera1->SetCamera(glm::vec3(0, 5, 10),
			glm::vec3(0, 1, 0), YAW, -10.f, 45, SPEED, SENSITIVITY);
	}

	//객체 초기화
	{
		TextureLoadManager::Instance()->Load("wall", "wall.jpg");





	}
	//매니저 초기화
	{

		TimeManager::Instance()->Init();
	}
}
void game_loop()
{
	//glutPostRedisplay();

	{
		update_world(); // 월드 업데이트
		drawScene();// 드로우 씬 호출
	}
	{
		//타이머 매니저 업데이트 DT업데이트
		TimeManager::Instance()->Update();
	}

}
void update_world()
{

	CollisionManager::Instance()->Update();
}

GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	//--- 화면 지우기(invaildRect)
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ShaderManager::Instance()->Use();




	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(g_camera1->GetPerspectiveMatrix()));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(g_camera1->GetViewMatrix()));
	{


		glUniform1i(useTextureLocation, GL_TRUE);
		TextureLoadManager::Instance()->Use("wall"); //---texture 적용

		glUniformMatrix4fv(worldLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

		//--- lightPos 값 전달: (0.0, 0.0, 5.0) 위치에 빛이 있다고 가정
		glUniform3fv(lightPosLocation, 1, glm::value_ptr(g_lightPos));

		//--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
		glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

		//--- object Color값 전달: (1.0, 0.5, 0.3)의 색
		glUniform3f(objColorLocation, 1.0, 0.5, 0.3);

		//--- viewPos 값 전달: 카메라 위치
		glUniform3f(viewPosLocation, g_camera1->GetPosition().x
			, g_camera1->GetPosition().y
			, g_camera1->GetPosition().z);


		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);




		auto mat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 3, 0));
		glUniform1i(useTextureLocation, GL_FALSE);
		glUniformMatrix4fv(worldLocation, 1, GL_FALSE, glm::value_ptr(mat));

		//--- lightPos 값 전달: (0.0, 0.0, 5.0) 위치에 빛이 있다고 가정
		glUniform3fv(lightPosLocation, 1, glm::value_ptr(g_lightPos));

		//--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
		glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

		//--- object Color값 전달: (1.0, 0.5, 0.3)의 색
		glUniform3f(objColorLocation, 1.0, 0, 0);

		//--- viewPos 값 전달: 카메라 위치
		glUniform3f(viewPosLocation, g_camera1->GetPosition().x
			, g_camera1->GetPosition().y
			, g_camera1->GetPosition().z);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

	glutSwapBuffers();
}

GLvoid TimerFunction(int value)
{
	//타이머마다 1번만 타이머 함수 불러서 다시 불러줘야됨

	glutPostRedisplay();

	glutTimerFunc(60, TimerFunction, 1);
}

GLvoid mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		g_camera1->ProcessMouseScroll(1.0f);
	}
	else
	{
		g_camera1->ProcessMouseScroll(-1.0f);
	}
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glutPostRedisplay();
}




GLvoid MouseMotion(int x, int y) {

	float xpos = static_cast<float>(x);
	float ypos = static_cast<float>(y);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	g_camera1->ProcessMouseMovement(xoffset, yoffset);

	// 마우스를 중앙으로 이동
	int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(centerX, centerY);

	// 중앙으로 이동한 후의 위치를 lastX, lastY로 설정
	lastX = static_cast<float>(centerX);
	lastY = static_cast<float>(centerY);

	glutPostRedisplay();
}
GLvoid Mouse(int button, int state, int x, int y) {
	float xpos = static_cast<float>(x);
	float ypos = static_cast<float>(y);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	g_camera1->ProcessMouseMovement(xoffset, yoffset);
	glutPostRedisplay();
}
