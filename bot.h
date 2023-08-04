#ifndef BOT_H
#define BOT_H
#include "player.h"
#include "card.h"

#include <ctime>
#include <cstdlib>  
#include <random>

class Bot: public Player {
public:
  Bot(int ID, Deck deck);
  Card random();
  Card random(Deck deck);
  Deck getnearby(Card in);
  Card semirandom(Card in);
  Card deteministic0(Card in);
  Card deterministic1(Card in);
};

#endif