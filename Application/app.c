#include <stdio.h>
#include "app.h"

int str_len(char* str) {
    int l = 0;

    while (str[l] != '\0') {
        l++;
    }
    return l;
}

void players_choices(char* player1_choice, char* player2_choice) {
    char choice;
    char str_ch[200];

    while (1) {
        printf("player 1 choice: X or O\n");
        gets(str_ch);
        if (str_len(str_ch) > 1) {
            printf("wrong input, try again\n");
            continue;
        }

        choice = str_ch[0];
        if (!(choice == 'X' || choice == 'x' || choice == 'O' || choice == 'o')) {
            printf("wrong input, try again\n");
            continue;
        }
        if (choice == 'x') { choice = 'X'; }
        else if (choice == 'o') { choice = 'O'; }

        *player1_choice = choice;
        if (choice == 'X') { *player2_choice = 'O'; }
        else { *player2_choice = 'X'; }

        printf("player 1 plays as %c\n", *player1_choice);
        printf("player 2 plays as %c\n", *player2_choice);
        break;
    }
}

void print_board(char(*game_board)[COL]) {
    for (int x = 0; x < ROW; x++) {
        for (int y = 0; y < COL; y++) {
            printf("%c ", game_board[x][y]);
        }
        printf("\n");
    }
}

void player_turn(char(*game_board)[COL], int player_num, char player_choice) {
    printf("player %d turn\n", player_num);
    int row, col;
    char str_val[200];

    while (1) {
        printf("player %d enters %c\n", player_num, player_choice);

        printf("choose row (1 to 3)\n");
        gets(str_val);
        if (str_len(str_val) > 1) {
            printf("wrong input, try again\n");
            continue;
        }

        row = str_val[0] - '0';
        if (row < 1 || row>3) {
            printf("wrong input, try again\n");
            continue;
        }

        printf("choose col (1 to 3)\n");
        gets(str_val);
        if (str_len(str_val) > 1) {
            printf("wrong input, try again\n");
            continue;
        }

        col = str_val[0] - '0';
        if (col < 1 || col>3) {
            printf("wrong input, try again\n");
            continue;
        }

        row--; col--;
        if (!(game_board[row][col] == '-')) {
            printf("this cell is filled, try again\n");
            continue;
        }

        break;
    }

    game_board[row][col] = player_choice;
}

int game_state(char(*game_board)[COL], char cell) {
    int state = 0;

    for (int x = 0, y = 0; x < ROW && y < COL; x++, y++) {
        if (game_board[x][0] == cell && game_board[x][1] == cell && game_board[x][2] == cell) {
            state = 1;
        }

        if (game_board[0][y] == cell && game_board[1][y] == cell && game_board[2][y] == cell) {
            state = 1;
        }
    }

    if (game_board[0][0] == cell && game_board[1][1] == cell && game_board[2][2] == cell) {
        state = 1;
    }
    if (game_board[0][2] == cell && game_board[1][1] == cell && game_board[2][0] == cell) {
        state = 1;
    }

    return state;
}

void app(void) {
    char game_board[3][3] = { "---", "---", "---" };

    char player1_choice, player2_choice;
    int cnt = 0, state = 0;

    players_choices(&player1_choice, &player2_choice);

    while (1) {
        printf("current game board\n");
        print_board(game_board);

        //player 1 turn
        player_turn(game_board, 1, player1_choice);
        if (game_state(game_board, player1_choice)) {
            printf("player 1 won\n");
            print_board(game_board);
            state = 1;
            break;
        }

        cnt++;
        if (cnt == 9) { break; }

        printf("current game board\n");
        print_board(game_board);

        //player 2 turn
        player_turn(game_board, 2, player2_choice);
        if (game_state(game_board, player2_choice)) {
            printf("player 2 won\n");
            print_board(game_board);
            state = 1;
            break;
        }

        cnt++;
    }

    if (!state) {
        printf("tie game\n");
        print_board(game_board);
    }
}