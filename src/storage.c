//
// Created by Loïc Vanden Bossche on 12/11/2021.
//

#include "../headers/storage.h"

void appendToStorage(storageNode** headRef, item item){

    storageNode* newNode = (storageNode*) malloc(sizeof(storageNode));
    storageNode* last = *headRef;

    newNode->item = item;
    newNode->next = NULL;

    if(*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    while(last->next != NULL)
        last = last->next;

    last->next = newNode;
};

void printStorage(storageNode* node)
{
    printf("=== storageList ===\n");
    int i = 0;
    while (node != NULL) {
        printf("%d - %d %d %d \n", ++i, node->item.id, node->item.qty, node->item.durabitity);
        node = node->next;
    }
}