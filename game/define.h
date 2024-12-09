#pragma once
#include "stdafx.h"
#define SINGLE(type) public:\
			static type* Instance()\
			{\
			static type instance;\
			return &instance;\
			}\
			private:\
			type();\
			~type();

#define KEY_CHECK(key, state) KeyManager::Instance()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define DT TimeManager::Instance()->GetDeltaTime()
struct FunctionWrapper {
	std::function<bool(std::pair<std::string, int>)> func;

	bool operator==(const FunctionWrapper& other) const {
		// 주의: 함수의 비교는 일반적으로 불가능하므로, 동일함을 보장할 수 없음.
		return func.target_type() == other.func.target_type();
	}
};

struct FunctionHash {
	std::size_t operator()(const FunctionWrapper& wrapper) const {
		// 함수 타입의 해시 코드 사용 (주소와 비슷한 효과)
		return std::hash<std::string>{}(wrapper.func.target_type().name());
	}
};
enum class SCENE_TYPE
{
	INTRO,
	START,
	STAGE1,
	STAGE2,
	END
};


namespace math {
	static std::default_random_engine dre{ std::random_device{}() };
	static const float PI = 3.14159265358979323846f;
	static void convertToWorldForVec2(float& x, float& y)
	{
		auto width = glutGet(GLUT_WINDOW_WIDTH);
		auto height = glutGet(GLUT_WINDOW_HEIGHT);
		x = (x - width / 2.f) / glm::abs(width / 2.f);
		y = (y - height / 2.f) / glm::abs(height / 2.f);
		y = -y;
	}
	static void screenToClip(float& x, float& y)
	{
		auto width = glutGet(GLUT_WINDOW_WIDTH);
		auto height = glutGet(GLUT_WINDOW_HEIGHT);
		x = (x / width) * 2.0f - 1.0f; 
		y = 1.0f - (y / height) * 2.0f; 
	}
	static void Rotate(float& x, float& y, float theta)
	{
		float tempX = x;
		float tempY = y;
		theta = glm::radians(theta);
		x = tempX * cos(theta) - tempY * sin(theta);
		y = tempX * sin(theta) + tempY * cos(theta);
	}
	static glm::vec3 normalize(glm::vec3& v)
	{
		float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		if (length == 0)
			return v;
		v.x /= length;
		v.y /= length;
		v.z /= length;
		return v;
	}
	static void normalize(float& x, float& y)
	{
		float length = sqrt(x * x + y * y);
		if (length == 0)
			return;
		x /= length;
		y /= length;
	}
	static void normalize(glm::vec2& v)
	{
		float length = sqrt(v.x * v.x + v.y * v.y);
		if (length == 0)
			return;
		v.x /= length;
		v.y /= length;
	}
	static void ViewToWorld(float& x, float& y)
	{
		auto width = glutGet(GLUT_WINDOW_WIDTH);
		auto height = glutGet(GLUT_WINDOW_HEIGHT);
		x = x * glm::abs(width / 2.f) + width / 2.f;
		y = y * -(glm::abs(height / 2.f)) + height / 2.f;
	}
	static void RotateV2(float& x, float& y, float theta)
	{
		theta = glm::radians(theta);
		float tempX = x;
		float tempY = y;
		x = tempX * cos(theta) - tempY * sin(theta);
		y = tempX * sin(theta) + tempY * cos(theta);
	}
	static void RotateV2(glm::vec2& v, float theta)
	{
		theta = glm::radians(theta);
		float tempX = v.x;
		float tempY = v.y;
		v.x = tempX * cos(theta) - tempY * sin(theta);
		v.y = tempX * sin(theta) + tempY * cos(theta);
	}
	static void RotateV3(glm::vec3& v, float theta)
	{
		theta = glm::radians(theta);
		float tempX = v.x;
		float tempY = v.y;
		v.x = tempX * cos(theta) - tempY * sin(theta);
		v.y = tempX * sin(theta) + tempY * cos(theta);
	}
}
//struct Vec2
//{
//	Vec2() : x{}, y{} { }
//	Vec2(float x, float y) : x{ x }, y{ y } { }
//	Vec2 operator + (const Vec2& other) {
//		return Vec2(x + other.x, y + other.y);
//	}
//	Vec2 operator +=(const Vec2& other) {
//		x += other.x;
//		y += other.y;
//		return *this;
//	}
//	float x;
//	float y;
//};
//struct GLRECT
//{
//	enum class moveway{
//		way1,
//		way2,
//		end
//	};
//	enum class rectChange {
//		sizeChange,
//		colorChange,
//		end
//	};
//	enum class howMove {
//		leftBottom,
//		leftTop,
//		rightBottom,
//		rightTop,
//		end
//	};
//	GLRECT() : left{}, top{}, right{}, bottom{}, size{}, pos{}
//		, color{}, how{ howMove::leftBottom }, way{ moveway::end }, rc{ rectChange::end }
//	{ }
//	GLRECT(GLfloat left, GLfloat top, GLfloat right, GLfloat bottom)
//		: left{ left }, top{ top }, right{ right }, bottom{ bottom }
//		, color{}, how{ howMove::leftBottom }, way{ moveway::end }, rc{ rectChange::end }
//	{
//		size	= Vec2(right - left, top - bottom);
//		pos		= Vec2(left + size.x / 2, bottom + size.y / 2);
//	}
//	GLRECT(Vec2 pivot, Vec2 size) : pos{ pivot }, size{ size }, how{ howMove::leftBottom }, way{ moveway::end }, rc{ rectChange::end }
//		,  color{} {
//		left	= pos.x - size.x / 2;
//		right	= pos.x + size.x / 2;
//		top		= pos.y + size.y / 2;
//		bottom	= pos.y - size.y / 2;
//	}
//	GLRECT(Vec2 pivot, Vec2 size,RGBA color) : pos{ pivot }, size{ size }, how{ howMove::leftBottom }, way{ moveway::end }, rc{ rectChange::end }
//		, color{color} {
//		left	= pos.x - size.x / 2;
//		right	= pos.x + size.x / 2;
//		top		= pos.y + size.y / 2;
//		bottom	= pos.y - size.y / 2;
//	}
//	bool isOverlapping(const GLRECT& other) {
//		if (left > other.right || right < other.left || top < other.bottom || bottom > other.top)
//			return false;
//		else
//			return true;
//	}
//	void repos(Vec2 pivot) {
//		pos		= pivot;
//		left	= pos.x - size.x / 2;
//		right	= pos.x + size.x / 2;
//		top		= pos.y + size.y / 2;
//		bottom	= pos.y - size.y / 2;
//	}
//	void scaling(const float& deltaSize) {
//		if (getScale()*100 > 3)
//		{
//			left	-= deltaSize;
//			top		+= deltaSize;
//			right	+= deltaSize;
//			bottom	-= deltaSize;
//		}
//	}
//	float getScale() {
//		return (right - left) * (top - bottom);
//	}
//	bool isInRect(const float& x, const float& y) {
//		if (x >= left && x <= right && y <= top && y >= bottom)//좌표계가 달라졌음 y가 반대가됨
//			return true;
//		else
//			return false;
//	}
//	void convertToWorldRect(const int width, const int height) {
//		math::convertToWorldForVec2(left, top);
//		math::convertToWorldForVec2(right, bottom);
//	}
//	void function() {
//		switch (way)
//		{
//		case GLRECT::moveway::way1:
//			move1();
//			break;
//		case GLRECT::moveway::way2:
//			move2();
//			break;
//		default:
//			break;
//		}
//
//		switch (rc)
//		{
//		case GLRECT::rectChange::sizeChange:
//		{
//			
//			std::random_device rd;
//			std::default_random_engine dre(rd());
//			std::uniform_real_distribution<float> dis(0.0f, 1.0f);
//			size = Vec2(dis(dre), dis(dre));
//			repos(pos);
//		}
//			break;
//		case GLRECT::rectChange::colorChange:
//		{
//			std::random_device rd;
//			std::default_random_engine dre(rd());
//			std::uniform_real_distribution<float> dis(0.0f, 1.0f);
//			color = RGBA(dis(dre), dis(dre), dis(dre), 1.0f);
//		}
//			break;
//		default:
//			break;
//		}
//		
//	}
//	void checkCoordinateFromWindow() {
//		if (pos.x - size.x < -1.0f)
//		{
//			switch (how)
//			{
//			case GLRECT::howMove::leftBottom:
//				how = GLRECT::howMove::rightBottom;
//				break;
//			case GLRECT::howMove::leftTop:
//				how = GLRECT::howMove::rightTop;
//				break;
//			default:
//				break;
//			}
//		}
//		else if (pos.y + size.y > 1.0f)
//		{
//			switch (how)
//			{
//			case GLRECT::howMove::leftTop:
//				how = GLRECT::howMove::rightBottom;
//				break;
//			case GLRECT::howMove::rightTop:
//				how = GLRECT::howMove::leftBottom;
//				break;
//			default:
//				break;
//			}
//		}
//		else if (pos.x + size.x > 1.0f)
//		{
//			switch (how)
//			{
//			case GLRECT::howMove::rightBottom:
//				how = GLRECT::howMove::leftBottom;
//				break;
//			case GLRECT::howMove::rightTop:
//				how = GLRECT::howMove::leftTop;
//				break;
//			default:
//				break;
//			}
//		}
//		else if (pos.y - size.y < -1.0f)
//		{
//			switch (how)
//			{
//			case GLRECT::howMove::rightBottom:
//				how = GLRECT::howMove::rightTop;
//				break;
//			case GLRECT::howMove::leftBottom:
//				how = GLRECT::howMove::leftTop;
//				break;
//			default:
//				break;
//			}
//		}
//	}
//	void draw() {
//		glColor4f(color.r, color.g, color.b, color.a);
//		glRectf(left, top, right, bottom);
//	}
//private:
//	void move1() {
//		Vec2 d;
//		switch (how)
//		{
//		case GLRECT::howMove::leftBottom:
//			d.x = -0.05f;
//			d.y = -0.05f;
//			break;
//		case GLRECT::howMove::leftTop:
//			d.x = -0.05f;
//			d.y = 0.05f;
//			break;
//		case GLRECT::howMove::rightBottom:
//			d.x = 0.05f;
//			d.y = -0.05f;
//			break;
//		case GLRECT::howMove::rightTop:
//			d.x = 0.05f;
//			d.y = 0.05f;
//			break;
//		default:
//			break;
//		}
//		
//		pos += d;
//		checkCoordinateFromWindow();//벽에 튕기게 세팅하는 코드
//		repos(pos);
//	}
//	void move2() {
//		Vec2 d;
//		static int count = 1;
//		switch (how)
//		{
//		case GLRECT::howMove::leftBottom:
//			d.x = -0.05f;
//			d.y = -0.05f;
//			if (count == 0)
//			{
//				how = howMove::rightBottom;
//			}
//			break;
//		case GLRECT::howMove::leftTop:
//			d.x = -0.05f;
//			d.y = 0.05f;
//			if (count == 0)
//			{
//				how = howMove::rightTop;
//			}
//			break;
//		case GLRECT::howMove::rightBottom:
//			d.x = 0.05f;
//			d.y = -0.05f;
//			if (count == 0)
//			{
//				how = howMove::leftBottom;
//			}
//			break;
//		case GLRECT::howMove::rightTop:
//			d.x = 0.05f;
//			d.y = 0.05f;
//			if (count == 0)
//			{
//				how = howMove::leftTop;
//			}
//			break;
//		default:
//			break;
//		}
//		count = (count + 1) % 3;
//
//		
//		pos += d;
//		checkCoordinateFromWindow();//벽에 튕기게 세팅하는 코드
//		repos(pos);
//	}
//public:	
//	moveway way;
//	howMove how;
//	rectChange rc;
//	GLfloat left;
//	GLfloat top;
//	GLfloat right;
//	GLfloat bottom;
//	Vec2 size;
//	Vec2 pos;
//	RGBA color;
//	
//};
//class ChildRect : public GLRECT
//{
//public:
//	enum class moveWay4 {
//		left,
//		right,
//		top,
//		bottom,
//		leftBottom,
//		leftTop,
//		rightBottom,
//		rightTop,
//	};
//	ChildRect(Vec2 pos, RGBA color, moveWay4 way4) : GLRECT(pos, Vec2(0.3f, 0.3f),color), isDeath{ false }
//	{
//		this->way4 = way4;
//		repos(pos);
//	}
//	
//	
//	void to_death()
//	{
//		if (this->size.x < 0.05f || this->size.y < 0.05f)
//		{
//			isDeath = true;
//		}
//	}
//	void shrink()
//	{
//		if (!isDeath)
//		{
//			this->size.x -= 0.01f;
//			this->size.y -= 0.01f;
//			repos(pos);
//		}
//
//	}
//	void childMove() {
//		Vec2 d;
//		switch (way4)
//		{
//		case moveWay4::left:
//			d.x = -0.05f;
//			d.y = 0.0f;
//			break;
//		case moveWay4::right:
//			d.x = 0.05f;
//			d.y = 0.0f;
//			break;
//		case moveWay4::top:
//			d.x = 0.0f;
//			d.y = 0.05f;
//			break;
//		case moveWay4::bottom:
//			d.x = 0.0f;
//			d.y = -0.05f;
//			break;
//		case moveWay4::leftBottom:
//			d.x = -0.05f;
//			d.y = -0.05f;
//			break;
//		case moveWay4::leftTop:
//			d.x = -0.05f;
//			d.y = 0.05f;
//			break;
//		case moveWay4::rightBottom:
//			d.x = 0.05f;
//			d.y = -0.05f;
//			break;
//		case moveWay4::rightTop:
//			d.x = 0.05f;
//			d.y = 0.05f;
//			break;
//		default:
//			break;
//		}
//		pos += d;
//		shrink();
//		repos(pos);
//		to_death();
//	}
//	void setWay4(moveWay4 way) {
//		way4 = way;
//	}
//	bool GetDeath()
//	{
//		return isDeath;
//	}
//private:
//	bool isDeath = false;
//	moveWay4 way4;
//};
//#define MAX_LINE_LENGTH 1024
//struct model
//{
//	model(const string& filename) {
//		if (filename == "NULL")
//		{
//			return;
//		}
//
//		std::ifstream file(filename);
//		if (!file.is_open()) {
//			std::cerr << "Error opening file" << std::endl;
//			exit(EXIT_FAILURE);
//		}
//
//		std::string line;
//		while (std::getline(file, line)) {
//			if (line.substr(0, 2) == "v ") {
//				glm::vec3 temp;
//				std::istringstream s(line.substr(2));
//				s >> temp.x >> temp.y >> temp.z;
//				this->vertices.push_back(temp);
//			}
//			else if (line.substr(0, 2) == "vn")
//			{
//				glm::vec3 temp;
//				std::istringstream s(line.substr(3));
//				s >> temp.x >> temp.y >> temp.z;
//				this->normals.push_back(temp);
//			}
//			else if (line.substr(0, 2) == "vt")
//			{
//				glm::vec3 temp;
//				std::istringstream s(line.substr(3));
//				s >> temp.x >> temp.y >> temp.z;
//				this->texture_coords.push_back(temp);
//			}
//			else if (line.substr(0, 2) == "f ") {
//				std::istringstream s(line.substr(2));
//				std::vector<std::string> tokens;
//				std::string token;
//				while (s >> token) {
//					tokens.push_back(token);
//				}
//				vector<UINT> v;
//				vector<UINT> vt;
//				vector<UINT> vn;
//				for (int i = 0; i < tokens.size(); ++i)
//				{
//					
//					
//					// 1/2/3 1//3  1
//					if(tokens[i].find("/") == std::string::npos)
//					{
//						UINT v1;
//						std::stringstream ss(tokens[i]);
//						ss >> v1;
//						v.push_back(v1);
//						continue;
//					}
//					else
//					{
//						tokens[i].replace(tokens[i].find("/"), 1, " ");
//						std::stringstream ss(tokens[i]);
//
//						if (tokens[i].find("  ") != std::string::npos)
//						{
//							UINT v1, vn1;
//							ss >> v1 >> vn1;
//							v.push_back(v1);
//							vn.push_back(vn1);
//						}
//						else if (tokens[i].find(" ") != std::string::npos)
//						{
//							UINT v1, vn1, vt1;
//							ss >> v1 >> vt1 >> vn1;
//							v.push_back(v1);
//							vt.push_back(vt1);
//							vn.push_back(vn1);
//						}
//						else
//						{
//							UINT v1;
//							ss >> v1;
//							v.push_back(v1);
//						}
//					}
//					
//				}
//				if (v.size()>0)
//				{
//					this->faces.emplace_back(v[0] - 1, v[1] - 1, v[2] - 1);
//				}
//				if (vn.size()>0)
//				{
//					this->normal_faces.emplace_back(vn[0] - 1, vn[1] - 1, vn[2] - 1);
//				}
//				if (vt.size() > 0)
//				{
//					this->texture_faces.emplace_back(vt[0] - 1, vt[1] - 1, vt[2] - 1);
//				}
//				
//			}
//		}
//		file.close();
//	}
//	vector<glm::vec3>	vertices;
//	vector<glm::vec3>	colors;
//	vector<glm::vec3>	normals;
//	vector<glm::vec3>	texture_coords;
//	vector<glm::uvec3>	faces;
//	vector<glm::uvec3>	normal_faces;
//	vector<glm::uvec3>	texture_faces;
//};



