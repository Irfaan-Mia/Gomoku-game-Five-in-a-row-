#ifndef display_h
#define display_h

#include <iostream> 
using namespace std;

class Display {        
  public:         
    //Constructor used to set private variables
    Display(int x, int y, char z); 
    //Required to format string in requested manner
    string getcomplete();

    //Variable that is only accesibly by the class
    private:     
    string complete;
};

#endif
