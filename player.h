#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "card.h"

#define DEALER 0
#define PLAYER_1 1
#define PLAYER_2 2
#define CPU 2
#define PRIZE 5
#define CONTESTED 6

class Player{
private:
  int ID;
  int points;
  bool halfpoint;
  int decksize;
  Deck deck;

public:
  Player(int ID, Deck deck);
  int getID();
  int getpoints();
  bool hashalfpoint();
  void sethalfpoint(bool in);
  void addpoints(int points);
  Deck getdeck();
  void setdeck(Deck deck);
  void listdeck();
  void printdeck();
  int sumdeck();
  void emptydeck();
  int findcard(Card card);
  void addcard(Card card);
  int removecard(Card card);
  void transferfirst(Player& player);
  void transfercard(Player& player, Card card);
};

#endif