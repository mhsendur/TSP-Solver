#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;

class locationsList {
public: double x, y, cityNum;

    bool operator==(const locationsList& other) const {
        return cityNum == other.cityNum;
    }
};

//Open the entered file
void openFile(string filename, ifstream &matrixFile){

    cout << "Enter the TSP filename: ";
    cin >> filename;

    matrixFile.open(filename.c_str());
    cout << (matrixFile.fail() ? "Error" : "Reading the file...") << endl;
}

//Create a vector of locations
void createMatrix(ifstream &matrixFile, vector<locationsList> &points){

    if (matrixFile.is_open()) {
        string c;
        while (matrixFile >> c ) {
            if (c == "NODE_COORD_SECTION")
            {break;}
            cout << c << " ";
        }
        cout << endl;
        double cN, x, y;
        while (matrixFile >> cN >> x >> y) {
            points.push_back({x, y, cN});
        }
    }
}

//Calculate the twoPointDistance between two cities
double twoPointDistance(const locationsList& c1, const locationsList& c2) {
    return sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
}

//Calculate the total twoPointDistance
double totalDistance(const vector<locationsList>& route) {
    double td = 0;
    for (int i = 0; i < route.size() - 1; i++) {
        td += twoPointDistance(route[i], route[i + 1]);
    }
    return td;
}

//Calculate the candidate list size for the dataset
int candidateListSize(int numCities) {
    if (numCities > 750) {
        return 17;
    }
    else if (numCities > 500) {
        return 15;
    }
    else if (numCities > 100) {
        return 10;
    }
    else if (numCities > 25) {
        return 5;
    }
    else {
        return 3;
    }
}


//Swap implementation
vector<locationsList> SWAP(vector<locationsList>& route, int x, int y) {
    if (x == y){
        return route;}
    if (x > y){swap(x, y);}
    if (x == route.size() - 1 || y == route.size() - 1) return route;
    if (x + 1 == y) return route;

    double initial = twoPointDistance(route[x], route[x + 1]) + twoPointDistance(route[y], route[y + 1]);
    double swapped = twoPointDistance(route[x], route[y]) + twoPointDistance(route[x + 1], route[y + 1]);

    //Swap if swapped returns a shorter route
    if (swapped < initial) {
        vector<locationsList> finalR = route;
        finalR[x + 1] = route[y];
        finalR[y] = route[x + 1];
        return finalR;
    }

    else {
        return route;
    }
}

//GRASP implementation
vector<locationsList> GRASP(const vector<locationsList>& cities, int &startP) {

    vector<locationsList> route = {cities[startP-1]};
    vector<locationsList> remaining = cities;

    remaining.erase(remaining.begin() + startP - 1);

    while (!remaining.empty()){
        int numCandidates = candidateListSize(cities.size());

        vector<locationsList> candidates;

        for (int i = 0; i < numCandidates && i < remaining.size(); i++) {
            candidates.push_back(remaining[i]);
        }

        sort(candidates.begin(), candidates.end(), [&](const locationsList& c1, const locationsList& c2) {
            return twoPointDistance(route.back(), c1 ) < twoPointDistance(route.back(), c2 );
        });

        double rNum = rand() % candidates.size();
        locationsList nextCity;

        nextCity = candidates[rNum - 1];

        route.push_back(nextCity);
        remaining.erase(find(remaining.begin(), remaining.end(), nextCity));

        //Swapping in each iteration multiple times
        for (int i = 0; i < candidates.size(); i++){

            int c1 = i ;
            int c2 = (i + 1) ;

            route = SWAP(route, c1, c2);
        }
    }

    //Final multiple times swapping

    int s = 0;
    int h = route.size()/7.5;
    if (route.size() > 1000){h = 75;}
    while (s != h){
        for (int i = 0; i < route.size() - 2; i++) {
            for (int j = i + 2; j < route.size() - 1; j++) {
                route = SWAP(route, i+3, j);
            }
        }
        s++;}

    route.push_back(cities[startP-1]);

    return route;
}




int main() {

    //Time Data
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> totalTime{};

    int timeLimit = 0;
    int startP = 0;
    string filename;
    ifstream matrixFile;
    vector<locationsList> points;

    openFile(filename, matrixFile);
    cout << "=========== Description of the TSP File ============" << endl;
    cout << endl;
    createMatrix(matrixFile, points);
    cout << endl;
    cout << "====================================================" << endl;
    cout << endl;
    cout << "There is " << points.size() << " locations to start from. Enter where you would like to start: ";
    cin >> startP;
    cout << endl << "====================================================" << endl;
    cout << endl << "Enter the time limit (in seconds): ";
    cin >> timeLimit;

    start = chrono::system_clock::now();

    vector<locationsList> bestRoute = GRASP(points, startP);
    double bestDistance = totalDistance(bestRoute);

    auto start2 = chrono::system_clock::now();

    while (chrono::duration<double>(chrono::system_clock::now() - start2).count() < timeLimit){

        vector<locationsList> newRoute = GRASP(points, startP);
        double newDistance = totalDistance(newRoute);

        if (newDistance < bestDistance){
            bestRoute = newRoute;
            bestDistance = newDistance;
        }
    }

    vector<locationsList> route = bestRoute;
    end = chrono::system_clock::now();
    totalTime = end - start;

    cout << endl;
    cout << "=========== Total Distance of the Route ============" << endl;
    cout << endl;
    cout << "The total distance is " << totalDistance(route) << endl;
    cout << endl;
    cout << "============== Route Taken in Detail ===============" << endl;
    cout << endl;
    cout << "Time to calculate the route taken is " << totalTime.count() << " seconds." << endl << endl;
    cout << "The Route: " << endl;

    int cnt=1;
    for (const locationsList &c: route){
        cout << "#" << cnt << " Location: " << c.cityNum << " - Coords: (" << c.x << ", " << c.y << ") " << "to " << endl;
        cnt++;
    }

    cout << endl;
    cout << "====================================================" << endl;

    return 0;
}
//For the large sized datasets time limit entered should be smaller than the designated time limit below to stop before reaching the time limit.
//Thus enter smaller time limit, as there are more swaps and GRASPs to be done.

/*
 Dataset examined with their designated time limit below:
        wi29, 15 seconds
        dj38, 15 seconds
        xqf131, 1 minute
        qa194, 1 minute
        uy734, 10 minutes
        zi929, 15 minutes
        lim963, 15 minutes
        xit1083, 15 minutes
*/
