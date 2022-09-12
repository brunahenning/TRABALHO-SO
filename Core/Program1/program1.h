#pragma once

#ifndef P_ONE

#define P_ONE

#endif // !P_ONE

#ifdef P_ONE

#define HAVE_STRUCT_TIMESPEC
#include <iostream>
#include <pthread.h>
#include <random>
#include <chrono>

using namespace std;

using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::duration;
using chrono::milliseconds;

constexpr unsigned int SIZE = 4;
// 19.56ms, 250x, singlethread
// 23.56ms, 250x, 4 threads
// 29.36ms, 250x, 8 threads
// 36.77ms, 250x, 16 threads, erro no cálculo, valores negativos
// 54ms, 250x, 32 threads, erro no cálculo, valores negativos
constexpr unsigned int MAX_THREAD = 4;
constexpr unsigned int PROGRAM_COUNT_LOOP = 250;

int matA[SIZE][SIZE] = {};
int matB[SIZE][SIZE] = {};
long int matC[SIZE][SIZE] = {};

void* multi(void* arg)
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matC[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }

    return nullptr;
}

void initializeMatrix() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matA[i][j] = rand() % 10000;
            matB[i][j] = rand() % 10000;
        }
    }

    cout << "Matriz A: " << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << matA[i][j] << " ";
        cout << endl;
    }

    cout << "Matriz B: " << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << matB[i][j] << " ";
        cout << endl;
    }
}

void print() {
    cout << endl << "Matriz C:" << endl;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << matC[i][j] << " ";
        cout << endl;
    }
}

void getTotalExecutionTime(float totalExecutionTime, float getExecutionTime[]) {
    for (int i = 0; i < PROGRAM_COUNT_LOOP; i++) {
        totalExecutionTime += getExecutionTime[i];
    }

    cout << "Tempo medio total:" << totalExecutionTime / PROGRAM_COUNT_LOOP << "ms";
}

void clean() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matA[i][j] = 0;
            matB[i][j] = 0;
            matC[i][j] = 0;
        }
    }
}

void ProgramOne() {
    srand((unsigned)time(NULL));

    float getExecutionTime[PROGRAM_COUNT_LOOP] = {};
    float totalExecutionTime = 0;

    for (int i = 0; i < PROGRAM_COUNT_LOOP; i++) {
        auto t1 = high_resolution_clock::now();

        initializeMatrix();

        pthread_t threads[MAX_THREAD]{};

        for (int i = 0; i < MAX_THREAD; i++) {
            pthread_create(&threads[i], NULL, multi, (void*)NULL);
        }

        for (int i = 0; i < MAX_THREAD; i++) {
            pthread_join(threads[i], NULL);
        }

        print();
        clean();

        auto t2 = high_resolution_clock::now();

        auto ms_int = duration_cast<milliseconds>(t2 - t1);

        duration<double, milli> ms_double = t2 - t1;

        cout << "Tempo: " << ms_double.count() << "ms\n";

        getExecutionTime[i] = ms_double.count();
    }

    getTotalExecutionTime(totalExecutionTime, getExecutionTime);
}

#endif // P_ONE