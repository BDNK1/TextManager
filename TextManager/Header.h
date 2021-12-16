#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
#include <iomanip>
#include <clocale>
#include <map>
#include <iomanip>
#include <filesystem>
#include <fstream>  
#include <sys/stat.h> 

namespace fs = std::filesystem;
using namespace std;

void menu();
int digs(double w);
void initPath();
void initArchives();
void initDocs();
void showDocs();
void showArchives();
int avgDocs();

class Date {
protected:
    bool leapyear;
    int day;
    int year;
    int month;
    bool leap(int y)const;
    int maxday()const;
public:
    Date(int d, int m, int y) :leapyear(leap(y)), day(d), month(m), year(y) {};
    Date() = default;
    Date& operator+=(int);
    Date& operator-=(int);
    int getDay();
    int getMonth();
    int getYear();
    std::string operator-(Date&)const;
    bool operator==(Date&)const;
    void show();
    string toString();
    bool operator <= (const Date& d) const;
};

class Person {
protected:
    string surname;
    string name;
    Date* dateOfBirth;
public:
    Person(string surname, string name, Date* dateOfBirth);
    
};
class Document;
class Author : public Person {
public:
    Author(string surname, string name, Date* dateOfBirth);
    static Author* addAuthor();
    static Author* addAuthor(string surname, string name, Date* date);
    string getName();
    string getSurname();
    void addDoc(Document* doc);
    Date* getDateOfBirth();
private:
    //vector<Document> docs;
};

class File {
protected:
    string name;
    string format;
    Date* dateOfCreation;
    string path;
    int size;
public:
    File(string name,string format,int size);
    string getName();
    Date* getDate();
    string getFullPath();
    int getSize();
};

class Archive:public File {
private:
    vector<string> files;
    string real_bin_file;
public:
    Archive(string name, string real_bin_file,int size);
    Archive(vector<string>& vec, string name);
    void getInfo();
    void InCompress();
    void showArchiveInfo();
    void OutCompress(string binary);
    static void delArchive();
    static void unpackArchive();
    static void makeArchive();
    static string get_file_name(string fn) { return fn.substr(fn.find_last_of("\\") + 1, fn.size()); }

};

class Document:public File {
private:    
    Author* author;
    vector<string> keywords;
public:
    Document(string name, int size,Author* author, vector<string> keywords);
    static void delDoc();
    void getDocInfo();
    void showDocInfo();
    string getText();
    Author* getAuthor();
    vector<string> getKeywords();
    static void makeDoc();
};



