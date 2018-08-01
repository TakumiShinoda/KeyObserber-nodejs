#include <stdio.h>
#include <time.h>
#include <ApplicationServices/ApplicationServices.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include "../picojson.h"
#include <string>

char* keyCodeToReadableString (CGKeyCode keyCode) {
  switch ((int) keyCode) {
    case   0: return "a";
    case   1: return "s";
    case   2: return "d";
    case   3: return "f";
    case   4: return "h";
    case   5: return "g";
    case   6: return "z";
    case   7: return "x";
    case   8: return "c";
    case   9: return "v";
    case  11: return "b";
    case  12: return "q";
    case  13: return "w";
    case  14: return "e";
    case  15: return "r";
    case  16: return "y";
    case  17: return "t";
    case  18: return "1";
    case  19: return "2";
    case  20: return "3";
    case  21: return "4";
    case  22: return "6";
    case  23: return "5";
    case  24: return "^";
    case  25: return "9";
    case  26: return "7";
    case  27: return "-";
    case  28: return "8";
    case  29: return "0";
    case  30: return "]";
    case  31: return "o";
    case  32: return "u";
    case  33: return "[";
    case  34: return "i";
    case  35: return "p";
    case  37: return "l";
    case  38: return "j";
    case  39: return "\"";
    case  40: return "k";
    case  41: return ";";
    case  42: return "\\";
    case  43: return ",";
    case  44: return "/";
    case  45: return "n";
    case  46: return "m";
    case  47: return ".";
    case  50: return "`";
    case  65: return "<keypad-decimal>";
    case  67: return "<keypad-multiply>";
    case  69: return "<keypad-plus>";
    case  71: return "<keypad-clear>";
    case  75: return "<keypad-divide>";
    case  76: return "<keypad-enter>";
    case  78: return "<keypad-minus>";
    case  81: return "<keypad-equals>";
    case  82: return "<keypad-0>";
    case  83: return "<keypad-1>";
    case  84: return "<keypad-2>";
    case  85: return "<keypad-3>";
    case  86: return "<keypad-4>";
    case  87: return "<keypad-5>";
    case  88: return "<keypad-6>";
    case  89: return "<keypad-7>";
    case  91: return "<keypad-8>";
    case  92: return "<keypad-9>";
    case  93: return "¥";
    case  94: return "_";
    case  36: return "<return>";
    case  48: return "<tab>";
    case  49: return "<space>";
    case  51: return "<delete>";
    case  53: return "<escape>";
    case  55: return "<command>";
    case  56: return "<shift>";
    case  57: return "<capslock>";
    case  58: return "<option>";
    case  59: return "<control>";
    case  60: return "<right-shift>";
    case  61: return "<right-option>";
    case  62: return "<right-control>";
    case  63: return "<function>";
    case  64: return "<f17>";
    case  72: return "<volume-up>";
    case  73: return "<volume-down>";
    case  74: return "<mute>";
    case  79: return "<f18>";
    case  80: return "<f19>";
    case  90: return "<f20>";
    case  96: return "<f5>";
    case  97: return "<f6>";
    case  98: return "<f7>";
    case  99: return "<f3>";
    case 100: return "<f8>";
    case 101: return "<f9>";
    case 102: return "<english>";
    case 103: return "<f11>";
    case 104: return "<japanese>";
    case 105: return "<f13>";
    case 106: return "<f16>";
    case 107: return "<f14>";
    case 109: return "<f10>";
    case 111: return "<f12>";
    case 113: return "<f15>";
    case 114: return "<help>";
    case 115: return "<home>";
    case 116: return "<pageup>";
    case 117: return "<forward-delete>";
    case 118: return "<f4>";
    case 119: return "<end>";
    case 120: return "<f2>";
    case 121: return "<page-down>";
    case 122: return "<f1>";
    case 123: return "<left>";
    case 124: return "<right>";
    case 125: return "<down>";
    case 126: return "<up>";
  }
  return "<unknown>";
}

CGEventRef on_tap(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon){
  CGKeyCode key = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
  time_t now;
  time(&now);

  std::cout << now << " " << keyCodeToReadableString(key) <<std::endl;
  fflush(stdout);
  return event;
}

int main(int argc, const char * argv[]) {
  CGEventFlags flags = CGEventSourceFlagsState(kCGEventSourceStateCombinedSessionState);
  CGEventMask mask = (CGEventMaskBit(kCGEventKeyUp) | CGEventMaskBit(kCGEventFlagsChanged));
  CFMachPortRef tap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, mask, on_tap, &flags);
  if (!tap) {
    fprintf(stderr, "This program requires sudo.");
    return -1;
  }
  CFRunLoopSourceRef runloop = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, tap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runloop, kCFRunLoopCommonModes);
  CGEventTapEnable(tap, true);
  CFRunLoopRun();
  return 0;
}
