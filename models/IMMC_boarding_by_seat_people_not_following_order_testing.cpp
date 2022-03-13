#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>

using namespace std;

string csv = "boarding_by_seat (10% disobey).csv";

int airplane[34][7]; //for each row, 1st index is A, 2nd index is B, 3rd index is C, 4th index is D,
//5th index is E, 6th index is F
int board[34][7];

pair<pair<int, int>, int> simulating_aisle[34];
int store_time[34];

vector<pair<pair<int, int>, int> > passengers; //first: row, column, second: number of baggages

vector<pair<pair<int, int>, int>> AF_section, BE_section, CD_section;


void next_second() {

    for (int i = 33; i >= 1; i--) {
        if (store_time[i] == 0 &&
            simulating_aisle[i].first.first == i) { //check if there are passengers that finished packing at this second


            board[i][simulating_aisle[i].first.second] = 1;
            //the passenger sits down, making the isle clear;
            simulating_aisle[i].first.first = -1;
            simulating_aisle[i].first.second = -1;
            simulating_aisle[i].second = -1;
        }

    }

    for (int i = 1; i <= 33; i++) {
        store_time[i] = max(store_time[i] - 1, 0);
    }


    for (int i = 32; i >= 1; i--) {
        if (simulating_aisle[i].first.first == -1) {
            continue;
        }
        if (simulating_aisle[i].first.first != i && simulating_aisle[i + 1].first.first == -1) {
            simulating_aisle[i + 1] = simulating_aisle[i];
            if (simulating_aisle[i + 1].first.first == i + 1) {
                store_time[i + 1] = simulating_aisle[i + 1].second;
                //check if there are people blocking the seat. Assumption: it takes an extra 5 seconds to sit if the seat is blocked by 1 person, 10 seconds if it is blocked by two person
                if (simulating_aisle[i + 1].first.second == 1 && board[i + 1][2] == 1) {
                    store_time[i + 1] += 5;
                }
                if (simulating_aisle[i + 1].first.second == 1 && board[i + 1][3] == 1) {
                    store_time[i + 1] += 5;
                }
                if (simulating_aisle[i + 1].first.second == 2 && board[i + 1][3] == 1) {
                    store_time[i + 1] += 5;
                }


                if (simulating_aisle[i + 1].first.second == 6 && board[i + 1][5] == 1) {
                    store_time[i] += 5;
                }
                if (simulating_aisle[i + 1].first.second == 6 && board[i + 1][4] == 1) {
                    store_time[i] += 5;
                }
                if (simulating_aisle[i + 1].first.second == 5 && board[i + 1][4] == 1) {
                    store_time[i] += 5;
                }
            }

            //now that the aisle at the ith row is clear
            simulating_aisle[i].first.first = -1;
            simulating_aisle[i].first.second = -1;
            simulating_aisle[i].second = -1;
        }
    }
}


int runModel(default_random_engine rng) {
    memset(airplane, 0, sizeof(airplane));
    memset(board, 0, sizeof(board));
    memset(simulating_aisle, 0, sizeof(simulating_aisle));
    memset(store_time, 0, sizeof(store_time));
    passengers.clear();
    AF_section.clear();
    BE_section.clear();
    CD_section.clear();

    for (int i = 1; i <= 33; i++) { //random boarding order for people in seat A
        int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
        int total_time = 0;
        for (int i = 1; i <= baggage_num; i++) {

            total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
            //printf("%d\n",cost);
        }
        AF_section.push_back(make_pair(make_pair(i, 1), total_time));
    }

    for (int i = 2; i <= 33; i++) { //random boarding order for people in seat F
        int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
        int total_time = 0;
        for (int i = 1; i <= baggage_num; i++) {

            total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
            //printf("%d\n",cost);
        }
        AF_section.push_back(make_pair(make_pair(i, 6), total_time));
    }

    shuffle(AF_section.begin(), AF_section.end(), rng);

    for (int i = 1; i <= 33; i++) { //random boarding order for people in seat B
        int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
        int total_time = 0;
        for (int i = 1; i <= baggage_num; i++) {

            total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
            //printf("%d\n",cost);
        }
        BE_section.push_back(make_pair(make_pair(i, 2), total_time));
    }

    for (int i = 2; i <= 33; i++) { //random boarding order for people in seat E
        int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
        int total_time = 0;
        for (int i = 1; i <= baggage_num; i++) {

            total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
            //printf("%d\n",cost);
        }
        BE_section.push_back(make_pair(make_pair(i, 5), total_time));
    }

    shuffle(BE_section.begin(), BE_section.end(), rng);

    for (int i = 1; i <= 33; i++) { //random boarding order for people in seat C
        int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
        int total_time = 0;
        for (int i = 1; i <= baggage_num; i++) {

            total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
            //printf("%d\n",cost);
        }
        CD_section.push_back(make_pair(make_pair(i, 3), total_time));
    }


    for (int i = 2; i <= 33; i++) { //random boarding order for people in seat D
        int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
        int total_time = 0;
        for (int i = 1; i <= baggage_num; i++) {

            total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
            //printf("%d\n",cost);
        }
        CD_section.push_back(make_pair(make_pair(i, 4), total_time));
    }

    shuffle(CD_section.begin(), CD_section.end(), rng);


    for (int i = 0; i < 20; i++) {

        int sizeAF = AF_section.size();
        int sizeBE = BE_section.size();
        int sizeCD = CD_section.size();

        int not_following = rand() % 6 + 1;
        if (not_following == 1 || not_following == 6) { //the person has his/her seat in A/F column
            int NFfrom = rand() % sizeAF;

            int goes_to = rand() %
                          2; //0 for the person to board with BE passengers, 1 for the person to board with CD passengers
            if (goes_to == 0) {
                int NFto = rand() % (sizeBE + 1);
                BE_section.insert(BE_section.begin() + NFto, AF_section[NFfrom]);
                AF_section.erase(AF_section.begin() + NFfrom);
            }
            if (goes_to == 1) {
                int NFto = rand() % (sizeCD + 1);
                CD_section.insert(CD_section.begin() + NFto, AF_section[NFfrom]);
                AF_section.erase(AF_section.begin() + NFfrom);
            }
        }


        if (not_following == 2 || not_following == 5) { //the person has his/her seat in B/E column
            int NFfrom = rand() % sizeBE;

            int goes_to = rand() %
                          2; //0 for the person to board with AF passengers, 1 for the person to board with CD passengers
            if (goes_to == 0) {
                int NFto = rand() % (sizeAF + 1);
                AF_section.insert(AF_section.begin() + NFto, BE_section[NFfrom]);
                BE_section.erase(BE_section.begin() + NFfrom);
            }
            if (goes_to == 1) {
                int NFto = rand() % (sizeCD + 1);
                CD_section.insert(CD_section.begin() + NFto, BE_section[NFfrom]);
                BE_section.erase(BE_section.begin() + NFfrom);
            }
        }

        if (not_following == 3 || not_following == 4) { //the person has his/her seat in C/D column
            int NFfrom = rand() % sizeCD;

            int goes_to = rand() %
                          2; //0 for the person to board with AF passengers, 1 for the person to board with BE passengers
            if (goes_to == 0) {
                int NFto = rand() % (sizeAF + 1);
                AF_section.insert(AF_section.begin() + NFto, CD_section[NFfrom]);
                CD_section.erase(CD_section.begin() + NFfrom);
            }
            if (goes_to == 1) {
                int NFto = rand() % (sizeBE + 1);
                BE_section.insert(BE_section.begin() + NFto, CD_section[NFfrom]);
                CD_section.erase(CD_section.begin() + NFfrom);
            }
        }
    }


    for (int i = 0; i < AF_section.size(); i++) {
        passengers.push_back(AF_section[i]);
    }

    for (int i = 0; i < BE_section.size(); i++) {
        passengers.push_back(BE_section[i]);
    }

    for (int i = 0; i < CD_section.size(); i++) {
        passengers.push_back(CD_section[i]);
    }


    int iterater1 = 0;
    int total1 = passengers.size();
    int time1 = 0;


    for (int i = 1; i <= 33; i++) { //initialisation
        simulating_aisle[i].first.first = -1;
        simulating_aisle[i].first.second = -1;
        simulating_aisle[i].second = -1;
    }

    while (iterater1 <= total1 - 1) {
        time1 = time1 + 1;
        next_second();
        if (simulating_aisle[1].first.first == -1) {
            simulating_aisle[1] = passengers[iterater1];
            iterater1 += 1;
            if (simulating_aisle[1].first.first == 1) {
                store_time[1] += simulating_aisle[1].first.second;
                store_time[1] = simulating_aisle[1].second;
                //check if there are people blocking the seat. Assumption: it takes an extra 5 seconds to sit if the seat is blocked by 1 person, 10 seconds if it is blocked by two person
                if (simulating_aisle[1].first.second == 1 && board[1][2] == 1) {
                    store_time[1] += 5;
                }
                if (simulating_aisle[1].first.second == 1 && board[1][3] == 1) {
                    store_time[1] += 5;
                }
                if (simulating_aisle[1].first.second == 2 && board[1][3] == 1) {
                    store_time[1] += 5;
                }


                if (simulating_aisle[1].first.second == 6 && board[1][5] == 1) {
                    store_time[1] += 5;
                }
                if (simulating_aisle[1].first.second == 6 && board[1][4] == 1) {
                    store_time[1] += 5;
                }
                if (simulating_aisle[1].first.second == 5 && board[1][4] == 1) {
                    store_time[1] += 5;
                }
            }
        }


    }
    bool finished = false;
    while (true) {
        finished = true;
        for (int i = 1; i <= 33; i++) {
            if (simulating_aisle[i].first.first != -1) {
                finished = false;
            }
        }
        if (finished) {
            break;
        }
        time1 += 1;

        next_second();
    }

    //printf("%d\n",time1);

    return time1;
}
