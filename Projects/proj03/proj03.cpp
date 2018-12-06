#include <iostream>
#include <iomanip>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
// add any other includes you need. Up to you

/*
  for this we will use:
  1 - rock
  2 - paper
  3 - scissors
*/

// PUT YOUR FUNCTIONS BELOW THIS LINE
int strategy1 (int player, int previous_result, int previous_play, int opponent_previous_play) { //Return your previous_play + 1. In order. If you had rock, it returns paper. If you had paper, return scissors.
    if (previous_play == 1) {
        return 2;
    }
    else if (previous_play == 2) {
        return 3;
    }
    else {
        return 1;
    }
}

int strategy2 (int player, int previous_result, int previous_play, int opponent_previous_play) { //If you won or tied, we stick to previous play. Otherwise, we pick the opponents previous play.
    if ((player == 1) && (previous_result == 0 || previous_result == 1)) {
        return previous_play;
    }
    else if ((player == 2) && (previous_result == 0 || previous_result == 2)) {
        return previous_play;
    }
    else {
        return opponent_previous_play;
    }
}

int strategy3 (int player, int previous_result, int previous_play, int opponent_previous_play) { //If player won or tied, we stick with that previous play. Otherwise, it picks a play that could beat the opponents previous play.
    if ((player == 1) && (previous_result == 0 || previous_result == 1)) {
        return previous_play;
    }
    else if ((player == 2) && (previous_result == 0 || previous_result == 2)) {
        return previous_play;
    }
    else {
        if (opponent_previous_play == 1) {
            return 2;
        }
        else if (opponent_previous_play == 2) {
            return 3;
        }
        else {
            return 1;
        }
    }
}

int score_round(int player1_move, int player2_move) { // Checks all moves possible pretty much and checks for winner on each matchup.
    if ((player1_move == 1) && (player2_move == 2)) {
        return 2;
    }
    else if ((player1_move == 2) && (player2_move == 3)) {
        return 2;
    }
    else if ((player1_move == 3) && (player2_move == 1)) {
        return 2;
    }
    else if ((player1_move == 2) && (player2_move == 1)) {
        return 1;
    }
    else if ((player1_move == 3) && (player2_move == 2)) {
        return 1;
    }
    else if ((player1_move == 1) && (player2_move == 3)) {
        return 1;
    }
    else {
        return 0;
    }
}


// MAIN IS BELOW, DON'T CHANGE

int main() {
  cout << boolalpha;   // print true or false for bools
  int test;
  cin >> test;
  
  switch (test) {
  case 1 : {   // strategy 1
    long player, previous_result, previous_play, opponent_play;
    cin >> player >> previous_result >> previous_play >> opponent_play;
    cout << strategy1(player, previous_result, previous_play, opponent_play) << endl;
    break;
  } // of case 1

  case 2:{    // strategy 2
    long player, previous_result, previous_play, opponent_play;
    cin >> player >> previous_result >> previous_play >> opponent_play;
    cout << strategy2(player, previous_result, previous_play, opponent_play) << endl;
    break;
  } // of case 2

  case 3: {    // strategy 3
    long player, previous_result, previous_play, opponent_play;
    cin >> player >> previous_result >> previous_play >> opponent_play;
    cout << strategy3(player, previous_result, previous_play, opponent_play) << endl;
    break;
  } // of case 3

  case 4: {       // score result
    long p1, p2;
    cin >> p1 >> p2;
    cout << score_round(p1, p2) << endl;
    break;
  } // of case 4
    
  } // of switch
} // of main
