#define BITMAP_SIZE 6
char charmap[][BITMAP_SIZE] = {
	{0x00,0x00}, // SPACE
	{0x5E}, // !
	{0x02,0x00,0x02}, // "
	{0x24,0x7E,0x24,0x7E,0x24}, // #
	{0x44,0x4A,0x7E,0x52,0x22}, // $
	{0x22,0x10,0x08,0x04,0x42}, // %
	{0x34,0x4A,0x54,0x20,0x40}, // &
	{0x02}, // '
	{0x18,0x24,0x42}, // (
	{0x42,0x24,0x18}, // )
	{0x54,0x38,0x7C,0x38,0x54}, // *
	{0x08,0x08,0x7E,0x08,0x08}, // +
	{0x40,0x20}, // ,
	{0x08,0x08,0x08}, // -
	{0x40}, // .
	{0x60,0x10,0x08,0x06}, // /
	{0x7E,0x52,0x4A,0x7E}, // 0
	{0x44,0x7E,0x40}, // 1
	{0x64,0x52,0x4A,0x44}, // 2
	{0x42,0x4A,0x34}, // 3
	{0x18,0x14,0x7E,0x10}, // 4
	{0x4E,0x4A,0x32}, // 5
	{0x3C,0x4A,0x4A,0x32}, // 6
	{0x6E,0x1A,0x06}, // 7
	{0x34,0x4A,0x4A,0x34}, // 8
	{0x4C,0x52,0x56,0x3C}, // 9
	{0x14}, // :
	{0x20,0x14}, // ;
	{0x10,0x28,0x44}, // <
	{0x28,0x28,0x28}, // =
	{0x44,0x28,0x10}, // >
	{0x02,0x5A,0x04}, // ?
	{0x7E,0x42,0x5A,0x52,0x5E}, // @
	{0x7E,0x12,0x12,0x7e}, //A
	{0x7E,0x4a,0x4a,0x34}, //B
	{0x7e,0x42,0x42,0x42}, //C
	{0x7E,0x42,0x42,0x3C}, //D
	{0x7E,0x52,0x52,0x42}, //E
	{0x7E,0x12,0x12,0x02}, //F
	{0x7E,0x42,0x42,0x72}, //G
	{0x7E,0x10,0x10,0x7E}, //H
	{0x42,0x7E,0x42,0x00}, //I
	{0x62,0x42,0x7E,0x02}, //J
	{0x7E,0x18,0x24,0x42}, //K
	{0x7E,0x40,0x40,0x40}, //L
	{0x7E,0x04,0x04,0x7E}, //M
	{0x7E,0x0C,0x30,0x7E}, //N
	{0x7E,0x42,0x42,0x7E}, //O
	{0x7E,0x12,0x12,0x1E}, //P
	{0x7E,0x42,0x4A,0x7E}, //Q
	{0x7E,0x12,0x32,0x6E}, //R
	{0x4E,0x4A,0x4A,0x72}, //S
	{0x02,0x7E,0x02,0x02}, //T
	{0x7E,0x40,0x40,0x7E}, //U
	{0x3E,0x60,0x60,0x3E}, //V
	{0x7E,0x20,0x20,0x7E}, //W
	{0x66,0x3C,0x3C,0x66}, //X
	{0x1E,0x10,0x10,0x7E}, //Y
	{0x62,0x52,0x4C,0x46}, //Z
	{0x7E,0x42},  // [
	{0x06,0x08,0x10,0x60}, // BACKSPACE
	{0x42,0x7E}, // ]
	{0x04,0x02,0x04}, // ^
	{0x40,0x40,0x40}, // _
	{0x02,0x04}, // `
	{0x7E,0x7E,0x7E} // UNKNOWN OR NOT SUPPORTED
	
};
