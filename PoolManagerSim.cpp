#include <cstdlib>
#include <cstdio>
#include <random>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>

#include "pool.hpp"
#include "engine.hpp"

using namespace std;

pool* p;

engine* e;

void updatePool();

void showStats();

void reader();

void engineOperation();

void inputManager();

void swim();

int main(int argc, char **argv)
{
    if (argc == 2) {
        cout << "Starting..." << endl;
        p = new pool(atof(argv[1]));
        e = new engine(p, 10);
        thread t1(updatePool);
        thread t2(engineOperation);
        inputManager();
        t1.join();
        t2.join();
    }
    else
    {
        cout << "Usage: poolmanager <water volume>\n";
    }
    return 0;
}

void updatePool() {
    //p = new pool(60.0);
    p->update();
}

void showStats()
{
    float ppm = p->getPPM();
    float ph = p->getPH();
    cout << "PPM: " << ppm << "\n" << "PH: " << ph << "\n";
}

void reader() {
    for (int i = 1; i > 0; i++) {
        this_thread::sleep_for(chrono::seconds(12));
        float ppm = p->getPPM();
        float ph = p->getPH();
        cout << ppm << endl;
        cout << ph << "\n";
    }
}

void engineOperation()
{
    e->start();
    e->clean();
}

void inputManager()
{
    short option;
    cout << "1: Show pool stats\n2: Let a new person swim\n3: exit\n";
    for (int i = 1; i > 0; i++) {
        cout << "> ";
        cin >> option;
        //cout << option << endl;
        switch (option) {
        case (1):
            showStats();
            break;
        case (2):
            swim();
            break;
        case (3):
            exit(0);
            break;
        default:
            cout << "Unvalid option\n";
            break;
        }
    }
}

void swim()
{
    p->risePH();
}
