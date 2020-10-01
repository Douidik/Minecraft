#ifndef MINECRAFT_KEYCODES_H
#define MINECRAFT_KEYCODES_H

enum class KeyCode : int {
	/* Imported from GLFW */
	Space               = 32,
	Apostrophe          = 39, /* ' */
	Comma               = 44, /* , */
	Minus               = 45, /* - */
	Period              = 46, /* . */
	Slash               = 47, /* / */

	D0                  = 48, /* 0 */
	D1                  = 49, /* 1 */
	D2                  = 50, /* 2 */
	D3                  = 51, /* 3 */
	D4                  = 52, /* 4 */
	D5                  = 53, /* 5 */
	D6                  = 54, /* 6 */
	D7                  = 55, /* 7 */
	D8                  = 56, /* 8 */
	D9                  = 57, /* 9 */

	Semicolon           = 59, /* ; */
	Equal               = 61, /* = */

	A                   = 65,
	B                   = 66,
	C                   = 67,
	D                   = 68,
	E                   = 69,
	F                   = 70,
	G                   = 71,
	H                   = 72,
	I                   = 73,
	J                   = 74,
	K                   = 75,
	L                   = 76,
	M                   = 77,
	N                   = 78,
	O                   = 79,
	P                   = 80,
	Q                   = 81,
	R                   = 82,
	S                   = 83,
	T                   = 84,
	U                   = 85,
	V                   = 86,
	W                   = 87,
	X                   = 88,
	Y                   = 89,
	Z                   = 90,

	LeftBracket         = 91,  /* [ */
	Backslash           = 92,  /* \ */
	RightBracket        = 93,  /* ] */
	GraveAccent         = 96,  /* ` */

	World1              = 161, /* non-US #1 */
	World2              = 162, /* non-US #2 */

	/* Function keys */
	Escape              = 256,
	Enter               = 257,
	Tab                 = 258,
	Backspace           = 259,
	Insert              = 260,
	Delete              = 261,
	Right               = 262,
	Left                = 263,
	Down                = 264,
	Up                  = 265,
	PageUp              = 266,
	PageDown            = 267,
	Home                = 268,
	End                 = 269,
	CapsLock            = 280,
	ScrollLock          = 281,
	NumLock             = 282,
	PrintScreen         = 283,
	Pause               = 284,
	F1                  = 290,
	F2                  = 291,
	F3                  = 292,
	F4                  = 293,
	F5                  = 294,
	F6                  = 295,
	F7                  = 296,
	F8                  = 297,
	F9                  = 298,
	F10                 = 299,
	F11                 = 300,
	F12                 = 301,
	F13                 = 302,
	F14                 = 303,
	F15                 = 304,
	F16                 = 305,
	F17                 = 306,
	F18                 = 307,
	F19                 = 308,
	F20                 = 309,
	F21                 = 310,
	F22                 = 311,
	F23                 = 312,
	F24                 = 313,
	F25                 = 314,

	/* Keypad */
	KP0                 = 320,
	KP1                 = 321,
	KP2                 = 322,
	KP3                 = 323,
	KP4                 = 324,
	KP5                 = 325,
	KP6                 = 326,
	KP7                 = 327,
	KP8                 = 328,
	KP9                 = 329,
	KPDecimal           = 330,
	KPDivide            = 331,
	KPMultiply          = 332,
	KPSubtract          = 333,
	KPAdd               = 334,
	KPEnter             = 335,
	KPEqual             = 336,

	LeftShift           = 340,
	LeftControl         = 341,
	LeftAlt             = 342,
	LeftSuper           = 343,
	RightShift          = 344,
	RightControl        = 345,
	RightAlt            = 346,
	RightSuper          = 347,
	Menu                = 348,

	Count = 349
};

#define MC_KEY_SPACE           KeyCode::Space
#define MC_KEY_APOSTROPHE      KeyCode::Apostrophe    /* ' */
#define MC_KEY_COMMA           KeyCode::Comma         /* , */
#define MC_KEY_MINUS           KeyCode::Minus         /* - */
#define MC_KEY_PERIOD          KeyCode::Period        /* . */
#define MC_KEY_SLASH           KeyCode::Slash         /* / */
#define MC_KEY_0               KeyCode::D0
#define MC_KEY_1               KeyCode::D1
#define MC_KEY_2               KeyCode::D2
#define MC_KEY_3               KeyCode::D3
#define MC_KEY_4               KeyCode::D4
#define MC_KEY_5               KeyCode::D5
#define MC_KEY_6               KeyCode::D6
#define MC_KEY_7               KeyCode::D7
#define MC_KEY_8               KeyCode::D8
#define MC_KEY_9               KeyCode::D9
#define MC_KEY_SEMICOLON       KeyCode::Semicolon     /* ; */
#define MC_KEY_EQUAL           KeyCode::Equal         /* = */
#define MC_KEY_A               KeyCode::A
#define MC_KEY_B               KeyCode::B
#define MC_KEY_C               KeyCode::C
#define MC_KEY_D               KeyCode::D
#define MC_KEY_E               KeyCode::E
#define MC_KEY_F               KeyCode::F
#define MC_KEY_G               KeyCode::G
#define MC_KEY_H               KeyCode::H
#define MC_KEY_I               KeyCode::I
#define MC_KEY_J               KeyCode::J
#define MC_KEY_K               KeyCode::K
#define MC_KEY_L               KeyCode::L
#define MC_KEY_M               KeyCode::M
#define MC_KEY_N               KeyCode::N
#define MC_KEY_O               KeyCode::O
#define MC_KEY_P               KeyCode::P
#define MC_KEY_Q               KeyCode::Q
#define MC_KEY_R               KeyCode::R
#define MC_KEY_S               KeyCode::S
#define MC_KEY_T               KeyCode::T
#define MC_KEY_U               KeyCode::U
#define MC_KEY_V               KeyCode::V
#define MC_KEY_W               KeyCode::W
#define MC_KEY_X               KeyCode::X
#define MC_KEY_Y               KeyCode::Y
#define MC_KEY_Z               KeyCode::Z
#define MC_KEY_LEFT_BRACKET    KeyCode::LeftBracket   /* [ */
#define MC_KEY_BACKSLASH       KeyCode::Backslash     /* \ */
#define MC_KEY_RIGHT_BRACKET   KeyCode::RightBracket  /* ] */
#define MC_KEY_GRAVE_ACCENT    KeyCode::GraveAccent   /* ` */
#define MC_KEY_WORLD_1         KeyCode::World1        /* non-US #1 */
#define MC_KEY_WORLD_2         KeyCode::World2        /* non-US #2 */

/* Function keys */
#define MC_KEY_ESCAPE          KeyCode::Escape
#define MC_KEY_ENTER           KeyCode::Enter
#define MC_KEY_TAB             KeyCode::Tab
#define MC_KEY_BACKSPACE       KeyCode::Backspace
#define MC_KEY_INSERT          KeyCode::Insert
#define MC_KEY_DELETE          KeyCode::Delete
#define MC_KEY_RIGHT           KeyCode::Right
#define MC_KEY_LEFT            KeyCode::Left
#define MC_KEY_DOWN            KeyCode::Down
#define MC_KEY_UP              KeyCode::Up
#define MC_KEY_PAGE_UP         KeyCode::PageUp
#define MC_KEY_PAGE_DOWN       KeyCode::PageDown
#define MC_KEY_HOME            KeyCode::Home
#define MC_KEY_END             KeyCode::End
#define MC_KEY_CAPS_LOCK       KeyCode::CapsLock
#define MC_KEY_SCROLL_LOCK     KeyCode::ScrollLock
#define MC_KEY_NUM_LOCK        KeyCode::NumLock
#define MC_KEY_PRINT_SCREEN    KeyCode::PrintScreen
#define MC_KEY_PAUSE           KeyCode::Pause
#define MC_KEY_F1              KeyCode::F1
#define MC_KEY_F2              KeyCode::F2
#define MC_KEY_F3              KeyCode::F3
#define MC_KEY_F4              KeyCode::F4
#define MC_KEY_F5              KeyCode::F5
#define MC_KEY_F6              KeyCode::F6
#define MC_KEY_F7              KeyCode::F7
#define MC_KEY_F8              KeyCode::F8
#define MC_KEY_F9              KeyCode::F9
#define MC_KEY_F10             KeyCode::F10
#define MC_KEY_F11             KeyCode::F11
#define MC_KEY_F12             KeyCode::F12
#define MC_KEY_F13             KeyCode::F13
#define MC_KEY_F14             KeyCode::F14
#define MC_KEY_F15             KeyCode::F15
#define MC_KEY_F16             KeyCode::F16
#define MC_KEY_F17             KeyCode::F17
#define MC_KEY_F18             KeyCode::F18
#define MC_KEY_F19             KeyCode::F19
#define MC_KEY_F20             KeyCode::F20
#define MC_KEY_F21             KeyCode::F21
#define MC_KEY_F22             KeyCode::F22
#define MC_KEY_F23             KeyCode::F23
#define MC_KEY_F24             KeyCode::F24
#define MC_KEY_F25             KeyCode::F25

/* Keypad */
#define MC_KEY_KP_0            KeyCode::KP0
#define MC_KEY_KP_1            KeyCode::KP1
#define MC_KEY_KP_2            KeyCode::KP2
#define MC_KEY_KP_3            KeyCode::KP3
#define MC_KEY_KP_4            KeyCode::KP4
#define MC_KEY_KP_5            KeyCode::KP5
#define MC_KEY_KP_6            KeyCode::KP6
#define MC_KEY_KP_7            KeyCode::KP7
#define MC_KEY_KP_8            KeyCode::KP8
#define MC_KEY_KP_9            KeyCode::KP9
#define MC_KEY_KP_DECIMAL      KeyCode::KPDecimal
#define MC_KEY_KP_DIVIDE       KeyCode::KPDivide
#define MC_KEY_KP_MULTIPLY     KeyCode::KPMultiply
#define MC_KEY_KP_SUBTRACT     KeyCode::KPSubtract
#define MC_KEY_KP_ADD          KeyCode::KPAdd
#define MC_KEY_KP_ENTER        KeyCode::KPEnter
#define MC_KEY_KP_EQUAL        KeyCode::KPEqual

#define MC_KEY_LEFT_SHIFT      KeyCode::LeftShift
#define MC_KEY_LEFT_CONTROL    KeyCode::LeftControl
#define MC_KEY_LEFT_ALT        KeyCode::LeftAlt
#define MC_KEY_LEFT_SUPER      KeyCode::LeftSuper
#define MC_KEY_RIGHT_SHIFT     KeyCode::RightShift
#define MC_KEY_RIGHT_CONTROL   KeyCode::RightControl
#define MC_KEY_RIGHT_ALT       KeyCode::RightAlt
#define MC_KEY_RIGHT_SUPER     KeyCode::RightSuper
#define MC_KEY_MENU            KeyCode::Menu


#endif //MINECRAFT_KEYCODES_H
