#ifndef APP_H_
#define APP_H_

#define ROW 3
#define COL 3

int str_len(char* );
void players_choices(char* , char* );
void print_board(char(*)[COL]);
void player_turn(char(*)[COL], int , char );
int game_state(char(*)[COL], char );
void app(void);

#endif /* APP_H_ */