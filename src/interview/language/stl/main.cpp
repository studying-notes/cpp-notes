#include <iostream>

const int MAX_SIZE = 1000;

typedef struct {
  int elements[MAX_SIZE];
  int front, rear;
} CircularQueue;

int IsEmpty(CircularQueue *queue) {
  return queue->front == queue->rear;
}

int isFull(CircularQueue *queue) {
  return (queue->rear + 1) % MAX_SIZE == queue->front;
}

int EnQueue(CircularQueue *queue, int element) {
  if (isFull(queue))
    return 0;
  queue->elements[queue->rear] = element;
  queue->rear = (queue->rear + 1) % MAX_SIZE;
  return 1;
}

int DeQueue(CircularQueue *queue, int &element) {
  if (IsEmpty(queue))
    return 0;
  element = queue->elements[queue->front];
  queue->front = (queue->front + 1) & MAX_SIZE;
  return 1;
}

int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
