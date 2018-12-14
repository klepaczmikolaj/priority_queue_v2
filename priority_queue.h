/*
  ************* Mikołaj Klepacz *************
  ****** Priority queue implementation ******

  This library allows to create and work with priority queue.
  The queue itself is implemented using monitors 

*/


#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#define QUEUE_CAPACITY 10
#define HIGH_PRI_PROBABILITY 4

#include <mutex>
#include <thread>

enum class QueueType {NORMAL, PRIORITY};
enum class Priority {LOW, HIGH};

class QueueElement{
    public: 
        QueueElement();
        QueueElement(int value, Priority priority);
        void randomizeValues();
        Priority priority;
        int value;
};

class PriorityQueue{
    public:
        PriorityQueue();
        PriorityQueue(QueueType type);
        void setType(QueueType type);
        /* Elementary queue operations */
        bool enqueue(QueueElement element);
        bool dequeue(QueueElement *element);
        bool isBufferFull();
        bool isBufferEmpty();
        void displayQueue();
        int getPriorQuantity();
    
    private:
        std::mutex mutex;
        QueueType type;
        QueueElement buffer[QUEUE_CAPACITY];
        int head;
        int tail;
        int size;
        int priorQuantity;
};

#endif