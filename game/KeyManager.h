#pragma once
enum class KEY_STATE {
	NONE,
	TAP,
	HOLD,
	AWAY
};
enum class KEY {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	SPACE,
	ENTER,
	ESC,
	ALT,
	LSHIFT,
	END,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,



	LAST
};

struct KeyInfo
{
	KEY_STATE	state;
	bool		prev;
};

class KeyManager
{
	SINGLE(KeyManager)
public:
	void Init();
	void Update();
	
	KEY_STATE GetKeyState(KEY key) { return vecKey[(int)key].state; }
private:
	
	vector<KeyInfo>	vecKey;
	WORD keyDataSize = 512;
};

