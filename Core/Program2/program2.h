#pragma once

#ifndef P_TWO

#define P_TWO

#endif // !P_TWO

#ifdef P_TWO

#pragma region INCLUDES && GLOBAL_VARS

#define HAVE_STRUCT_TIMESPEC
#include <random>
#include <iostream>
#include <chrono>
#include <pthread.h>

using namespace std;

using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::duration;
using chrono::milliseconds;

constexpr unsigned int SIZE2 = 200;
// 77ms, 250x, singlethread
// 88ms, 250x, 4 threads
// 93ms, 250x, 8 threads
// 96ms, 250x, 16 threads
// 136ms, 250x, 32 threads
constexpr unsigned int PROGRAM_COUNT_LOOP2 = 250;
constexpr unsigned int MAX_THREAD2 = 4;

int arr2[SIZE2] = {};

#pragma endregion

#pragma region FUNCTIONS

void print2() {
    for (int i = 0; i < SIZE2; i++) {
        cout << arr2[i] << endl;
    }
}

void* bubbleSort2(void* arg) {
    for (int j = 0; j < SIZE2 - 1; j++) {
        for (int i = 0; i < SIZE2; i++) {
            if (arr2[i] > arr2[i + 1]) {
                swap(arr2[i], arr2[i + 1]);
            }
        }
    }

    return nullptr;
}

void initializeArray2() {
    for (int i = 0; i < SIZE2; i++) {
        arr2[i] = rand() % 10000;
    }
}

void getTotalExecutionTime2(float totalExecutionTime, float getExecutionTime[]) {
    for (int i = 0; i < PROGRAM_COUNT_LOOP2; i++) {
        totalExecutionTime += getExecutionTime[i];
    }

    cout << "Tempo medio total:" << totalExecutionTime / PROGRAM_COUNT_LOOP2 << "ms";
}

void clean2() {
    for (int i = 0; i < SIZE2; i++) {
        arr2[i] = 0;
    }
}

#pragma endregion

void ProgramTwo() {
    srand((unsigned)time(NULL));

    float getExecutionTime[PROGRAM_COUNT_LOOP2] = {};
    float totalExecutionTime = 0;

    // executa n vezes e calcula o tempo médio de execução do programa em milisegundos
    for (int i = 0; i < PROGRAM_COUNT_LOOP2; i++) {
        auto t1 = high_resolution_clock::now();

        initializeArray2();

        pthread_t threads[MAX_THREAD2]{};

        for (int i = 0; i < MAX_THREAD2; i++) {
            pthread_create(&threads[i], NULL, bubbleSort2, (void*)NULL);
        }

        for (int i = 0; i < MAX_THREAD2; i++) {
            pthread_join(threads[i], NULL);
        }

        print2();
        clean2();

        auto t2 = high_resolution_clock::now();

        auto ms_int = duration_cast<milliseconds>(t2 - t1);

        // calcula o tempo de execução em milisegundos.
        duration<double, milli> ms_double = t2 - t1;

        cout << "Tempo: " << ms_double.count() << "ms\n";

        getExecutionTime[i] = ms_double.count();
    }

    getTotalExecutionTime2(totalExecutionTime, getExecutionTime);
}

#endif // P_TWO