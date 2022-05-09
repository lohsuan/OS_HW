#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

void fifo();
void lru();
void optimal();
int repeatPlace(int frame[], int number);
int earliestPlace(int frame[], int number[]);
int lastUse(int frame[], int pos);
void printFrame(int frame[]);

int frameSize = 0;
int sequence[20];

int main(){
    srand(time(NULL));

    while(frameSize < 1 || frameSize > 7){
        printf("Enter the size of frame (1~7): ");
        scanf("%d", &frameSize);
    }

    std::cout << "The random page-reference string:" << std::endl;
    for(int i = 0; i < 20; i++){
        sequence[i] = rand() % 10;
        std::cout << sequence[i] << " ";
    }
    std::cout << std::endl;

    fifo();
    lru();
    optimal();
}

void fifo(){
    int pageFault = 0, pointer = 0, j = 0;
    int frame[frameSize];

    std::fill_n(frame, frameSize, -1);

    for(int i = 0; i < 20; i++){
        if(repeatPlace(frame, sequence[i]) != -1)
            continue;
        if(j < frameSize){
            frame[i] = sequence[i];
            j++;
        }else{
            frame[pointer] = sequence[i];
            pointer = (pointer + 1) % frameSize;
        }
        pageFault++;
        printFrame(frame);
    }

    std::cout << "The number of page faults incurred by the FIFO page-replacement algorithm: " << pageFault << std::endl;
}

void lru(){
    int pageFault = 0, j = 0;
    int frame[frameSize];
    int number[10];

    std::fill_n(frame, frameSize, -1);
    std::fill_n(number, 10, -1);

    for(int i = 0; i < 20; i++){
        if(repeatPlace(frame, sequence[i]) != -1){
            number[sequence[i]] = i;
            continue;
        }
        number[sequence[i]] = i;
        if(j < frameSize){
            frame[i] = sequence[i];
            j++;
        }else{
            int place = earliestPlace(frame, number);
            frame[place] = sequence[i];
        }
        pageFault++;
        printFrame(frame);
    }

    std::cout << "The number of page faults incurred by the LRU page-replacement algorithm: " << pageFault << std::endl;
}

void optimal(){
    int pageFault = 0, j = 0;
    int frame[frameSize];

    std::fill_n(frame, frameSize, -1);

    for(int i = 0; i < 20; i++){
        if(repeatPlace(frame, sequence[i]) != -1){
            continue;
        }       
        if(j < frameSize){
            frame[i] = sequence[i];
            j++;
        }else{
            int place = lastUse(frame, i);
            frame[place] = sequence[i];
        }
        pageFault++;
        printFrame(frame);
    }

    std::cout << "The number of page faults incurred by the optimal page-replacement algorithm: " << pageFault << std::endl;
}

int repeatPlace(int frame[], int number){
    int result = -1;

    for(int i = 0; i < frameSize; i++){
        if(number == frame[i])
            result = i;
    }

    return result;
}

int earliestPlace(int frame[], int number[]){
    int result, compare = 20;

    for(int i = 0; i < frameSize; i++){
        if(compare > number[frame[i]]){
            compare = number[frame[i]];
            result = i;
        }
    }
    
    return result;
}

int lastUse(int frame[], int pos){
    int result = 0, index = 0;

    for(int i = 0; i < frameSize; i++){
        int n = 20;
        for(int j = pos + 1; j < 20; j++){
            if(frame[i] == sequence[j]){
                n = j;
                break;
            }
        }
        if(n > index){
            index = n;
            result = i;
        }
    }

    return result;
}

void printFrame(int frame[]){
    std::cout << "frame: ";
    for(int i = 0; i < frameSize; i++)
        std::cout << " " << frame[i];
    std::cout << std::endl;
}