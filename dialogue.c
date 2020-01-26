#include "dialogue.h"
#include "move.h"

#include <ncurses.h>

int play_again_dialogue(WINDOW* dialogue_window, int player, enum win_conditions win_condition) {
    char response;

    wclear(dialogue_window);
    if (win_condition == Win) {
        wattron(dialogue_window, COLOR_PAIR(player));
        mvwaddch(dialogue_window, 2, 3, ACS_BLOCK);
        waddch(dialogue_window, ACS_BLOCK);
        wattroff(dialogue_window, COLOR_PAIR(player));
        wprintw(dialogue_window, " wins!!\n");
    } else if (win_condition == Draw) {
        mvwprintw(dialogue_window, 2, 3, "It's a draw!");
    }
    mvwprintw(dialogue_window, 3, 3, "Play again? [y/n]");
    box(dialogue_window, 0, 0);
    wrefresh(dialogue_window);

    while ((response != 'y') && (response != 'n')) {
        response = wgetch(dialogue_window);
    }

    if (response == 'y')
        return 1;
    return 0;
}

void move_dialog(WINDOW* dialogue_window, int player) {
    wclear(dialogue_window);
    wattron(dialogue_window, COLOR_PAIR(player));
    mvwaddch(dialogue_window, 2, 3, ACS_BLOCK);
    waddch(dialogue_window, ACS_BLOCK);
    wattroff(dialogue_window, COLOR_PAIR(player));
    wprintw(dialogue_window, "'s move.");
    mvwprintw(dialogue_window, 3, 3, "Choose column...");
    box(dialogue_window, 0, 0);
    wrefresh(dialogue_window);
}

