#include "ScrabbleAI.h"
#include "Game.h"
#include <algorithm>
#include <cassert>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

ScrabbleAI::ScrabbleAI(Game& game) : game_(game) {}
ScrabbleCPUL::ScrabbleCPUL(Game& game) : ScrabbleAI(game) {}
ScrabbleCPUS::ScrabbleCPUS(Game& game) : ScrabbleAI(game) {}

set<string> GeneratePermutationStrings(set<Tile*> tiles) {
  string letters;
  for (set<Tile*>::iterator i = tiles.begin(); i != tiles.end(); i++) {
    Tile* tile = *i;
    if (tile->isBlank()) {
      letters.push_back(' ');
    } else {
      letters.push_back(tile->getLetter());
    }
  }

  // std::next_permutation needs to start with a sorted string.
  sort(letters.begin(), letters.end());
  set<string> perms;
  do {
    // Add all the subsets to the permutations.
    for (size_t i = 0; i < tiles.size(); i++) {
      perms.insert(letters.substr(0, i));
    }
  } while (std::next_permutation(letters.begin(), letters.end()));

  return perms;
}

// Return true if the permutation should be skipped because the beginning
// letters are part of a prefix that didn't work.
bool SkipPrefix(const unordered_set<string>& skipPrefixes,
                const string& permutation) {
  for (size_t i = 0; i < permutation.size(); i++) {
    if (skipPrefixes.find(permutation.substr(0, i)) != skipPrefixes.end()) {
      return true;
    }
  }
  return false;
}

// Search for the best placement of a player's tiles.
// Returns an empty vector if there is no valid placement.
vector<PlacedTile> ScrabbleAI::BestPlacementSearch(const set<Tile*>& tiles) {
  Board& board = game_.board();
  vector<vector<Tile*>>& boardTiles = board.tiles();

  int startRow = board.startRow();
  int startCol = board.startCol();
  const bool firstWordOfGame =
      (boardTiles[startRow][startCol] == nullptr && !game_.initFileSpecified());

  int width = board.width();
  int height = board.height();

  // Create a vector of all the permutations and subsets of permutations.
  set<string> perms = GeneratePermutationStrings(tiles);

  // Keep track of max score and tiles placed for the best placement.
  // Also keep track of any blank letters used for this maximum.
  vector<PlacedTile> maxPlacedTiles;
  vector<int> maxBlankIndices;
  vector<char> maxBlankLetters;
  int maxScore = -1;

  // Examine every possible placement and permutation of the player_tiles.
  for (int r = 0; r < height; r++) {     // All rows.
    for (int c = 0; c < width; c++) {    // All columns.
      if (boardTiles[r][c] != nullptr) { // Skip (row,col) if not free
        continue;
      }
      for (int d = 0; d < 2; d++) { // Horizontal and Vertical.
        if (firstWordOfGame) {
          if ((d == 0 && r != startRow) || (d == 1 && c != startCol)) {
            continue;
          }
        }

        // cout << "r = " << r << ", c = " << c << ", d = " << d << endl;

        // Use hashed sets for faster lookup.
        unordered_set<string> skipPrefixes;

        for (set<string>::iterator p = perms.begin(); p != perms.end(); p++) {
          const string& perm = *p;

          if (perm.find_first_of(' ') == string::npos) {
            TryPermutation(perm, perm, tiles, r, c, d, skipPrefixes,
                           maxPlacedTiles, maxScore);
          } else { // Try all letters for the blank tiles.
            // Get the indices of the permutation where ther are blanks.
            vector<int> blankIndices;
            vector<char> blankLetters;
            for (size_t i = 0; i < perm.size(); i++) {
              if (perm[i] == ' ') {
                blankIndices.push_back(i);
                break; // First try one blank.
              }
            }
            blankLetters.resize(blankIndices.size());

            for (int i = 0; i < 26; i++) {
              string permCopy = perm;
              char ch = 'A' + i;
              blankLetters[0] = ch;
              permCopy[blankIndices[0]] = ch;
              if (TryPermutation(permCopy, perm, tiles, r, c, d, skipPrefixes,
                                 maxPlacedTiles, maxScore)) {
                maxBlankIndices = blankIndices;
                maxBlankLetters = blankLetters;
              }
            } // for (int i = 0; i < 26; i++)
          }   // else try all blank tile letters.
        }     // for (p = perms.begin(); p != perms.end(); p++)
      }       // for (int d = 0; d < 2; d++)
    }         // for (int c = 0; c < width; c++)
  }           // for (int r = 0; r < height; r++)

  for (size_t i = 0; i < maxBlankIndices.size(); i++) {
    Tile* tile = maxPlacedTiles[maxBlankIndices[i]].tile;
    tile->useAs(maxBlankLetters[i]);
  }
  return maxPlacedTiles;
}

// See if the permutation is the best so far.
bool ScrabbleAI::TryPermutation(const string& perm, const string& permBlanks,
                                const set<Tile*>& tiles, int r, int c, int d,
                                unordered_set<string>& skipPrefixes,
                                vector<PlacedTile>& maxPlacedTiles,
                                int& maxScore) {
  // Check if this permutation should be skipped in case the prefix
  // formed by a subset of the permutation was not part of any valid
  // word. In this there is no point trying a permutation
  // with additional letters.
  if (SkipPrefix(skipPrefixes, perm)) {
    return false;
  }

  // Get the squares and word from placing permutation on board.
  string word;
  vector<RowCol> squares = PlacePermutation(perm, r, c, d, word);
  if (squares.empty()) {
    return false; // Couldn't place all the letters of the permutation.
  }
  assert(squares.size() == perm.size());

  const Dictionary& dictionary = game_.dictionary();
  if (dictionary.isDictionaryWord(word)) {
    // Get the tiles for the permutation.
    vector<PlacedTile> placedTiles =
        GetPermutationPlacedTiles(perm, permBlanks, squares, tiles);

    // Place tiles on board and construct the words.
    vector<string> words;
    vector<int> scores;
    string error = game_.ConstructWords(placedTiles, words, scores);
    if (error.empty()) {
      // Take the tiles off the board since words were only
      // constructed to get the best score.
      vector<vector<Tile*>>& boardTiles = game_.board().tiles();
      for (size_t i = 0; i < placedTiles.size(); i++) {
        const PlacedTile& placedTile = placedTiles[i];
        boardTiles[placedTile.row][placedTile.col] = nullptr;
      }

      // Get the AI score from derived class.
      int score = GetAIScore(placedTiles, words, scores);
      if (score > maxScore) {
        maxScore = score;
        maxPlacedTiles = placedTiles;
        return true;
      }
    }
  } else if (!dictionary.isDictionaryPrefix(word)) {
    // If the word formed by this permutation is not a valid prefix then add
    // this word to the prefixes to skip.
    skipPrefixes.insert(perm);
  }

  return false; // Permutation is not good.
}

// Place a permutation of tiles on the board starting at (r,c). If successful
// return what squares the tiles were placed and the word made.
// Return an empty vector if all the tiles of permutation could not be placed.
vector<RowCol> ScrabbleAI::PlacePermutation(const string& perm, int r, int c,
                                            int dir, string& word) {
  // Find the first letter of the word.
  Board& board = game_.board();
  vector<vector<Tile*>>& tiles = board.tiles();
  int width = board.width();
  int height = board.height();

  vector<RowCol> emptySquares;

  int n = perm.size();
  if (dir == 0) {
    if (c + n > width) {
      return emptySquares;
    }

  } else if (r + n > height) {
    return emptySquares;
  }

  // Get the letters of the word starting with the first letter.
  // Keep track of the tiles with their row, col used to make this word.
  vector<RowCol> squares;
  if (dir == 0) {
    // Find left-most non-empty tile.
    while (c > 0 && tiles[r][c - 1] != nullptr) {
      c--;
    }

    size_t permIndex = 0;
    while (permIndex < perm.size() && c < width) {
      Tile* tile = tiles[r][c];
      if (tile == nullptr) { // Place perm tile at this blank square.
        word.push_back(perm[permIndex++]);
        squares.push_back(RowCol(r, c));
      } else {
        word += tile->getLetter();
      }
      c++;
    }

    if (permIndex < perm.size()) { // Couldn't place all the tiles.
      return emptySquares;
    } else { // Get any remaining non-null tiles to the right.
      for (; c < width && (tiles[r][c] != nullptr); c++) {
        word += tiles[r][c]->getLetter();
      }
    }
  } else {
    // Find upper-most non-empty tile.
    while (r > 0 && tiles[r - 1][c] != nullptr) {
      r--;
    }

    size_t permIndex = 0;
    while (permIndex < perm.size() && r < height) {
      Tile* tile = tiles[r][c];
      if (tile == nullptr) { // Place perm tile at this blank square.
        word.push_back(perm[permIndex++]);
        squares.push_back(RowCol(r, c));
      } else {
        word += tile->getLetter();
      }
      r++;
    }

    if (permIndex < perm.size()) {
      return vector<RowCol>(); // Couldn't place all the tiles.
    } else {                   // Get any remaining non-null tiles below.
      for (; r < height && (tiles[r][c] != nullptr); r++) {
        word += tiles[r][c]->getLetter();
      }
    }
  }

  return squares;
}

// Get a tiles for the letters in the permutation.
// permBlanks are the original letters with the blanks which is used
// to get the blank tiles.
vector<PlacedTile> ScrabbleAI::GetPermutationPlacedTiles(
    const string& perm, const string& permBlanks, const vector<RowCol>& squares,
    const set<Tile*>& tiles) {
  assert(perm.size() == squares.size());

  const int permSize = perm.size();
  vector<PlacedTile> placedTiles;
  for (size_t i = 0; i < squares.size(); i++) {
    PlacedTile placedTile(nullptr, squares[i].row, squares[i].col);
    placedTiles.push_back(placedTile);
  }

  int count = 0;
  for (set<Tile*>::const_iterator i = tiles.begin();
       i != tiles.end() && count < permSize; i++) {
    Tile* tile = *i;
    for (size_t j = 0; j < placedTiles.size(); j++) {
      PlacedTile& placedTile = placedTiles[j];
      if (placedTile.tile != nullptr) {
        continue;
      } else if (tile->isBlank()) {
        if (permBlanks[j] == ' ') {
          placedTile.tile = tile;
          tile->useAs(perm[j]);
          count++;
          break;
        }
      } else if (tile->getLetter() == perm[j]) {
        placedTile.tile = tile;
        count++;
        break;
      }
    }
  }

  return placedTiles;
}

// Maximize total length of words created.
int ScrabbleCPUL::GetAIScore(const vector<PlacedTile>& placedTiles,
                             const vector<string>&, const vector<int>&) const {
  return placedTiles.size();
}

// Maximize total score.
int ScrabbleCPUS::GetAIScore(const vector<PlacedTile>& placedTiles,
                             const vector<string>&,
                             const vector<int>& word_scores) const {
  int score = 0;
  for (size_t i = 0; i < word_scores.size(); i++) {
    score += word_scores[i];
  }
  if (placedTiles.size() == (size_t)game_.handSize()) {
    score += 50;
  }

  return score;
}
