#include "Display.h"

//Format the output with respect to report specifications 
Display::Display(int x, int y, char z) {
  string a = "r" + to_string(x) + "c" + to_string(y) + " " + "alg" + z;
  Display::complete = a;
}

//will return the private variable complete to output file
string Display::getcomplete() 
{
    return Display::complete;
}