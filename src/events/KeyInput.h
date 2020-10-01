#ifndef MINECRAFT_KEYINPUT_H
#define MINECRAFT_KEYINPUT_H

enum class KeyInputType
{
	None,
	Released,
	Pressed,
	Repeated
};

struct KeyInput
{
	KeyInput() = default;

	KeyInput(int _code, KeyInputType _type)
		: code(_code), type(_type)
	{}

	int code;
	KeyInputType type;
};

struct KeyPressed : public KeyInput
{
	KeyPressed(int _code)
		: KeyInput(_code, KeyInputType::Pressed)
	{}
};

struct KeyReleased : public KeyInput
{
	KeyReleased(int _code)
		: KeyInput(_code, KeyInputType::Released)
	{}
};

struct KeyRepeated : public KeyInput
{
	KeyRepeated(int _code)
		: KeyInput(_code, KeyInputType::Repeated)
	{}
};

#endif //MINECRAFT_KEYINPUT_H
