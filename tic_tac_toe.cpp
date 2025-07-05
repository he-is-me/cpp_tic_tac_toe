#include <cstdio>
#include <cstdlib>
#include <map>
#include <ios>
#include <ostream>
#include <tuple>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

#define DEBUG

map<int, vector<char>> screen_board {

    {0, {' ','|',' ','|',' '}},

    {1, {'-','-','-','-','-'}},

    {2, {' ', '|',' ','|',' '}},

    {3, {'-','-','-','-','-'}},

    {4, {' ', '|',' ','|',' '}}
  };




int getPlayerCount()
{
  int player_count{};
  while (!(cin >> player_count) || (player_count != 2 && player_count != 1)){
    if (cin.fail()){
    cout << "Invalid player count dickhead !\n";
    cout << "Number of players: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    } else {

    cout << "Invalid range dumbass try again\n"
            "Enter a number between (1-2): ";
    }
    }
  return player_count;
  }



void intro()
{
  cout << "WELCOME TO TICK TACK TOES !!\n"
          "how many users will be playing?(1-2)\n"
          "Number of players: ";
}


map<int, vector<char>> updateScreenBoard(map<int, vector<char>>& updated_screen_board,
                                      int played_row, int played_col, char player_symbol)
{
  screen_board[played_row][played_col] = player_symbol;
  for (const auto& [rowId, rows]: screen_board ){
    cout << '\n';
    for (const auto& row: rows){
      cout << row << "";
    }
  }
    cout << endl;

  return screen_board;
}

void displayBoard()
{
  for (const auto& [rowId, rows]: screen_board ){
    cout << '\n';
    for (const auto& row: rows){
      cout << row << "";
    }
  }
    cout << endl;
}


void modifyValidMoves(map<string, vector<tuple<int,int,char>>>& winning_moves_map,
                      int played_row, int played_col, char player_symbol)
{
  for (const auto& [key,vec]: winning_moves_map) {
    int vec_count{0};
    for (const auto& [row, col, symbol]: vec){
      if (row == played_row && col == played_col){
        if (symbol != ' '){
          cout << "this spot is taken, pick another !" << endl;
          return;
        }else {
          get<2>(winning_moves_map[key][vec_count]) = player_symbol;
        #ifdef DEBUG
          cout << "key: " << key << '\n' << "--------\n";
          cout << "row: " << row << " col: " << col << " player: " << player_symbol << '\n';
        #endif 
        }

      }
    ++vec_count;
    }
  }
}


map<string, vector<tuple<int,int,char>>> validMoves()
  // key: move name, tuple(row, col , held by? x||o)
{
  map<string, vector<tuple<int,int,char>>> winning_moves 
  {
    {"top_hor", { make_tuple(0,0,' '), make_tuple(0,2,' '), make_tuple(0,4,' ')}},
    {"mid_hor", { make_tuple(2,0,' '), make_tuple(2,2,' '), make_tuple(2,4,' ')}},
    {"bot_hor", { make_tuple(4,0,' '), make_tuple(4,2,' '), make_tuple(4,4,' ')}},
    {"left_diag", { make_tuple(0,0,' '), make_tuple(2,2,' '), make_tuple(4,4,' ')}},
    {"right_diag", { make_tuple(0,4,' '), make_tuple(2,2,' '), make_tuple(4,0,' ')}},
    {"right_vert", { make_tuple(0,4,' '), make_tuple(2,4,' '), make_tuple(4,4,' ')}},
    {"mid_vert", { make_tuple(0,2,' '), make_tuple(2,2,' '), make_tuple(4,2,' ')}},
    {"left_vert", { make_tuple(0,0,' '), make_tuple(2,0,' '), make_tuple(4,0,' ')}},
  };
  return winning_moves;
}


pair<int, int> verifyMove(int row, int col)
{
  if (row == 1){
    --row;
  }else if (row == 3) {
    ++row;
  }
  if (col == 1){
    --col;
  }else if (col == 3) {
    ++col;
  } return {row , col};
  if (col > 4 || row > 4){
    return {9,9};
  }else if (col < 1 || row < 1) {
    return {9,9};
  }
  return {row, col};
}


int main () 
{
  intro();
  int game_progress{0};
  int player_count{getPlayerCount()};
  cout << player_count << " Player game it is then!\n";
  auto winning_moves_map{validMoves()};
  displayBoard();
  int row_move;
  int col_move;
  while (game_progress != 9){
    if (cin >> row_move >> col_move){
      pair<int, int> moves{verifyMove(row_move,col_move)};

    if (moves.first == 9 && moves.second == 9){
      cout << "INVALID MOVE (1-3 only)" << '\n';
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
      continue;
    }
      modifyValidMoves(winning_moves_map, moves.first, moves.second, 'x');
      cout << moves.first << " " << moves.second;
      updateScreenBoard(screen_board, moves.first,moves.second, 'x');
      ++game_progress;
#ifdef DEBUG
      cout << "GAME PROGRESS: " << game_progress;
#endif // DEBUG

      }else {
        continue;
            }
  }
  cout << "Game Over !" << endl;
  return 0;

}   



