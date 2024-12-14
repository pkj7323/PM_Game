#pragma once
#include "stdafx.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 30.f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 45.0f;

class SpaceSpip;
// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{

	// calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
    
public:
	Camera();
	// Constructor with vectors

	~Camera();
    //Yaw is rotated by degree
    void CameraYaw(float degree);
    void SetPosition(glm::vec3 position);
    void SetCamera(glm::vec3 Position = glm::vec3(0, 5, 10), glm::vec3 WorldUp = glm::vec3(0, 1, 0)
        , float Yawdegree = YAW, float pitchdegree = PITCH, float zoom = ZOOM
        , float speed = SPEED, float sensitivity = SENSITIVITY);

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction , const bool is_roll);
    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    void Move(const bool is_roll);
    //processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

   
    glm::vec3 GetPosition() const { return Position; }
	glm::vec3 GetFront() const { return Front; }
    glm::vec3 GetUp() const { return Up; }
    glm::vec3 GetRight() const { return Right; }
	// calculate the perspective matrix zoom=degree
    void SetPerspective(float zoom, float _aspect, float _near,float _far );

    glm::mat4 GetOrtho();


	// return PerspectiveMatrix
    glm::mat4 GetPerspectiveMatrix() const;
	void OrbitAroundOrigin(float angle);

	float GetNear() const { return m_Near; }
	float GetFar() const { return m_Far; }
    float GetSpeed() const { return MovementSpeed; }
    float GetYaw() const { return Yaw; }
    float GetPitch() const { return Pitch; }

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() const;


    
private:
    void setBillBoard();
	GLuint BillBoard_VAO = 0;
	GLuint BillBoard_VBO;
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    glm::mat4 PerspectiveMatrix;

    //움직임 처리
    bool left{};
    bool right{};
    bool front{};
    bool back{};


    // euler Angles
    float Yaw;//degree
	float Pitch;//degree

    // camera options
    float MovementSpeed;
    float MouseSensitivity;

    float Zoom;
    float m_aspect;
	float m_Near;
	float m_Far;

    
};
