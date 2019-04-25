#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "cgi/cgi.h"

using namespace std;


struct Comment{
    char name[80];
    char surname[80];
    char text[500];
};

void show_comments(){
    ifstream f("data/comments.data", ios::binary);
    if(f.is_open()){
        Comment comment;
        f.seekg(0, ios::beg);
        while(f.read((char*)&comment, sizeof(Comment))){
            cout<<"<div class='content'>"
            <<"<h4 class='author'>"<<comment.name<<" "<<comment.surname<<"</h4>"
            <<"<div class='comment'>"<<"\n"<<comment.text<<"</div>"
            <<"</div>"<<endl;
        }
        f.close();
    }
}

int main() {
    cout << "Content-type: text/html;"
            "charset=utf-8\n\n";

    ifstream f;
    f.open("reviews.html");
    if (f.is_open()){
        char *buf = new char[65536];
        while (!f.eof()) {
            f.getline(buf, 65536);
            if (strcmp(buf, "<!--Comments-->") == 0) {
                show_comments();
            }
            cout << buf << endl;
        }
        delete[] buf;
        f.close();
    }
    return 0;
}