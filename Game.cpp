#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <vector>

#include "Ball.h"
#include "Platform.h"
#include "Wall.h"

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

Platform platform{ {10, 100}, 100, {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT * 0.8f} };

int wallThinkness = 20;
Wall wallLeft{ {SCREEN_HEIGHT, wallThinkness}, {0,0} };
Wall wallRight{ {SCREEN_HEIGHT, wallThinkness}, {SCREEN_WIDTH - wallThinkness, 0} };
Wall wallUp{ {wallThinkness, SCREEN_WIDTH}, {0,0} };
Wall wallDown{ {wallThinkness, SCREEN_WIDTH}, {0,SCREEN_HEIGHT - wallThinkness} };

Ball ball{ 50.0f, {0, 100}, &platform, &wallLeft, &wallRight, &wallUp, &wallDown };

// initialize game data in this function
void initialize()
{

}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
	if (is_key_pressed(VK_ESCAPE))
		schedule_quit_game();
	if (is_key_pressed(VK_LEFT))
	{
		//std::cout << "LEFT BUTTON PRESSED\n";
	}
	if (is_key_pressed(VK_RIGHT))
	{
		//std::cout << "RIGHT BUTTON PRESSED\n";
	}

	ball.Act(dt);
	platform.Act(dt);
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
	// clear backbuffer
	memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
	ball.Draw();
	platform.Draw();
	wallLeft.Draw();
	wallRight.Draw();
	wallUp.Draw();
	wallDown.Draw();
}

// free game data in this function
void finalize()
{}

