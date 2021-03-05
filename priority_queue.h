#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>

const int INF = INT16_MAX;

typedef struct Node
{
    int id;
    int weight;
    Node *link;
} * Node_T;

class PriorityQueue
{
public:
    PriorityQueue(int capacity = 0);
    ~PriorityQueue();
    PriorityQueue(const PriorityQueue &);
    void set_capacity(int);
    int get_size() const;
    int get_capacity() const;
    void increment_size();
    void decrement_size();
    void insert(const Node_T &);
    Node_T peek_minimum() const;
    Node_T delete_minimum();
    bool is_empty() const;
    bool is_full() const;
private:
    int size;
    int capacity;
    Node_T *queue;
    void create_queue(int);
};

PriorityQueue::PriorityQueue(int capacity)
{
    create_queue(capacity);
    size = 0;
}

PriorityQueue::~PriorityQueue()
{
    delete[] queue;
}

PriorityQueue::PriorityQueue(const PriorityQueue &x)
{
    set_capacity(x.capacity);
    queue = new Node_T[get_capacity()];
    if (get_size() >= x.size) {
        for (int i = 1; i <= x.size; i++) {
            queue[i] = x.queue[i];
        }
    }
    else {
        for (int i = 1; i <= get_size(); i++) {
            queue[i] = x.queue[i];
        }
    }
}

void PriorityQueue::set_capacity(int capacity)
{
    this->capacity = capacity;
}

void PriorityQueue::create_queue(int capacity)
{
    set_capacity(capacity);
    queue = new Node_T[get_capacity()];
}

int PriorityQueue::get_size() const
{
    return size;
}

int  PriorityQueue::get_capacity() const
{
    return capacity;
}

void PriorityQueue::increment_size()
{
    size++;
}

void PriorityQueue::decrement_size()
{
    size--;
}

void PriorityQueue::insert(const Node_T &item)
{
    if (is_full()) {
        std::cerr << "Queue is full: Insertion is not possible. \n";
        exit(EXIT_FAILURE);
    }
    increment_size();
    queue[get_size()] = item;
    int i = get_size();
    int p = i / 2;
    while (p > 1 && (queue[p] > queue[i])) {
        std::swap(queue[i], queue[p]);
        i = p;
        p /= 2;
    }
}

Node_T PriorityQueue::peek_minimum() const
{
    return queue[1];
}

Node_T PriorityQueue::delete_minimum()
{
    if (is_empty()) {
        std::cerr << "Queue is empty: Deletion is not possible.\n";
        exit(EXIT_FAILURE);
    }
    Node_T item = queue[1];
    queue[1] = queue[get_size()];
    queue[get_size()] = 0;
    decrement_size();
    bool flag = false;
    int i = 1, lchild = 0, rchild = 0, x = 0, y = 0;
    while ((flag == false) && (i < get_size())) {
        lchild = 2 * i;
        rchild = 2 * i + 1;
        if (lchild <= get_size())
            x = queue[lchild]->weight;
        else
            x = INF;
        if (rchild <= get_size())
            y = queue[rchild]->weight;
        else
            y = INF;
        if (queue[i]->weight <= x && queue[i]->weight <= y) {
            flag = true;
        }
        else if (x < y && queue[i]->weight > x) {
            std::swap(queue[i], queue[lchild]);
            i = lchild;
        }
        else if (y < x && queue[i]->weight > y) {
            std::swap(queue[i], queue[rchild]);
            i = rchild;
        }
    }
    return item;
}

bool PriorityQueue::is_empty() const
{
    return get_size() == 0;
}

bool PriorityQueue::is_full() const
{
    return get_size() >= get_capacity();
}

#endif /* PRIORITY_QUEUE */
