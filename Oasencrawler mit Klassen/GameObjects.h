#pragma once
#include <iostream>
#include <Windows.h>
#include "Vector2d.h"
#include <conio.h>

/// <summary>
/// Base class for game objects
/// </summary>
class GameObjects
{
	public:
		/// <summary>
		/// Sets the X/Y-position of this GameObject directly.
		/// </summary>
		/// <param name="x">X value of the new GameObject position.</param>
		/// <param name="y">Y value of the new GameObject position.</param>
		void setPosition(int x, int y);

		/// <summary>
		/// Sets the X/Y-position of this GameObject.
		/// </summary>
		/// <param name="position">The new GameObject position.</param>
		void setPosition(Vector2d position);

		/// <summary>
		/// Get the current position of this GameObject.
		/// </summary>
		/// <returns>The current position of this GameObject.</returns>
		Vector2d getPosition() const;

		/// <summary>
		/// Outputs letter by letter text on the screen.
		/// </summary>
		/// <param name="outputText">Text to be displayed.</param>
		void printText(const std::string &outputText) const;				// TODO: should be moved to game.h!

		/// <summary>
		/// Normalizes a number to -1, 0 or 1.
		/// </summary>
		int normalize(int value) const;

	private:
		/// <summary>
		/// Current postion of this GameObject.
		/// </summary>
		Vector2d position;
};
