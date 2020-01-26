#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <ncurses.h>
#include "move.h"

int play_again_dialogue(WINDOW* dialogue_window, int player, enum win_conditions win_condition);
void move_dialog(WINDOW* dialogue_window, int player);

#endif /* ifndef DIALOGUE_H */
