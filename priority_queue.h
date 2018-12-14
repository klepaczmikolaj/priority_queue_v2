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
#include <condition_variable>

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

        /* Elementary queue operations */
        void enqueue(QueueElement element);
        void dequeue(QueueElement *element);
        bool isBufferFull();
        bool isBufferEmpty();

        /*Other methods*/
        void setType(QueueType type);
        void displayQueue();
        int getPriorQuantity();
    
    private:
        QueueType type;
        QueueElement buffer[QUEUE_CAPACITY];
        int head;
        int tail;
        int size;
        int priorQuantity;
        std::mutex mutex;
        std::condition_variable space_in_buffer;
        std::condition_variable buffer_empty;
};

#endif