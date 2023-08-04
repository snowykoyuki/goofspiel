#include "card.h"

Card::Card(int suit, int rank){
  this->suit = suit;
  this->rank = rank;
}

Card::Card(){

}

int Card::getsuit(){
  return this->suit;
}

int Card::getrank(){
  return this->rank;
}

void Card::printcard(){
  //print rank
  switch (this->rank){
    case 1:
      std::cout << "A";
      break;
    case 11:
      std::cout << "J";
      break;
    case 12:
      std::cout << "Q";
      break;
    case 13:
      std::cout << "K";
      break;
    default:
      std::cout << this->rank;
      break;
  }
  //print suit
  switch (this->suit){
    case SPADES:
      std::cout << "♠";
      break;
    case HEARTS:
      std::cout << "♥";
      break;
    case CLUBS:
      std::cout << "♣";
      break;
    case TILES:
      std::cout << "♦";
      break;
    default:
      std::cout << "?";
      break;
  }
}
bool Card::isequal(Card card){
  return (*this == card);
}

bool Card::operator==(const Card &card) {
  int out = 0;
  if (this->suit == card.suit)
    out++;
  if (this->rank == card.rank)
    out++;
  return (out==2);
}

int Card::cmpcard(Card card){
  if (this->rank > card.rank){
    return 1;
  }
  if (this->rank < card.rank){
    return -1;
  }
  return 0;
}

void Card::setsuit(int suit){
  this->suit = suit;
}

/*
std::ostream& Card::operator<<(std::ostream& os, const Card& card){
  switch (card.rank){
    case 1:
      os << "A";
      break;
    case 11:
      os << "J";
      break;
    case 12:
      os << "Q";
      break;
    case 13:
      os << "K";
      break;
    default:
      os << card.rank;
      break;
  }
  switch (card.suit){
    case SPADES:
      os << "♠";
      break;
    case HEARTS:
      os << "♥";
      break;
    case CLUBS:
      os << "♣";
      break;
    case TILES:
      os << "♦";
      break;
    default:
      os << "?";
      break;
  }
  return os;
}
*/