#pragma once
extern unsigned char temp_key;
extern unsigned char temp_keya;
extern unsigned char temp_keyb;
extern bool switcher;
class Board
{
	public:
	bool active;
	bool cursor_end_position;
	int x,y, dx, dy;
	int x_start;
	int y_start;
	int x_final;
	int y_final;
	int x_turn;
	int y_turn;
	int matrix[30][30];
	bool turn_allowed;
	Board();
	void MovePass();
	void Matrix_Fill();
};
