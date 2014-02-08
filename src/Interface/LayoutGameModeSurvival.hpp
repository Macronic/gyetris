#ifndef LAYOUTGAMEMODESURVIVAL_H_DEFINED
#define LAYOUTGAMEMODESURVIVAL_H_DEFINED

#include <Interface/Layout.hpp>
#include <Game/GameModeSurvival.hpp>

#include <vector>

class LayoutGameModeSurvival: public Layout
{
public:
	LayoutGameModeSurvival(GameModeSurvival* game, int width, int height);
	virtual ~LayoutGameModeSurvival();

	void windowsInit();
	void windowsExit();

	void draw();

private:
	GameModeSurvival* game;

	// On `Layout` we have a `main` Window, where
	// everything's inside

	/// Container for things that are on the left of the window.
	Window* leftmost;

	/// Where we'll show the currently held piece (if exists).
	Window* hold;

	/// Showing High Score, current Score and Level.
	Window* score;

	/// Container for the board.
	Window* middle_left;

	/// Where we'll print the main stuff - board and pieces.
	Window* board;

	/// Next pieces
	Window* middle_right;

	/// Set of all the next pieces' respectives Windows.
	/// Layout it responsive according to it's Global::Game size.
	std::vector<Window*> next;

	/// Miscellaneous information and Statistics.
	/// Optional for the player.
	Window* rightmost;
};

#endif //LAYOUTGAMEMODESURVIVAL_H_DEFINED
