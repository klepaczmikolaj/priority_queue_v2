#include <iostream>
#include <mutex>
#include <thread>
#include "priority_queue.h"


PriorityQueue::PriorityQueue(QueueType type){
    this->type = type;
    this->head = 0;
    this->tail = 0;
    this->size = 0;
    this->priorQuantity = 0;
}

bool PriorityQueue::enqueue(QueueElement element){
    if(isBufferFull())
        return false;
    
    std::lock_guard<std::mutex> guard(this->mutex);

    //start of critical section
    if(this->type == QueueType::NORMAL && element.priority == Priority::HIGH){
        this->head == 0 ? this->head = QUEUE_CAPACITY-1 : this->head--;
        this->buffer[this->head] = element;
    }
    else{
        this->buffer[this->tail] = element;
        this->tail = (this->tail + 1) % QUEUE_CAPACITY;
    }

    this->size++;
    if(element.priority == Priority::HIGH)
        this->priorQuantity++;

    //end of critical section

    return true;
}

bool PriorityQueue::dequeue(QueueElement *element){
    if(isBufferEmpty()){
        return false;
    }

    std::lock_guard<std::mutex> guard(this->mutex);

    //start of critical section
    *element = this->buffer[this->head];
    this->head = (this->head + 1) % QUEUE_CAPACITY;
    this->size--;
    if(element->priority == Priority::HIGH)
        this->priorQuantity--;

    //end of critical section

    return true;
}

bool PriorityQueue::isBufferFull(){
    std::lock_guard<std::mutex> guard(this->mutex);
    return this->size == QUEUE_CAPACITY;
}

bool PriorityQueue::isBufferEmpty(){
    std::lock_guard<std::mutex> guard(this->mutex);
    return this->size == 0;
}

void PriorityQueue::displayQueue(){
    int id, pri;
    std::lock_guard<std::mutex> guard(this->mutex);

    printf("HEAD-- ");
    id = this->head;
    for(int i = 0; i < this->size; i++){
        if(this->buffer[id].priority == Priority::HIGH)
            pri = 'H';
        else
            pri = 'L';

        printf("%d(%c) ", this->buffer[id].value, pri);
        id = (id + 1) % QUEUE_CAPACITY;
    }
    printf("--TAIL");
    printf("\n");

}

QueueElement::QueueElement(int value, Priority priority){
    this->value = value;
    this->priority = priority;
}