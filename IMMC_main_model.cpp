//
// Created by Garv Shah on 12/3/2022.
//

#include <fstream>
#include <iostream>
//#include "models/IMMC_random_model_testing.cpp"
//#include "models/IMMC_boarding_by_section_testing.cpp"
#include "models/IMMC_boarding_by_seat_testing.cpp"

//Change which file above is included to test different models

using namespace std;

int main()
{
    random_device rd;
    default_random_engine rng(rd());

    ofstream outputFile;
    outputFile.open("data_output.txt");
    for (int i = 0; i < 1000; i++)
    {
        int time = runModel(rng);
        printf("%d\n", time);
        outputFile << time << endl;
    }
    outputFile.close();

    try {
        std::__fs::filesystem::rename("data_output.txt", "../data_output.txt");
    } catch (std::__fs::filesystem::filesystem_error& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}
