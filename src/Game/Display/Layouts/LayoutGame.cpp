#include <Game/Display/Layouts/LayoutGame.hpp>
#include <Game/Config/Globals.hpp>
#include <Game/Entities/Profile.hpp>
#include <Engine/Helpers/Utils.hpp>
#include <Engine/Graphics/Colors.hpp>
#include <Engine/Graphics/Animation/AnimationFire.hpp>
#include <Engine/Graphics/Animation/AnimationWater.hpp>
#include <Engine/Graphics/Animation/AnimationSnakes.hpp>
#include <Engine/Graphics/Animation/AnimationGameOfLife.hpp>

LayoutGame::LayoutGame(Game* game, int width, int height):
    Layout(width, height),
    game(game),
    leftmost(NULL),
    hold(NULL),
    score(NULL),
    middle_left(NULL),
    board(NULL),
    middle_right(NULL),
    rightmost(NULL),
    helpWindows(NULL),
    animation(NULL)
{
    this->windowsInit();
}
LayoutGame::~LayoutGame()
{
    this->windowsExit();
}
void LayoutGame::windowsInit()
{
    Layout::windowsInit();

    // If we're not going to show statistics, will
    // leave a big hole on the left.
    // Let's align it then.
    int leftmost_x = 0;

    if (! Globals::Profiles::current->settings.screen.show_statistics)
        leftmost_x = 18;

    // Leftmost window
    this->leftmost = new Window(this->main,
                                leftmost_x,
                                0,
                                4*2 + 2 + 2, // 4 blocks + borders + 2 space
                                0);
    this->leftmost->borders(Window::BORDER_NONE); // container Window

    if (Globals::Profiles::current->settings.game.can_hold)
    {
        this->hold = new Window(this->leftmost,
                                0,
                                0,
                                this->leftmost->getW(),
                                4);
        this->hold->setTitle("Hold");
    }

    // This window will span all available height if
    // we can't hold.
    int score_y = ((this->hold) ?
                   this->hold->getH():
                   0);

    int score_height = ((this->hold) ?
                        this->leftmost->getH() - this->hold->getH():
                        this->leftmost->getH());

    this->score = new Window(this->leftmost,
                             0,
                             score_y,
                             0,
                             score_height);

    // Middle-left, container for the board
    this->middle_left = new Window(this->main,
                                   this->leftmost->getX() + this->leftmost->getW(),
                                   0,
                                   10 + 2, // 10 blocks + borders
                                   22);      // 20 blocks + borders

    // The actual game border, inside that container.
    this->board = new Window(this->middle_left, 0, 0, 0, 0);

    // Middle-right, container of all the next pieces.
    // It's height depents on how many next pieces we're showing.
    int middle_right_height = Globals::Profiles::current->settings.game.next_pieces * 3 + 1;

    this->middle_right = new Window(this->main,
                                    this->middle_left->getX() + this->middle_left->getW(),
                                    0,
                                    4*2 + 2, // 4 blocks + borders
                                    middle_right_height);

    this->middle_right->setTitle("Next");

    // First next piece
    this->next.resize(Globals::Profiles::current->settings.game.next_pieces);
    this->next[0] = new Window(this->middle_right, 0, 0, 0, 3);
    this->next[0]->borders(Window::BORDER_NONE);

    // The rest of the next pieces
    for (unsigned int i = 1; i < (this->next.size()); i++)
    {
        this->next[i] = new Window(this->middle_right,
                                   0,
                                   this->next[i - 1]->getY() + this->next[i - 1]->getH(),
                                   0,
                                   3);

        this->next[i]->borders(Window::BORDER_NONE);
    }

    // Will only show the right window if statistics is enabled
    if (Globals::Profiles::current->settings.screen.show_statistics)
    {
        // Container for Statistics and Miscellaneous information.
        this->rightmost = new Window(this->main,
                                     this->middle_right->getX() + this->middle_right->getW(),
                                     0,
                                     this->main->getW() - (this->middle_right->getX() + this->middle_right->getW()) - 1,
                                     0);

        this->rightmost->setTitle("Statistics");
    }

    // Le pause window.
    this->pause = new Window(this->main,
                             this->main->getW() / 4,
                             this->main->getH() / 2 - 1, //center
                             this->main->getW() / 2,
                             6);

    this->pause->setTitle("Paused");

    this->helpWindows = new WindowGameHelp();


    // Now, the (optional) animation that will go
    // behind the game screen.
    if (Globals::Profiles::current->settings.screen.animation_game == "random")
    {
        // Deciding randomly the type of the Animation
        switch(Utils::Random::between(0, 3))
        {
            case 0:
                this->animation = new AnimationWater(this->board);
                break;

            case 1:
                this->animation = new AnimationSnakes(this->board);
                break;

            case 2:
                this->animation = new AnimationGameOfLife(this->board);
                break;

            default:
                this->animation = new AnimationFire(this->board);
                break;
        }
    }
    else if (Globals::Profiles::current->settings.screen.animation_game == "fire")
        this->animation = new AnimationFire(this->board);

    else if (Globals::Profiles::current->settings.screen.animation_game == "water")
        this->animation = new AnimationWater(this->board);

    else if (Globals::Profiles::current->settings.screen.animation_game == "snakes")
        this->animation = new AnimationSnakes(this->board);

    else if (Globals::Profiles::current->settings.screen.animation_game == "life")
        this->animation = new AnimationGameOfLife(this->board);

    else
        this->animation = nullptr;

    if (this->animation)
        this->animation->load();
}
void LayoutGame::windowsExit()
{
    SAFE_DELETE(this->leftmost);
    SAFE_DELETE(this->hold);
    SAFE_DELETE(this->score);
    SAFE_DELETE(this->middle_left);
    SAFE_DELETE(this->board);
    SAFE_DELETE(this->middle_right);
    SAFE_DELETE(this->rightmost);
    SAFE_DELETE(this->pause);
    SAFE_DELETE(this->helpWindows);
    SAFE_DELETE(this->animation);

    for (unsigned int i = 0; i < this->next.size(); i++)
        SAFE_DELETE(this->next[i]);

    this->next.clear(); // clear() as in std::vector

    this->main->clear(); // clear() as in Window
    this->main->refresh(); // clear() as in Window

    Layout::windowsExit();
}
void LayoutGame::draw(Menu* menu)
{
    if (!this->game)
        return;

    // Will only show the requested windows then exit.

    if (this->game->isPaused && this->game->showPauseMenu)
    {
        this->pause->clear();
        menu->draw(this->pause);
        this->pause->refresh();
        this->main->refresh();
        return;
    }

    if (this->game->showHelp)
    {
        this->helpWindows->run();
        this->game->showHelp = false;

        return;
    }

    // First, updating all the container windows
    // (we need to do this otherwise when we draw something
    //  on top of them, they'll be broken with dirty things
    //  left on top)
    this->main->clear();
    this->board->clear();
    this->leftmost->clear();
    this->middle_left->clear();
    this->middle_right->clear();

    if (Globals::Profiles::current->settings.screen.show_statistics)
    {
        this->rightmost->clear();
    }

    // Now we'll draw the internal windows

    // Hold piece
    if (Globals::Profiles::current->settings.game.can_hold)
    {
        this->hold->clear();

        if (this->game->pieceHold)
            this->game->pieceHold->draw(this->hold);
    }

    // Next pieces
    for (int i = 0; i < Globals::Profiles::current->settings.game.next_pieces; i++)
    {
        Window* w = this->next[i];
        w->clear();

        Piece p(this->game->nextPieces[i], -1, -1);
        if (p.getType() == Piece::O)
            p.moveBy(0, 1);

        p.draw(w);

    }

    // Statistics on the left side
    // A mess of direct Ncurses calls - fix this later
    this->score->clear();

    int lowest_y = this->score->getH() - 2; // border

    this->score->print("Hi-Score", 1, lowest_y - 7, EngineGlobals::Theme::hilite_text);
    this->score->print("Score",    1, lowest_y - 4, EngineGlobals::Theme::hilite_text);
    this->score->print("Level",    1, lowest_y - 1, EngineGlobals::Theme::hilite_text);

    // Default color
    //Colors::pairActivate(this->score->win, EngineGlobals::Theme::text);

    this->score->print(std::to_string(Globals::Profiles::current->scores->score.points), 1, lowest_y - 3);
    this->score->print(std::to_string(Globals::Profiles::current->scores->score.level), 1, lowest_y);

    if (! Globals::Profiles::current->scores->highScore)
        this->score->print("(none)", 1, lowest_y - 6);
    else
        this->score->print(std::to_string(Globals::Profiles::current->scores->highScore->points), 1, lowest_y - 6);

    // Statistics and Misc. info
    // on the right part of the screen
    if (Globals::Profiles::current->settings.screen.show_statistics)
    {

        char buff[100];
        // User name
        this->rightmost->print(Globals::Profiles::current->name, this->rightmost->getW() - Globals::Profiles::current->name.size() - 2, 01, EngineGlobals::Theme::hilite_text);

        // Piece and Line Statistics
        this->rightmost->print("[I] x" + std::to_string(this->game->stats.I), 2, 2, Globals::Profiles::current->settings.theme.piece_I->color);
        this->rightmost->print("[T] x" + std::to_string(this->game->stats.T), 2, 3, Globals::Profiles::current->settings.theme.piece_T->color);
        this->rightmost->print("[L] x" + std::to_string(this->game->stats.L), 2, 4, Globals::Profiles::current->settings.theme.piece_L->color);
        this->rightmost->print("[J] x" + std::to_string(this->game->stats.J), 2, 5, Globals::Profiles::current->settings.theme.piece_J->color);
        this->rightmost->print("[S] x" + std::to_string(this->game->stats.S), 2, 6, Globals::Profiles::current->settings.theme.piece_S->color);
        this->rightmost->print("[Z] x" + std::to_string(this->game->stats.Z), 2, 7, Globals::Profiles::current->settings.theme.piece_Z->color);
        this->rightmost->print("[O] x" + std::to_string(this->game->stats.O), 2, 8, Globals::Profiles::current->settings.theme.piece_O->color);

        int x_offset = this->rightmost->getW() - 15;

        this->rightmost->print("Singles x" + std::to_string(this->game->stats.singles), x_offset, 2, EngineGlobals::Theme::hilite_text);
        this->rightmost->print("Doubles x" + std::to_string(this->game->stats.doubles), x_offset, 3, EngineGlobals::Theme::hilite_text);
        this->rightmost->print("Triples x" + std::to_string(this->game->stats.triples), x_offset, 4, EngineGlobals::Theme::hilite_text);
        this->rightmost->print("Tetris  x" + std::to_string(this->game->stats.tetris),  x_offset, 5, EngineGlobals::Theme::hilite_text);

        this->rightmost->print("Pieces  x" + std::to_string(this->game->stats.pieces),  x_offset, 7, EngineGlobals::Theme::hilite_text);
        this->rightmost->print("Lines   x" + std::to_string(this->game->stats.lines),   x_offset, 8, EngineGlobals::Theme::hilite_text);

        // Timer - how much time has passed since game start
        this->rightmost->print("Timer", 2, 10, EngineGlobals::Theme::hilite_text);

        long delta_s = this->game->timer.delta_s();

        int seconds = delta_s % 60;
        int minutes = (delta_s / 60) % 60;
        int hours   = ((delta_s / 60) / 60) % 24;

        snprintf(buff, sizeof(buff), "%02d:%02d:%02d", hours, minutes, seconds);
        std::string buffAsStdStr = buff;
        this->rightmost->print(buff, 8, 10, EngineGlobals::Theme::hilite_text);
        this->rightmost->print("Delay", 2, 12, EngineGlobals::Theme::hilite_text);

        this->rightmost->print(std::to_string(this->game->getDelay(Globals::Profiles::current->scores->score.level)), 8, 12);

        this->rightmost->print("gyetris v" VERSION, 1, this->rightmost->getH() - 2, EngineGlobals::Theme::hilite_text);

        this->rightmost->print("H", this->rightmost->getW() - 5, this->rightmost->getH() - 2, EngineGlobals::Theme::hilite_hilite_text);
        this->rightmost->print("elp", this->rightmost->getW() - 4, this->rightmost->getH() - 2, EngineGlobals::Theme::hilite_text);
    }

    // Need to draw the animation behind
    // the actual game
    if (this->animation)
    {
        this->animation->update();
        this->animation->draw();
    }

    this->game->board->draw(this->board);

    if (Globals::Profiles::current->settings.game.has_ghost)
        this->game->pieceGhost->draw(this->board);

    this->game->pieceCurrent->draw(this->board);

    this->hold->refresh();
    this->score->refresh();
    this->board->refresh();

    for (Window* window : next)
    {
        window->refresh();
    }

    this->middle_left->refresh();
    this->middle_right->refresh();
    this->rightmost->refresh();
    this->leftmost->refresh();
    this->main->refresh();
}

