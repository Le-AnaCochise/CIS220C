// Ana Le
// Chpt6 PA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define structure to represent the key-value pair (Item)
typedef struct Item {
    char *key;  
    char *value;  
    struct Item *next;  
} Item;

// Define structure to represent the hash table
typedef struct HashTable {
    Item **hashTable;  
    int length;  
} HashTable;

// Function to create a new Item (key-value pair)
Item* createItem(char *key, char *value) {
    Item *newItem = (Item*)malloc(sizeof(Item));  
    newItem->key = strdup(key);  
    newItem->value = strdup(value);  
    newItem->next = NULL;  
    return newItem;
}

// Function to create a new hash table with a specified number of buckets
HashTable* createHashTable(int size) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));  
    table->length = size;  
    table->hashTable = (Item**)malloc(sizeof(Item*) * size);  

    for (int i = 0; i < size; i++) {
        table->hashTable[i] = NULL;  
    }
    return table;
}

// Hash function to compute the index for a given key
int hash(char *key) {
	// Added
	int stringHash = 0; 		// sets initial value to 0
    int multiplier = 13; 		// sets multiplier as 13
    while (*key) { 		// while the current character != '\0' (null terminator)
        stringHash = (stringHash * multiplier) + *key; 		// updates stringHash based on the pseudoCode provided in Figure 6.8.3 in zyBooks
        key++; 		// iterate to next character of the key 
    }
    return stringHash; 		// returns the hash value 
    
}

// Function to insert a key-value pair into the hash table, pseudocode found in Figure 6.3.1
int hashInsert(HashTable *table, char *key, char *value) {
    int bucketIndex = hash(key) % table->length;
   
    Item *currentItem = table->hashTable[bucketIndex];
    Item *previousItem = NULL;

    while (currentItem != NULL) {
        if (strcmp(currentItem->key, key) == 0) {
            free(currentItem->value);
            currentItem->value = strdup(value);
            return 1;
        }
        previousItem = currentItem;
        currentItem = currentItem->next;
    }

    Item *newItem = (Item *)malloc(sizeof(Item));
    newItem->key = strdup(key);
    newItem->value = strdup(value);
    newItem->next = NULL;

    if (table->hashTable[bucketIndex] == NULL) {
        table->hashTable[bucketIndex] = newItem;
    } else {
        previousItem->next = newItem;
    }
    return 1;  
}

// Function to search for the specified key and return the corresponding value, pseudocode found in Figure 6.3.1
char *hashGet(HashTable *table, char *key) {
    int bucketIndex = hash(key) % table->length;
    

    Item *item = table->hashTable[bucketIndex];

    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
        item = item->next;
    }
    return NULL;
}

// Function to remove the key-value pair from the hash table, pseudocode found in Figure 6.3.1 
int hashRemove(HashTable *table, char *key) {
    int bucketIndex = hash(key) % table->length;
    
    Item *currentItem = table->hashTable[bucketIndex];
    Item *previousItem = NULL;

    while (currentItem != NULL) {
        if (strcmp(currentItem->key, key) == 0) {
            if (previousItem == NULL) {
                table->hashTable[bucketIndex] = currentItem->next;
            } else {
                previousItem->next = currentItem->next;
            }
            free(currentItem->key);
            free(currentItem->value);
            free(currentItem);
            return 1;
        }
        previousItem = currentItem;
        currentItem = currentItem->next;
    }
    return 0;
}

// Function to print the contents of the hash table
// Update the function to display the hash for each key-value pair
void printTable(HashTable *table) {
    for (int i = 0; i < table->length; i++) {  
        printf("Bucket %d: ", i);  
        Item *currentItem = table->hashTable[i];  
        if (currentItem == NULL) {  
            printf("empty\n");  
        } else {
            while (currentItem != NULL) {
				// Added
                int hashValue = hash(currentItem->key); 		// calculates the hash value for each key
                printf("[Hash is: %d, key is: %s, value is: %s] ", hashValue, currentItem->key, currentItem->value);
                currentItem = currentItem->next;
            }
            printf("\n");  
        }
    }
}

// Main function to test the hash table
// Implement the main function per the assignment instructions
int main() {
    // Create a hash table with 5 buckets
	HashTable *table = createHashTable(5);
	
	// Added
	hashInsert(table, "keyA1", "value1"); 		// 1. Insert the following key-value pair: keyA1, value1
	hashInsert(table, "keyB2", "value2"); 		// 2. Insert the following key-value pair: keyB2, value2
	hashInsert(table, "keyC3", "value3"); 		// 3. Insert the following key-value pair: keyC3, value3
	hashInsert(table, "keyD23", "value23"); 		// 4. Insert the following key-value pair: keyD23, value23
	hashInsert(table, "keyE45", "value45"); 		// 5. Insert the following key-value pair: keyE45, value45
	hashInsert(table, "keyF52", "value52"); 		// 6. Insert the following key-value pair: keyF52, value52
	
	// 7. Display the hash table contents
	printf("\nHashTable contents:\n");
	printTable(table);
	printf("\n");
	
	// 8. Remove keyF52. If the key was found, displays "keyF52 was removed", otherwise, "keyF52 was not found"
	if (hashRemove(table, "keyF52")) { 		// true
		printf("keyF52 was removed\n");
	} 
	else {
		printf("keyF52 was not found\n");
	}
	printf("\n");
	
	// 9. Attempt to get a non-existing key’s value: keyZ6
	char *value = hashGet(table, "keyZ6");
	if (value) {
		printf("Key found: %s\n", value);
	} 
	else {
		printf("keyZ6 was not found\n");
	}
	printf("\n");
	
	// 10. Get an existing key: keyC3.
	value = hashGet(table, "keyC3");
	if (value) {
		printf("%s\n", value);
	} 
	else {
		printf("keyC3 not found in table.\n");
	}
	
	hashInsert(table, "keyG18", "value18"); 		// 11. Insert the following key-value pair: keyG18, value18
	hashInsert(table, "keyH7", "value7"); 		// 12. Insert the following key-value pair: keyH7, value7
	hashInsert(table, "keyI33", "value33"); 		// 13. Insert the following key-value pair: keyI33, value33
	
	// 14. Update keyD23 value to newvalue23
	hashInsert(table, "keyD23", "newvalue23");
	
	//15. Display the hash table contents
	printf("\nHashTable contents after additional inserts, removal, and update:\n");
	printTable(table);
	
	
    for (int i = 0; i < table->length; i++) {
        Item *currentItem = table->hashTable[i];
        while (currentItem != NULL) {
            Item *temp = currentItem;
            currentItem = currentItem->next;
            free(temp->value);
            free(temp);
        }
    }

    free(table->hashTable);  
    free(table);  

    return 0;
}