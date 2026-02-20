/*****************************************************************************
* Project: DrawingWorksV2
* File : Utils.h
* Date : 09.09.2025
* Author : Bastian Pfaller (BP)
*
* A collection of helpful functions for diffrent objectives.
* (Changing window settings, clearing the console, drawing diffrent shapes or symbols)
*
* History:
* 09.09.25 BP Created
******************************************************************************/

#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <io.h>
#include <fcntl.h>
#include "IDrawable.h"

static class Utils
{
public:
	/// <summary>
	/// Allows or disallows window resizing by the user
	/// </summary>
	/// <param name="a_value"></param>
	static void ChangeManualWindowResizing(bool a_value);

	/// <summary>
	/// Changes the window size
	/// </summary>
	/// <param name="a_width"></param>
	/// <param name="a_height"></param>
	static void ChangeWindowSize(int a_width, int a_height);

	/// <summary>
	/// Clears the console
	/// </summary>
	static void ClearScreen();

	/// <summary>
	/// Clears the screen and redraws all drawables
	/// </summary>
	/// <param name="a_drawables"></param>
	static void ResetScreen(std::vector<IDrawable*>* a_drawables);

	/// <summary>
	/// Enables fullscreen
	/// </summary>
	static void EnableFullscreen();

	/// <summary>
	/// Enabled windowed mode
	/// </summary>
	static void EnableWindowedMode();

	/// <summary>
	/// Sets fore and background color
	/// </summary>
	/// <param name="a_foreGroundColor"></param>
	/// <param name="a_backGroundColor"></param>
	static void SetForeGroundAndBackGroundColor(int a_foreGroundColor, int a_backGroundColor);

	/// <summary>
	/// Resets cursor position to 0,0
	/// </summary>
	static void SetCursorPosition();

	/// <summary>
	/// Set cursor position
	/// </summary>
	/// <param name="a_position"></param>
	static void SetCursorPosition(COORD* a_position);

	/// <summary>
	/// Sets the character drawing color
	/// </summary>
	/// <param name="a_color"></param>
	static void SetColor(WORD a_color);

	/// <summary>
	/// Writes a pixel in the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_color"></param>
	static void DrawPixel(COORD* a_position, unsigned char a_color);

	/// <summary>
	/// Draws a pixel in the console
	/// </summary>
	/// <param name="a_x"></param>
	/// <param name="a_y"></param>
	/// <param name="a_color"></param>
	static void DrawPixel(int a_x, int a_y, unsigned char a_color);

	/// <summary>
	/// Draws a pixel in the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_color"></param>
	/// <param name="a_character"></param>
	static void DrawPixel(COORD* a_position, unsigned char a_color, char a_character);

	/// <summary>
	/// Draws a pixel in the console
	/// </summary>
	/// <param name="a_x"></param>
	/// <param name="a_y"></param>
	/// <param name="a_color"></param>
	/// <param name="a_character"></param>
	static void DrawPixel(int a_x, int a_y, unsigned char a_color, char a_character);

	/// <summary>
	/// Draws a circle into the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_radius"></param>
	/// <param name="a_color"></param>
	static void DrawCircle(COORD* a_position, int a_radius, int a_color);

	/// <summary>
	/// Draws a line into the console
	/// </summary>
	/// <param name="a_position0"></param>
	/// <param name="a_position1"></param>
	/// <param name="a_color"></param>
	static void DrawLine(COORD* a_position0, COORD* a_position1, int a_color);

	/// <summary>
	/// Draws a x-shape into the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_size"></param>
	/// <param name="a_color"></param>
	static void DrawBigX(COORD* a_position, int a_size, int a_color);

	/// <summary>
	/// Draws a frame centered around given coordinate into the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_width"></param>
	/// <param name="a_height"></param>
	/// <param name="a_color"></param>
	static void DrawFrameCenter(COORD* a_position, int a_width, int a_height, int a_color);

	/// <summary>
	/// Draws a frame with the top left corner beeing the given position into the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_width"></param>
	/// <param name="a_height"></param>
	/// <param name="a_color"></param>
	/// <param name="a_charakter"></param>
	static void DrawFrameTopLeft(COORD* a_position, int a_width, int a_height, int a_color, char a_charakter);

	/// <summary>
	/// Draws a frame with the top left corner beeing the given position into the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_width"></param>
	/// <param name="a_height"></param>
	/// <param name="a_color"></param>
	static void DrawFrameTopLeftDoubleLined(COORD* a_position, int a_width, int a_height, int a_color);

	/// <summary>
	/// Draws a frame with the top left corner beeing the given position into the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_width"></param>
	/// <param name="a_height"></param>
	/// <param name="a_color"></param>
	static void DrawFrameTopLeftSingleLined(COORD* a_position, int a_width, int a_height, int a_color);

	/// <summary>
	/// Draws a color palette into the console
	/// </summary>
	static void DrawColorPalette();

	/// <summary>
	/// Draws a color palette into the console
	/// </summary>
	/// <param name="a_position"></param>
	static void DrawColorPalette(COORD* a_position);

	/// <summary>
	/// Draws a char palette into the console
	/// </summary>
	static void DrawCharPalette();

	/// <summary>
	/// Draws a char palette into the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_color"></param>
	static void DrawCharPalette(COORD* a_position, int a_color);

	/// <summary>
	/// Draws a given string into the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_color"></param>
	/// <param name="a_text"></param>
	static void DrawString(COORD* a_position, unsigned char a_color, const std::string a_text);

	/// <summary>
	/// Draws a given multilined string into the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_color"></param>
	/// <param name="a_text"></param>
	static void DrawString(COORD* a_position, unsigned char a_color, const std::vector<std::string>* a_text);

	/// <summary>
	/// Draws a given wide string into the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_color"></param>
	/// <param name="a_text"></param>
	static void DrawWString(COORD* a_position, unsigned char a_color, const std::wstring a_text);

	/// <summary>
	/// Draws a given multilined wide string into the console
	/// </summary>
	/// <param name="a_position"></param>
	/// <param name="a_color"></param>
	/// <param name="a_text"></param>
	static void DrawWString(COORD* a_position, unsigned char a_color, const std::vector<std::wstring>* a_text);
private:

	//Saved special characters
	static const unsigned char M_SQUARE = (unsigned char)219;
	static const unsigned char M_SQUARELIGHT = (unsigned char)176;

	static const unsigned char M_DOUBLELINECORNERTOPLEFT = (unsigned char)201;
	static const unsigned char M_DOUBLELINECORNERTOPRIGHT = (unsigned char)187;
	static const unsigned char M_DOUBLELINECORNERBOTTOMLEFT = (unsigned char)200;
	static const unsigned char M_DOUBLELINECORNERBOTTOMRIGHT = (unsigned char)188;
	static const unsigned char M_DOUBLELINEHORIZONTAL = (unsigned char)205;
	static const unsigned char M_DOUBLELINEVERTICAL = (unsigned char)186;

	static const unsigned char M_SINGLELINECORNERTOPLEFT = (unsigned char)218;
	static const unsigned char M_SINGLELINECORNERTOPRIGHT = (unsigned char)191;
	static const unsigned char M_SINGLELINECORNERBOTTOMLEFT = (unsigned char)192;
	static const unsigned char M_SINGLELINECORNERBOTTOMRIGHT = (unsigned char)217;
	static const unsigned char M_SINGLELINEHORIZONTAL = (unsigned char)196;
	static const unsigned char M_SINGLELINEVERTICAL = (unsigned char)179;

};

