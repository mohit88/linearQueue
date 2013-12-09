#include "queue.h"

Queue* create(int capacity, int elementSize){
	Queue* queue = calloc(1,sizeof(Queue));
	queue->data = calloc(capacity,elementSize);
	queue->capacity = capacity;
	queue->elementSize = elementSize;
	queue->front = -1;
	queue->rear = -1;
	return queue;
}

int isFull(Queue* queue){
	if(queue->capacity == queue->rear)return 1;
	return 0;
}

int enqueue(Queue* queue, void* element){
	if(isFull(queue)) return 0;
	if(queue->front == -1 && queue->rear == -1){
		queue->front = 0;
		queue->rear = 0;
	}
	memcpy(queue->data+(queue->rear*queue->elementSize),element,queue->elementSize);
	queue->rear += 1;
	return 1;
}

int isEmpty(Queue* queue){
	if(queue->rear == -1 && queue->front == -1) return 1;
	return 0;
}

void* dequeue(Queue *queue){
	void* result = calloc(1, queue->elementSize);;
	if(isEmpty(queue)) return NULL;
	queue->rear -= 1;
	memcpy(result, queue->data , queue->elementSize);
	if(queue->rear == 0){
		queue->front = -1;
		queue->rear = -1;
		return result;
	}
	memcpy(queue->data, queue->data + queue->elementSize,queue->elementSize*queue->rear);
	return result;
}

void dispose(Queue* queue){
	free(queue->data);
	free(queue);
}