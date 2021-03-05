#include "priority_queue.h"
#include <iostream>

int main()
{
    int V = 3;
    PriorityQueue pq(V + 1);
    for (int i = 1; i <= V; i++) {
        Node_T node = new Node;
        node->id = i;
        node->weight = 0;
        node->link;
        pq.insert(node);
    }

    for (int i = 1; i <= V; i++) {
        Node_T temp = pq.delete_minimum();
        std::cout << temp->id << std::endl;
    }
}
