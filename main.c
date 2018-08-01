#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include "Defines.h"

#define WIN32_LEAN_AND_MEAN

struct KeyChecker{
  int key = 0;
  short state = 0;
  bool check = false;
  bool get(){
    if(state & 0x0001){
      if(!check){
        check = true;
        return 1;
      }
    }

    if(state & 0x8000){
    }else{
      check = false;
    }
    return 0;
  }
  std::string getChar(){
    return keyCodeToReadableString(key);
  }
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
  time_t now;
  struct KeyChecker KeyCheckers[sizeof(Keys) / sizeof(int)];

  for(int i = 0; i < sizeof(Keys) / sizeof(int); i++){
    KeyCheckers[i].key = Keys[i];
    KeyCheckers[i].state = GetAsyncKeyState(KeyCheckers[i].key);
    KeyCheckers[i].get();
  }

  while(true){
    for(int i = 0; i < sizeof(Keys) / sizeof(int); i++){
      KeyCheckers[i].state = GetAsyncKeyState(KeyCheckers[i].key);
    }

    for(int i = 0; i < sizeof(Keys) / sizeof(int); i++){
      if(KeyCheckers[i].get()){
        now = time(NULL);
        std::string fromJson = getCharFromJson("keyLayouts.json", std::to_string(KeyCheckers[i].key));

        if(fromJson.empty()){
          std::cout << now << " " << KeyCheckers[i].getChar().c_str() << " native" << std::endl;
        }else{
          std::cout << now << " " << fromJson << " json" << std::endl;
        }
      }
    }
  }
  return 0;
}
