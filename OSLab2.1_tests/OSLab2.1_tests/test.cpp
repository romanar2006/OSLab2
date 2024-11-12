#include "pch.h"
#include <gtest/gtest.h>
#include "../../OSLab2.1/OSLab2.1.h"
#define NOMINMAX
#include "windows.h"
#include <vector>

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

TEST(OSLab2Tests, FindMinMax) {
    ThreadData data;
    data.array = { 3, 1, 4, 1, 5 };

    HANDLE hMinMax = CreateThread(NULL, 0, findMinMax, &data, 0, NULL);
    WaitForSingleObject(hMinMax, INFINITE);
    CloseHandle(hMinMax);

    EXPECT_EQ(data.min, 1);
    EXPECT_EQ(data.max, 5);
}

TEST(OSLab2Tests, CalculateAverage) {
    ThreadData data;
    data.array = { 3, 1, 4, 1, 5 };

    HANDLE hAverage = CreateThread(NULL, 0, calculateAverage, &data, 0, NULL);
    WaitForSingleObject(hAverage, INFINITE);
    CloseHandle(hAverage);

    EXPECT_NEAR(data.average, 2.8, 0.1);
}

TEST(OSLab2Tests, ModifyArray) {
    ThreadData data;
    data.array = { 3, 1, 4, 1, 5 };

    HANDLE hMinMax = CreateThread(NULL, 0, findMinMax, &data, 0, NULL);
    WaitForSingleObject(hMinMax, INFINITE);
    CloseHandle(hMinMax);

    HANDLE hAverage = CreateThread(NULL, 0, calculateAverage, &data, 0, NULL);
    WaitForSingleObject(hAverage, INFINITE);
    CloseHandle(hAverage);

    for (int& num : data.array) {
        if (num == data.min || num == data.max) {
            num = static_cast<int>(data.average);
        }
    }

    std::vector<int> expected = { 3, 2, 4, 2, 2 };
    EXPECT_EQ(data.array, expected);
}
