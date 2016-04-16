#include <iostream>
#include "inputhandler.h"
using namespace std;
int main(int argc, char* argv[]) {
    cout<<"Hello"<<endl;
    InputHandler ih;
    pair<int, vector<string> > com;

    com = ih.parseInput("list");
    cout<< "This should be 1: " << com.first << endl;

    com = ih.parseInput("create newsgroup newsgroup.wiki.com");
    cout<< "This should be 2: " << com.first << endl;

    com = ih.parseInput("delete newsgroup.wiki.com");
    cout<< "This should be 3: " << com.first << endl;

    com = ih.parseInput("list newsgroup.wiki.com");
    cout<< "This should be 4: " << com.first << endl;

    com = ih.parseInput("create article newsgroup.wiki.com /home/anton/Documents/Floobits/article.txt");
    cout<< "This should be 5: " << com.first << endl;
    cout<< "Newsgroup: " << com.second[0] << endl;
    cout<< "This is the article read: \n" << "Title: " << com.second[1] << "\n";
    cout<< "Author: " << com.second[2] << "\n";
    cout<< "Text: " << com.second[3] << endl;

    com = ih.parseInput("delete article newsgroup.wiki.com 1");
    cout<< "This should be 6: " << com.first << endl;

    com = ih.parseInput("get 1");
    cout<< "This should be 7: " << com.first << endl;

    com = ih.parseInput("");
    cout<< "This should be 8: " << com.first << endl;

    com = ih.parseInput("This not input");
    cout<< "This should be 8: " << com.first << endl;


}
