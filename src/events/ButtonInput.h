#ifndef MINECRAFT_BUTTONINPUT_H
#define MINECRAFT_BUTTONINPUT_H

enum class ButtonInputType
{
	None,
	Released,
	Pressed,
};

struct ButtonInput
{
	ButtonInput() = default;

	ButtonInput(int _code, ButtonInputType _type)
			: code(_code), type(_type)
	{}

	int code;
	ButtonInputType type;
};

struct ButtonPressed : public ButtonInput
{
	ButtonPressed(int _code)
			: ButtonInput(_code, ButtonInputType::Pressed)
	{}
};

struct ButtonReleased : public ButtonInput
{
	ButtonReleased(int _code)
			: ButtonInput(_code, ButtonInputType::Released)
	{}
};

#endif //MINECRAFT_BUTTONINPUT_H
