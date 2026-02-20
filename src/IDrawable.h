/*****************************************************************************
* Project: DrawingWorksV2
* File : IDrawable.h
* Date : 05.10.2025
* Author : Bastian Pfaller (BP)
*
* An interface for every drawable art or illustration in the console.
*
* History:
* 05.10.25 BP Created
******************************************************************************/


#pragma once
class IDrawable
{
public:
	/// <summary>
	/// Draws the drawable
	/// </summary>
	virtual void Draw() = 0;
};

