#include <iostream>
#include "priority_queue.h"


int main(int argc, char const *argv[]){
    PriorityQueue queue(QueueType::PRIORITY);

    for(int i = 0; i < 12; i++){
        Priority priority;
        if(rand() % 2 == 0)
            priority = Priority::HIGH;
        else
            priority = Priority::LOW;
        QueueElement elem(i, priority);
        queue.enqueue(elem);

        queue.displayQueue();
    }


    for(int i = 0; i < 12; i++){
        QueueElement elem;
        queue.dequeue(&elem);
        queue.displayQueue();
    }

    return 0;
}