#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <map>
#include <vector>

#include "Game.h"
#include "SquareButton.h"
#include "TileButton.h"

// This is the main widget for the scrabble game which contains the widgets
// for the players, scores, board, and current player's tiles.
class Scrabble : public QWidget {
  Q_OBJECT
public:
  Scrabble(Game& game);

private slots:
  void Play();
  void Exchange();
  void Pass();

  void SelectTile(int);
  void SelectSquare(int, int);

private:
  // Methods to create the layout of the main window.
  void CreateMainLayout();
  void CreateLHSLayout();
  void CreateBoardLayout();

  // Method to go to the next player after a valid move.
  void GoToNextPlayer();

  // Update the display of the main window with the tiles of the player.
  void UpdateCurrentPlayer();

  // Display the winners at the end of the game.
  void ShowWinners(std::string message);

  // Get the icon for a letter.
  // Draw a border around the icon if the tile is selected.
  QIcon GetTileIcon(Tile* tile, bool selected);

  // Show a timed out message.
  void CreateTimeoutMessageBox();
  void ShowMessage(const std::string& message);

  // Keep a reference to the game constructed in the main.
  Game& game_;

  // The number of players in the game.
  int numPlayers_;

  // The number of tiles in each player's hand.
  // Can be less when there are no more tiles to draw from.
  size_t handSize_;

  // The current player in [0, num_players).
  int currentPlayer_;

  // The number of consecutive pass moves.
  int numPasses_;

  // Qt label for players' names.
  std::vector<QLabel*> nameLabels_;

  // Qt label for players' scores
  std::vector<QLabel*> scoreLabels_;

  // Qt buttons for each square on the board.
  std::vector<std::vector<SquareButton*>> boardButtons_;

  // Qt group box around current tiles to show the player's name.
  QGroupBox* tilesGroupBox_;

  // Buttons for handSize number of displayed tiles.
  // These get updated after every move.
  std::vector<TileButton*> tileButtons_;

  // The three move buttons.
  QPushButton* playButton_;
  QPushButton* passButton_;
  QPushButton* exchangeButton_;

  // The icons for every letter.
  std::map<char, QIcon*> letterIcons_;

  // The main layout which holds all the widgets.
  QHBoxLayout* mainLayout_;

  // MessageBox used to display all messages.
  QWidget* messageBox_;
  QTimer* messageBoxTimer_;
  QLabel* messageBoxLabel_;
};

#endif // SCRABBLE_H
