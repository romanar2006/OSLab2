#ifndef OSLAB2_1_H
#define OSLAB2_1_H

#define NOMINMAX
#include <windows.h>
#include <vector>
#include <limits>
#include <iostream>

struct ThreadData {
    std::vector<int> array;
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    double average = 0.0;
};

extern "C" {
    DWORD WINAPI findMinMax(LPVOID lpParam);
    DWORD WINAPI calculateAverage(LPVOID lpParam);
}

#endif
