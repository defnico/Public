#ifndef GET_PLAYERS_DIALOG_H
#define GET_PLAYERS_DIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QWidget>

#include "Game.h"

class GetPlayersDialog : public QDialog {
  Q_OBJECT
public:
  GetPlayersDialog(Game& game);

private slots:
  void SetNumPlayers(int);
  void Okay();

private:
  void CreateLayout();

  // Keep a reference to the game constructed in the main.
  Game& game_;
  QSpinBox* numPlayersSpinBox_;
  QLineEdit* playerNames_[8];
};

#endif // GET_PLAYERS_DIALOG_H
