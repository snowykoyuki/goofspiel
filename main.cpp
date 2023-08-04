#include <iostream>
#include <fstream>
#include "game.h"

#define RUN_GAME 0
#define END_GAME 1

#define MAIN_MENU 0
#define PLAY_MENU 1
#define DIFF_MENU 2
#define SETT_MENU 4
#define RULE_MENU 5

//function def
int menu(int mode);
void startgame(int gamemode, int rule);
void howtoplay();
void about();
void cls();
void playmenu();
void altrules();
void settings();
void debugmenu();

int altrule = 0;
int debugmode = 0;

//main
int main(){
  int in = 0;
  int flag = RUN_GAME;
  cls();
  
  while (!flag){
    std::cout << "Goofspiel" << std::endl;
    
    in = menu(MAIN_MENU);
    switch (in){
      case 1:
        cls();
        if (debugmode ==0)
          playmenu();
        else
          startgame(debugmode, altrule);
        break;
      case 2:
        cls();
        howtoplay();
        break;
      case 3:
        cls();
        about();
        break;
      case 4:
        cls();
        settings();
        break;
      case 5:
        //end game
        flag = END_GAME;
        break;
      default:
        cls();
        std::cout << "Invalid Input"<< std::endl;
        break;
    }
  }
}

//handle main menu, play menu
int menu(int mode){
  std::string in;
  int out;
  
  //menu contents
  switch (mode){
    case MAIN_MENU:
      switch (debugmode){
        case 0:
          std::cout << "1) Play" << std::endl;
          break;
        case -1:
          std::cout << "1) Hybrid vs Random" << std::endl;
          break;
        case -2:
          std::cout << "1) Hybrid vs Deterministic" << std::endl;
          break;
      }
      std::cout << "2) How to play" << std::endl;
      std::cout << "3) About Goofspiel" << std::endl;
      std::cout << "4) Settings" << std::endl;
      std::cout << "5) Quit" << std::endl;
      std::cout << "> ";
      break;
    case PLAY_MENU:
      std::cout << "1) Singleplayer" << std::endl;
      std::cout << "2) Multiplayer" << std::endl;
      std::cout << "3) Return to Main Menu" << std::endl;
      std::cout << "> ";
      break;
    case SETT_MENU:
      std::cout << "1) Toggle Alternate Rules" << std::endl;
      std::cout << "2) Debug Mode Options" << std::endl;
      std::cout << "3) Return to Main Menu" << std::endl;
      std::cout << "> ";
      break;
    case RULE_MENU:
      std::cout << "1) Enable Alternate Rules" << std::endl;
      std::cout << "2) Disable Alternate Rules" << std::endl;
      std::cout << "3) Return to Main Menu" << std::endl;
      std::cout << "> ";
      break;
    case DIFF_MENU:
      std::cout << "1) Random" << std::endl;
      std::cout << "2) Deterministic" << std::endl;
      std::cout << "3) Disable Debug Mode" << std::endl;
      std::cout << "4) Return" << std::endl;
      std::cout << "> ";
      break; 
  }
  //get userinput
  std::getline(std::cin, in);
  
  try {
    //try convert to int
    out = std::stoi(in);
  } catch(std::exception &err) {
    return -1;
  }
  return out;
}

void cls(){
  std::cout << std::string(55, '\n');
}

void startgame(int gamemode, int rule){
  Game game(gamemode, rule);
  game.initgame();
}

void howtoplay(){
    std::ifstream f("howtoplay.txt");
  if (f.is_open()){
    std::cout << f.rdbuf() << std::endl << std::endl;
    std::cout << "Press Enter to Continue...";
    std::cin.ignore();
    cls();
  }else {
    cls();
    std::cout << "Failed to read howtoplay.txt." << std::endl;
  }
}

void about(){
  std::ifstream f("about.txt");
  if (f.is_open()){
    std::cout << f.rdbuf() << std::endl << std::endl;
    std::cout << "Press Enter to Continue...";
    std::cin.ignore();
    cls();
  }else {
    cls();
    std::cout << "Failed to read about.txt." << std::endl;
  }
}

void playmenu(){
  int in=0;
  while (in!=3){
    std::cout << std::endl;
    std::cout << "Select gamemode" << std::endl;
    in=menu(PLAY_MENU);

    switch (in){
      case 1:
        startgame(SINGLEPLAYER, altrule);
        in = 3;
        break;
      case 2:
        startgame(MULTIPLAYER, altrule);
        in = 3;
        break;
      case 3:
        cls();
        return;
      default:
        cls();
        std::cout << "Invalid input" << std::endl;
    }
  }
  cls();
}

void settings(){
  int in = 0;
  bool flag = 0;
  do{
    std::cout << "SETTINGS" << std::endl << std::endl;
    in = menu(SETT_MENU);
    switch(in){
      case 1:
        cls();
        altrules();
        break;
      case 2:
        cls();
        debugmenu();
        break;
      case 3:
        break;
      default:
        cls();
        std::cout << "Input invalid" << std::endl;
    }
  }while(in!=3);
  cls();
}

void altrules(){
  bool contloop = 0;
  int ruleset = 0;
  do{
    std::cout << "An alternative gamemode is offered in this game" << std::endl;
    std::cout << "Enabled: " << "When tied, prize will move to next round and nobody will get points." << std::endl;
    std::cout << "Disabled: " << "When tied, prize will be split between the two players." << std::endl << std::endl;

    if (altrule){
      std::cout << "Current Setting: Enabled" << std::endl << std::endl;
    } else {
      std::cout << "Current Setting: Disabled" << std::endl << std::endl;
    }
    ruleset = menu(RULE_MENU);
    
    switch (ruleset){
      case 1:
        contloop = 0;
        cls();
        altrule = 1;
        std::cout << "Alternate rules enabled! Do not mark coursework with this enabled!" << std::endl;
        std::cout << "Press Enter to Continue...";
        std::cin.ignore();
        cls();
        break;
      case 2:
        contloop = 0;
        cls();
        altrule = 0;
        std::cout << "Alternate rules disabled!" << std::endl;
        std::cout << "Press Enter to Continue...";
        std::cin.ignore();
        cls();
        break;
      case 3:
        cls();
        contloop = 0;
        break;
      default:
        cls();
        std::cout << "Input invalid!" << std::endl << std::endl;
        contloop = 1;
        break;
    }
  }while(contloop);
}

void debugmenu(){
  bool contloop = 0;
  int debugset = 0;
  do{
    std::cout << "DEBUG MODE" << std::endl;
    std::cout << "" << std::endl;
    switch (debugmode){
      case 0:
        std::cout << "Debug mode is disabled." << std::endl;
        break;
      case DEBUGRNG:
        std::cout << "Debug mode is enabled." << std::endl << "Bot will play against random algorithm." << std::endl;
        break;
      case DEBUGDET:
        std::cout << "Debug mode is enabled." << std::endl << "Bot will play against deterministic algorithm." << std::endl;
        break;
    }

    debugset = menu(DIFF_MENU);
    
    switch (debugset){
      case 1:
        contloop = 0;
        cls();
        debugmode = DEBUGRNG;
        std::cout << "Debug mode enabled! (Random)" << std::endl;
        std::cout << "Press Enter to Continue...";
        std::cin.ignore();
        cls();
        break;
      case 2:
        contloop = 0;
        cls();
        debugmode = DEBUGDET;
        std::cout << "Debug mode enabled! (Deterministic)" << std::endl;
        std::cout << "Press Enter to Continue...";
        std::cin.ignore();
        cls();
        break;
      case 3:
        contloop = 0;
        cls();
        debugmode = 0;
        std::cout << "Debug mode disabled!" << std::endl;
        std::cout << "Press Enter to Continue...";
        std::cin.ignore();
        cls();
        break;
      case 4:
        cls();
        contloop = 0;
        break;
      default:
        cls();
        std::cout << "Input invalid!" << std::endl << std::endl;
        contloop = 1;
        break;
    }
  }while(contloop);
}