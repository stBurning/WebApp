#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "cgi/cgi.h"
/**
 * @author Ustinov Konstantin
 * Данный CGI-скрипт предназначен для вывода страницы-формы и обработки данных с нее:
 *      1.В случае GET-запроса - отрисовка страницы с формой ввода
 *      2.В случае POST-запросв - отрисовка страницы с формой ввода и сохранение комментария в файл
 *      **/
using namespace std;
struct Comment{
    /**Структура для сериализации данных из формы**/
    char name[80];
    char surname[80];
    char text[500];
};


int main() {
    cout << "Content-type: text/html;"
            "charset=utf-8\n\n";
    //Открываем поток ввода для чтения файла form.html как шаблон страницы
    ifstream f;
    f.open("form.html");
    if (f.is_open()){
        char *buf = new char[65536];
        char *data;
        get_form_data(data);//Получаем данные формы
        //Если данные получены -> POST-запрос
        if ((data) && (strlen(data) > 0)) {//Если получены данные
            ofstream out("data/comments.data",std::ios::binary|std::ios::app);
            if (out.is_open()) {
                char* name; char* surname; char* text;
                get_user_value(name, data, "name");
                get_user_value(surname, data, "surname");
                get_user_value(text, data, "comment");
                Comment comment;
                strcpy(comment.name, name);
                strcpy(comment.surname, surname);
                strcpy(comment.text, text);
                out.write((char*)&comment, sizeof(Comment));//Сериализуем данные в бинарный файл
                out.close();
            }
            delete[] data;
        }
        //Выводим страницу
        while (!f.eof()) {
            f.getline(buf, 65536);
            cout << buf << endl;
        }
        delete[] buf;
        f.close();

    }
    return 0;
}