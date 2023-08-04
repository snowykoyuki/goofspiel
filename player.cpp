#include "player.h"

Player::Player(int ID, Deck deck){
  this->ID = ID;
  this->points = 0;
  this->halfpoint = 0;
  this->deck = deck;
}

int Player::getID(){
  return this->ID;
}

int Player::getpoints(){
  return this->points;
}

bool Player::hashalfpoint(){
  return this->halfpoint;
}

void Player::sethalfpoint(bool in){
  this->halfpoint = in;
}

void Player::addpoints(int points){
  this->points += points;
}

Deck Player::getdeck(){
  return this->deck;
}

void Player::setdeck(Deck deck){
  this->deck = deck;
}

void Player::listdeck(){
  Deck playerdeck = this->deck;
  std::cout << "Your deck:" <<std::endl;
  for (int i=0; i<playerdeck.size(); i++){
    std::cout << (i+1) << ") ";
    playerdeck[i].printcard();
    std::cout << std::endl;
  }
}

void Player::printdeck(){
  Deck playerdeck = this->deck;
  for (int i=0; i<playerdeck.size(); i++){
    playerdeck[i].printcard();
    std::cout << " ";
  }
  std::cout << std::endl;
}

int Player::sumdeck(){
  int out = 0;
  Deck playerdeck = this->deck;
  for (int i=0; i<playerdeck.size(); i++){
    out += playerdeck[i].getrank();
  }
  return out;
}

void Player::emptydeck(){
  Deck deck;
  this->setdeck(deck);
}

int Player::findcard(Card card){
  Deck playerdeck = this->deck;
  Deck::iterator it = std::find(playerdeck.begin(), playerdeck.end(), card);
 
  if (it != playerdeck.cend()) {
    return std::distance(playerdeck.begin(), it);
  } else {
    return -1;
  }
}

void Player::addcard(Card card){
  this->deck.push_back(card);
}

int Player::removecard(Card card){
  int index = this->findcard(card);
  if (index != -1){
    this->deck.erase(this->deck.begin() + index);
    return 0;
  } else {
    return 1;
  }
}

void Player::transferfirst(Player& player){
  this->transfercard(player, this->deck.front());
}

void Player::transfercard(Player& player, Card card){
  this->removecard(card);
  player.addcard(card);
}

/*
int Player::transfercard(Player& player, Card card){
  int a = this->removecard(card);
  if (a){
    return 1;
  } else {
    player.addcard(card);
  }
}
*/