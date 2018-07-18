
# Welcome to the Miosix kernel


You can find information on how to configure and use the kernel
at the following url: http://miosix.org

============================
 
## OVERVIEW

This application is designed for Miosix 2.02 on the STM32F407 Discovery board. It uses the on-board MEMS microphone to collect audio samples and analyse their frequency.The application also uses a random number generator who define a random frequency from the range of human whistle frequencies (500 to 5000 Hz).
The purpose of the application is to make a game with 2 to 4 players. The winner is the player who produces a sound that is closest to the required frequency.


## YOU NEED (Ubuntu 16.04 assumed; no other environment have been tested)
 - an RS-232 cable like this one (https://goo.gl/CFUBLj)

 After that, you only need to compile the firmware, with the usual command `$ make` in 'miosix-kernel' directory.


## HOW TO USE IT

 Because of some conflicts in the DMA channels, this firmware uses USART2 as default, so you need to connect RS-232 pins to PA2 and PA3. Once it's done, the usage is simple:
 - use the keyboard to enter the number of players to the serial connection
 - for each player, press user button to start recording, and press it again to stop it
 
 It could be possible that:
 - communication errors due to RS-232 limits corrupt some data on the link, so the script may not be able to collect data coming from the board. You can identify this situation because every time the script collect a batch of data, it printf a dot on the screen. If the red led is on in the board but dots stop appearing, you have to reset the board and the script
 - the user button takes 2 clicks at time, so it stops immediately the recording. If it happens, just make another try. 

 However, some measures has been taken to solve these situations, so they should not happen often.

 Just in case you are struggling because you are stuck using or understanding some part of this code, feel free to contact me on GitHub :whale:
