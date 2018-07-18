/**************************************************************************
 * Copyright (C) 2017 Giovanni Beri                                       *
 *                                                                        *
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
    // send actual size of the batch
    //write(STDOUT_FILENO,&size,sizeof(int));
    // send the batch of data
   int Fs = 11025;
   int fftSize = 2048;
   int freq;

    //printf("Max index %d\n",index);

   freq = (index * Fs)/ (2*fftSize);

   if (abs(freq - gameFreq) < winnerFreq )
   {
      winnerFreq = abs(freq - gameFreq);
      winner = player;
      printf("The frequency is %d and the winner freq and player were change into %d and %d.\n", freq, winnerFreq, winner);
   }	
 
   //printf("Value of the frequency is %d\n", freq);
 
}


// configure stdout in raw mode
void setRawStdout(){
    struct termios t;
    tcgetattr(STDOUT_FILENO,&t);
    t.c_lflag &= ~(ISIG | ICANON); 
    tcsetattr(STDOUT_FILENO,TCSANOW, &t); 
}


void sendInitSignal(int expectedBatchSize){
    // send signal to desktop script
    char init[] = "ready\n";
    write(STDOUT_FILENO,init,strlen(init));
    // send expected size of the data batches
    write(STDOUT_FILENO,&expectedBatchSize,sizeof(int));
}


int main()
{
    char players;
    int requiredFreq;
    volatile int i=0;
    Microphone& mic = Microphone::instance(); 
    mic.init(bind(calculateFreq,placeholders::_1,placeholders::_2, placeholders::_3, placeholders::_4));

    HardwareRng& rng = HardwareRng::instance();
    buttonInit();

   printf("Enter number of players...");
   while(1){
   scanf("%c", &players);
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

    requiredFreq = rng.get() % 4500 + 500; 
    printf("The required frequency is %d\n", requiredFreq);   
 
   while (i < (int) players - 48)  {

    printf("Ready for player %d...start by pressing the button\n", i+1);

    waitForButton();
    mic.start(i+1,requiredFreq);
    ledOn();

    // ending procedure
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
