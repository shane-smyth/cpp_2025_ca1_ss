//title,genre,director,year,runtime,rating,revenue
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
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
map<string, int> countOfGenres(const vector<Movie> &movies);
void getMoviesByGenre(vector<Movie> &movies, const string genre);
tuple<int, Movie, Movie> runtimeStatics(const vector<Movie> &movies);
vector<Movie> moviesContaining(const vector<Movie> &movies, const string &str);
void sortRatingDesc(vector<Movie> &movies);

int main() {
    vector<Movie > movies;
    readCSV(movies);
    // displayMovies(movies);

    // string searchTitle = "";
    // cout << "Enter a movie title: ";
    // getline(cin, searchTitle);
    //
    // int index = findMovieByTitle(movies, searchTitle);
    // if (index != -1) {
    //     cout << "Movie was found" << endl;
    //     displayMovieDetails(movies, index);
    // }
    // else {
    //     cout << "No movie found" << endl;
    // }

    // map<string, int> genreCounts = countOfGenres(movies);
    // for (const auto &genre : genreCounts) {
    //     cout << "Genre: " << genre.first << " | Count: " << genre.second << endl;
    // }

    // cout << "Enter Movie Genre: ";
    // string selectedGenre;
    // cin >> selectedGenre;
    // getMoviesByGenre(movies, selectedGenre);

    // https://medium.com/@ryan_forrester_/tuples-in-c-complete-guide-516a53837e45
    // auto [avg, highest, lowest] = runtimeStatics(movies);
    // cout << "Average Runtime: " << avg << " minutes\n";
    // cout << "Longest Movie: " << highest.title << " (" << highest.runtime << " minutes)\n";
    // cout << "Shortest Movie: " << lowest.title << " (" << lowest.runtime << " minutes)\n";

    // cout << "Enter a string: ";
    // string str;
    // getline(cin, str);
    // vector<Movie> filteredMovies = moviesContaining(movies, str);
    // displayMovies(filteredMovies, "Movies containing: " + str);

    sortRatingDesc(movies);

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
    for (const auto &movie : movies) { // https://www.geeksforgeeks.org/cpp-vector-of-structs/
        cout << "----------------------------------------" << endl;
        cout << "Title: " << movie.title << endl;
        cout << "Genre: " << movie.genre << endl;
        cout << "Director: " << movie.director << endl;
        cout << "Year: " << movie.year << endl;
        cout << "Runtime: " << movie.runtime << " minutes" << endl;
        cout << "Rating: " << movie.rating << endl;
        cout << "Revenue: $" << movie.revenue << endl;
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

// https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
// https://www.w3schools.com/cpp/cpp_maps.asp
map<string, int> countOfGenres(const vector<Movie> &movies) {
    map<string, int> count;
    for (const auto &movie : movies) {
        string key;
        key = movie.genre;
        count[key]++;
    }
    return count;
}

// https://www.geeksforgeeks.org/how-to-convert-std-string-to-lower-case-in-cpp/
string toLowerCase(const string &str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(),lowerStr.begin(), ::tolower);
    return lowerStr;
}

void getMoviesByGenre(vector<Movie> &movies, const string genre) {
    vector<Movie> subset;
    string genreLower = toLowerCase(genre);
    for (const auto &movie : movies) {
        string movieGenreLower = toLowerCase(movie.genre);
        if (movieGenreLower == genreLower) {
            subset.push_back(movie);
        }
    }
    if (!subset.empty()) {
        displayMovies(subset, "Displaying All " + genre);
    } else {
        cout << "No movies found for the genre: " << genre << endl;
    }
}

// https://www.geeksforgeeks.org/how-to-return-multiple-values-from-a-function-in-c-or-cpp/
// https://www.geeksforgeeks.org/tuples-in-c/
tuple<int, Movie, Movie> runtimeStatics(const vector<Movie> &movies) {
    if (movies.empty()) {
        return {0, Movie(), Movie()};
    }

    const Movie *lowestRun = &movies[0];
    const Movie *highestRun = &movies[0];
    int totalRun = 0;

    for (const auto &movie : movies) {
        totalRun += movie.runtime;
        if (movie.runtime > highestRun->runtime) {
            highestRun = &movie;
        }
        if (movie.runtime < lowestRun->runtime) {
            lowestRun = &movie;
        }
    }
    int averageRun = totalRun / movies.size();
    return {averageRun, *highestRun, *lowestRun};
}

vector<Movie> moviesContaining(const vector<Movie> &movies, const string &str) {
    vector<Movie> subset;
    string searchStr = toLowerCase(str);

    for (auto iter = movies.begin(); iter != movies.end(); ++iter) {
        if (toLowerCase(iter->title).find(searchStr) != string::npos) {
            subset.push_back(*iter);
        }
    }

    if (subset.empty()) {
        cout << "No movies found that contain: " << str << endl;
    }
    return subset;
}

void sortRatingDesc(vector<Movie> &movies) {
    auto func = [](Movie &a, Movie &b) -> bool {return a.rating > b.rating;};
    sort(movies.begin(), movies.end(), func);
    displayMovies(movies, "Movies in Descending order of Rating:");
}