#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>

void* crossBridge(int index, int direction);
void EnterBridge();
void ExitBridge();

enum Direction {NORTH, SOUTH};

sem_t cross;

int main(){
    int north, south;
    std::vector<std::thread> farmers;

    srand(time(NULL));

    sem_init(&cross, 0, 1);

    printf("Enter total number of northbound farmers: ");
    scanf("%d", &north);
    printf("Enter total number of southbound farmers: ");
    scanf("%d", &south);

    for(int i = 0; i < north; i++)
        farmers.push_back(std::thread(crossBridge, i + 1, Direction::NORTH));

    for(int i = 0; i < south; i++)
        farmers.push_back(std::thread(crossBridge, i + 1, Direction::SOUTH));

    for(int i = 0; i < farmers.size(); i++)
        farmers[i].join();

    std::cout << "All farmers crossed the bridge." << std::endl;

    return 0;
}

void* crossBridge(int index, int direction){
    std::string direct;
    char buf[100];

    if(direction == Direction::NORTH)
        direct = "northbound";
    else
        direct = "southbound";

    std::this_thread::sleep_for(std::chrono::seconds(1));
    EnterBridge();
    snprintf(buf, 100, "The %s farmer %d is entering the bridge.", direct.c_str(), index);
    puts(buf);
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 2 + 1));
    ExitBridge();
    snprintf(buf, 100, "The %s farmer %d exited the bridge.", direct.c_str(), index);
    puts(buf);
}

void EnterBridge(){
    sem_wait(&cross);
}

void ExitBridge(){
    sem_post(&cross);
}
