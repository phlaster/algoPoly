#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>


int randInt(int min, int max)
{
    return min<max ?
        rand() % (max - min + 1) + min :
        rand() % (min - max + 1) + max;
}

void Delay(int msec)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

// Платформозависимая реализация
void Clear()
{
    #if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        // system("clear");
        std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
    #elif defined (__APPLE__)
        system("clear");
    #endif
}