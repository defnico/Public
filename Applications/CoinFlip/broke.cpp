#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
  cout << "Enter initial number of coins: ";
  int coins;
  cin >> coins;
  cout << "Enter the fairness as a decimal: ";
  double fairness;
  cin >> fairness;
  cout << "Enter number of game simulations: ";
  int games;
  cin >> games;

  srand(time(0));
  int total_turns = 0;
  for (int i = 0; i < games; i++) {
    int pcoins[3];
    for (int i = 0; i < 3; i++) {
      pcoins[i] = coins;
    }
    while (pcoins[0] > 0 && pcoins[1] > 0 && pcoins[2] > 0) {
      int player[3];
      for (int i = 0; i < 3; i++) {
        player[i] = 0;
      }
      for (int i = 0; i < 3; i++) {
        double flip = (double) rand() / RAND_MAX;
        if (flip < fairness) {
          player[i] = 1;
        }
      }
      if (player[0] != player[1] && player[0] != player[2]) {
        pcoins[0]+=2;
        pcoins[1]--;
        pcoins[2]--;
      } else if (player[1] != player[0] && player[1] != player[2]) {
        pcoins[1]+=2;
        pcoins[0]--;
        pcoins[2]--;
      } else if (player[2] != player[0] && player[2] != player[1]) {
        pcoins[2]+=2;
        pcoins[1]--;
        pcoins[0]--;
      }
      total_turns++;
    }
  }
  cout << setprecision(3);
  double avg_turns = (double) total_turns / games;
  cout << "Average: " << avg_turns << endl;
}