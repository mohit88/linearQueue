#include "testUtils.h"
#include "queue.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed
Queue* integerQueue;
void setup(){
	integerQueue = create(3, sizeof(int));
}

void tearDown(){
	dispose(integerQueue);
}

int areQueueEqual(Queue* expected,Queue* actual){
	int result = expected->elementSize == actual->elementSize
					&& expected->capacity == actual->capacity 
					&& expected->front	== actual->front 
					&& expected->rear	== actual->rear;
	if(!result) return result;
	if(expected->front == -1 && expected->rear == -1) return result;
	return 0 == memcmp(expected->data, actual->data,(expected->rear-1)*(expected->elementSize));
}



void test_create_initial_queue_of_capacity_3(){
	Queue* actual = create(3,sizeof(int));
	int data[3] = {0,0,0};
	Queue expected = {&data,3,sizeof(int),-1,-1};
	ASSERT(areQueueEqual(&expected,actual));
}

void test_inserting_element_in_integer_queue(){
	int data[3] = {8,0,0};
	int _8 = 8;
	Queue expected = {&data,3,sizeof(int),0,1};
	ASSERT(enqueue(integerQueue, &_8));
	ASSERT(areQueueEqual(&expected,integerQueue));
}

void test_inserting_integer_in_full_queue(){
	int data[3] = {0,0,0};
	int _8 = 8;
	Queue expected = {&data,3,sizeof(int),0,3};
	integerQueue->front = 0;
	integerQueue->rear = 3;
	ASSERT(0 == enqueue(integerQueue, &_8));
	ASSERT(areQueueEqual(&expected,integerQueue));
}

void test_deleting_integer_from_queue(){
	int data[3] = {8,0,0};
	int* result;
	Queue expected = {&data,3,sizeof(int),0,2};
	int* intData = (int*)integerQueue->data;
	intData[0] = 4; intData[1] = 8;
	integerQueue->front = 0;
	integerQueue->rear = 3;
	result = (int*)dequeue(integerQueue);
	ASSERT(*result == 4);
	ASSERT(areQueueEqual(&expected,integerQueue));
}

void test_deleting_integer_from_empty_queue(){
	int data[3] = {0,0,0};
	void* result;
	result = dequeue(integerQueue);
	ASSERT(result == NULL);
}

void test_deleting_integer_from_queue_having_only_one_element(){
	int data[3] = {0,0,0};
	int* result;
	Queue expected = {&data,3,sizeof(int),-1,-1};
	int* intData = (int*)integerQueue->data;
	intData[0] = 4;
	integerQueue->front = 0;
	integerQueue->rear = 1;
	result = (int*)dequeue(integerQueue);
	ASSERT(*result == 4);
	ASSERT(integerQueue->front == -1);
	ASSERT(integerQueue->rear == -1);
}
