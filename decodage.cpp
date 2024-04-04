#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<ostream>
#include<cassert>
#include"decodage.hpp"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
 
struct termios initial_settings, new_settings;
 
void deleteEchoMode()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &new_settings);
}
 
void resetEchoMode()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

std::string decodage(std::string filename){
	int dec;std::string s;
	int mdp;
	std::cout << "mot de passe : ";
	deleteEchoMode();
	std::cin >> mdp;
	resetEchoMode();
	std::cout << std::endl;
	if(mdp != 27182818) {
		std::cout << "mot de passe incorrect" << std::endl;
		return "\0";
	}
	std::cout << "decalage : ";
	deleteEchoMode();
	std::cin >> dec;
	resetEchoMode();
	std::cout << std::endl;
	std::ifstream lecture(filename);
	char c;wchar_t v;
	while(lecture.get(c)) {
		v = ((wchar_t) c-dec) & 0x000000FF;
		c = (char)v;
		//std::cout << c;
		s.push_back(c);
	}
	lecture.close();
	return s;
}
