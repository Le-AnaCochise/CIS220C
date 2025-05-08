// Ana Le
// Chpt5 PA

#include <stdio.h>
#include <stdlib.h>

// Define a Node structure for each element in the queue
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define a Queue structure to represent the queue implemented as a linked list
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create and initialize an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Enqueue operation: adds an item to the end of the queue, pseudocode found in PA 5.5.1
void enqueue(Queue* queue, int item) {
    // Allocate new node and assign data (newNode->next is set to NULL)
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newNode->data = item;
    newNode->next = NULL;
    
    if (queue->front == NULL) {
        // If the queue is empty, set front to the new node
        queue->front = newNode;
    } else {
        // Otherwise, link the new node at the end of the queue
        queue->rear->next = newNode;
    }
    // Update the rear pointer to the new node
    queue->rear = newNode;
}

// Dequeue operation: removes and returns the item from the front of the queue, pseudocode found in PA 5.5.1
int dequeue(Queue* queue) {
    if (queue->front == NULL) {
        // Return 0 if the queue is empty
        printf("An item was not dequeued.\n"); //Displays that the item was not removed 
		return 0;
    }
    // Save the data from the front node and move the front pointer
    Node* temp = queue->front;
    int dequeuedItem = temp->data;
    queue->front = temp->next;
    // If the queue becomes empty, update the rear pointer to NULL
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp); // free memory for the dequeued node
	// Added
    printf("Item %d was removed from the queue.\n", dequeuedItem); 		// displays item removed 	// should be FIFO
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
	// Added
    if (queue->front == NULL) { 		// if front of queue linked list is empty or NULL, display empty
		printf("The queue is empty.\n");
	}
	else { 		// if NOT empty, display NOT empty
		printf("The queue is not empty.\n");
	}
}

// Function to peek at the front item without removing it
int peek(Queue* queue) {
	// Added
    if (queue->front != NULL) { 		// if the front of the queue is not empty, displays front's data
		printf("The top item on the queue is: %d\n", queue->front->data);
	}
	else { 		// if front of queue linked list is empty or NULL, display empty
		printf("The queue is empty.\n");
	}
}

// Function to get the length of the queue
int getLength(Queue* queue) {
	// Added
	int length = 0;
	
    Node* currentN = queue->front; 		// current node = front of queue 
	while (currentN != NULL) { 		// Until there is nothing in queue
		length++;
		currentN = currentN->next; 		// iterates to the next node/position 
	}
	printf("The queue's length is: %d\n", length); // once while-loop ends, display length
}

// Function to traverse and display the queue
void displayQueue(Queue* queue) {
	// Added
    Node* currentN = queue->front; 		// current node = front of queue 
	while (currentN != NULL) { 		// Until there is nothing in queue
		printf("%d -> ", currentN->data); 		// display currentN's data
		currentN = currentN->next; 		// iterates to the next node/position 
	}
	printf("NULL\n"); 		// if queue is empty
}

int main() {
    Queue* queue = createQueue();
    
   // Implement the main method
   //Added
   displayQueue(queue); 		// Display the queue
   isEmpty(queue); 		// Call isEmpty to display if the queue is empty
   peek(queue); 		// Call peek and display the top item in the queue
   getLength(queue); 		// Display the queue's length
   enqueue(queue, 1); 		// Enqueue item 1 to queue
   enqueue(queue, 2); 		// Enqueue item 2 to queue 
   peek(queue); 		// Call peek and display the top item in the queue
   enqueue(queue, 3); 		// Enqueue item 3 to queue 
   getLength(queue); 		// Display the queue's length 
   dequeue(queue); 		// Dequeue an item from the queue and display the item's value
   peek(queue); 		// Call peek and display the top item in the queue
   enqueue(queue, 4); 		// Enqueue item 4 to queue
   displayQueue(queue); 		// Display the queue
   enqueue(queue, 5); 		// Enqueue item 5 to queue
   dequeue(queue); 		// Dequeue an item from the queue and display the item's value
   enqueue(queue, 6); 		// Enqueue item 6 to queue
   getLength(queue); 		// Display the queue's length
   displayQueue(queue); 		// Display the queue
   dequeue(queue); 		// Dequeue an item from the queue and display the item's value
   isEmpty(queue); 		// Call isEmpty to display if the queue is empty
   dequeue(queue); 		// Dequeue an item from the queue and display the item's value
   dequeue(queue); 		// Dequeue an item from the queue and display the item's value
   getLength(queue); 		// Display the queue's length
   dequeue(queue); 		// Dequeue an item from the queue and display the item's value
   dequeue(queue); 		// Dequeue an item from the queue and display the item's value
   isEmpty(queue); 		// Call isEmpty to display if the queue is empty
    
    // Free the queue structure (all nodes should have been dequeued by now)
    free(queue);
    
    return 0;
}
