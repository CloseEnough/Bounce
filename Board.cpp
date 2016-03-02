#pragma once
#include "board.h"
Board::Board()
{
	x = 1;
	y = 1;
	active = false;
	for (int i = 0; i < 29; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < 30; i++)
	{
		matrix[i][0] = 1;
	}
	for (int i = 0; i < 30; i++)
	{
		matrix[i][29] = 1;
	}
	for (int i = 0; i < 30; i++)
	{
		matrix[0][i] = 1;
	}
	for (int i = 0; i < 30; i++)
	{
		matrix[29][i] = 1;
	}
	turn_allowed = false;
};
void Board::MovePass()
{
	if (active == true)
	{
		matrix[x - 1][y - 1] = 2;
		if (temp_key == 'w')
		{
			dy = -1;
			y += dy;
		}
		else if (temp_key == 'a')
		{
			dx = -1;
			x += dx;
		}
		else if (temp_key == 's')
		{
			dy = 1;
			y += dy;
		}
		else if (temp_key == 'd')
		{
			dx = 1;
			x += dx;
		}
		if (matrix[x - 1][y - 1] == 1)
		{
			active = false;
			cursor_end_position = true;
			turn_allowed = false;

			if (temp_key == 'w')
			{
				x_final = x;
				y_final = y + 1;
			}
			if (temp_key == 'a')
			{
				x_final = x + 1;
				y_final = y;
			}
			if (temp_key == 's')
			{
				x_final = x;
				y_final = y - 1;
			}
			if (temp_key == 'd')
			{
				x_final = x - 1;
				y_final = y;
			}
		}

	}
};
void Board::Matrix_Fill()
{
	if ((!active) && (cursor_end_position))
	{
		if ((temp_keya == 's'&&temp_keyb == 'a') || (temp_keya == 'd'&&temp_keyb == 'w'))
		for (int i = 0; i < x_turn; i++)
		for (int j = 0; j < y_turn; j++)
		{
			matrix[i][j] = 1;
		}
		else if ((temp_keya == 's'&&temp_keyb == 'd') || (temp_keya == 'a'&&temp_keyb == 'w'))
		for (int i = x_turn - 1; i < 30; i++)
		for (int j = 0; j < y_turn; j++)
		{
			matrix[i][j] = 1;
		}
		else if ((temp_keya == 'w'&&temp_keyb == 'a') || (temp_keya == 'd'&&temp_keyb == 's'))
		for (int i = 0; i < x_turn; i++)
		for (int j = y_turn - 1; j < 30; j++)
		{
			matrix[i][j] = 1;
		}
		else if ((temp_keya == 'w'&&temp_keyb == 'd') || (temp_keya == 'a'&&temp_keyb == 's'))
		for (int i = x_turn - 1; i < 30; i++)
		for (int j = y_turn - 1; j < 30; j++)
		{
			matrix[i][j] = 1;
		}
		else if ((y_start <= 15) && (cursor_end_position) && (temp_keya == 'd') && (temp_keyb = ' '))
		{
			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < y_final; j++)
				{
					matrix[i][j] = 1;
				}
			}
		}
		else if ((y_start >= 16) && (cursor_end_position) && (temp_keya == 'd') && (temp_keyb = ' '))
		{
			for (int i = 0; i < 30; i++)
			{
				for (int j = y_final - 1; j < 30; j++)
				{
					matrix[i][j] = 1;
				}
			}
		}
		else if ((y_start <= 15) && (cursor_end_position) && (temp_keya == 'a') && (temp_keyb = ' '))
		{
			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < y_final; j++)
				{
					matrix[i][j] = 1;
				}
			}
		}
		else if ((y_start >= 16) && (cursor_end_position) && (temp_keya == 'a') && (temp_keyb = ' '))
		{
			for (int i = 0; i < 30; i++)
			{
				for (int j = y_final - 1; j < 30; j++)
				{
					matrix[i][j] = 1;
				}
			}
		}
		else if ((x_start <= 15) && (cursor_end_position) && (temp_keya == 's') && (temp_keyb = ' '))
		{
			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < x_final; j++)
				{
					matrix[j][i] = 1;
				}
			}
		}
		else if ((x_start >= 16) && (cursor_end_position) && (temp_keya == 's') && (temp_keyb = ' '))
		{
			for (int i = 0; i < 30; i++)
			{
				for (int j = x_final - 1; j < 30; j++)
				{
					matrix[j][i] = 1;
				}
			}
		}
		else if ((x_start <= 15) && (cursor_end_position) && (temp_keya == 'w') && (temp_keyb = ' '))
		{
			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < x_final; j++)
				{
					matrix[j][i] = 1;
				}
			}
		}
		else if ((x_start >= 16) && (cursor_end_position) && (temp_keya == 'w') && (temp_keyb = ' '))
		{
			for (int i = 0; i < 30; i++)
			{
				for (int j = x_final - 1; j < 30; j++)
				{
					matrix[j][i] = 1;
				}
			}
		}
		temp_keya = ' ';
		temp_keyb = ' ';
		switcher = 0;
		cursor_end_position = 0;
	}
};