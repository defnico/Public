#ifndef GAME_H_
#define GAME_H_

#include <fstream>
#include <iostream>
#include <vector>

#include "Bag.h"
#include "Board.h"
#include "Dictionary.h"
#include "Player.h"

// Struct to store on which square a tile is placed on the board.
struct PlacedTile {
  PlacedTile(Tile* t, int r, int c) : tile(t), row(r), col(c) {}

  Tile* tile;

  // The row, col of the square where the tile is placed.
  int row;
  int col;
};

class Game {
public:
  Game();

  bool LoadConfigFile(std::string config_file_name, int bag_random_seed);

  void SetPlayers(const std::vector<std::string>& names);

  Board& board() { return board_; }
  Dictionary& dictionary() { return dictionary_; }
  int numPlayers() const { return numPlayers_; }
  Player& getPlayer(int i); // Get the ith player where 0 <= i < num_players.
  Bag& bag() { return bag_; }
  bool initFileSpecified() const { return initFileSpecified_; }

  size_t handSize() const { return handSize_; }

  // Construct words from the given tiles places on squares.
  // If successful outputs a  vector of constructed words and their scores.
  // Returns an empty string if successful and otherwise an error message.
  std::string ConstructWords(const std::vector<PlacedTile>& tiles,
                             std::vector<std::string>& words,
                             std::vector<int>& scores);

  // Exchange the input tiles and return the new tiles.
  std::set<Tile*> ExchangeTiles(int player, std::set<Tile*> tiles);

  // Return the names of all the winners with the max_score.
  std::vector<std::string> GetWinners(int& max_score);

  // Get the word using the tile at row, col in the given direction.
  // Give bonus points only if it is a new tile placed (in placedTiles).
  std::set<Tile*> GetWordAtSquare(int sr, int sc, int direction,
                                  const std::vector<PlacedTile>& placedTiles,
                                  std::string& word, int& score);

  void RemoveTilesFromBoard(const std::vector<PlacedTile>& squareTiles);
  bool BoardIsEmpty() const;

private:
  int numPlayers_;
  Dictionary dictionary_;
  Board board_;
  Bag bag_;
  std::vector<Player> players_; // Of size num_players_.
  size_t handSize_;
  bool initFileSpecified_;
};

#endif // GAME_H_
