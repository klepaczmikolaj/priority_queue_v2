#include <iostream>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include "priority_queue.h"


QueueElement::QueueElement(int value, Priority priority){
    this->value = value;
    this->priority = priority;
}

QueueElement::QueueElement(){
    this->value = 0;
    this->priority = Priority::LOW;
}

void QueueElement::randomizeValues(){
    std::srand(std::time(nullptr));
    this->value = std::rand() % 10;
    std::rand() % HIGH_PRI_PROBABILITY == 0 ? 
        this->priority = Priority::HIGH : this->priority = Priority::LOW;
}

PriorityQueue::PriorityQueue(){
    this->type = QueueType::NORMAL;
    this->head = 0;
    this->tail = 0;
    this->size = 0;
    this->priorQuantity = 0;
}

PriorityQueue::PriorityQueue(QueueType type){
    this->type = type;
    this->head = 0;
    this->tail = 0;
    this->size = 0;
    this->priorQuantity = 0;
}

void PriorityQueue::setType(QueueType type){
    this->type = type;
}

bool PriorityQueue::enqueue(QueueElement element){
    std::unique_lock<std::mutex> lock(mutex);
    if(this->size == QUEUE_CAPACITY)
        space_in_buffer.wait(lock);

    //start of critical section
    if(this->type == QueueType::PRIORITY && element.priority == Priority::HIGH){
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
    lock.unlock();
    buffer_empty.notify_all();

    return true;
}

bool PriorityQueue::dequeue(QueueElement *element){
    std::unique_lock<std::mutex> lock(mutex);
    if(this->size == 0)
        buffer_empty.wait(lock);

    //start of critical section
    *element = this->buffer[this->head];
    this->head = (this->head + 1) % QUEUE_CAPACITY;
    this->size--;
    if(element->priority == Priority::HIGH)
        this->priorQuantity--;

    //end of critical section
    lock.unlock();
    space_in_buffer.notify_all();

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

int PriorityQueue::getPriorQuantity(){
    return this->priorQuantity;
}