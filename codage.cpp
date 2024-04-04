#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<ostream>
#include<cassert>
#include"codage.hpp"
#include"decodage.hpp"

int codage(std::string &decoded_string){
	int dec;
	int mdp;
	std::cout << "mot de passe : ";
	deleteEchoMode();
	std::cin >> mdp;
	resetEchoMode();
	std::cout << std::endl;
	if(mdp != 27182818) {
		std::cout << "mot de passe incorrect" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "decalage : ";
	deleteEchoMode();
	std::cin >> dec;
	resetEchoMode();
	std::cout << std::endl;
	for (int i = 0;i<(int)decoded_string.size();i++) {
		decoded_string[i] = (uint8_t) decoded_string[i]+dec;
	}
	return EXIT_SUCCESS;
}
