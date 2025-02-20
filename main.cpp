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
void readCSV(vector<Movie> &movies);
void displayMovies(const vector<Movie> &movies, string message = "All Movies");
int findMovieByTitle(const vector<Movie> &movies, const string &title);
void displayMovieDetails(const vector<Movie> &movies, int index);

int main() {
    vector<Movie > movies;
    readCSV(movies);
    // displayMovies(movies);

    string searchTitle = "";
    cout << "Enter a movie title: ";
    getline(cin, searchTitle);

    int index = findMovieByTitle(movies, searchTitle);
    if (index != -1) {
        cout << "Movie was found" << endl;
        displayMovieDetails(movies, index);
    }
    else {
        cout << "No movie found" << endl;
    }

    return 0;
}



void readCSV(vector<Movie> &movies) {
    ifstream fin("IMDB-Movie-Data.csv");
    if (fin) {
        while (!fin.eof()) {
            string line;
            getline(fin, line);
            Movie movie;
            if (line.length() >0) {
                parse(line, movie);
                movies.push_back(movie);
            }
        }
        fin.close();
    }
    else {
        cout << "File could not be opened" << endl;
    }
}


void parse(string line, Movie &movie) {
    /*
    * I was getting "terminate called after throwing an instance of 'std::out_of_range'
  what():  stoi", becuase some revenue was too large for a normal int so i changed movie.revenue to a long long and used stoll
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


void displayMovies(const vector<Movie> &movies, string message) {
    cout << message << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    for (const auto &movie : movies) {
        cout
        << "Title: " << movie.title
        << " | Genre: " << movie.genre
        << " | Director: " << movie.director
        << " | Year: " << movie.year
        << " | Runtime: " << movie.runtime
        << " | Rating: " << movie.rating
        << " | Revenue: $" << movie.revenue
        << endl;
    }
}

int findMovieByTitle(const vector<Movie> &movies, const string &title) {
    for (int i = 0; i < movies.size(); i++) {
        if (movies[i].title == title) {
            return i;
        }
    }
    return -1;
}

void displayMovieDetails(const vector<Movie> &movies, int index) {
    if (index >= 0 && index < movies.size()) {
        const Movie &movie = movies[index];
        cout << "----------------------------------------" << endl;
        cout << "Title: " << movie.title << endl;
        cout << "Genre: " << movie.genre << endl;
        cout << "Director: " << movie.director << endl;
        cout << "Year: " << movie.year << endl;
        cout << "Runtime: " << movie.runtime << " minutes" << endl;
        cout << "Rating: " << movie.rating << endl;
        cout << "Revenue: $" << movie.revenue << endl;
        cout << "----------------------------------------" << endl;
    }
}