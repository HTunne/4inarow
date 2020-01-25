#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <ncurses.h>

int play_again_dialogue(WINDOW* dialogue_window, int player);
void move_dialog(WINDOW* dialogue_window, int player);

#endif /* ifndef DIALOGUE_H */
