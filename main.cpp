#include"decodage.hpp"
#include"codage.hpp"
#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<fstream>
#include"element.hpp"


#define FILENAME "mdp.txt"

std::vector<element> Init_Data(std::string str) {
    std::string chapter_name;
    std::string content;
    std::vector<element> tab;
    int i = 0;
    while (i<(int)str.size()) {
        if (str[i]=='{' && chapter_name!="") {
            while  (str[i]!='}') {
                if (str[i]!='\n' && str[i]!='\r' && str[i]!='{') {
                    content += str[i];
                }
                i++;
            }
            element * elem = new element(chapter_name,content);
            tab.push_back(*elem);
            chapter_name = "";
            content = "";
        }
        else if (str[i] != '\n' && str[i] != '\r') {
            chapter_name += str[i];
        }
        i++;
    }
    return tab;
}

bool IsBigger(const std::string a, const std::string b) {
    int l = std::min(a.size(),b.size());
    for(int i = 0; i < l; i++) {
        if (a[i]>b[i]) return true;
        else if (a[i]<b[i]) return false;
    }
    if ( (int) b.size() > l) return false;
    return true;
}

//Order the element in alphabetic order
void Order(std::vector<element> & tab) {
    for (int i = 0; i<(int)tab.size(); i++) {
        for (int j = i; j<(int)tab.size(); j++) {
            if (IsBigger(tab[i].GetChapter(),tab[j].GetChapter()) == true) {
                element temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }

}

//decrypt and print the data in the terminal
void PrintAll(std::string str) {
    std::string flux = decodage(str);
    int number =0;
    //std::cout << flux;
    std::vector<element> data = Init_Data(flux);
    Order(data);
    std::cout << "**********************************" << std::endl;
    for (int i = 0; i<(int)data.size();i++) {
        std::cout << i+1 << " : " << data[i].GetChapter() << std::endl;
    }
    std::cout << "**********************************" << std::endl;
        std::cout << "Select a number :" ;
        std::cin >> number;
    if (number <= (int)data.size()) {
        std::cout << "**********************************" << std::endl;
        std::cout << data[number-1].GetChapter() << std::endl;
        std::cout << "**********************************" << std::endl;
        std::cout << data[number-1].GetContent() << std::endl;
        std::cout << "**********************************" << std::endl;
    }
    else {
        std::cout << "Number out of range !!!" << std::endl;
    }

}
// convert the vector structure to a string (crypted)
std::string write_string(std::vector<element> vect) {
    std::string str = "";
    for (int i = 0;i<(int)vect.size();i++) {
        str+=vect[i].GetChapter();
        str+="\n{\n";
        str+=vect[i].GetContent();
        str+="\n}\n";
    }
    return str;
}

void EncodeString(std::string & str,int dec) {
    for(int i = 0;i<(int)str.size();i++) {
        str[i] += dec;
    }
}

//Add data and encrypt it in the source file
int AddData(std::string filename) {
    std::string name,content;
    std::string confirmation;
    std::string flux = decodage(filename);
    if (flux != "\0") {
        std::vector<element> data = Init_Data(flux);
        std::cout << "Enter the new chapter : ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Enter the new infos : ";
        std::getline(std::cin, content);
        std::cout << "Confirmation (y/n): ";
        std::getline(std::cin, confirmation);
        if (confirmation == "y" || confirmation == "yes") {
            element * elem = new element(name,content);
            data.push_back(*elem);
            std::string str=write_string(data);
            if (codage(str)==EXIT_SUCCESS) {
                std::ofstream ecriture(filename);
	            for(char x : str) {
		            ecriture << x;
	            }  
	            ecriture.close();
            }
            else return EXIT_FAILURE;
        }
        else {
            std::cout << "Operation aborded." << std::endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}


//decrypt remove and update the data 
int RemoveData(std::string filename) {
    std::string flux = decodage(filename);
    int number = 0;
    std::string confirmation = "";
    //std::cout << flux;
    std::vector<element> data = Init_Data(flux);
    Order(data);
    std::cout << "**********************************" << std::endl;
    for (int i = 0; i<(int)data.size();i++) {
        std::cout << i+1 << " : " << data[i].GetChapter() << std::endl;
    }
    std::cout << "**********************************" << std::endl;
    std::cout << "Select a number :" ;
    std::cin >> number;
    if (number < (int)data.size()) {
        std::cout << "**********************************" << std::endl;
        std::cout << "Confirmation (y/n): ";
        std::cin.ignore();
        std::getline(std::cin, confirmation);
        if (confirmation == "y" || confirmation == "yes") {
            data.erase(data.begin()+number-1);
            std::string str=write_string(data);
            if (codage(str)==EXIT_SUCCESS) {
                std::ofstream ecriture(filename);
	            for(char x : str) {
		            ecriture << x;
	            }  
	            ecriture.close();
            }
            else return EXIT_FAILURE;
        }
        else return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void PrintHelp() {
    std::cout << "command allowed :" << std::endl;
    std::cout << "'q' for quit" << std::endl;
    std::cout << "'s' for show password" << std::endl;
    std::cout << "'a' to add a password" << std::endl;
    std::cout << "'r' to remove a password" << std::endl;
    std::cout << "'m' to change a password" << std::endl;
}

//this function allow the user to chage the content of a chapter in case of a password needs to be corrected
//TODO : Not working, modification not taking into account
int ModifyPassword(std::string filename) {
    std::string flux = decodage(filename);
    int number = 0;
    std::string confirmation = "";
    std::string NewContent = "";
    std::string NewChapter = "";
    std::string ChangeChapter = "";
    //std::cout << flux;
    std::vector<element> data = Init_Data(flux);
    Order(data);
    std::cout << "**********************************" << std::endl;
    for (int i = 0; i<(int)data.size();i++) {
        std::cout << i+1 << " : " << data[i].GetChapter() << std::endl;
    }
    std::cout << "**********************************" << std::endl;
    std::cout << "Select the number of the chapter to change :" ;
    std::cin >> number;
    std::cout << "**********************************" << std::endl;
    std::cout << "Do you want to change the chapter name (y/n):" ;
    std::cin.ignore();
    std::getline(std::cin, ChangeChapter);
    if (ChangeChapter == "y" || ChangeChapter == "yes" || ChangeChapter == "Y" ) {
        std::cout << "**********************************" << std::endl;
        std::cout << "Please enter the new chapter name:" ;
        std::getline(std::cin, NewChapter);
        data[number-1].SetChapter(NewChapter);
        std::cout << "**********************************" << std::endl;
    }
    if (number < (int)data.size()) {
        std::cout << "enter the new content of the chapter to change :" ;
        std::getline(std::cin, NewContent);
        data[number-1].SetContent(NewContent);
        std::cout << "**********************************" << std::endl;
        std::cout << "Confirmation (y/n): ";
        std::getline(std::cin, confirmation);
        if (confirmation == "y" || confirmation == "yes" || confirmation == "Y" ) {
            std::cout << "**********************************" << std::endl;
            std::string str=write_string(data);
            if (codage(str)==EXIT_SUCCESS) {
                std::ofstream ecriture(filename);
	            for(char x : str) {
		            ecriture << x;
	            }  
	            ecriture.close();
            }
            else return EXIT_FAILURE;
        }
        else return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}




int main() {
    char cmd = '\0';
    std::cout << "**********************************" << std::endl;
    std::cout << "WELCOME TO YOUR PASSWORD MANAGER !" << std::endl;
    std::cout << "**********************************" << std::endl;
    std::cout << "**********************************" << std::endl;
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
    while (cmd != 'q') {
        std::cout << ">>> ";
        std::cin >> cmd;
        //To show the password
        if (cmd == 's') {
            PrintAll(FILENAME);
        }
        //To add a password
        else if (cmd == 'a') {
            AddData(FILENAME);
        }
        //To remove a password
        else if (cmd == 'r') {
            RemoveData(FILENAME);
        }
        //Help option
        else if (cmd == 'h') {
            PrintHelp();
        }
        else if (cmd == 'q') {
            std::cout << "Good bye" << std::endl;
            return EXIT_SUCCESS;
        }
        else if (cmd == 'm') {
            ModifyPassword(FILENAME);
        }
        else {
            std::cout << "!!! command not recognized !!!" << std::endl;
        }

    }
}