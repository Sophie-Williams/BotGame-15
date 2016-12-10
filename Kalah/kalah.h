//////////////////////////////////////////////////////////////////////////
// Header for the Kalah.cpp code                                                                     
//
// mi.mesquita.medeiros@fnal.gov - Michelle Mesquita de Medeiros - Feb. 27, 2014.                           
////////////////////////////////////////////////////////////////////////

#ifndef KALAH_H
#define KALAH_H

#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 

using namespace std;

class Kalah {

   public:
     Kalah(string name);
     ~Kalah();

   public:

     // Variables needed for the functions above
     int house[7];
     string playerName;

     // Handle game moves
     void InitGame();
     void AddSeeds(int houseNum, int lasthouse);
     void RemoveSeeds(int houseNum);
     void MoveSeeds(int houseNum, Kalah &player, Kalah &oponent);
     void SetSeeds(int numSeeds, int houseNum);
     int NumSeeds(int houseNum);
     string Name(string name);
     bool StillPlaying(int houseNum);
     bool Empty(int houseNum);
     bool Finished();

//   private:
     // Variables needed for the functions above
//     int house[7]; // One for each player. Can access by calling Kalah class
//     string playerName;

};

#endif // KALAH_H
////////////////////////////////////////////////////////////////////////
