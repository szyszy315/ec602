#include <iostream>
#include <string>
#include <vector>
#include<algorithm>
#include "movedef.h"
#include <map>
using namespace std; 

using std::cout;
using std::string;
using std::vector;

char tttresult(string board) {
  std::vector<char> result; 
  int check;
  int xnum;
  int onum;
  check = 0;
  int n = board.size();
  if (n != 9){
    return 'i';
  }
  xnum = count(board.begin(),board.end(), 'x');
  onum = count(board.begin(),board.end(), 'o');
  if ((xnum - onum)> 1 ||(xnum < onum)){
    return 'i';
  }
  for (int i = 0; i < 7 ; i = i + 3){
    if (board.at(i)==board.at(i+1) && board.at(i)== board.at(i+2) && board.at(i) != '#'){
      result.push_back(board.at(i));
    }
  }
  for (int i = 0; i < 3 ; i = i + 1){
    if (board.at(i)==board.at(i+3) && board.at(i)== board.at(i+6) && board.at(i) != '#'){
      result.push_back(board.at(i));
    }
  }
  if (board.at(0)==board.at(4) && board.at(0)== board.at(8) && board.at(0) != '#'){
    result.push_back(board.at(0));
  }
  if (board.at(2)==board.at(4) && board.at(0)== board.at(6) && board.at(2) != '#'){
    result.push_back(board.at(0));
  }
  if (result.size() == 1){
    return result.at(0);
  }
  else if (result.size() > 1){
    for (int i = 0;i != result.size()-1; i ++){
      if (result.at(i) != result.at(i+1)){
        return 'i';
      }
    return result.at(0);
    }
  }
    return 'c';
}

char tttresult(vector<Move> board) {
  string res = "#########";
  int count = 0;
  for (int i = 0; i != board.size(); i++){
    if ((count%2 == 0 && board.at(i).player == 'o') || (count%2 == 1 && board.at(i).player == 'x')){
      return 'i';
    }
    if(board.at(i).r == 0){
      res.at(board.at(i).c) = board.at(i).player;
    }
    else if (board.at(i).r == 1)
      res.at(board.at(i).c + 3) == board.at(i).player;
    else{
      res.at(board.at(i).c + 6) == board.at(i).player;
    }
    count += 1;
  }
  return tttresult(res);
}

void getallhelper(string path,vector<string> boards){
  if (path.size() == 9){
    boards.push_back(path);
    return;
  }
  getallhelper(path.append("o"),boards);
  getallhelper(path.append("x"),boards);
  getallhelper(path.append("#"),boards);
}

vector<string> get_all_boards() {
  vector<string> boards;
  string path;
  getallhelper(path,boards);
  return boards;
}


void ttt_tally() {
  string keys ="xotic";
  map <char,int> tally;
  char results;
  vector<string> boards = get_all_boards();
  for (std::vector<string>::iterator i = boards.begin();i != boards.end(); i++){
    results = tttresult(*i);
    tally[results] += 1;
  }
  for (map <char,int>::const_iterator it = tally.begin() ; it != tally.end() ; it ++){
    cout << it -> first << ' ' << it -> second << "\n";
  }
}

// This version of main interactively
// tests either:
//
//  string tttresult "s"
//  vector tttresult "v"
// or 
//  get_all_boards "a"
//
// MAIN

int main() {
  int n;
  std::string board;
  Move m;
  std::vector<Move> moves;
  std::vector<std::string> boards;
  std::string asktype;

  while (std::cin >> asktype) {
    if (asktype == "v") {  // test tttresult vector
      moves.clear();
      std::cin >> n;
      for (int i = 0; i < n; i++) {
        std::cin >> m.r >> m.c >> m.player;
        moves.push_back(m);
      }
      std::cout << tttresult(moves) << "\n";
    } else if (asktype == "s") {  // test tttresult string
      std::cin >> board;
      std::cout << tttresult(board) << "\n";
    } else if (asktype == "a") {  // test get_all_boards
      boards = get_all_boards();
      for (auto b : boards) {
        std::cout << b << "\n";
      }
    } else if (asktype == "t") {  // test ttt_tally
      ttt_tally();
    } else {
      return 0;
    }
  }
  return 0;
}
