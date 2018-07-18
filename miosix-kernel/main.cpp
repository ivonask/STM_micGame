/**************************************************************************
 * Copyright (C) 2017 Giovanni Beri                                       *
 * Edited by: 2018 Ivona Skorjanc and Odri Tomas                          *
 * This program is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by   *
 * the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                    *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 * GNU General Public License for more details.                           *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 **************************************************************************/

#include <cstdio>
#include <stdint.h>
#include "miosix.h"
#include "Microphone.h"
#include "button.h"
#include <math.h>
#include <functional>
#include <termios.h>
#include <string.h>
#include "stm32_hardware_rng.h"

using namespace std;
using namespace miosix;

int winnerFreq = 4500;
int winner;

void calculateFreq(unsigned char* compressedData, unsigned int index, int player, int gameFreq){

   int Fs = 11025;
   int fftSize = 2048;
   int freq;

   freq = (index * Fs)/ (2*fftSize); //calculate the frequency from the index of the maximal frequency from the FFT analysis

   if (abs(freq - gameFreq) < winnerFreq )
   {
      winnerFreq = abs(freq - gameFreq);
      winner = player;
      printf("The frequency is %d and the winner freq and player were change into %d and %d.\n", freq, winnerFreq, winner);
   }	
 
}

int main()
{
    char players; //var that stores the number of players in the game
    int requiredFreq; //var that stored the frequency the players need to produce
    volatile int i=0;

    //microphone insance
    Microphone& mic = Microphone::instance(); 
    mic.init(bind(calculateFreq,placeholders::_1,placeholders::_2, placeholders::_3, placeholders::_4));

    //instance of the hardware random generator
    HardwareRng& rng = HardwareRng::instance();
    //initialise the user button
    buttonInit();

   printf("Enter number of players...");
   while(1){
   scanf("%c", &players);

   //check if the entered number is between 2 and 4 (game specifications)
   if (players == '2' || players == '3' || players == '4')
	{
		printf("Ok\n");
		break;
	}
   else if (players != '\n')
	{
		printf("Try again...");
	}

  }

    printf("Number of player %c\n", players);

    //generate random frequency
    requiredFreq = rng.get() % 4500 + 500; 
    printf("The required frequency is %d\n", requiredFreq);   
 
   //record player sounds and analyse frequency
   while (i < (int) players - 48)  {

    printf("Ready for player %d...start by pressing the button\n", i+1);

    //recording starts when the button is pressed
    waitForButton();
    mic.start(i+1,requiredFreq);
    ledOn();

    // recording finishes with the button pressed againe
    waitForButton();
    mic.stop();
    ledOff();

     i++;
   }
  
   printf ("The winner is....%d\n", winner);
   printf("End of the game\n"); 
   while (1){
    };
    
}
