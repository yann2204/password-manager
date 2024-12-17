
#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include<string>



class element {
    std::string chapter;
    std::string content;
    public:
        element(std::string chapter_name = "", std::string content_ = "") {
            chapter = chapter_name;
            content = content_;
        }
        std::string GetChapter();
        std::string GetContent();
        void SetChapter(std::string str);
        void SetContent(std::string str);
        void printelement();
};

#endif