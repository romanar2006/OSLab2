#include <iostream>
#define NOMINMAX
#include <windows.h>
#include <vector>
#include <numeric>
#include <limits>
#include <thread>
#include <algorithm>
#include "OSLab2.1.h"

DWORD WINAPI findMinMax(LPVOID lpParam) {
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    for (size_t i = 0; i < data->array.size(); ++i) {
        if (data->array[i] < data->min) {
            data->min = data->array[i];
        }
        if (data->array[i] > data->max) {
            data->max = data->array[i];
        }
        Sleep(7); 
    }
    std::cout << "min: " << data->min << std::endl;
    std::cout << "max: " << data->max << std::endl;
    return 0;
}

DWORD WINAPI calculateAverage(LPVOID lpParam) {
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    int sum = 0;
    for (size_t i = 0; i < data->array.size(); ++i) {
        sum += data->array[i];
        Sleep(12); 
    }
    data->average = static_cast<double>(sum) / data->array.size();
    std::cout << "Average: " << data->average << std::endl;
    return 0;
}

int main() {
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    std::vector<int> array(size);
    std::cout << "Enter array: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> array[i];
    }

    ThreadData data;
    data.array = array;

    HANDLE hMinMax = CreateThread(NULL, 0, findMinMax, &data, 0, NULL);
    WaitForSingleObject(hMinMax, INFINITE);

    HANDLE hAverage = CreateThread(NULL, 0, calculateAverage, &data, 0, NULL);
    WaitForSingleObject(hAverage, INFINITE);

    for (int& num : data.array) {
        if (num == data.min || num == data.max) {
            num = static_cast<int>(data.average);
        }
    }

    std::cout << "Modified array: ";
    for (int num : data.array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    return 0;
}
