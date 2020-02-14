#pragma once

#include <stdbool.h>
#include <ncurses.h>
#include "move.h"
#include "print.h"

bool play_again_dialogue(WINDOW* dialogue_window, const enum players player, enum win_conditions win_condition);
void move_dialog(WINDOW* dialogue_window, const enum players player);
