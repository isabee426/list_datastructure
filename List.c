/*
Isabella Shapland
ishaplan
pa1
*/

#include "list.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct List{
    Node *front;
    Node *back;
    Node *cursor;
    int length;
    int index;
}List;

//construct and make all the arguments of the list null
List newList(void){
    List *L = calloc(1, sizeof(List));
    assert(L!= NULL);
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}
//delete every item in the list then 
void freeList(List *pL){ //use by passing a pointer to List
    if((*pL) != NULL){
        Node *curr = (*pL)->front;
        Node *temp;
        while (curr != NULL) { 
            temp = curr;
            curr = curr->next;
            free(temp);
        }
        free(*pL);
        *pL = NULL;
    }
}

int length(List L){ //returns -1 on bad list
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      return -1;
   } //return the length
   return(L->length);
}

int index(List L){ //if the problem arises from list index check the return val
    if( L==NULL ){
      fprintf(stderr, "List Error: calling index() on NULL List reference\n");
      return -1;
   }
    if(L->index < 0){ //cant get index if its undefined?
        printf(, "index() not defined\n");
        return -1;
    }
    else{ //return the cursor index
        return L->index;
    }
}
//gets the front of the list
int front(List L){
    if(L==NULL || L->front == NULL){
      fprintf(stderr, "List Error: front()\n");
      return -1;
   }
    if(L->length > 0){
        return L->front->value;
   }
}

int back(List L){ 
    //the last thing here should never be true but its good practice to include
    if(L==NULL || L->back == NULL){
        fprintf(stderr,"List Error: back()\n");
        return -1;
   }
    if(L->length > 0){
        return L->back->value;
   }
}

int get(List L){
    //check not empty and index is not negative
    if(L->length > 0 && L->index >= 0){
        return L->cursor->value;
    }
    else{
        printf(stderr,"List Error: get()\n");
        return -1; //return val? when error??
    }
}

void set(List L, int x){ //WHEN USING THE SET FUNCTION PLEASE CHANGE INDEX FIRST
    // Pre: length()>0, index()>=0
    if(L == NULL || L->length <= 0 || L->index < 0){
        fprintf(stderr,"List Error: moveBack()\n");
        return;
    }
    //Overwrites the cursor element’s data with x.
    else{
        L->cursor->value = x;
    }
}
//If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveFront(List L){
    if(L == NULL || L->length <= 0){ //idk why i do less than but ik i dont rlly have to include that
        fprintf(stderr,"List Error: moveFront()\n");
        return;
    }
    else if( L->length == 0){
        printf("List Error: empty no front for moveFront()\n");
        return;
    }
    else{
        L->index = 0;
        set(L, L->front->value);
    }
}
 //If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void moveBack(List L){
    if(L == NULL || L->length <= 0){
        fprintf(stderr,"List Error: moveBack()\n");
        return;
    }
    else if(L->length == 0){
        return;
    }
    else{
        L->index = (L->length)-1;
        set(L, L->back->value);
    }
}

void movePrev(List L){
    // if cursor is defined and at 
    // front, cursor becomes undefined; 
    if(L->index == 0 && L->cursor != NULL){
        L->index = -1;
        L->cursor = NULL;
        return;
    }
    // If cursor is defined and not at front, move cursor one 
    // step toward the front of L;
    if(L->index > 0 && L->cursor != NULL){
        L->index--;
        set(L, L->cursor->prev->value);
        return;
    }
    //if cursor is undefined 
    // do nothing
    else{
        return;
    }
}

void moveNext(List L){
    // If cursor is defined and not at back, move cursor one 
    // step toward the back of L;
    if(L->index >= 0 && L->cursor != NULL){
        L->index++;
        set(L, L->cursor->next->value);
        return;
    }
    // if cursor is defined and at 
    // back, cursor becomes undefined; 
    else if(L->index == (L->length)-1 && L->cursor != NULL){
        L->index = -1;
        L->cursor = NULL;
        return;
    }
    //if cursor is undefined 
    // do nothing
    else{
        return;
    }
    
}

void prepend(List L, int x){
    Node *newN = calloc(1, sizeof(Node));
    newN->value = x;
    newN->next = NULL;
    newN->prev = NULL;
    if(L->length == 0){
        L->front = newN;
        L->back = newN; 
    }
    else{
        newN->next = L->front;
        L->front->prev = newN;
        L->front = newN;
    }
    L->length++;
    if(L->index >=0){
        L->index++;
    }
}

void append(List L, int x){
    Node *newN = calloc(1, sizeof(Node));
    newN->value = x;
    newN->next = NULL;
    newN->prev = NULL;
    if(L->length == 0){
        L->front = newN;
        L->back = newN; 
    }
    else{
        newN->prev = L->back;
        L->back->next = newN;
        L->back = newN;
    }
    L->length++;
}

void insertBefore(List L, int x){
    if(L->index >= 0 && L->length > 0){
        if(L->index == 0){
            prepend(L, x);
        }
        else if(L->index > 0){
            Node *newN = calloc(1, sizeof(Node));
            newN->value = x;
            L->cursor->prev->next = newN;
            newN->prev = L->cursor->prev;
            L->cursor->prev = newN;
            newN->next = L->cursor;
            L->index++;
        }
        
    }
    else{
        fprintf(stderr, "insert before did not work");
        return;
    }
    
    
}

void insertAfter(List L, int x){
    if(L->index >= 0 && L->length > 0){
        if(L->index == (L->length)-1){
            append(L, x);
        }
        else if(L->index > 0){
            Node *newN = calloc(1, sizeof(Node));
            newN->value = x;
            L->cursor->next->prev = newN;
            newN->next = L->cursor->next;
            L->cursor->next = newN;
            newN->prev = L->cursor;
        }
    } else {
        fprintf(stderr, "insert before did not work");
        return;
    }
}

void deleteFront(List L){
    if(L->length >0){
        Node *temp = L->front;
        if(L->length == 1){
            L->back = NULL;
            L->front = NULL;
        }
        else{
            L->front = L->front->next;
            L->front->prev = NULL;
        }
        if(L->index == 0){
            L->cursor = NULL;
            L->index = -1;
            free(temp);
            L->length--;
            return;
        }
        free(temp);
        L->length--;
        L->index--;
    }
    else{
        fprintf("deleteFront did not work. List length too short");
    }
}

void deleteBack(List L){
    if(L->length >0){
        Node *temp = L->back;
        if(L->length == 1){
            L->back = NULL;
            L->front = NULL;
        }
        else{
            L->back = L->back->prev;
            L->back->next = NULL;
        }
        if(L->index == (L->length)-1){
            L->cursor = NULL;
            L->index = -1;
        }
        free(temp);
        L->length--;
    }
    else{
        fprintf("deleteFront did not work. List length too short");
    }
}


// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
    // Pre: length()>0, index()>=0
    if(L == NULL || L->length <= 0 || L->index < 0){
        fprintf(stderr,"List Error: delete()\n");
        return;
    }
    if (L->index == 0){
        deleteFront(L);
    }
    else if(L->index == (L->length)-1){
        deleteBack(L);
    }
    else{
        Node* temp = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        free(temp);
        L->length--;
        L->cursor = NULL;
        L->index = -1;
    }
}

void clear(List L){
    moveFront(L);
    while(L->length != 0){
        deleteBack(L);
    }
}

bool equals(List A, List B){
    moveFront(A);
    moveFront(B);
    do{
        Node *a = A->cursor;
        Node *b = B->cursor;
        if(a->value != b->value){
            return false;
        }
        moveNext(A);
        moveNext(B);
    while(A->cursor != NULL && B->cursor != NULL)}
    return true;
}
void printList(FILE * out, List L){
    moveFront(L);
    while(L->cursor != NULL){
        int val = get(L);
        fprintf(out, "%d ", val);
        moveNext(L);
    }
}
void copyList(List L){
    List *copy = newList();
    moveFront(L);
    while(L->cursor != NULL){
        int val = get(L);
        append(copy, val);
        moveNext(L);
    }
    copy->cursor = NULL;
    copy->index = -1;
}
