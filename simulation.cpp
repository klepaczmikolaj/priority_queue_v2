#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <unistd.h>
#include "priority_queue.h"

#define SIMULATION_TIME 30
#define QUEUE_NUMBER 4
#define THREAD_NUMBER 4
#define PROCESS_INTERVAL 2

typedef enum queueID {LEFT_UP, RIGHT_UP, LEFT_DOWN, RIGHT_DOWN} queueID;

int randSleep(){
    int interval = 1e6 * PROCESS_INTERVAL;
    interval = interval * 3 / 4 + rand() % (interval / 2);
    return interval;
}

void producerDouble(PriorityQueue *queue1, PriorityQueue *queue2){
    time_t timer = time(0);
    while(time(0) - timer <= SIMULATION_TIME){
        QueueElement element;
        element.randomizeValues();
        if(rand() % 2 == 0)
            queue1->enqueue(element);
        else
            queue2->enqueue(element);
        usleep(randSleep() / 2);
    }
}

void consumerDouble(PriorityQueue *queue1, PriorityQueue *queue2){
    time_t timer = time(0);
    while(time(0) - timer <= SIMULATION_TIME){
        QueueElement element;
        if(queue1->getPriorQuantity() > queue2->getPriorQuantity())
            queue1->dequeue(&element);
        else if(queue1->getPriorQuantity() < queue2->getPriorQuantity())
            queue2->dequeue(&element);
        else{
            if(rand() % 2 == 0)
                queue1->dequeue(&element);
            else
                queue2->dequeue(&element);
        }
        usleep(randSleep());
    }
}

void producerConsumer(PriorityQueue *sourceQueue, PriorityQueue *destinationQueue){
    time_t timer = time(0);
    sleep(10);
    while(time(0) - timer <= SIMULATION_TIME){
        QueueElement element;
        sourceQueue->dequeue(&element);
        destinationQueue->enqueue(element);

        usleep(randSleep());
    }
}

void displayQueues(PriorityQueue queueList[QUEUE_NUMBER]){
    printf("\n######################################\n");
    printf("\nLeft up: \n");
    queueList[LEFT_UP].displayQueue();
    printf("\n\t\t\tRight up: \n\t\t\t");
    queueList[RIGHT_UP].displayQueue();
    printf("\nLeft down: \n");
    queueList[LEFT_DOWN].displayQueue();
    printf("\n\t\t\tRight down: \n\t\t\t");
    queueList[RIGHT_DOWN].displayQueue();
    printf("\n######################################\n");
}

void displayTask(PriorityQueue queueList[QUEUE_NUMBER]){
    int interval = 50000;   //microseconds
    time_t timer = time(0);
    while(time(0) - timer <= SIMULATION_TIME){
        //clear console 
        printf("\033[H\033[J");
        displayQueues(queueList);

        usleep(interval);
    }

}

int main(int argc, char const *argv[]){
    PriorityQueue queueList[QUEUE_NUMBER];
    queueList[LEFT_UP].setType(QueueType::PRIORITY);
    queueList[RIGHT_UP].setType(QueueType::PRIORITY);

    srand(time(NULL));
    
    std::thread t1(producerDouble, &queueList[LEFT_DOWN], &queueList[RIGHT_DOWN]);
    std::thread t2(consumerDouble, &queueList[LEFT_UP], &queueList[RIGHT_UP]);
    std::thread t3(producerConsumer, &queueList[LEFT_DOWN], &queueList[LEFT_UP]);
    std::thread t4(producerConsumer, &queueList[RIGHT_DOWN], &queueList[RIGHT_UP]);

    displayTask(queueList);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}