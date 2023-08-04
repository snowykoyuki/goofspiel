#include "game.h"

Game::Game(int gamemode, int rule){
  this->gamemode = gamemode;
  this->rule = rule;
}

Deck Game::generatecards(){
  Deck out;
  for (int i=0; i<NUMBER_OF_SUITS; i++){
    for (int j=1; j<=NUMBER_OF_RANKS; j++){
      Card card(i, j);
      out.push_back(card);
    }
  }
  return out;
}

Deck Game::shufflecards(Deck deck){
  std::srand ( unsigned ( std::time(0) ) );
  std::random_shuffle(deck.begin(), deck.end());
  return deck;
}

void Game::distributecards(Player& dealer, Player& player1, Player& player2, Player& prize){
  for (int i=0; i<PLAYER_DECK; i++){
    dealer.transferfirst(player1);
  }
  for (int i=0; i<PLAYER_DECK; i++){
    dealer.transferfirst(player2);
  }
  for (int i=0; i<PLAYER_DECK; i++){
    dealer.transferfirst(prize);
  }
}

void Game::initgame(){
  Deck publicdeck = generatecards();
  //publicdeck = shufflecards(publicdeck);
  Player dealer(DEALER, publicdeck);
  Deck emptydeck;
  Player prize(PRIZE, emptydeck);
  Player contested(CONTESTED, emptydeck);
  Player player1(PLAYER_1, emptydeck);
  Player player2(PLAYER_2, emptydeck);
  Bot cpu(CPU, emptydeck);
  Bot cpu2(CPU, emptydeck);
  cls();
  
  switch (this->gamemode){
    case DEBUGRNG:
    case DEBUGDET:
      distributecards(dealer, cpu, cpu2, prize);
      prize.setdeck(shufflecards(prize.getdeck()));
      debug(cpu, cpu2, prize);
      break;
    case SINGLEPLAYER:
      distributecards(dealer, player1, cpu, prize);
      prize.setdeck(shufflecards(prize.getdeck()));
      singleplayer(player1, cpu, prize);
      break;
    case MULTIPLAYER:
      distributecards(dealer, player1, player2, prize);
      prize.setdeck(shufflecards(prize.getdeck()));
      multiplayer(player1, player2, prize);
      break;
  }
}

void Game::singleplayer(Player player, Bot cpu, Player prize){
  Deck emptydeck;
  Player contested(CONTESTED, emptydeck);
  Card playerbid;
  Card cpubid;
  int win = 0;
  int finished = 0;
  bool dec = 0;
  
  do{
    prize.transferfirst(contested);
    playerbid = getbid(player, contested);
    player.removecard(playerbid);
    cpubid = cpu.semirandom(contested.getdeck().back());
    cpu.removecard(cpubid);
    win = playerbid.cmpcard(cpubid);

    std::cout << "Prize: ";
    contested.printdeck();
    std::cout << "Your bid: ";
    playerbid.printcard();
    std::cout << std::endl;
    std::cout << "Opponent's bid: ";
    cpubid.printcard();
    std::cout << std::endl << std::endl;
    
    switch (win){
      case 1:
        std::cout << "You earn " << contested.sumdeck() << " points!" <<std::endl;
        player.addpoints(contested.sumdeck());
        contested.emptydeck();
      break;
      case -1:
        std::cout << "Your opponent earns " << contested.sumdeck() << " points!" <<std::endl;
        cpu.addpoints(contested.sumdeck());
        contested.emptydeck();
      break;
      case 0:
        if (this->rule == 0){
        std::cout << "Tie! Score is split between the two players." << std::endl;
        std::cout << "Both players get " << contested.sumdeck()/2;
        
        if (contested.sumdeck()%2){
          std::cout << ".5";
          dec = 1;
        } else{
          dec = 0;
        }
        
        std::cout << " points! " << std::endl;
        if (dec && player.hashalfpoint()){
          player.addpoints(contested.sumdeck()/2+1);
          cpu.addpoints(contested.sumdeck()/2+1);
          player.sethalfpoint(0);
          cpu.sethalfpoint(0);
        } else {
          player.addpoints(contested.sumdeck()/2);
          player.sethalfpoint(dec);
          cpu.addpoints(contested.sumdeck()/2);
          cpu.sethalfpoint(dec);
        }
        contested.emptydeck();
      } else {
        std::cout << "Tie! Prize will move to next round." << std::endl;
      }
      break;
    }
    std::cout << std :: endl;
    //print player1 points
    std::cout << "Your points: " << player.getpoints();
    if (player.hashalfpoint()){
      std::cout << ".5";
    }
    std::cout << std::endl;
    
    //print player2 points
    std::cout << "Your opponent's points: " << cpu.getpoints();
    if (cpu.hashalfpoint()){
      std::cout << ".5";
    }
    std::cout << std::endl;
    std::cout << "Press Enter to continue";
    std::cin.ignore();
    cls();
    if (prize.getdeck().empty()){
      finished = 1;
    }
    
  }while(!finished);
  
  std::cout << "Your points: " << player.getpoints();
  if (player.hashalfpoint()){
    std::cout << ".5";
  }
  std::cout << std::endl;
  
  std::cout << "Your opponent's points: " << cpu.getpoints();
  if (cpu.hashalfpoint()){
    std::cout << ".5";
  }
  std::cout << std::endl;
  
  if (player.getpoints() > cpu.getpoints()){
    //player 1 win
    std::cout << "You won with " << player.getpoints();
    if (player.hashalfpoint())
      std::cout << ".5";
    std::cout << " points!" << std::endl;
  } else if (cpu.getpoints() > player.getpoints()) {
    //player 2 win
    std::cout << "Your opponent wins with " << cpu.getpoints();
    if (cpu.hashalfpoint())
      std::cout << ".5";
    std::cout << " points!" << std::endl;
  } else {
    std::cout << "It is a tie! Nobody won and both players have " << player.getpoints();
    if (player.hashalfpoint())
      std::cout << ".5";
    std::cout  << " points." << std::endl;
  }
  
  std::cout << "Press Enter to continue";
  std::cin.ignore();
  cls();
}

void Game::multiplayer(Player player1, Player player2, Player prize){
  Deck emptydeck;
  Player contested(CONTESTED, emptydeck);
  Card player1bid;
  Card player2bid;
  int win = 0;
  int finished = 0;
  bool dec = 0;
  
  do{
    prize.transferfirst(contested);
    player1bid = getbid(player1, contested);
    player1.removecard(player1bid);
    waitturn(player2);
    player2bid = getbid(player2, contested);
    player2.removecard(player2bid);
    win = player1bid.cmpcard(player2bid);

    std::cout << "Prize: ";
    contested.printdeck();
    std::cout << "Player " << player1.getID() << "'s bid: ";
    player1bid.printcard();
    std::cout << std::endl;
    std::cout << "Player " << player2.getID() << "'s bid: ";
    player2bid.printcard();
    std::cout << std::endl << std::endl;

    switch (win){
      case 1:
        std::cout << "Player " << player1.getID() << " earns " << contested.sumdeck() << " points!" <<std::endl;
        player1.addpoints(contested.sumdeck());
        contested.emptydeck();
      break;
      case -1:
        std::cout << "Player " << player2.getID() << " earns " << contested.sumdeck() << " points!" <<std::endl;
        player2.addpoints(contested.sumdeck());
        contested.emptydeck();
      break;
      case 0:
        if (this->rule == 0){
        std::cout << "Tie! Score is split between the two players." << std::endl;
        std::cout << "Both players get " << contested.sumdeck()/2;
        
        if (contested.sumdeck()%2){
          std::cout << ".5";
          dec = 1;
        } else{
          dec = 0;
        }
        
        std::cout << " points! " << std::endl;
        if (dec && player1.hashalfpoint()){
          player1.addpoints(contested.sumdeck()/2+1);
          player2.addpoints(contested.sumdeck()/2+1);
          player1.sethalfpoint(0);
          player2.sethalfpoint(0);
        } else {
          player1.addpoints(contested.sumdeck()/2);
          player1.sethalfpoint(dec);
          player2.addpoints(contested.sumdeck()/2);
          player2.sethalfpoint(dec);
        }
        contested.emptydeck();
      } else {
        std::cout << "Tie! Prize will move to next round." << std::endl;
      }
      break;
    }
    std::cout << std :: endl;
    //print player1 points
    std::cout << "Player " << player1.getID() << " points: " << player1.getpoints();
    if (player1.hashalfpoint()){
      std::cout << ".5";
    }
    std::cout << std::endl;
    
    //print player2 points
    std::cout << "Player " << player2.getID() << " points: " << player2.getpoints();
    if (player2.hashalfpoint()){
      std::cout << ".5";
    }
    std::cout << std::endl;
    std::cout << "Press Enter to continue";
    std::cin.ignore();
    cls();
    if (!prize.getdeck().empty()){
      waitturn(player1);
    } else {
      finished = 1;
    }
    
  }while(!finished);
  
  std::cout << "Player " << player1.getID() << " points: " << player1.getpoints() << std::endl;
  std::cout << "Player " << player2.getID() << " points: " << player2.getpoints() << std::endl;
  std::cout << std::endl;
  
  if (player1.getpoints() > player2.getpoints()){
    //player 1 win
    std::cout << "Player " << player1.getID() << " wins with " << player1.getpoints();
    if (player1.hashalfpoint())
      std::cout << ".5";
    std::cout << " points!" << std::endl;
  } else if (player2.getpoints() > player1.getpoints()) {
    //player 2 win
    std::cout << "Player " << player2.getID() << " wins with " << player2.getpoints();
    if (player2.hashalfpoint())
      std::cout << ".5";
    std::cout << " points!" << std::endl;
  } else {
    std::cout << "It is a tie! Nobody won and both players have " << player1.getpoints();
    if (player1.hashalfpoint())
      std::cout << ".5";
    std::cout  << " points." << std::endl;
  }
  
  std::cout << "Press Enter to continue";
  std::cin.ignore();
  cls();
}

Card Game::getbid(Player player, Player contested){
  std::string in;
  int out;
  int flag = 0;
  Card bid;
  do{
    //menu contents
    std::cout << "Prize: ";
    contested.printdeck();
    player.listdeck();
    switch (this->gamemode){
      case 0:
        std::cout << "Your bid: " << std::endl;
        break;
      case 1:
        std::cout << "Player " << player.getID() << " bid: " << std::endl;
        break;
    }
    std::cout << "> ";
    //get userinput
    std::getline(std::cin, in);
    int bidvalid = 0;
    cls();
    try {
      //try convert to int
      out = std::stoi(in) - 1; //-1 because index starts at 0
    } catch(std::exception &err) {
      out = -1;
    }
    
    //verify input
    bidvalid = verifybid(out, player);
    if (bidvalid){
      bidvalid = confirmbid(out, player, contested);
      if (bidvalid){
        flag = 0;
        bid = player.getdeck().at(out);
        std::cout << "You bidded ";
        bid.printcard();
        std::cout << ". Press Enter to end your turn.";
        std::cin.ignore();
        cls();
      } else {
        flag = 1;
        std::cout << "Bid cancelled " << std::endl << std::endl;
      }
    } else {
      flag = 1;
    }
  }while(flag);
  return bid;
}

bool Game::verifybid(int in, Player player){
  if (in < 0){
    std::cout << "Invalid number" <<std::endl;
    return 0;
  }
  if (in >= player.getdeck().size()){
    std::cout << "Invalid number" <<std::endl;
    return 0;
  }
  return 1;
}

void Game::debug(Bot cpu1, Bot cpu2, Player prize){
  Deck emptydeck;
  Player contested(CONTESTED, emptydeck);
  
  Card cpu1bid;
  Card cpu2bid;
  int win = 0;
  int finished = 0;
  bool dec = 0;
  
  do{
    prize.transferfirst(contested);
    cpu1bid = cpu1.semirandom(contested.getdeck().back());
    cpu1.removecard(cpu1bid);
    if (this->gamemode == DEBUGRNG)
      cpu2bid = cpu2.random();
    else if (this->gamemode == DEBUGDET)
      cpu2bid = cpu2.deteministic0(contested.getdeck().back());
    cpu2.removecard(cpu2bid);
    win = cpu1bid.cmpcard(cpu2bid);
    
    std::cout << "Prize: ";
    contested.printdeck();
    std::cout << "Hybrid bid: ";
    cpu1bid.printcard();
    std::cout << std::endl;
    if (this->gamemode == DEBUGRNG)
      std::cout << "Random bid: ";
    else if (this->gamemode == DEBUGDET)
      std::cout << "Deterministic bid: ";
    cpu2bid.printcard();
    std::cout << std::endl << std::endl;
    
    switch (win){
      case 1:
        std::cout << "Hybrid earns " << contested.sumdeck() << " points" <<std::endl;
        cpu1.addpoints(contested.sumdeck());
        contested.emptydeck();
      break;
      case -1:
        std::cout << "Other algorithm earns " << contested.sumdeck() << " points" <<std::endl;
        cpu2.addpoints(contested.sumdeck());
        contested.emptydeck();
      break;
      case 0:
        if (this->rule == 0){
        std::cout << "Tie! Score is split between the two players." << std::endl;
        std::cout << "Both players get " << contested.sumdeck()/2;
        
        if (contested.sumdeck()%2){
          std::cout << ".5";
          dec = 1;
        } else{
          dec = 0;
        }
        
        std::cout << " points! " << std::endl;
        if (dec && cpu1.hashalfpoint()){
          cpu1.addpoints(contested.sumdeck()/2+1);
          cpu2.addpoints(contested.sumdeck()/2+1);
          cpu1.sethalfpoint(0);
          cpu2.sethalfpoint(0);
        } else {
          cpu1.addpoints(contested.sumdeck()/2);
          cpu1.sethalfpoint(dec);
          cpu2.addpoints(contested.sumdeck()/2);
          cpu2.sethalfpoint(dec);
        }
        contested.emptydeck();
      } else {
        std::cout << "Tie! Prize will move to next round." << std::endl;
      }
      break;
    }
    std::cout << std :: endl;
    //print player1 points
    std::cout << "Hybrid points: " << cpu1.getpoints();
    if (cpu1.hashalfpoint()){
      std::cout << ".5";
    }
    std::cout << std::endl;
    //print player2 points
    std::cout << "Other algorithm points: " << cpu2.getpoints();
    if (cpu2.hashalfpoint()){
      std::cout << ".5";
    }
    std::cout << std::endl;
    std::cout << std::endl << std::endl << std::endl;
    if (prize.getdeck().empty()){
      finished = 1;
    }
  }while(!finished);
  
  std::cout << "Hybrid points: " << cpu1.getpoints();
  if (cpu1.hashalfpoint()){
    std::cout << ".5";
  }
  std::cout << std::endl;
  if (this->gamemode == DEBUGRNG){
    std::cout << "Random points: " << cpu2.getpoints();
  } else if (this->gamemode == DEBUGDET){
    std::cout << "Deterministic points: " << cpu2.getpoints();
  }
  if (cpu2.hashalfpoint()){
    std::cout << ".5";
  }
  std::cout << std::endl;
      
if (cpu1.getpoints() > cpu2.getpoints()){
    //player 1 win
    std::cout << "Hybrid algorithm wins with " << cpu1.getpoints();
    if (cpu1.hashalfpoint())
      std::cout << ".5";
    std::cout << " points!" << std::endl;
  } else if (cpu2.getpoints() > cpu1.getpoints()) {
    //player 2 win
    if (this->gamemode == DEBUGDET){
      std::cout << "Deterministic algorithm wins with " << cpu2.getpoints();
    } else if (this->gamemode == DEBUGRNG) {
      std::cout << "Random algorithm wins with " << cpu2.getpoints();
    }
    if (cpu2.hashalfpoint())
      std::cout << ".5";
    std::cout << " points!" << std::endl;
  } else {
    std::cout << "It is a tie! Nobody won and both players have " << cpu1.getpoints();
    if (cpu1.hashalfpoint())
      std::cout << ".5";
    std::cout  << " points." << std::endl;
  }
  
  std::cout << "Press Enter to continue";
  std::cin.ignore();
  cls();
}

    
bool Game::confirmbid(int cardindex, Player player, Player contested){
  bool flag = 0;
  do{
    std::cout << "Prize: ";
    contested.printdeck();
    std::cout << std::endl;
    switch (this->gamemode){
      case SINGLEPLAYER:
        std::cout << "Do ";
        break;
      case MULTIPLAYER:
        std::cout << "Player " << player.getID() << ", do ";
    }
    std::cout << "you confirm biddling ";
    player.getdeck().at(cardindex).printcard();
    std::cout << "? (Y/N)" << std::endl;
    std::cout << "> ";
    
    std::string in;
    std::getline(std::cin, in);
    std::transform(in.begin(), in.end(), in.begin(),
      [](unsigned char c){ return std::tolower(c); });
    cls();
    
    if (!in.compare("y")){
      flag = 0;
      return 1;
    } else if (!in.compare("n")){
      flag = 0;
      return 0;
    } else {
      std::cout << "Invalid Input" << std::endl;
      flag = 1;
    }
  }while(flag);
  return 0;
}

//function to clear screen
void Game::cls(){
  //print \n 55 times
  std::cout << std::string(55, '\n');
}

//screen for player transision for multiplayer games
void Game::waitturn(Player next){
  std::cout << "PLAYER " << next.getID() << "'S TURN" << std::endl;
  std::cout << "Press Enter to continue";
  std::cin.ignore();
  cls();
}