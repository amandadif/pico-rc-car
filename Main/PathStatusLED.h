#include <Arduino.h>
#ifndef PATHSTATUSLED_H
#define PATHSTATUSLED_H


class PathStatusLED {

  public:
    PathStatusLED();      // Constructor
    void activateStatusLED(bool pathClearStatus) ;
};

#endif