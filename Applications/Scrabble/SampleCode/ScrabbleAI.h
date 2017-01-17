#ifndef SCRABBLE_AI_H_
#define SCRABBLE_AI_H_

#include "Game.h"
#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

struct RowCol {
  RowCol(int r, int c) : row(r), col(c) {}
  int row;
  int col;
};

class ScrabbleAI {
public:
  ScrabbleAI(Game& game);
  virtual ~ScrabbleAI() {}

  // Search for  the best placement of a player's tiles.
  // Returns an empty vector if there is no valid placement.
  std::vector<PlacedTile>
  BestPlacementSearch(const std::set<Tile*>& player_tiles);

protected:
  // Get the score for given placement from the derived AI classes.
  virtual int GetAIScore(const std::vector<PlacedTile>& placedTiles,
                         const std::vector<std::string>& words,
                         const std::vector<int>& word_scores) const = 0;

  // Place a permutation of tiles on the board starting at (r,c). If successful
  // return what squares the letters were placed and the word made.
  std::vector<RowCol> PlacePermutation(const std::string& perm, int row,
                                       int col, int dir, std::string& word);

  // See if the permutation is the best so far.
  bool TryPermutation(const std::string& perm, const std::string& permBlanks,
                      const std::set<Tile*>& tiles, int r, int c, int d,
                      std::unordered_set<std::string>& skipPrefixes,
                      std::vector<PlacedTile>& maxPlacedTiles, int& maxScore);

  // Get the vector of placed tiles from where the letters in the permutation
  // were placed.
  std::vector<PlacedTile> GetPermutationPlacedTiles(
      const std::string& perm, const std::string& permBlanks,
      const std::vector<RowCol>& squares, const std::set<Tile*>& tiles);

  Game& game_;
};

class ScrabbleCPUL : public ScrabbleAI {
public:
  ScrabbleCPUL(Game& game);
  int GetAIScore(const std::vector<PlacedTile>& placedTiles,
                 const std::vector<std::string>& words,
                 const std::vector<int>& word_scores) const;
};

class ScrabbleCPUS : public ScrabbleAI {
public:
  ScrabbleCPUS(Game& game);
  int GetAIScore(const std::vector<PlacedTile>& placedTiles,
                 const std::vector<std::string>& words,
                 const std::vector<int>& word_scores) const;
};

#endif // SCRABBLE_AI_H_
