/////////////////////////////////////////////////////////////////////////////////
// This code allows the user to play Kalah game against the computer           //
// Computer is actually pretty dummy...                                        //
//                                                                             //                             //
// For g++ compiler, should be compiled like this                              //  
//          g++ -LANG:std Kalah.cpp -o Kalah                                   //
// Then you can run it:                                                        //   
//          Kalah                                                              //
//  			 						       //
// mi.mesquita.medeiros@fnal.gov - Michelle Mesquita de Medeiros - 	       //
// Feb. 27, 2014.                                                              //
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
#include "Kalah.h"

using namespace std;

int main() {

   cout << "Welcome to Kalah game!" << endl;

//   int house[7]; // One for each player. Can access by calling Kalah class
//   string playerName;

   string name1;
   string name2 = "Computer";
   cout << "Enter name: ";
   cin >> name1;
   cout << "You will be playing against the computer." << endl;

// Initializing all houses with zero seeds
  
   Kalah player1(name1);
   for (int i = 0; i < 7; i++) {
      player1.Kalah::SetSeeds(0,i);
   }

   Kalah player2(name2);
   for (int i = 0; i < 7; i++) {
      player2.Kalah::SetSeeds(0,i);
   }

// Now lets place the 30 seeds randomly across the board (w/o counting the stores) - total houses = 12   
   int randNum[12];
   srand(time(NULL));

// Getting random numbers from up to 30 to fill the houses, 11 parameters, the last one is just 30-sumOf11
   for (int i = 0; i < 11; i++) {
      randNum[i] = rand() % 30;
   }

// However the sum of seeds needs to be exactly 30
   int sum = 0;
   int sum2 = 0;

   for (int i = 0; i < 11; i++) {
      sum += randNum[i];
   }

// Transform the number in its equivalent if the sum was 30
   for (int i = 0; i < 11; i++) {
      randNum[i] = 30*randNum[i]/sum;
      randNum[11] = 30-sum;
   }

   for (int i = 0; i < 11; i++) {
      sum2 += randNum[i];
   }	

   randNum[11] = 30-sum;
   randNum[11] = 30-sum2;

// Filling the houses with the random numbers
   for (int i = 0; i < 6; i++) {
      player1.Kalah::SetSeeds(randNum[i],i);
   }
   for (int i = 6; i < 12; i++) {
      player2.Kalah::SetSeeds(randNum[i],i-6);
   }

   int turn = 1;

// The games keeps going until someone wins
   
   while ((!player1.Kalah::Finished())&&(!player2.Kalah::Finished())) {
      int house1;
      int house2;

         // This is for the user to play............
         while (turn == 1) {

            house1 = 0;
            // Lets print configuration

            cout << endl << "\t Player " << player1.Kalah::Name(name1) << "\t Player " << player2.Kalah::Name(name2) << endl;
            for (int i = 0; i < 6; i++) {
               cout << "House " << i << ":    " << player1.Kalah::NumSeeds(i) << "\t\t\t  " << player2.Kalah::NumSeeds(i) << endl;
            }
            cout << "Store" << ":      " << player1.Kalah::NumSeeds(6) << "\t\t\t  " << player2.Kalah::NumSeeds(6) << endl;

            // Tell player to play
            cout << endl << "Choose a house to sow (enter number from 0 to 5): ";
            cin >> house1;
            cout << endl;
            while ((house1 > 5) || (house1 < 0) || (player1.Kalah::NumSeeds(house1) == 0)) {
               cout << "Your choice is invalid. Try again: ";
               cin >> house1;
               cout << endl;
            }

            // Analyze if user should keep playing
            if (player1.Kalah::StillPlaying(house1)) {
               turn = 1;
            } else {
               turn = 2;
            }

            player1.Kalah::MoveSeeds(house1,player1,player2);
            if (player1.Kalah::Finished()) break;

         }

         // This is for the computer to play............
         while (turn == 2) {
            house2 = 0;

            // Lets print configuration
            cout << endl << "\t Player " << player1.Kalah::Name(name1) << "\t Player " << player2.Kalah::Name(name2) << endl;
            for (int i = 0; i < 6; i++) {
               cout << "House " << i << ":    " << player1.Kalah::NumSeeds(i) << "\t\t\t  " << player2.Kalah::NumSeeds(i) << endl;
            }
            cout << "Store" << ":      " << player1.Kalah::NumSeeds(6) << "\t\t\t  " << player2.Kalah::NumSeeds(6) << endl;

            cout << endl << "Wait. Computer is playing..." << endl;
            house2 = rand() % 5 + 1;
            while (player2.Kalah::NumSeeds(house2) == 0) {
	       house2 = rand() % 5 + 1;
               cout << "THinking... house " << house2 << endl;
            }
            cout << "Computer chose house " << house2 << endl;

            // Analyze if user should keep playing			
            if (player2.Kalah::StillPlaying(house2)) {
               turn = 2;
            } else {
               turn = 1;
            }
            player2.Kalah::MoveSeeds(house2,player2,player1);
            if (player2.Kalah::Finished()) break;

      }

   }

// Game is Kalah::Finished!
// Analyzing who won, if stores have the same number of seeds, it's a tie!

   if (player1.Kalah::NumSeeds(6) == player2.Kalah::NumSeeds(6)) {
      cout << "Tied game." << endl;
   } else if (player1.Kalah::NumSeeds(6) > player2.Kalah::NumSeeds(6)) {
      cout << player1.Kalah::Name(name1) << " wins!" << endl;
   } else {
      cout << player2.Kalah::Name(name2) << " wins!" << endl;
   }

   return 0;

}


void Kalah::MoveSeeds(int houseNum, Kalah &player, Kalah &playeropo) {
   // How many seeds are in this house?
   int nseeds = Kalah::NumSeeds(houseNum);
      
   // Lets clear this house
   player.Kalah::RemoveSeeds(houseNum);

   // Seeds should be added to houses up to the number of seeds in this particular house
   // So which is the last house receiving a seed?
   int lasthouse = houseNum + nseeds;
   cout << "lasthouse is: " << lasthouse << endl;

   if ((lasthouse > 6)&&(lasthouse < 13)) {

      lasthouse = lasthouse - 7; // need to count that oponents board starts with zero and not one

   cout << "we are in the oponent board 1st time" << endl;
   cout << "lasthouse is: " << lasthouse << endl;

      // Putting the seeds in each house:
      playeropo.Kalah::AddSeeds(0,lasthouse);
      player.Kalah::AddSeeds(houseNum+1,6);

   } else if (lasthouse <= 6) {

      // we are still in the player board

      player.Kalah::AddSeeds(houseNum+1,lasthouse);

   } else if (lasthouse == 13) {

      // we stopped in oponent store, not good

      player.Kalah::AddSeeds(houseNum+1,6);
      playeropo.Kalah::AddSeeds(0,5);
      player.Kalah::AddSeeds(0,0);

   } else if ((lasthouse > 13)&&(lasthouse <= 20)) {

      lasthouse = lasthouse - 14; // need to count that oponents board starts with zero and not one

      // we are still in the player board 2nd time

      player.Kalah::AddSeeds(houseNum+1,6);
      playeropo.Kalah::AddSeeds(0,5);
      player.Kalah::AddSeeds(0,lasthouse+1); // need to skip the store of the oponent

   } else if ((lasthouse > 20)&&(lasthouse < 27)) {

      lasthouse = lasthouse - 21; // need to count that oponents board starts with zero and not one

      // we are in the oponent board 2nd time

      // Putting the seeds in each house:
      playeropo.Kalah::AddSeeds(0,5);
      playeropo.Kalah::AddSeeds(0,lasthouse+1); // need to skip the store of the oponent
      player.Kalah::AddSeeds(houseNum+1,6);
      player.Kalah::AddSeeds(0,6);

   } else if ((lasthouse == 27)) {

     // we stopped in oponent store 2nd time, not good

      // Putting the seeds in each house:
      player.Kalah::AddSeeds(houseNum+1,6);
      playeropo.Kalah::AddSeeds(0,5);
      player.Kalah::AddSeeds(0,6);
      playeropo.Kalah::AddSeeds(0,5);
      player.Kalah::AddSeeds(0,0);

   } else if ((lasthouse > 27)) {

      lasthouse = lasthouse - 28; // need to count that oponents board starts with zero and not one

      // we are still in the player board 3rd time

      // Putting the seeds in each house:
      player.Kalah::AddSeeds(houseNum+1,6);
      playeropo.Kalah::AddSeeds(0,5);
      player.Kalah::AddSeeds(0,6);
      playeropo.Kalah::AddSeeds(0,5);
      player.Kalah::AddSeeds(0,lasthouse+2); // need to skip the store of the oponent

   } else {
      cout << "Something is wrong with the numbers of seeds!" << endl;
   }

   // Checking if stopped in an Kalah::Empty house of this Kalah::Player (house 6 is the store)
   if ((lasthouse != 6)&&(Kalah::Empty(lasthouse))&&(!player.Kalah::Empty(lasthouse))) {
      house[6] = house[6] + (house[lasthouse] + player.Kalah::NumSeeds(lasthouse));
      // Clearing the last house and the opposite house from the other Kalah::Player
      Kalah::RemoveSeeds(lasthouse); 
      player.Kalah::RemoveSeeds(lasthouse); 	 
   }

} // Finished this move!


void Kalah::RemoveSeeds(int houseNum) {
   house[houseNum] = 0;
}


void Kalah::AddSeeds(int houseNum, int lasthouse) {

   for (int i = houseNum; i <= lasthouse; i++) {
      house[i]++;
   }
}


int Kalah::NumSeeds(int houseNum) {
   return house[houseNum];
}


void Kalah::SetSeeds(int numSeeds, int houseNum) {
   house[houseNum] = numSeeds;
}

string Kalah::Name(string name) {
   return playerName = name;
}

bool Kalah::Empty(int houseNum) {
   return (house[houseNum] == 0);
}

// Check is the same Kalah::Player keeps playing (is the last seed stopping in his store?)
bool Kalah::StillPlaying(int houseNum) {
   int lasthouse = houseNum + house[houseNum];
   return (lasthouse == 6);
}

// Check if the game is Kalah::Finished (sum of seeds from all houses, for a particular Kalah::Player, is zero)
bool Kalah::Finished() {
   int totalseeds = 0;
   for (int i=0; i < 6; i++) { // be careful not to count the store
      totalseeds = totalseeds + house[i];
   }
   return (totalseeds == 0);
}

Kalah::Kalah(string name) {

}

Kalah::~Kalah() {

}

void InitGame();


