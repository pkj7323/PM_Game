#include "stdafx.h"
#include "KeyManager.h"

int arrVK[(int)KEY::LAST]{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
	VK_MENU,
	VK_LSHIFT,
	VK_END,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
	//LAST
};
KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

void KeyManager::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		vecKey.emplace_back(KeyInfo{ KEY_STATE::NONE,false });
	}
}

void KeyManager::Update()
{
	HWND hWnd = GetFocus();

	//윈도우 포커싱 중일때 (현재 창이 있음)
	if (hWnd != nullptr)
	{
		//모든 키에 대해서 키가 눌렸는가 체크
		for (size_t i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			if (GetAsyncKeyState(arrVK[i]) & 0x8000) //0x8000<-이거 하고 키가 같아지면 눌렸다는 의미 
				//&==(AND)비트연산자
			{
				//현재 프레임에 눌려진 키인데
				if (vecKey[i].prev)
				{
					//이전 프레임에 눌려진 키
					vecKey[i].state = KEY_STATE::HOLD;
				}
				else
				{
					//이전 프레임에 눌려지지 않은 키
					vecKey[i].state = KEY_STATE::TAP;
				}
				vecKey[i].prev = true;
			}
			else
			{
				//현재 프레임에 눌려지지 않은 키
				if (vecKey[i].prev)
				{
					vecKey[i].state = KEY_STATE::AWAY;
				}
				else
				{
					vecKey[i].state = KEY_STATE::NONE;
				}
				vecKey[i].prev = false;
			}
		}
	}
	//그렇지 않을 때
	else
	{
		//윈도우 포커싱이 없을 때
		for (size_t i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{

			vecKey[i].prev = false;
			if (KEY_STATE::TAP == vecKey[i].state
				|| KEY_STATE::HOLD == vecKey[i].state)
			{
				vecKey[i].state = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == vecKey[i].state)
			{
				vecKey[i].state = KEY_STATE::NONE;
			}
		}
	}




}
