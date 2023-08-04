#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "player.h"
#include "bot.h"

#include <ctime>
#include <cstdlib>  
#include <random>
#include <iostream>
#include <algorithm>
#include <string>

#define NUMBER_OF_PLAYERS 2
#define SINGLEPLAYER 0
#define MULTIPLAYER 1
#define DEBUGRNG -1
#define DEBUGDET -2

class Game{
private:
  int gamemode;
  int rule;
  Deck generatecards();
  Deck shufflecards(Deck deck);
  void distributecards(Player& dealer, Player& player1, Player& player2, Player& prize);
  void singleplayer(Player player, Bot cpu, Player prize);
  void multiplayer(Player player1, Player player2, Player prize);
  void debug(Bot cpu1, Bot cpu2, Player prize);
  Card getbid(Player player, Player contested);
  bool verifybid(int in, Player player);
  bool confirmbid(int in, Player player, Player contested);
  void cls();
public:
  Game(int gamemode, int rule);
  void waitturn(Player next);
  void initgame();
};
#endif