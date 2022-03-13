#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>

using namespace std;

string csv = "back_to_front.csv";

int airplane[34][7]; //for each row, 1st index is A, 2nd index is B, 3rd index is C, 4th index is D,
//5th index is E, 6th index is F
int board[34][7];

pair<pair<int, int>, int> simulating_aisle[34];
int store_time[34];

vector<pair<pair<int, int>, int> > passengers; //first: row, column, second: number of baggages

int marked[34];

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
    memset(marked, 0, sizeof(marked));


    for (int i = 33; i >= 1; i--) {
        int left_right = rand() % 2;//0 = A/B/C, 1 = D/E/F
        if (left_right == 0) {
            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 1), total_time));
            marked[i] = 0;
        } else {

            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 6), total_time));
            marked[i] = 1;
        }
    }

    for (int i = 33; i >= 1; i--) {
        int left_right = 1 - marked[i];

        if (left_right == 0) {
            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 1), total_time));
            marked[i] = 0;
        } else {

            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 6), total_time));
            marked[i] = 1;
        }
    }

    for (int i = 33; i >= 1; i--) {
        int left_right = rand() % 2;//0 = A/B/C, 1 = D/E/F
        if (left_right == 0) {
            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 2), total_time));
            marked[i] = 0;
        } else {

            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 5), total_time));
            marked[i] = 1;
        }
    }

    for (int i = 33; i >= 1; i--) {
        int left_right = 1 - marked[i];

        if (left_right == 0) {
            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 2), total_time));
            marked[i] = 0;
        } else {

            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 5), total_time));
            marked[i] = 1;
        }
    }

    for (int i = 33; i >= 1; i--) {
        int left_right = rand() % 2;//0 = A/B/C, 1 = D/E/F
        if (left_right == 0) {
            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 3), total_time));
            marked[i] = 0;
        } else {

            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 4), total_time));
            marked[i] = 1;
        }
    }

    for (int i = 33; i >= 1; i--) {
        int left_right = 1 - marked[i];

        if (left_right == 0) {
            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 3), total_time));
            marked[i] = 0;
        } else {

            int baggage_num = rand() % 4; //assumption: every passenger will have a random number of baggage from 0 to 3
            int total_time = 0;
            for (int i = 1; i <= baggage_num; i++) {

                total_time += rand() % 11 + 5;; //assumption: every baggage will cost 5-15 seconds to be placed
                //printf("%d\n",cost);
            }

            passengers.push_back(make_pair(make_pair(i, 4), total_time));
            marked[i] = 1;
        }
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
