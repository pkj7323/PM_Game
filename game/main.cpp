#include "stdafx.h"

#include "CameraManager.h"
#include "CollisionManager.h"
#include "Model.h"
#include "TimeManager.h"
#include "TextureLoadManager.h"
#include "Shader.h"

// �� �Ʒ��� ��� ���� �߰�



//------��������
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> size{ 0.1f, 0.5f };
std::uniform_real_distribution<float> dis{ -1.f, 1.f };

//------��������

bool firstMouse = true;
float lastX = 400, lastY = 400;
float g_speed = 30.0f;
glm::vec3 g_lightPos(1.2f, 1.0f, 2.0f);
CameraManager* g_camera = nullptr;

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
};
// positions all containers
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
// positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};
vector<std::string> faces
{
	"resources/right.jpg",
	"resources/left.jpg",
	"resources/top.jpg",
	"resources/bottom.jpg",
	"resources/front.jpg",
	"resources/back.jpg"
};
// first, configure the cube's VAO (and VBO)
unsigned int VBO, cubeVAO,cubeVBO;
unsigned int lightCubeVAO;
unsigned int quadVAO, quadVBO;
unsigned int planeVAO, planeVBO;
unsigned int skyboxVAO, skyboxVBO;
GLuint fbo;
GLuint rbo;
GLuint textureColorbuffer;


Shader stencilShader;
Shader stencilSingleColorShader;
Shader lightCubeShader;
Shader ModelShader;
Shader shader;
Shader screenShader;
Shader skyboxShader;


Model ourModel;
Model ourCube;


///------ �Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMotion(int x, int y);
//	button (��ư �Ķ����): GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
//	state(���� �Ķ����) : GLUT_UP, GLUT_DOWN
//	x, y : �����쿡�� ���콺����ġ
GLvoid TimerFunction(int value);
GLvoid SpecialKeyboard(int key, int x, int y);
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
	glutCreateWindow("Example21");//--- ������ ���� (������ �̸�)
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
	//glEnable(GL_CULL_FACE);

	glEnable(GL_MULTISAMPLE);
	glutSetCursor(GLUT_CURSOR_NONE);

	
	


	//--- ������ ����ϰ� �ݹ��Լ� ����
	glutDisplayFunc(drawScene);//--- ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape);//--- �ٽ� �׸��� �ݹ��Լ� ����
	glutKeyboardFunc(Keyboard);//--- Ű���� �Է� �ݹ��Լ� ����(����� Ű������)
	glutSpecialFunc(SpecialKeyboard);//--- Ư��Ű �Է� �ݹ��Լ� ����
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutIdleFunc(game_loop); // --- ���� ���� ������ �⺻ �޼��� ����
	glutMouseWheelFunc(mouseWheel);
	//glutTimerFunc(60, TimerFunction, 1); //---Ÿ�̸� ���� �ݹ��Լ�



	init_world();
	glutMainLoop();//--- �̺�Ʈ ó�� ����
}



void init_world()
{
	cout << "�ʱ�ȭ ����" << endl;
	//���̴� �ʱ�ȭ �� ������
	{
		cout << "���̴� ������" << endl;
		shader = Shader("cubemap_vs.glsl", "cubemap_fs.glsl");
		screenShader = Shader("framebuffer_screen_vs.glsl", "framebuffer_screen_fs.glsl");
		skyboxShader = Shader("skybox_vs.glsl", "skybox_fs.glsl");
		//stencilShader = Shader("stencil_testing_vs.glsl", "stencil_testing_fs.glsl");
		ModelShader = Shader("model_vertex.glsl", "model_fragment.glsl");
		lightCubeShader = Shader("OldVertex.glsl", "OldFragment.glsl");
		//stencilSingleColorShader = Shader("stencil_testing_vs.glsl", "stencil_single_color_fs.glsl");
	}
	//�� �ʱ�ȭ
	{
		cout << "�� �ε�" << endl;
		/*ourModel = Model("resources/statue/statue.obj");*/

		ourCube = Model("resources/cube.obj");
		cout << "�� �ε� ����" << endl;
	}
	


	//��ü �ʱ�ȭ
	{
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		
		

		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		glGenTextures(1, &textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
			glutGet(GLUT_WINDOW_WIDTH),
			glutGet(GLUT_WINDOW_HEIGHT), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);



		

		cout << "�ؽ��� �ε�" << endl;
		TextureLoadManager::Instance()->Load("wall", "wall.jpg");
		TextureLoadManager::Instance()->Load("container2", "container2.png");
		TextureLoadManager::Instance()->Load("container2_specular", "container2_specular.png");
		TextureLoadManager::Instance()->Load("marble", "resources/marble.jpg");
		TextureLoadManager::Instance()->Load("metal", "resources/metal.png");
		TextureLoadManager::Instance()->loadCubeMap("skybox", faces);
		cout << "�ؽ��� �ε� ����" << endl;

		
	}
	//ī�޶� �ʱ�ȭ
	{
		cout << "ī�޶� �ʱ�ȭ" << endl;
		g_camera = new CameraManager;
		g_camera->SetCamera(glm::vec3(0, 5, 10),
			glm::vec3(0, 1, 0), YAW, -10.f, 45, SPEED, SENSITIVITY);
		cout << "ī�޶� �ʱ�ȭ ����" << endl;
	}
	//�Ŵ��� �ʱ�ȭ
	{
		cout << "�Ŵ��� �ʱ�ȭ" << endl;
		TimeManager::Instance()->Init();
		CollisionManager::Instance()->Init();
		cout << "�Ŵ��� �ʱ�ȭ ����" << endl;
	}
	cout << "�ʱ�ȭ �Ϸ�" << endl;
	{
		
	}
}
void game_loop()
{
	//glutPostRedisplay();

	{
		update_world(); // ���� ������Ʈ
		drawScene();// ��ο� �� ȣ��
	}
	{
		//Ÿ�̸� �Ŵ��� ������Ʈ DT������Ʈ
		TimeManager::Instance()->Update();
	}

}

void update_world()
{
	
	CollisionManager::Instance()->Update();
}

GLvoid drawScene()
{
	// bind to framebuffer and draw scene as we normally would to color texture 
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	// make sure we clear the framebuffer's content
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	// cubes
	/*glBindVertexArray(cubeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->Use("skybox"));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);*/
	// set uniforms
	glm::mat4 projection = g_camera->GetPerspectiveMatrix();
	glm::mat4 view = g_camera->GetViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	lightCubeShader.Use();
	lightCubeShader.setMat4("projection", projection);
	lightCubeShader.setMat4("view", view);
	// render the cube
	model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
	lightCubeShader.setMat4("model", model);
	ourCube.Draw(lightCubeShader);
	






	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);

	screenShader.Use();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);


	glutSwapBuffers();
}

GLvoid TimerFunction(int value)
{
	//Ÿ�̸Ӹ��� 1���� Ÿ�̸� �Լ� �ҷ��� �ٽ� �ҷ���ߵ�

	glutPostRedisplay();

	glutTimerFunc(60, TimerFunction, 1);
}
GLvoid mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		g_camera->ProcessMouseScroll(1.0f);
	}
	else
	{
		g_camera->ProcessMouseScroll(-1.0f);
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

	g_camera->ProcessMouseMovement(xoffset, yoffset);

	// ���콺�� �߾����� �̵�
	int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(centerX, centerY);

	// �߾����� �̵��� ���� ��ġ�� lastX, lastY�� ����
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

	g_camera->ProcessMouseMovement(xoffset, yoffset);
	glutPostRedisplay();
}
GLvoid Keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'q':
		glutDestroyWindow(glutGetWindow());
		break;
	case 'w':
		g_camera->ProcessKeyboard(FORWARD, TimeManager::Instance()->GetDeltaTime());
		break;
	case 's':
		g_camera->ProcessKeyboard(BACKWARD, TimeManager::Instance()->GetDeltaTime());
		break;
	case 'a':
		g_camera->ProcessKeyboard(LEFT, TimeManager::Instance()->GetDeltaTime());
		break;
	case 'd':
		g_camera->ProcessKeyboard(RIGHT, TimeManager::Instance()->GetDeltaTime());
		break;
	case 'g':
		ourModel.ChangeMode(GL_LINE_STRIP);
		break;
	case 'G':
		ourModel.ChangeMode(GL_TRIANGLES);
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

