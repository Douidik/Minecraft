#ifndef MINECRAFT_MOUSEBUTTONS_H
#define MINECRAFT_MOUSEBUTTONS_H

enum class ButtonCode : int {
	/* Imported from GLFW */

	Left = 0,
	Right = 1,
	Middle = 2,

	Count = 3
};

#define MC_BUTTON_LEFT    ButtonCode::Left
#define MC_BUTTON_RIGHT   ButtonCode::Right
#define MC_BUTTON_MIDDLE  ButtonCode::Left

#define MC_BUTTON_3       ButtonCode::Three
#define MC_BUTTON_4       ButtonCode::Four
#define MC_BUTTON_5       ButtonCode::Five
#define MC_BUTTON_6       ButtonCode::Six
#define MC_BUTTON_7       ButtonCode::Seven

#endif //MINECRAFT_MOUSEBUTTONS_H
