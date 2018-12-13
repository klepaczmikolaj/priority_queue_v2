/*
  ************* Mikołaj Klepacz *************
  ****** Priority queue implementation ******

  This library allows to create and work with priority queue.
  The queue itself is implemented using monitors 

*/


#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#define QUEUE_CAPACITY 10

#include <mutex>
#include <thread>

enum class QueueType {NORMAL, PRIORITY};
enum class Priority {LOW, HIGH};

class QueueElement{
    public: 
        QueueElement(int value, Priority priority);
        Priority priority;
        int value;
};

class PriorityQueue{
    public:
        PriorityQueue(QueueType type);
        ~PriorityQueue();
        /* Elementary queue operations */
        bool enqueue(QueueElement element);
        bool dequeue(QueueElement *element);
        bool isBufferFull();
        bool isBufferEmpty();
        void displayQueue();
    
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