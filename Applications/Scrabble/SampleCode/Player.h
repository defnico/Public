#ifndef PLAYER_H_
#define PLAYER_H_

#include <set>
#include <string>
#include <vector>

#include "Tile.h"

enum AIType {
  None,
  CPUL, // Computer player that places the word with max length.
  CPUS  // Computer player that places the word with max score.
};
class ScrabbleAI;

class Player {
public:
  Player() : score_(0), ai_(nullptr) {}
  ~Player();

  const std::set<Tile*>& tiles() const { return tiles_; }
  void addTiles(const std::set<Tile*>& tiles);
  void removeTiles(std::set<Tile*> tiles);

  void addPoints(int num_points) { score_ += num_points; }
  int score() const { return score_; }

  std::string name() const { return name_; }
  void setName(std::string name);

  AIType aiType() const { return aiType_; }
  ScrabbleAI* ai() { return ai_; }
  void setAI(class Game& game);

private:
  std::string name_;
  std::set<Tile*> tiles_;
  int score_;
  AIType aiType_;
  ScrabbleAI* ai_;
};

#endif // PLAYER_H_
