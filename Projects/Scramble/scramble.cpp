// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

int main(int argc, char* argv[]) {
  srand(time(0));
  char guess[80];

  ifstream ifile(argv[1]);
  if (argc != 2) {
    cout << "Please enter filename" << endl;
    return 1;
  }
  int numWords;
  ifile >> numWords;
  //cout << "numWords = " << numWords << endl;
  if (ifile.fail()) {
    cout << "Could not read file" << endl;
    return 1;
  }
  char** wordBank = new char*[numWords];
  for (int i = 0; i < numWords; i++) {
    char buffer[41];
    ifile >> buffer;
    //cout << "buffer = " << buffer << endl;
    int len = strlen(buffer);
    //cout << "len = " << len << endl;
    char* temp = new char[len];
    strncpy(temp, buffer, len+1);
    //cout << "temp = " << temp << endl;
    wordBank[i] = temp;
  }
  ifile.close();

  bool wordGuessed = false;
  int numTurns = 10;

  // Pick a random word from the wordBank
  int target = rand() % numWords;
  int targetLen = strlen(wordBank[target]);

  // Make a dynamically-allocated copy of the word and scramble it
  char* word = new char[targetLen+1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);
  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (!wordGuessed && numTurns > 0) {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? ";
    cin >> guess;
    wordGuessed = (strcmp(guess, wordBank[target]) == 0);
    numTurns--;
  }
  if (wordGuessed) {
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
    cout << "Word was: " << wordBank[target] << endl;
  }
  delete[] word;
  return 0;
}

// Scramble the letters. See "Knuth shuffle" on Wikipedia.
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}
