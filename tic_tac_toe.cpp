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
  // This is printing out the gameboard to the screen 
  screen_board[played_row][played_col] = player_symbol;
  for (const auto& [rowId, rows]: screen_board ){
    cout << '\n';
    for (const auto& row: rows){
      cout << row << "";
    }
  }
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


bool modifyValidMoves(map<string, vector<tuple<int,int,char>>>& winning_moves_map,
                      int played_row, int played_col, char player_symbol)
{
  int vec_count{0};
  for (const auto& [key,vec]: winning_moves_map) {
    vec_count = 0;
    for (const auto& [row, col, symbol]: vec){
      if (row == played_row && col == played_col){
        if (symbol != ' '){
          cout << "this spot is taken, pick another !" << endl;
#ifdef DEBUG
          cout << "CURRENT SYMBOL IN " << key << "("<< played_col << "," << played_col
               << "): [" << symbol << "]" << endl;
#endif // DEBUG
          return false;
        }else {
          cout << "!!!!!!!!!!\n!!!!!!!!!!!!!!!!!!!\n!!!!!!!!!!!!!!!!!!!!!\n!!!!!!!!!!!!!!!!!!!!!!!!\n";
          get<2>(winning_moves_map[key][vec_count]) = player_symbol;

        #ifdef DEBUG
          cout << "JUST PLACED " << player_symbol << " AT " << key << ": (" << row << ", " << col << endl;
          cout << "key: " << key << '\n' << "--------\n";
          cout << "row: " << row << " col: " << col << " player: " << player_symbol << '\n';
        #endif 
        }

      }
    ++vec_count;
    }
  }
#ifdef DEBUG
  cout << "MODIFIED VALID MOVES RETURNING TRUE\n\n";

#endif // DEBUG
  return true;
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

map<string, vector<tuple<int,int,char>>> validMovesMap()
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



pair<int,int> getMoves(char player_1, char player_2,
                       int player_count, char player)
{
  pair<int, int> moves{0,0};
  int row_move{};
  int col_move{};

  //if the user is a dickhead force them to generate braincells
  cout << "\n\n";
  while (true){
    cout << "Row: ";
    cin >> row_move;
    if (cin.fail()){
      cout << '\n' << "INVALID ROW #" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    cout << "Row: " << row_move << " Col: ";
    cin >> col_move;
    if (cin.fail()){
      cout << '\n' << "INVALID COLUMN #" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
  }
      cout << "Row: " << row_move << " Col: " << col_move;
  
#ifdef DEBUG
    cout << "adjusted verified moves: " << moves.first << " & " << moves.second << '\n'
         << "current player: " << player << '\n' 
         << "player_1: " << player_1 << '\n'
         << "player_2: " << player_2 << '\n'
         << "player_count " << player_count << '\n'
         << "row move: " << row_move << '\n' 
         << "col_move: "<< col_move << endl;
#endif // DEBUG

  moves = verifyMove(row_move,col_move);
  if (moves.first == 9 && moves.second == 9){
      cout << "INVALID MOVE (1-3 only)" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }else {
      return {moves.first, moves.second};
    }
  } 
}

      






bool twoPlayerMode(char player_1, char player_2, int player_count,
                  map<string, vector<tuple<int,int,char>>>& winning_moves_map)
{
  for (char player: {player_1,player_2}){
    char current_player = player;

    pair<int,int> moves = getMoves(player_1, player_2, player_count, player);

    bool placement = modifyValidMoves(winning_moves_map, moves.first, moves.second, current_player);
#ifdef DEBUG
      cout << moves.first << " " << moves.second << endl;
#endif // DEBUG
     
      if (placement){
      updateScreenBoard(screen_board, moves.first,moves.second, current_player);
      }else {
        while (true){ 
          cout << "pre-check PLACEMENT BOOL: "<< placement << endl;
    
          // keep looping until user gives a move thats not taken
          // placement checks that the move the player entered isnt
          // already occupied
        pair<int,int> moves = getMoves(player_1, player_2, player_count, player);
        cout << "DEBUGGG: " << moves.first << " " << moves.second << "current_player: !!!!!" << current_player <<  endl;
        placement = modifyValidMoves(winning_moves_map, moves.first, moves.second, current_player);
        cout << "post-check PLACEMENT BOOL: " << placement << endl;
        //after we finally get valid placement update the screen with it
        if (placement){
        updateScreenBoard(screen_board, moves.first,moves.second, current_player);
        break;
        } else {
        continue;
          }
        }
      }
    if (checkForWinner(winning_moves_map, moves.first, moves.second, current_player)){
      return false;
    }
    }
return true;
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
  auto winning_moves_map{validMovesMap()};
  displayBoard();

  bool game_over{true};
  while (game_over){
    if (player_count == 2){
      game_over = twoPlayerMode(player_1, player_2, player_count, winning_moves_map);
                                     
    }
  }
  cout << "Game Over !" << endl;
  return 0;
}   



