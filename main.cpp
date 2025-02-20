//title,genre,director,year,runtime,rating,revenue
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

struct Movie {
    string title;
    string genre;
    string director;
    int year;
    int runtime;
    double rating;
    long long revenue;
};

void parse(string line, Movie &movie);
void readCSV();

int main() {
    readCSV();
    return 0;
}


void parse(string line, Movie &movie) {
    /*
    * I was getting terminate called after throwing an instance of 'std::out_of_range'
  what():  stoi, becuase some revenue was too large for a normal int so i changed movie.revenue to a long long and used stoll
  to convert it to a long interger
    https://en.cppreference.com/w/cpp/string/basic_string/stol
     */
    stringstream ss(line);
    string temp;
    getline(ss, movie.title, ',');
    getline(ss, movie.genre, ',');
    getline(ss, movie.director, ',');
    getline(ss, temp, ',');
    movie.year = stoi(temp);
    getline(ss, temp, ',');
    movie.runtime = stoi(temp);
    getline(ss, temp, ',');
    movie.rating = stod(temp);
    getline(ss, temp, ',');
    movie.revenue = stoll(temp);
}

void readCSV() {
    ifstream fin("IMDB-Movie-Data.csv");
    if (fin) {
        while (!fin.eof()) {
            string line;
            getline(fin, line);
            Movie movie;
            if (line.length() >0) {
                parse(line, movie);
                cout << movie.title << endl;
                cout << movie.genre << endl;
                cout << movie.director << endl;
                cout << movie.year << endl;
                cout << movie.runtime << endl;
                cout << movie.rating << endl;
                cout << movie.revenue << endl;
            }
        }
        fin.close();
    }
    else {
        cout << "File could not be opened" << endl;
    }
}