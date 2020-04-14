/***********************************************************************************
 * File: input.h
 * C++
 * Author: Virgínia Sátyro
 * License: Free - Open Source
 * Created on April 2020 
 * 
 * Using this to substitute the conio.h library - that can be used only on windows.
 * To use the program in linux, had to implement this helping function.
 ***********************************************************************************/

#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int _kbhit(void); // input function

#endif // INPUT_H