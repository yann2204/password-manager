#include"element.hpp"
#include<ostream>
#include<iostream>
#include<string>

std::string element::GetChapter() {
    return this->chapter;
}

std::string element::GetContent() {
    return this->content;
}

void element::SetChapter(std::string str) {
    this->chapter = str; 
}

 void element::SetContent(std::string str) {
    this->content = str;
 }

 void element::printelement(){
    std::cout << "{ Chapter : " << this->GetChapter() << ", Content : " << this->GetContent() << " }" << std::endl;
 }


