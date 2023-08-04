#include "bot.h"

Bot::Bot(int ID, Deck deck):Player(ID, deck){

}

Card Bot::random(){
  return random(this->getdeck());
}

Card Bot::random(Deck deck){
  if (deck.size()<2){
    return deck[0];
  }
  std::srand(unsigned(std::time(0)));
  std::random_shuffle(deck.begin(), deck.end());
  return deck[0];
}

Deck Bot::getnearby(Card in){
  Deck deck = this->getdeck();
  if(deck.size() <=5){
    return deck;
  }
  Player temp(-1, deck);
  
  for (auto & card: deck){
    if ((card.getrank()-2>in.getrank()) || (((card.getrank()+2)<in.getrank()) && in.getrank()<11)){
      temp.removecard(card);
    }
  }
  return temp.getdeck();
}

    
Card Bot::semirandom(Card in){
  //return lowest rank for low prizes
  if (in.getrank()==1 || in.getrank()==2){
    return this->getdeck().front();
  }
  
  
  //get a random value from nearby cards
  return random(getnearby(in));
}


Card Bot::deteministic0(Card in){
  return Card(this->getdeck().front().getsuit(), in.getrank());
}
    
Card Bot::deterministic1(Card in){
  if (in.getrank()==K){
    return Card(this->getdeck().front().getsuit(), 1);
  }
  return Card(this->getdeck().front().getsuit(), in.getrank()+1);
}