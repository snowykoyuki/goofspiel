#ifndef CARD_H
#define CARD_H

#include <vector>
#include <iostream>

#define NUMBER_OF_SUITS 4
#define SPADES 0
#define PIKES 0
#define HEARTS 1
#define CLUBS 2
#define CLOVER 2
#define TILES 3
#define DIAMOND 3

#define NUMBER_OF_RANKS 13
#define A 1
#define J 11
#define Q 12
#define K 13

#define PLAYER_DECK 13
#define NUMBER_OF_CARDS 52

class Card {
private:
  int suit;
  int rank;

public:
  Card(int suit, int rank);
  Card();
  int getowner();
  int getsuit();
  int getrank();
  void setsuit(int suit);
  void printcard();
  bool isequal(Card card);
  bool operator==(const Card &card);
  int cmpcard(Card card);
  //std::ostream& operator<<(std::ostream& os, const Card& card);
};

typedef std::vector<Card> Deck;
#endif