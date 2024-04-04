#include"element.hpp"
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


