#include <cstdio>
#include <cstdlib>
#include <map>
#include <ios>
#include <ostream>
#include <tuple>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

#define DEBUG
// #define DEEP_DEBUG
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

  int vec_count{0};
  for (const auto& [key,vec]: winning_moves_map) {
    vec_count = 0;
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




bool checkForWinner(map<string, vector<tuple<int,int,char>>>& winning_moves_map,
                    int played_row, int played_col, char player_symbol)
{
  int win_count{0}; 
  for (const auto& [key,vec]: winning_moves_map) {
    for (const auto& [r,c,symbol]: vec){
      char pos_1 = get<2>(winning_moves_map[key][0]);
      char pos_2 = get<2>(winning_moves_map[key][1]);
      char pos_3 = get<2>(winning_moves_map[key][2]);
        if (
            symbol != ' ' 
            && pos_1 == player_symbol
            && pos_2 == player_symbol
            && pos_3 == player_symbol
            )
        {

          cout << "key: " << key << '\n' << "--------\n"
               << player_symbol << " WINS !!" << endl;
          return true;

        }else {
        break;
        }
    }
  }
  return false;
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
  if (col >= 4 || row >= 4){
    return {9,9};
  }else if (col < 1 || row < 1) {
    return {9,9};
  }
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
  return {row, col};
}


pair<char,char> getPlayerSymbols()
{
   
  char player_1{' '};
  char player_2{' '};
  cout << "player #1 choose your symbol: x or o ?" << '\n';
  while (!(cin >> player_1)){
    cout << "Did I tell you that was an option ?? No , no I didnt." << '\n';
  }
  if (player_1 == 'x'){
    player_1 = 'x';
    player_2 = 'o';
    return {player_1, player_2};
  }else{
    player_1 = 'o';
    player_2 = 'x';
    return {player_1, player_2};
  }
}



int main () 
{
  intro();
  int game_progress{0};
  int player_count{getPlayerCount()};

  pair<char,char> player_symbols;
  if (player_count == 2){
    player_symbols = getPlayerSymbols();
  }else{
    player_symbols = {'x','o'};
    }
  char player_1 = player_symbols.first;
  char player_2 = player_symbols.second;

  cout << player_count << " Player game it is then!\n";
  auto winning_moves_map{validMoves()};
  displayBoard();
  int row_move;
  int col_move;

  while (game_progress != 9){
    if (player_count == 2){
      for (char player: {player_1,player_2}){
        char current_player = player;

        if (cin >> row_move >> col_move){
          pair<int, int> moves{verifyMove(row_move,col_move)};

#ifdef DEBUG
          cout << "current player: " << player << " " 
               << "player_1: " << player_1 << " "
               << "player_2: " << player_2 << " "
               << "player_count " << player_count << " "
               << "row move: " << row_move << " " 
               << "col_move: "<< col_move << '\n';
#endif // DEBUG

        if (moves.first == 9 && moves.second == 9){
          cout << "INVALID MOVE (1-3 only)" << '\n';
          continue;
        }

          modifyValidMoves(winning_moves_map, moves.first, moves.second, current_player);
          cout << moves.first << " " << moves.second;
          updateScreenBoard(screen_board, moves.first,moves.second, current_player);

          if (checkForWinner(winning_moves_map, moves.first, moves.second, current_player)){
            return 0;
          }else{
            ++game_progress;
#ifdef DEBUG
            cout << "GAME PROGRESS: " << game_progress << '\n';
#endif // DEBUG
            continue;
          }

          }else {
            cout << "THE FUCK ?!?" << '\n';
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue;
                }
        }
    }
  }
  cout << "Game Over !" << endl;
  return 0;
}   



