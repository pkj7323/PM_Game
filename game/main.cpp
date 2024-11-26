#include "stdafx.h"

#include "CameraManager.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "Model.h"
#include "TimeManager.h"
#include "TextureLoadManager.h"
#include "Shader.h"

// �� �Ʒ��� ��� ���� �߰�



//------��������
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> size{ 0.1f, 0.5f };
std::uniform_real_distribution<float> cr{ 0.f, 1.f };

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
	"resources/skybox/right.png",
	"resources/skybox/left.png",
	"resources/skybox/top.png",
	"resources/skybox/bottom.png",
	"resources/skybox/front.png",
	"resources/skybox/back.png"
};
// first, configure the cube's VAO (and VBO)
unsigned int VBO, cubeVAO,cubeVBO;
unsigned int lightCubeVAO;
unsigned int quadVAO, quadVBO;
unsigned int planeVAO, planeVBO;
unsigned int skyboxVAO, skyboxVBO;
GLuint fbo;
GLuint rbo;
GLuint screenTextureColorBuffer;


Shader stencilShader;
Shader stencilSingleColorShader;
Shader lightCubeShader;
Shader ModelShader;
Shader shader;
Shader screenShader;
Shader skyboxShader;
Shader cubeMapShader;

Model ourModel;
Model ourCube;
Model ourPlane;

Model ourPyramid;

Model ourSphere;

glm::mat4 space_ship_model(1.0f);
glm::vec3 pointLightColor(0.8,0.8,0.8);
bool rotation_light = false;
bool light_on = true;
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
	
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutIdleFunc(game_loop);	// --- ���� ���� ������ �⺻ �޼��� ����
	glutMouseWheelFunc(mouseWheel);
	



	init_world();//��ü �ʱ�ȭ
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
		cubeMapShader = Shader("cubemap_vs.glsl", "cubemap_fs.glsl");
		//stencilSingleColorShader = Shader("stencil_testing_vs.glsl", "stencil_single_color_fs.glsl");
	}
	//�� �ʱ�ȭ
	{
		cout << "�� �ε�" << endl;
		ourModel = Model("resources/rock/rock.obj");
		ourPlane = Model("resources/plane.obj");
		//ourPyramid = Model("resources/pyramid.obj");
		ourCube = Model("resources/cube.obj");
		//ourSphere = Model("resources/sphere.obj");
		cout << "�� �ε� ����" << endl;
	}
	


	//��ü �ʱ�ȭ
	{
		//��� ��ü�� init�Լ��� �ҷ����ϴ� �κ��ε� ����� �ӽ÷� �𵨾Ⱦ��� ����Ŷ� ����
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		//quad�� ��ü �����찡 �׷��� ������ ���� �簢��
		// �����ӹ��ۿ� �� �׸��� �� �簢���� �����ӹ��۸� �������� �̿��ؼ� �׸���.
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glBindVertexArray(0);
		//�����ӹ��� ��ü����
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//�����ӹ��۴� �ؽ��ķ� ������ �����ϰ� �Ѱ��ش�.
		glGenTextures(1, &screenTextureColorBuffer);
		glBindTexture(GL_TEXTURE_2D, screenTextureColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
			glutGet(GLUT_WINDOW_WIDTH),
			glutGet(GLUT_WINDOW_HEIGHT), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTextureColorBuffer, 0);
		//�������۴� ���̿� ���ٽ��� �����Ѵ�.
		//�����ӹ��۴� �Ѱ��̻��� ��������,���̹���,���ٽǹ��۰� �����ؾ���
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		//�������۸� ��ü ȭ��ũ��� �����Ѵ�.
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		//�����ӹ��۰� �ϼ��Ǿ����� Ȯ��
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);



		

		cout << "�ؽ��� �ε�" << endl;
		TextureLoadManager::Instance()->Load("wall", "wall.jpg");
		TextureLoadManager::Instance()->Load("container2", "container2.png");
		TextureLoadManager::Instance()->Load("container2_specular", "container2_specular.png");
		TextureLoadManager::Instance()->Load("marble", "resources/marble.jpg");
		TextureLoadManager::Instance()->Load("metal", "resources/metal.png");
		TextureLoadManager::Instance()->Load("space_ship", "resources/space_ship_test_color.png");
		TextureLoadManager::Instance()->loadCubeMap("skybox", faces);//��ī�̹ڽ� �ؽ��� �ε�
		//��ī�̹ڽ��� �ε尡 �ٸ���. ť����Լ����� ����ؼ� �ε��ϰ� �������� ���� �ʿ��ϱ� �� faces���͹迭�� �Ѱ��ش�.
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
		KeyManager::Instance()->Init();
		cout << "�Ŵ��� �ʱ�ȭ ����" << endl;
	}
	cout << "�ʱ�ȭ �Ϸ�" << endl;
	
}
void game_loop()
{
	//glutPostRedisplay();

	{
		update_world(); // ���� ������Ʈ
		drawScene();	// ��ο� �� ȣ��
	}
	{
		//Ÿ�̸� �Ŵ��� ������Ʈ DT������Ʈ
		TimeManager::Instance()->Update();
	}

}
float timer = 0;
bool go_right = true;
void update_world()//��� ������Ʈ�� �θ��� ������Ʈ �Լ�
{
	KeyManager::Instance()->Update();
	CollisionManager::Instance()->Update();
	//������ ���� ������Ʈ�� �ҷ��� ������ �޶�����
	// ������Ʈ�� �޶����� �ְԲ� �����ϰ� �ؾ���
	if (KEY_TAP(KEY::ESC))
	{
		glutDestroyWindow(glutGetWindow());
	}
	if (KEY_HOLD(KEY::W))
	{
		g_camera->ProcessKeyboard(FORWARD);
	}
	if (KEY_HOLD(KEY::S))
	{
		g_camera->ProcessKeyboard(BACKWARD);
	}
	if (KEY_HOLD(KEY::A))
	{
		g_camera->ProcessKeyboard(LEFT);
	}
	if (KEY_HOLD(KEY::D))
	{
		g_camera->ProcessKeyboard(RIGHT);
	}
	if (rotation_light)
	{
		for (int i = 0; i < 4; i++)
		{
			pointLightPositions[i] = glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::vec4(pointLightPositions[i],1.0);
		}
	}
	
}

GLvoid drawScene()
{
	// bind to framebuffer and draw scene as we normally would to color texture
	// ������ ���۸� ���ε��ϰ� ���� �׸���. 
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glEnable(GL_DEPTH_TEST); // ������ ���� �׽�Ʈ�� Ų��. (���߿� quad�׸������� �����Ѵ�.)

	// ������ ���ۿ� �׸� �͵��� ���´�.
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//����� 0.1,0.1,0.1�� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������ۿ� ���̹��۸� Ŭ�����Ѵ�. ������
	glm::mat4 projection = g_camera->GetPerspectiveMatrix();
	glm::mat4 view = g_camera->GetViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	// draw scene as normal
	
	// render the cube
	
	//�� ���̴��� ������ ���� �־��ش�. 
	ModelShader.Use();//�̰žƷ��� �׸��� ���۵��� �� ���̴��� ������ ��ģ��. 1pass
	ModelShader.setMat4("projection", g_camera->GetPerspectiveMatrix());
	ModelShader.setMat4("view", g_camera->GetViewMatrix());
	ModelShader.setVec3("viewPos", g_camera->GetPosition());
	ModelShader.setFloat("material.shininess", 32.0f);
	// directional light
	// �¾籤 ����
	ModelShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	ModelShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	ModelShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	// point light 1
	// ����Ʈ ����Ʈ 1 ����
	ModelShader.setVec3("pointLights[0].position", pointLightPositions[0]);//����Ʈ ����Ʈ�� ��ġ
	ModelShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);//����Ʈ ����Ʈ�� �ֺ���
	ModelShader.setVec3("pointLights[0].diffuse", pointLightColor);//����Ʈ ����Ʈ�� Ȯ�걤
	ModelShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);//����Ʈ ����Ʈ�� �ݻ籤
	ModelShader.setFloat("pointLights[0].constant", 1.0f);//����Ʈ ����Ʈ�� �����
	ModelShader.setFloat("pointLights[0].linear", 0.09);//����Ʈ ����Ʈ�� ������(1��)
	ModelShader.setFloat("pointLights[0].quadratic", 0.032);//����Ʈ ����Ʈ�� ������(2��)
	//�Ʒ� ������ �׵��� ����Ʈ ����Ʈ�� ��������� �����ϱ����� ���̴�.
	//��4�� ��������
	// ���̴��� ������� � ���� �̸������ߴ�.
	// point light 2
	ModelShader.setVec3("pointLights[1].position", pointLightPositions[1]);
	ModelShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("pointLights[1].diffuse", pointLightColor);
	ModelShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("pointLights[1].constant", 1.0f);
	ModelShader.setFloat("pointLights[1].linear", 0.09f);
	ModelShader.setFloat("pointLights[1].quadratic", 0.032f);
	// point light 3
	ModelShader.setVec3("pointLights[2].position", pointLightPositions[2]);
	ModelShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("pointLights[2].diffuse", pointLightColor);
	ModelShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("pointLights[2].constant", 1.0f);
	ModelShader.setFloat("pointLights[2].linear", 0.09f);
	ModelShader.setFloat("pointLights[2].quadratic", 0.032f);
	// point light 4
	ModelShader.setVec3("pointLights[3].position", pointLightPositions[3]);
	ModelShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("pointLights[3].diffuse", pointLightColor);
	ModelShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("pointLights[3].constant", 1.0f);
	ModelShader.setFloat("pointLights[3].linear", 0.09f);
	ModelShader.setFloat("pointLights[3].quadratic", 0.032f);
	// spotLight
	ModelShader.setVec3("spotLight.position", g_camera->GetPosition());
	ModelShader.setVec3("spotLight.direction", g_camera->GetFront());
	ModelShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	ModelShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	ModelShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("spotLight.constant", 1.0f);
	ModelShader.setFloat("spotLight.linear", 0.09f);
	ModelShader.setFloat("spotLight.quadratic", 0.032f);
	ModelShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	//�������� ���������� ���� ����
	ModelShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	//�������� �ٱ��� ������ ���� ���� <-- �� ���� ���̿� �ִ� ������ �޴µ� �پ��鼭 �޴´�(�ǰ����� ȿ��).

	

	model = glm::mat4(1.0f);
	ModelShader.setMat4("model", space_ship_model);//�� ���̴��� ��ü�� ��������� �־��ش�.
	TextureLoadManager::Instance()->Use("space_ship");//�ؽ��ĸ� ����Ѵ�.
	ourModel.Draw(ModelShader);//���� �׸���.
	glBindTexture(GL_TEXTURE_2D, 0);//�ؽ��ĸ� ����ε��Ѵ�.

	/*model = glm::mat4(1.0f);
	ModelShader.setMat4("model", model);
	TextureLoadManager::Instance()->Use("metal");
	ourPlane.Draw(ModelShader);
	glBindTexture(GL_TEXTURE_2D, 0);*/

	if (light_on)
	{
		lightCubeShader.Use();//������ ��ġ�� �����ֱ����� ť����� ���� ���̴�(������ �Ͼ������ ������)
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		// render the cube
		for (int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			//�������� ���� ����
			lightCubeShader.setMat4("model", model);

			ourCube.Draw(lightCubeShader);

		}
	}
	
	cubeMapShader.Use();// ȯ�� ������ ���� ���̴�
	//���� ȯ�� ������ �ƴ����� skybox�� �ؽ��ĸ� ����ؼ� ����,�ݻ縦 ǥ���Ѵ�.
	model = glm::mat4(1.0f);
	cubeMapShader.setMat4("view", view);
	cubeMapShader.setMat4("projection", projection);
	cubeMapShader.setMat4("model", model);
	cubeMapShader.setVec3("cameraPos", g_camera->GetPosition());
	ourPlane.Draw(cubeMapShader);
	glBindTexture(GL_TEXTURE_2D,0);
	
	
	




	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	// ���� �Լ� ����: ���� �׽�Ʈ�� ���� ������ ����� ���� ���� �� ���
	skyboxShader.Use();
	view = glm::mat4(glm::mat3(g_camera->GetViewMatrix())); // remove translation from the view matrix
	skyboxShader.setMat4("view", view);
	skyboxShader.setMat4("projection", g_camera->GetPerspectiveMatrix());
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureLoadManager::Instance()->GetTexture("skybox"));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDepthFunc(GL_LESS); // �ٽ� ������������ ������.

	
	// ���� �⺻ ������ ���۷� ���ư��� ���� �ؽ��İ� ���� ������ ���۷� �簢���� �׸���.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	// ���� �׽�Ʈ�� ��Ȱ��ȭ�Ͽ� ȭ�� ���� �簢���� ���� �׽�Ʈ�� ���� �������� �ʵ����մϴ�.
	// ��� ���۸� Ŭ�����Ѵ�.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);// ������� ����(�����δ� �ʿ����� ������, ��� �簢�� �ڷ� �� �� ���� ������)
	glClear(GL_COLOR_BUFFER_BIT);

	screenShader.Use();//��ũ�� ���̴��� ����Ѵ�. �����ӹ��� ������ ���� �׸���.
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, screenTextureColorBuffer);	//�÷� �����ڸ� ����ؼ� quad�� ������ �ؽ��ķ� ȭ���� �׸���.
	glDrawArrays(GL_TRIANGLES, 0, 6);


	glutSwapBuffers();
}

GLvoid mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		g_camera->ProcessMouseScroll(1.0f);//fovy������
	}
	else
	{
		g_camera->ProcessMouseScroll(-1.0f);//fovy������
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


