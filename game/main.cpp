#include "stdafx.h"

#include "CameraManager.h"
#include "CollisionManager.h"
#include "Model.h"
#include "TimeManager.h"
#include "TextureLoadManager.h"
#include "Shader.h"
#include "New3D.h"
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



New3D* g_flat = nullptr;

CameraManager* g_camera1 = nullptr;

GLuint texture;


float cubeVertices[] = {
	// positions          // texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
float planeVertices[] = {
	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
	 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
// first, configure the cube's VAO (and VBO)
unsigned int VBO, cubeVAO,cubeVBO;
unsigned int lightCubeVAO;

unsigned int planeVAO, planeVBO;

Shader stencilShader;
Shader stencilSingleColorShader;
Shader lightCubeShader;
Shader ModelShader;


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

	//���Ľ� �׽�Ʈ Ȱ��ȭ
	glEnable(GL_STENCIL_TEST);
	// ���ٽ� �׽�Ʈ�� �����մϴ�. GL_NOTEQUAL�� ���ٽ� ���� 1�� "�ƴ�" ��쿡�� ����ϵ��� �մϴ�.
	// 0xFF�� ����ũ ������, ���ٽ� ������ ��� ��Ʈ�� ����մϴ�.
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	// ���ٽ� �׽�Ʈ�� ����� ���� ������ �����մϴ�. 
	// GL_KEEP�� ���ٽ� ���� ������� �ʵ��� �ϰ�, GL_REPLACE�� ���ٽ� ���� 1�� �����մϴ�.
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	// fail:GL_KEEP = > ���ٽ� �׽�Ʈ�� �����ϸ� ���ٽ� ������ ���� �����մϴ�.
	// zfail:GL_KEEP = > ���� �׽�Ʈ�� �����ϸ�(���� �׽�Ʈ�� �׻� �����ϹǷ� ������ �ʽ��ϴ�.)
	// zpass:GL_REPLACE = > ���ٽ� �׽�Ʈ�� ���� �׽�Ʈ�� ��� �����ϸ� ���ٽ� ������ ���� 1�� �����մϴ�.
	// (glStencilFunc(GL_NOTEQUAL, 1, 0xFF);)�� 1���� Replace���̴�.
	// �⺻������ 3�� ���� GL_KEEP�ε� ���Ľ� ���� �̿��Ϸ��� 3�����ϳ��� �ٲ����

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

void init_world()
{
	//���̴� �ʱ�ȭ �� ������
	{
		stencilShader = Shader("stencil_testing_vs.glsl", "stencil_testing_fs.glsl");
		ModelShader = Shader("model_vertex.glsl", "model_fragment.glsl");
		lightCubeShader = Shader("OldVertex.glsl", "OldFragment.glsl");
		stencilSingleColorShader = Shader("stencil_testing_vs.glsl", "stencil_single_color_fs.glsl");
	}
	
	


	//��ü �ʱ�ȭ
	{

		glGenVertexArrays(1, &planeVAO);
		glGenBuffers(1, &planeVBO);
		glBindVertexArray(planeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glBindVertexArray(0);

		TextureLoadManager::Instance()->Load("wall", "wall.jpg");
		TextureLoadManager::Instance()->Load("container2", "container2.png");
		TextureLoadManager::Instance()->Load("container2_specular", "container2_specular.png");
		TextureLoadManager::Instance()->Load("marble", "resources/marble.jpg");
		TextureLoadManager::Instance()->Load("metal", "resources/metal.png");

		ourModel = Model("resources/statue/statue.obj");
		ourCube = Model("resources/cube.obj");
	}
	//ī�޶� �ʱ�ȭ
	{
		g_camera1 = new CameraManager;
		g_camera1->SetCamera(glm::vec3(0, 5, 10),
			glm::vec3(0, 1, 0), YAW, -10.f, 45, SPEED, SENSITIVITY);
	}
	//�Ŵ��� �ʱ�ȭ
	{

		TimeManager::Instance()->Init();
	}
	{
		ModelShader.Use();
		ModelShader.setInt("texture1", 0);//ó���� �����׸�Ʈ ���̴��� �ִ� �ؽ��ĸ� 0���� ����-> unbind
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
	//--- ����� ���� ����
	//--- ȭ�� �����(invaildRect)
	glClearColor(0.1, 0.1, 0.1, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	/*
	 1.	������Ʈ�� �׸��� ���� stencil �Լ��� GL_ALWAYS�� �����ϰ� ������Ʈ�� fragment�� �������ɶ����� stencil buffer�� 1�� �����մϴ�.
	 2.	������Ʈ�� �������մϴ�.
	 3.	stencil �ۼ��� depth testing�� ��Ȱ��ȭ�մϴ�.
	 4.	�� ������Ʈ���� �ణ Ȯ���մϴ�.
	 5.	�ϳ���(�ܰ���) �÷��� ����ϴ� ������ fragment shader�� ����մϴ�.
	 6.	������Ʈ�� �ٽ� �׸����� stencil ���� 1�� ���� ���� fragment�鸸 �׸��ϴ�.
	 7.	�ٽ� stencil �ۼ��� depth testing�� Ȱ��ȭ�մϴ�.
	*/
	{
		glm::mat4 projection = g_camera1->GetPerspectiveMatrix();
		glm::mat4 view = g_camera1->GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));

		


		// �ٴ��� ���������� �׸���. ������ �츮�� �ٴ��� ���ٽ� ���ۿ� ���� �ʴ´�. �츮�� �����̳ʿ��� ������ �ִ�. ���ٽ� ���ۿ� ���� �ʵ��� ����ũ�� 0x00���� �����Ѵ�.
		glStencilMask(0x00);
		// �ٴ�
		

		

		// also draw the lamp object
		lightCubeShader.Use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		for (auto pointLightPosition : pointLightPositions)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPosition);
			model = glm::scale(model, glm::vec3(0.01f)); // Make it a smaller cube
			lightCubeShader.setMat4("model", model);
			ourCube.Draw(lightCubeShader);
		}
		stencilShader.Use();
		stencilShader.setMat4("projection", projection);
		stencilShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		stencilShader.setMat4("model", model);

		glBindVertexArray(planeVAO);
		glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->Use("metal"));
		ModelShader.setMat4("model", glm::mat4(1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		// 1st. render pass, draw objects as normal, writing to the stencil buffer
		// ù��° ���� �н� : ���ٽ� ���ۿ� ���� ���� ������Ʈ�� �Ϲ������� �׸��ϴ�.
		// --------------------------------------------------------------------
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		ModelShader.Use();
		ModelShader.setMat4("projection", projection);
		ModelShader.setMat4("view", view);
		ModelShader.setMat4("model", model);
		ModelShader.setVec3("viewPos", g_camera1->GetPosition());
		ModelShader.setFloat("material.shininess", 32.0f);
		
		ModelShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		ModelShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		ModelShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		ModelShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		// point light 1
		// ����Ʈ ����Ʈ 1 ����
		ModelShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		ModelShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		ModelShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		ModelShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		ModelShader.setFloat("pointLights[0].constant", 1.0f);
		ModelShader.setFloat("pointLights[0].linear", 0.09);
		ModelShader.setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		ModelShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		ModelShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		ModelShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		ModelShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		ModelShader.setFloat("pointLights[1].constant", 1.0f);
		ModelShader.setFloat("pointLights[1].linear", 0.09f);
		ModelShader.setFloat("pointLights[1].quadratic", 0.032f);
		// point light 3
		ModelShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		ModelShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		ModelShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		ModelShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		ModelShader.setFloat("pointLights[2].constant", 1.0f);
		ModelShader.setFloat("pointLights[2].linear", 0.09f);
		ModelShader.setFloat("pointLights[2].quadratic", 0.032f);
		// point light 4
		ModelShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		ModelShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		ModelShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		ModelShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		ModelShader.setFloat("pointLights[3].constant", 1.0f);
		ModelShader.setFloat("pointLights[3].linear", 0.09f);
		ModelShader.setFloat("pointLights[3].quadratic", 0.032f);
		// spotLight
		ModelShader.setVec3("spotLight.position", g_camera1->GetPosition());
		ModelShader.setVec3("spotLight.direction", g_camera1->GetFront());
		ModelShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		ModelShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		ModelShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		ModelShader.setFloat("spotLight.constant", 1.0f);
		ModelShader.setFloat("spotLight.linear", 0.09f);
		ModelShader.setFloat("spotLight.quadratic", 0.032f);
		ModelShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		ModelShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		
		// ������
		model = glm::mat4(1.0f);
		ModelShader.Use();
		ModelShader.setMat4("model", model);
		ourModel.Draw(ModelShader);


		// 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
	    // Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing 
	    // the objects' size differences, making it look like borders.
		// �ι�° ���� �н�: ���� ������Ʈ�� �ణ Ȯ��� ������ �׸��ϴ�. �̹����� ���ٽ� ���⸦ ��Ȱ��ȭ�մϴ�.
		// �ֳ��ϸ� ���ٽ� ���۴� ���� �������� 1�� ä���� �ֽ��ϴ�. 1�� ���� �κ��� �׷����� �����Ƿ�, ������Ʈ�� ũ�� ���̸� �׷����ϴ�.
		// ������Ʈ�� ����� �ణ Ű����	�׸��ϴ�. ��輱�� ���̵���
	    // -----------------------------------------------------------------------------------------------------------------------------
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		stencilSingleColorShader.Use();
		stencilSingleColorShader.setMat4("view", g_camera1->GetViewMatrix());
		stencilSingleColorShader.setMat4("projection", g_camera1->GetPerspectiveMatrix());
		float scale = 1.00f;
		// cubes
		model = glm::mat4(1.0f);
		stencilSingleColorShader.setMat4("model", model);
		//stencillSingleColorShader�� vertex���̴����� ������ ��� �������� �ణ�� ������ ������ ������
		ourModel.Draw(stencilSingleColorShader);



		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);
	}

	glutSwapBuffers();
	{
		cout << TimeManager::Instance()->GetFPS() << endl;
	}
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

	g_camera1->ProcessMouseMovement(xoffset, yoffset);
	glutPostRedisplay();
}