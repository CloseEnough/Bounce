#include <glut.h>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include "ball.h"
#include "board.h"
int difficulty;
unsigned char temp_key;
unsigned char temp_keya;
unsigned char temp_keyb;
bool data = true;
bool parameters = false;
int score = 0;
int level = 0;
int lose_timer = 0;
int lives = 0;
int start_speed=1;
int speed = start_speed;
int start_lose_speed=10000;
int lose_speed = start_lose_speed;
int start_ball_speed=1;
int ball_speed = start_ball_speed;
bool switcher=0;
bool isCollision;
bool game_started = 0;
bool game_over;
bool active_global = 1;
int n;
Board board;
Ball *ball=new Ball[n];
bool pause=0;
bool win=0;
void Collision()
{
	for (int z = 0; z < n; z+=2)
	{
		float cursor_x = ((board.x - 1) * 10) + 5, cursor_y = ((board.y - 1) * 10) + 5, cursor_r = (2 * sqrt(2.0) * 5) / 2;
		if (sqrt((cursor_x - ball[z].x)*(cursor_x - ball[z].x) + (cursor_y - ball[z].y)*(cursor_y - ball[z].y)) <= 10)
		{
			isCollision = 1;
		}
		if (isCollision)
		{
			if (board.active)
			{
				board.y_final = board.y;
				board.x_final = board.x;

				if ((ball[z].x - cursor_x<0) || (ball[z].x - cursor_x>0))
				{
					ball[z].dx *= -1;

				}
				if ((ball[z].y - cursor_y<0) || (ball[z].y - cursor_y>0))
				{
					ball[z].dy *= -1;
				}
				if (!board.turn_allowed)
				{
					if (temp_keya == 'w')
					{
						board.x = board.x_start;
						board.y = board.y_start + 1;
						for (int i = board.y_start; i > board.y_turn; i--)
						{
							board.matrix[board.x_start - 1][i - 1] = 0;
						}
					}
					if (temp_keya == 'a')
					{
						board.x = board.x_start + 1;
						board.y = board.y_start;
						for (int i = board.x_start; i > board.x_turn; i--)
						{
							board.matrix[i - 1][board.y_start - 1] = 0;
						}
						
					}
					if (temp_keya == 's')
					{
						board.x = board.x_start;
						board.y = board.y_start - 1;
						for (int i = board.y_start; i < board.y_turn; i++)
						{
							board.matrix[board.x_start - 1][i - 1] = 0;
						}	
					}
					if (temp_keya == 'd')
					{
						board.x = board.x_start - 1;
						board.y = board.y_start;
						for (int i = board.x_start; i < board.x_turn; i++)
						{
							board.matrix[i - 1][board.y_start - 1] = 0;
						}
						
					}
					if (temp_keyb == 'w')
					{
						
						for (int i = board.y_turn; i > board.y_final; i--)
						{
							board.matrix[board.x_turn - 1][i - 1] = 0;
						}
					}
					if (temp_keyb == 'a')
					{
						
						for (int i = board.x_turn; i > board.x_final; i--)
						{
							board.matrix[i - 1][board.y_turn - 1] = 0;
						}
					}
					if (temp_keyb == 's')
					{
						for (int i = board.y_turn; i < board.y_final; i++)
						{
							board.matrix[board.x_turn - 1][i - 1] = 0;
						}
					}
					if (temp_keyb == 'd')
					{
						
						for (int i = board.x_turn; i < board.x_final; i++)
						{
							board.matrix[i - 1][board.y_turn - 1] = 0;
						}
					}
				}
				else
				{
					if (temp_keya == 'w')
					{
						board.x = board.x_start;
						board.y = board.y_start + 1;
						for (int i = board.y_start; i > board.y_final; i--)
						{
							board.matrix[board.x_start - 1][i - 1] = 0;
						}
					}
					if (temp_keya == 'a')
					{
						board.x = board.x_start + 1;
						board.y = board.y_start;
						for (int i = board.x_start; i > board.x_final; i--)
						{
							board.matrix[i - 1][board.y_start - 1] = 0;
						}
					}
					if (temp_keya == 's')
					{
						board.x = board.x_start;
						board.y = board.y_start - 1;
						for (int i = board.y_start; i < board.y_final; i++)
						{
							board.matrix[board.x_start - 1][i - 1] = 0;
						}
					}
					if (temp_keya == 'd')
					{
						board.x = board.x_start - 1;
						board.y = board.y_start;
						for (int i = board.x_start; i < board.x_final; i++)
						{
							board.matrix[i - 1][board.y_start - 1] = 0;
						}
					}
				}
				switcher = 0;
				board.active = 0;
				board.cursor_end_position = 0;
				temp_keya = ' ';
				temp_keyb = ' ';
			}
			isCollision = 0;
		}
		for (int j = 0; j < 30; j++)
		{
			for (int i = 0; i < 30; i++)
			{
				if (board.matrix[i][j] == 1)
				{

						if (ball[z].active)
						{
							float brick_x = ((i)* 10) + 5, brick_y = ((j)* 10) + 5, brick_r = (2 * sqrt(2.0) * 5) / 2;
							if (sqrt((brick_x - ball[z].x)*(brick_x - ball[z].x) + (brick_y - ball[z].y)*(brick_y - ball[z].y)) <= 4)
							{
								ball[z].active = 0;
							}
							if (sqrt((brick_x - ball[z].x)*(brick_x - ball[z].x) + (brick_y - ball[z].y)*(brick_y - ball[z].y)) <= 10)
							{
								isCollision = 1;
							}
							if (isCollision)
							{
								
								if ((ball[z].x - brick_x<0) || (ball[z].x - brick_x>0))
								{
									ball[z].dx *= -1;
								}
								if ((ball[z].y - brick_y<0) || (ball[z].y - brick_y>0))
								{
									ball[z].dy *= -1;
								}
								
								isCollision = 0;
							}
						}
				}
				if (board.matrix[i][j] == 2)
				{
					if (ball[z].active)
					{
						float brick_x = ((i)* 10) + 5, brick_y = ((j)* 10) + 5, brick_r = (2 * sqrt(2.0) * 5) / 2;
						if (sqrt((brick_x - ball[z].x)*(brick_x - ball[z].x) + (brick_y - ball[z].y)*(brick_y - ball[z].y)) <= 10)
						{
							isCollision = 1;
						}

						if (isCollision)
						{

							if ((ball[z].x - brick_x<0) || (ball[z].x - brick_x>0))
							{
								ball[z].dx *= -1;
							}
							if ((ball[z].y - brick_y<0) || (ball[z].y - brick_y>0))
							{
								ball[z].dy *= -1;
							}
							if (board.active)
							{
								board.y_final = board.y;
								board.x_final = board.x;

								if (!board.turn_allowed)
								{
									if (temp_keya == 'w')
									{
										board.x = board.x_start;
										board.y = board.y_start + 1;
										for (int i = board.y_start; i > board.y_turn; i--)
										{
											board.matrix[board.x_start - 1][i - 1] = 0;
										}

									}
									if (temp_keya == 'a')
									{
										board.x = board.x_start + 1;
										board.y = board.y_start;
										for (int i = board.x_start; i > board.x_turn; i--)
										{
											board.matrix[i - 1][board.y_start - 1] = 0;
										}

									}
									if (temp_keya == 's')
									{
										board.x = board.x_start;
										board.y = board.y_start - 1;
										for (int i = board.y_start; i < board.y_turn; i++)
										{
											board.matrix[board.x_start - 1][i - 1] = 0;
										}

									}
									if (temp_keya == 'd')
									{
										board.x = board.x_start - 1;
										board.y = board.y_start;
										for (int i = board.x_start; i < board.x_turn; i++)
										{
											board.matrix[i - 1][board.y_start - 1] = 0;
										}

									}
									if (temp_keyb == 'w')
									{

										for (int i = board.y_turn; i > board.y_final; i--)
										{
											board.matrix[board.x_turn - 1][i - 1] = 0;
										}
									}
									if (temp_keyb == 'a')
									{

										for (int i = board.x_turn; i > board.x_final; i--)
										{
											board.matrix[i - 1][board.y_turn - 1] = 0;
										}
									}
									if (temp_keyb == 's')
									{
										for (int i = board.y_turn; i < board.y_final; i++)
										{
											board.matrix[board.x_turn - 1][i - 1] = 0;
										}
									}
									if (temp_keyb == 'd')
									{

										for (int i = board.x_turn; i < board.x_final; i++)
										{
											board.matrix[i - 1][board.y_turn - 1] = 0;
										}
									}
								}
								else
								{
									if (temp_keya == 'w')
									{
										board.x = board.x_start;
										board.y = board.y_start + 1;
										for (int i = board.y_start; i > board.y_final; i--)
										{
											board.matrix[board.x_start - 1][i - 1] = 0;
										}
									}
									if (temp_keya == 'a')
									{
										board.x = board.x_start + 1;
										board.y = board.y_start;
										for (int i = board.x_start; i > board.x_final; i--)
										{
											board.matrix[i - 1][board.y_start - 1] = 0;
										}
									}
									if (temp_keya == 's')
									{
										board.x = board.x_start;
										board.y = board.y_start - 1;
										for (int i = board.y_start; i < board.y_final; i++)
										{
											board.matrix[board.x_start - 1][i - 1] = 0;
										}
									}
									if (temp_keya == 'd')
									{
										board.x = board.x_start - 1;
										board.y = board.y_start;
										for (int i = board.x_start; i < board.x_final; i++)
										{
											board.matrix[i - 1][board.y_start - 1] = 0;
										}
									}
								}
								switcher = 0;
								board.active = 0;
								board.cursor_end_position = 0;
								temp_keya = ' ';
								temp_keyb = ' ';
							}
							lives--;
							isCollision = 0;
						}
					}
				}
			}
		}
		
	}
}
void Keyboard(unsigned char button, int x, int y)
{
	if (active_global)
	{
		if (game_started)
		{
			if ((board.matrix[board.x - 1][board.y - 1] == 1) && board.active == false)
			{
				if (board.y > 1)
				if (button == 'w')
				{
					board.y--;
				}
				if (board.x > 1)
				if (button == 'a')
				{
					board.x--;

				}
				if (board.y < 30)
				if (button == 's')
				{
					board.y++;

				}
				if (board.x < 30)
				if (button == 'd')
				{
					board.x++;
				}
				if ((button == 'w') || (button == 'a') || (button == 's') || (button == 'd'))
				{
					temp_key = button;
				}
			}
			if (board.turn_allowed)
			{
				board.x_turn = board.x;
				board.y_turn = board.y;
			}
			if ((board.matrix[board.x - 1][board.y - 1] == 0) && board.active == false)
			{
				board.turn_allowed = true;
				board.active = true;
				board.cursor_end_position = false;
				board.x_start = board.x;
				board.y_start = board.y;
			}
			if (board.active == true && board.turn_allowed == true)
			{
				if ((switcher == 0) && (board.turn_allowed))
				{
					if ((button == 'w') || (button == 'a') || (button == 's') || (button == 'd'))
					{
						temp_keya = button;
						switcher = !switcher;
					}
				}
				else if (switcher == 1 && button != temp_keya && board.turn_allowed)
				{
					if ((button == 'w') || (button == 'a') || (button == 's') || (button == 'd'))
					{
						if ((!(temp_keya == 'a'&&button == 'd')) && (!(temp_keya == 'd'&&button == 'a')) && (!(temp_keya == 'w'&&button == 's')) && (!(temp_keya == 's'&&button == 'w')))
						{
							temp_keyb = button;
							switcher = !switcher;
						}
					}
				}


				unsigned char temp_key3 = temp_key;
				unsigned char temp_key2 = temp_key;
				if ((button == 'w') || (button == 'a') || (button == 's') || (button == 'd'))
					temp_key = button;
				if (temp_key3 == 'a'&&temp_key == 'd')
				{
					temp_key = 'a';
				}
				if (temp_key3 == 'd'&&temp_key == 'a')
				{
					temp_key = 'd';
				}
				if (temp_key3 == 'w'&&temp_key == 's')
				{
					temp_key = 'w';
				}
				if (temp_key3 == 's'&&temp_key == 'w')
				{
					temp_key = 's';
				}
				if (temp_key != temp_key2)
					board.turn_allowed = false;
			}
		}

		srand(time(NULL));
		if (((button == ' ') && !game_started))
		{
			if (difficulty == 1)
			{
				if (!win)
				{
	
					n = 1;
				}
				if (win)
				{
					if (n<100)
					n += 2;
					win = false;
				}
				if (!parameters)
				{
					
					start_ball_speed = 1;
					ball_speed = start_ball_speed;
					start_speed = 23;
					speed = start_speed;

				}
			}
			else if (difficulty == 2)
			{
				if (!win)
				{

					n = 1;
				}
				if (win)
				{
					if (n<100)
						n += 2;
					win = false;
				}
				if (!parameters)
				{
					
					start_ball_speed = 1;
					ball_speed = start_ball_speed;
					start_speed = 1;
					speed = start_speed;
				}
			}
			else if (difficulty == 3)
			{
				if (!win)
				{
					n = 1;
				}
				if (win)
				{
					if (n<100)
						n += 2;
					win = false;
				}
				if (!parameters)
				{
					start_ball_speed = 5;
					ball_speed = start_ball_speed;
					start_speed = 23;
					speed = start_speed;
				}
			}
			else if (difficulty == 4)
			{
				if (!win)
				{
					n = 1;
				}
				if (win)
				{
					if (n<100)
						n += 2;
					win = false;
				}
				if (!parameters)
				{
					start_ball_speed = 5;
					ball_speed = start_ball_speed;
					start_speed = 1;
					speed = start_speed;
				}
			}
			for (int i = 0; i < n; i+=2)
			{
				ball[i].x = (rand() % 15 + 5) * 10;
				ball[i].y = (rand() % 15 + 5) * 10;
				ball[i].r = 5;
				ball[i].active = true;
				int apriori;
				apriori = rand() % 3;
				if (apriori == 0)
				{
					ball[i].dx = ball_speed;
					ball[i].dy = -ball_speed;
				}
				else if (apriori == 1)
				{
					ball[i].dx = -ball_speed;
					ball[i].dy = ball_speed;
				}
				else if (apriori == 2)
				{
					ball[i].dx = ball_speed;
					ball[i].dy = ball_speed;
				}
				else if (apriori == 3)
				{
					ball[i].dx = -ball_speed;
					ball[i].dy = -ball_speed;
				}
			}
			game_started = 1;
			if (lives == 0)
				lives = 3;
			lose_timer = 0;
		}
	}
	if (button == 'p')
	{
		if (pause)
		{
			active_global = true;
			
		}
		else
		{
			active_global = false;
		}
		for (int i = 0; i < n; i+=2)
		{
			if (pause)
			{
				ball[i].active = true;
			}
			else
			{
				ball[i].active = false;
			}
		}
		pause = !pause;
	}
}
void Draw()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	glRectf(0, 310, lose_timer * 10, 300);
	glColor3f(1, 0, 0);
	glRectf(310, 0, 300, lives * 10);
	glColor3f(0, 1, 0);
	glRectf(320, 0, 310, level * 10);
	glColor3f(0, 1, 0);
	

	for (int j = 0; j < n; j++)
	{
		glBegin(GL_POLYGON);
		for (float i = 0; i < 2 * 3.14; i += 3.14 / 4)
		{
			glVertex2f(ball[j].x + ball[j].r*sin(i), ball[j].y + ball[j].r*cos(i));
		}
		glEnd();
	}
	glColor3f(1, 1, 1);
	int temp_x1, temp_y1, temp_x2, temp_y2;
	temp_x1 = board.x * 10;
	temp_y1 = board.y * 10;
	temp_x2 = board.x * 10 - 10;
	temp_y2 = board.y * 10 - 10;
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (board.matrix[j][i] == 1)
			{
				glColor3f(1, 1, 1);
				glRectf((j+1)* 10, (i+1)* 10, (j+1)* 10 - 10, (i+1)* 10 - 10);
			}
			if (board.matrix[j][i] == 2)
			{
				glColor3f(1, 1, 0);
				glRectf((j + 1) * 10, (i + 1) * 10, (j + 1) * 10 - 10, (i + 1) * 10 - 10);
			}
		}
	}
	glColor3f(0, 1,0);
	glRectf(temp_x1, temp_y1, temp_x2, temp_y2);
	glutSwapBuffers();
}
void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 320, 310, 0, 1, 0);
}
void Timer(int)
{
	if (active_global)
	{
		Draw();
		for (int i = 0; i < n; i++)
		{
			Collision();
			if (ball[i].active == true)
			{

				ball[i].Move();
			}

		}

		int sum = 0;
		for (int i = 1; i < 29; i++)
		for (int j = 1; j < 29; j++)
		{
			if (board.matrix[i][j] == 1)
				sum++;
		}
		if ((lives == 0) || (lose_timer == 32))
		{
			lose_timer = 0;
			if (game_started)
			{
				win = 0;
				score += sum;
				if (difficulty == 2)
					score *= 2;
				if (difficulty == 3)
					score *= 3;
				if (difficulty == 4)
					score *= 4;

				std::cout << std::endl << "Score: " << score << " Levels passed: " << level << std::endl;


				
				speed = start_speed;
				lose_speed = start_lose_speed;
				level = 0;

				temp_keya = NULL;
				temp_keyb = NULL;
				temp_key = NULL;
				board.x = 1;
				board.y = 1;
				for (int i = 0; i < n; i++)
				{
					ball[i].x = NULL;
					ball[i].y = NULL;
					ball[i].r = NULL;
					ball[i].active = false;
					ball[i].dx = NULL;
					ball[i].dy = NULL;
				}
				for (int i = 1; i < 29; i++)
				{
					for (int j = 1; j < 29; j++)
					{
						board.matrix[i][j] = 0;
					}
				}
				Draw();
				std::cout << std::endl << "Enter your name:";
				std::string name;
				std::cin >> name;
				std::ofstream fout("scores.txt", std::ios::app);
				fout << name <<" " <<score <<std::endl;
				fout.close();
				std::cout << std::endl << "Game Over. Choose another difficulty? (y/n)" << std::endl;
				unsigned char alpha;
			again:
				std::cin >> alpha;
				if (alpha == 'y')
					game_over = 1;
				else if (alpha == 'n')
					game_over = 0;
				else
				{
					goto again;
				}
				if (game_over)
				{
					std::cout << std::endl << "Choose diffictily:" << std::endl << "1 - Easy" << std::endl << "2 - Medium" << std::endl << "3 - Hard" << std::endl << "4 - Nightmare" << std::endl;
					std::cin >> difficulty;
				}
				std::cout << std::endl << "Press space to start a new session..." << std::endl;;
				game_started = false;
				score = 0;
			}
		}
		bool isAllBallsDestroyed=1;
		for (int i = 0; i < n; i++)
		{
			if (ball[i].active == 1)
				isAllBallsDestroyed = 0;
		}
		if ((sum >= 588) || (isAllBallsDestroyed))
		{
			
			score += sum;
			if (game_started)
			{
				win = 1;
				std::cout << std::endl << "Level passed! Press space to start next level." << std::endl;
				lose_timer = 0;
				level++;
				lives++;
				lose_speed += 1000;
				board.x = 1;
				board.y = 1;
				temp_keya = NULL;
				temp_keyb = NULL;
				temp_key = NULL;
				for (int i = 0; i < n; i++)
				{

					ball[i].x = NULL;
					ball[i].y = NULL;
					ball[i].r = NULL;
					ball[i].active = false;
					ball[i].dx = NULL;
					ball[i].dy = NULL;
				}
				for (int i = 1; i < 29; i++)
				{
					for (int j = 1; j < 29; j++)
					{
						board.matrix[i][j] = 0;
					}
				}
				game_started = false;
			}

		}
		if ((data) && (game_started))
		{
			system("cls");
			for (int i = 0; i < n; i+=2)
			{
				std::cout << "ball " << i/2 << " coordinates: " << ball[i].x << " " << ball[i].y << std::endl;
			}
			std::cout << "number of balls: " << n/2 << std::endl;
			std::cout << "temp_key value:" << temp_key << std::endl;
			std::cout << "cursor coordinates: x:" << board.x << " y:" << board.y << std::endl;
			std::cout << "cell value: " << board.matrix[board.x - 1][board.y - 1] << std::endl;
			std::cout << "x start: " << board.x_start << std::endl;
			std::cout << "y start: " << board.y_start << std::endl;
			std::cout << "x final: " << board.x_final << std::endl;
			std::cout << "y final: " << board.y_final << std::endl;
			std::cout << "x turn: " << board.x_turn << std::endl;
			std::cout << "y turn: " << board.y_turn << std::endl;
			std::cout << "turn alowed:" << board.turn_allowed << std::endl;
			std::cout << "temp_key:" << temp_key << std::endl;
			std::cout << "temp_key a:" << temp_keya << std::endl;
			std::cout << "temp_key_b:" << temp_keyb << std::endl;
			std::cout << "lose after: " << 31 - lose_timer << std::endl;
			std::cout << "board_active: " << board.active << std::endl;
			std::cout << "lose_speed: " << lose_speed << std::endl;
			std::cout << "start_lose_speed: " << start_lose_speed << std::endl;
		}
	}
	glutTimerFunc(speed, Timer, 0);
	
}
void Timer1(int)
{
	if (active_global)
	{
		board.MovePass();
		if (board.active == false)
		{
			board.turn_allowed = false;
		}
		board.Matrix_Fill();

	}
	glutTimerFunc(250, Timer1, 1);
	
}
void Timer3(int)
{
	if (active_global)
	{
		if ((lose_timer < 33) && (game_started))
			lose_timer++;
	}
		glutTimerFunc(lose_speed, Timer3, 2);
	
}
int main(int argc, char** argv)
{

	std::cout << "Bounce v0.3" << std::endl;
	std::cout << "Do you wanna play a little game?" << std::endl;
	std::cout << "Please follow instructions to start a game." << std::endl<<std::endl;
	std::cout << "Controls on WASD" << std::endl;
	std::cout << "Pause - 'p'" << std::endl << std::endl;
	std::cout << "WARNING" << std::endl;
	std::cout << "Before playing make sure that keyboard language " <<std::endl;
	std::cout << "is switched on English and CapsLock is off." << std::endl;
	std::cout << "WARNING" << std::endl << std::endl;
	std::cout << "Choose difficulty:" << std::endl << "1 - Easy" << std::endl << "2 - Medium" << std::endl << "3 - Hard" << std::endl << "4 - Nightmare" << std::endl;
	std::cin >> difficulty;
	if (parameters == 1)
	{
		std::cout << "start_lose_speed: ";
		std::cin >> start_lose_speed;
		lose_speed = start_lose_speed;
		std::cout << "start_timer_speed:";
		std::cin >> start_speed;
		speed = start_speed;
		std::cout << "start_ball_speed:";
		std::cin >> start_ball_speed;
		ball_speed = start_ball_speed;
	}
	std::cout << std::endl << "After window initialization is done press space to start a game session." << std::endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(310, 310);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("KBounce");
	glutDisplayFunc(Draw);
	glutTimerFunc(speed, Timer, 0);
	glutTimerFunc(250, Timer1, 1);
	glutTimerFunc(lose_speed, Timer3, 2);
	glutKeyboardFunc(Keyboard);
	Init();
	glutMainLoop();
}