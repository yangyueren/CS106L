/*
 * TODO: complete this file comment.
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <chrono>
#include <time.h>
#include <unistd.h>
#include "SimpleGraph.h"

using namespace std;

const double kPi = 3.14159265358979323;
const double krepel = 0.001;
const double kattract = 0.001;

void Welcome();
void getFileName(string &fileName);
void getTimeLimit(int &timeLimit);
void initNode(SimpleGraph &g, int &n, const string &fileName);
void updateNode(SimpleGraph &g, int &n, const int &timeLimit);




// Main method
int main() {

    Welcome();
    while(true){
        string fileName;
        int timeLimit;
        SimpleGraph g;
        int n;
        getFileName(fileName);
        getTimeLimit(timeLimit);
        initNode(g, n, fileName);
        updateNode(g, n, timeLimit);
    }


    /* TODO: your implementation here */
    return 0;
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
    cout << "Welcome to CS106L GraphViz!" << endl;
    cout << "This program uses a force-directed graph layout algorithm" << endl;
    cout << "to render sleek, snazzy pictures of various graphs." << endl;
    cout << endl;
}

void getFileName(string &fileName){
    cout << "enter the file name to open:" <<endl;
    ifstream ifs;
    while(true){
        std::getline(std::cin, fileName);
        ifs.open(fileName);
        if(ifs.fail()){
            cout << "file not exist, input again:" <<endl;
        }else{
            return;
        }
    }
}
void getTimeLimit(int &timeLimit){
    cout << "enter time limit:" <<endl;
    while (true){
        string line;
        char trash;
        getline(cin, line);
        istringstream iss(line);
        if(iss>>timeLimit && !(iss>>trash)){
            return;
        }else{
            cout << "input again:" <<endl;
        }
    }  
}

void initNode(SimpleGraph &g, int &n, const string &fileName){
    ifstream fin(fileName);
    if(fin.fail()){
        throw domain_error("open file failed.");
    }else{
        fin >> n;
        size_t a, b;
        while(fin >> a >> b){
            Edge e{a, b};
            g.edges.push_back(e);
        }
        for (int i = 0; i < n; i++){
            Node node{cos(2*kPi*i/n), sin(2*kPi*i/n)};
            g.nodes.push_back(node);
        }
        InitGraphVisualizer(g);
        DrawGraph(g);
    }

}
void updateNode(SimpleGraph &g, int &n, const int &timeLimit){
    auto start = clock();
    while(double(clock()-start)/CLOCKS_PER_SEC < timeLimit){
        vector<pair<double, double> > diff;
        for(int i=0; i < n; i++){
            diff.push_back(make_pair<double, double>(0.0, 0.0));
        }
        //compute repulsive force
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                Node a = g.nodes[i];
                Node b = g.nodes[j];
                double Frepel = krepel / sqrt((b.y-b.x)*(b.y-b.x) +(a.y-a.x)*(a.y-a.x));
                double theta = atan2(b.y - b.x, a.y - a.x);
                diff[i].first -= Frepel * cos(theta);
                diff[i].second -= Frepel * sin(theta);
                diff[j].first += Frepel * cos(theta);
                diff[j].second += Frepel * sin(theta);
            }
        }
        // compute attractive force
        for(int i=0; i < g.edges.size(); i++){
            int start = g.edges[i].start;
            int end = g.edges[i].end;
            Node a = g.nodes[start];
            Node b = g.nodes[end];
            double Fattract = kattract / sqrt((b.y-b.x)*(b.y-b.x) + (a.y-a.x)*(a.y-a.x));
            double theta = atan2(b.y - b.x, a.y - a.x);
            diff[start].first += Fattract * cos(theta);
            diff[start].second += Fattract * sin(theta);
            diff[end].first -= Fattract * cos(theta);
            diff[end].second -= Fattract * sin(theta);
        }
        for (int i = 0; i < n; i++){
             g.nodes[i].x += diff[i].first;
             g.nodes[i].y += diff[i].second;
         }
        DrawGraph(g);
    }

}





