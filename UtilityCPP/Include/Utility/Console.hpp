#pragma once
#include <iostream>
#include <string>
#include <conio.h>  

namespace  BenScr {
    class Console
    {
    public:
        template<typename... Args>
        static void WriteLine(Args&&... args) {
            (std::cout << ... << args);
            std::cout << '\n';
		}
        template<typename... Args>
        static void Write(Args&&... args) {
            (std::cout << ... << args);
        }

        static std::string ReadLine()
        {
            std::string input;
            std::getline(std::cin, input);
            return input;
        }

        static char ReadKey() {
            return  _getch();
        }

        static void Clear()
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }
    };
}