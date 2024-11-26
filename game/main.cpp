#include "stdafx.h"

#include "CameraManager.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "Model.h"
#include "TimeManager.h"
#include "TextureLoadManager.h"
#include "Shader.h"

// 요 아래에 헤더 파일 추가



//------전역변수
std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> size{ 0.1f, 0.5f };
std::uniform_real_distribution<float> cr{ 0.f, 1.f };

//------전역변수

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
	



	init_world();//전체 초기화
	glutMainLoop();//--- 이벤트 처리 시작
}



void init_world()
{
	cout << "초기화 시작" << endl;
	//쉐이더 초기화 및 컴파일
	{
		cout << "쉐이더 컴파일" << endl;
		shader = Shader("cubemap_vs.glsl", "cubemap_fs.glsl");
		screenShader = Shader("framebuffer_screen_vs.glsl", "framebuffer_screen_fs.glsl");
		skyboxShader = Shader("skybox_vs.glsl", "skybox_fs.glsl");
		//stencilShader = Shader("stencil_testing_vs.glsl", "stencil_testing_fs.glsl");
		ModelShader = Shader("model_vertex.glsl", "model_fragment.glsl");
		lightCubeShader = Shader("OldVertex.glsl", "OldFragment.glsl");
		cubeMapShader = Shader("cubemap_vs.glsl", "cubemap_fs.glsl");
		//stencilSingleColorShader = Shader("stencil_testing_vs.glsl", "stencil_single_color_fs.glsl");
	}
	//모델 초기화
	{
		cout << "모델 로드" << endl;
		ourModel = Model("resources/rock/rock.obj");
		ourPlane = Model("resources/plane.obj");
		//ourPyramid = Model("resources/pyramid.obj");
		ourCube = Model("resources/cube.obj");
		//ourSphere = Model("resources/sphere.obj");
		cout << "모델 로드 종료" << endl;
	}
	


	//객체 초기화
	{
		//사실 객체의 init함수를 불러야하는 부분인데 현재는 임시로 모델안쓰고 만든거라 생략
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		//quad는 전체 윈도우가 그려질 일종의 가상 사각형
		// 프레임버퍼에 다 그린후 이 사각형에 프레임버퍼를 색상으로 이용해서 그린다.
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
		//프레임버퍼 객체생성
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//프레임버퍼는 텍스쳐로 색상을 저장하고 넘겨준다.
		glGenTextures(1, &screenTextureColorBuffer);
		glBindTexture(GL_TEXTURE_2D, screenTextureColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
			glutGet(GLUT_WINDOW_WIDTH),
			glutGet(GLUT_WINDOW_HEIGHT), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTextureColorBuffer, 0);
		//렌더버퍼는 깊이와 스텐실을 저장한다.
		//프레임버퍼는 한개이상의 렌더버퍼,깊이버퍼,스텐실버퍼가 존재해야함
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		//렌더버퍼를 전체 화면크기로 설정한다.
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		//프레임버퍼가 완성되었는지 확인
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);



		

		cout << "텍스쳐 로드" << endl;
		TextureLoadManager::Instance()->Load("wall", "wall.jpg");
		TextureLoadManager::Instance()->Load("container2", "container2.png");
		TextureLoadManager::Instance()->Load("container2_specular", "container2_specular.png");
		TextureLoadManager::Instance()->Load("marble", "resources/marble.jpg");
		TextureLoadManager::Instance()->Load("metal", "resources/metal.png");
		TextureLoadManager::Instance()->Load("space_ship", "resources/space_ship_test_color.png");
		TextureLoadManager::Instance()->loadCubeMap("skybox", faces);//스카이박스 텍스쳐 로드
		//스카이박스는 로드가 다르다. 큐브맵함수들을 사용해서 로드하고 여러장의 사진 필요하기 에 faces벡터배열을 넘겨준다.
		cout << "텍스쳐 로드 종료" << endl;

		
	}
	//카메라 초기화
	{
		cout << "카메라 초기화" << endl;
		g_camera = new CameraManager;
		g_camera->SetCamera(glm::vec3(0, 5, 10),
			glm::vec3(0, 1, 0), YAW, -10.f, 45, SPEED, SENSITIVITY);
		cout << "카메라 초기화 종료" << endl;
	}
	//매니저 초기화
	{
		cout << "매니저 초기화" << endl;
		TimeManager::Instance()->Init();
		CollisionManager::Instance()->Init();
		KeyManager::Instance()->Init();
		cout << "매니저 초기화 종료" << endl;
	}
	cout << "초기화 완료" << endl;
	
}
void game_loop()
{
	//glutPostRedisplay();

	{
		update_world(); // 월드 업데이트
		drawScene();	// 드로우 씬 호출
	}
	{
		//타이머 매니저 업데이트 DT업데이트
		TimeManager::Instance()->Update();
	}

}
float timer = 0;
bool go_right = true;
void update_world()//모든 업데이트를 부르는 업데이트 함수
{
	KeyManager::Instance()->Update();
	CollisionManager::Instance()->Update();
	//원래는 씬의 업데이트를 불러서 각씬이 달라지면
	// 업데이트도 달라질수 있게끔 가능하게 해야함
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
	// 프레임 버퍼를 바인드하고 씬을 그린다. 
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glEnable(GL_DEPTH_TEST); // 지금은 깊이 테스트를 킨다. (나중에 quad그리기전에 꺼야한다.)

	// 프레임 버퍼에 그릴 것들을 적는다.
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//배경을 0.1,0.1,0.1로 설정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 색상버퍼와 깊이버퍼를 클리어한다. 무조건
	glm::mat4 projection = g_camera->GetPerspectiveMatrix();
	glm::mat4 view = g_camera->GetViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	// draw scene as normal
	
	// render the cube
	
	//모델 쉐이더의 유니폼 값을 넣어준다. 
	ModelShader.Use();//이거아래의 그리기 동작들은 모델 쉐이더에 영향을 미친다. 1pass
	ModelShader.setMat4("projection", g_camera->GetPerspectiveMatrix());
	ModelShader.setMat4("view", g_camera->GetViewMatrix());
	ModelShader.setVec3("viewPos", g_camera->GetPosition());
	ModelShader.setFloat("material.shininess", 32.0f);
	// directional light
	// 태양광 설정
	ModelShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	ModelShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	ModelShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	// point light 1
	// 포인트 라이트 1 설정
	ModelShader.setVec3("pointLights[0].position", pointLightPositions[0]);//포인트 라이트의 위치
	ModelShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);//포인트 라이트의 주변광
	ModelShader.setVec3("pointLights[0].diffuse", pointLightColor);//포인트 라이트의 확산광
	ModelShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);//포인트 라이트의 반사광
	ModelShader.setFloat("pointLights[0].constant", 1.0f);//포인트 라이트의 상수값
	ModelShader.setFloat("pointLights[0].linear", 0.09);//포인트 라이트의 선형값(1차)
	ModelShader.setFloat("pointLights[0].quadratic", 0.032);//포인트 라이트의 이차값(2차)
	//아래 세개의 항들은 포인트 라이트를 사실적으로 감쇠하기위한 항이다.
	//총4개 설정가능
	// 쉐이더에 조명들이 몇개 들어갈지 미리선언했다.
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
	//손전등의 안쪽조명을 받을 각도
	ModelShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	//손전등의 바깥쪽 조명을 받을 각도 <-- 이 각도 사이에 있는 조명을 받는데 줄어들면서 받는다(실감나는 효과).

	

	model = glm::mat4(1.0f);
	ModelShader.setMat4("model", space_ship_model);//모델 쉐이더에 객체의 뭘드행렬을 넣어준다.
	TextureLoadManager::Instance()->Use("space_ship");//텍스쳐를 사용한다.
	ourModel.Draw(ModelShader);//모델을 그린다.
	glBindTexture(GL_TEXTURE_2D, 0);//텍스쳐를 언바인드한다.

	/*model = glm::mat4(1.0f);
	ModelShader.setMat4("model", model);
	TextureLoadManager::Instance()->Use("metal");
	ourPlane.Draw(ModelShader);
	glBindTexture(GL_TEXTURE_2D, 0);*/

	if (light_on)
	{
		lightCubeShader.Use();//조명의 위치를 보여주기위한 큐브들을 위한 쉐이더(모든색이 하얀색으로 설정됨)
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		// render the cube
		for (int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			//스케일이 먼저 적용
			lightCubeShader.setMat4("model", model);

			ourCube.Draw(lightCubeShader);

		}
	}
	
	cubeMapShader.Use();// 환경 매핑을 위한 쉐이더
	//동적 환경 매핑은 아니지만 skybox의 텍스쳐를 사용해서 굴절,반사를 표현한다.
	model = glm::mat4(1.0f);
	cubeMapShader.setMat4("view", view);
	cubeMapShader.setMat4("projection", projection);
	cubeMapShader.setMat4("model", model);
	cubeMapShader.setVec3("cameraPos", g_camera->GetPosition());
	ourPlane.Draw(cubeMapShader);
	glBindTexture(GL_TEXTURE_2D,0);
	
	
	




	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	// 깊이 함수 변경: 깊이 테스트가 깊이 버퍼의 내용과 값이 같을 때 통과
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
	glDepthFunc(GL_LESS); // 다시 원래설정으로 돌린다.

	
	// 이제 기본 프레임 버퍼로 돌아가서 색상 텍스쳐가 붙은 프레임 버퍼로 사각형을 그린다.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	// 깊이 테스트를 비활성화하여 화면 공간 사각형이 깊이 테스트로 인해 버려지지 않도록합니다.
	// 모든 버퍼를 클리어한다.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);// 흰색으로 설정(실제로는 필요하지 않지만, 사실 사각형 뒤로 볼 수 없기 때문에)
	glClear(GL_COLOR_BUFFER_BIT);

	screenShader.Use();//스크린 쉐이더를 사용한다. 프레임버퍼 내용을 전부 그린다.
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, screenTextureColorBuffer);	//컬러 결합자를 사용해서 quad의 내용을 텍스쳐로 화면을 그린다.
	glDrawArrays(GL_TRIANGLES, 0, 6);


	glutSwapBuffers();
}

GLvoid mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		g_camera->ProcessMouseScroll(1.0f);//fovy값변경
	}
	else
	{
		g_camera->ProcessMouseScroll(-1.0f);//fovy값변경
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

	g_camera->ProcessMouseMovement(xoffset, yoffset);
	glutPostRedisplay();
}


