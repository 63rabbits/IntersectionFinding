#include <unistd.h>
//#define checkMemoryLeak

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "IntersectionFinding.h"

//////////////////////////////////////////////////
void test(void);
Element_t *createList(int length);
bool createIntersection(Element_t *list1, Element_t *list2, int intersectionID1, int intersectionID2);
void destroyTwoLists(Element_t *list1, Element_t *list2);
Element_t *createElementForSLList(int value);

//////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    
#ifdef checkMemoryLeak
    while (true) {
        test();
        sleep(1);
    }
#else
    test();
#endif
    
    return EXIT_SUCCESS;
}

void test() {
    int length1 = 15;
    int length2 = 10;
    int intersectionID1 = 10;
    int intersectionID2 = 5;
    
    Element_t *list1 = createList(length1);
    if (list1 == NULL) {
        printf("error [%s] : could not creat a List1.\n", __func__);
        return;
    }
    Element_t *list2 = createList(length2);
    if (list2 == NULL) {
        printf("error [%s] : could not creat a List2.\n", __func__);
        return;
    }
    
    int id1 = findIntersection(list1, list2);
    if (id1 >= 0) {
        printf("[%s] find intersection. ID is %d.\n", __func__, id1);
    }
    else {
        printf("[%s] could not find intersection.\n", __func__);
    }
    
    //////////////////////////////
    bool c = createIntersection(list1, list2, intersectionID1, intersectionID2);
    if (!c) {
        printf("error [%s] : could not creat a Intersection ID = (%d, %d).\n", __func__, intersectionID1, intersectionID2);
        return;
    }
    
    int id2 = findIntersection(list1, list2);
    if (id2 >= 0) {
        printf("[%s] find intersection. ID is %d.\n", __func__, id2);
    }
    else {
        printf("[%s] could not find intersection.\n", __func__);
    }
    
    destroyTwoLists(list1, list2);
}

//////////////////////////////////////////////////
// for two linked list with intersection point.
Element_t *createList(int length) {
    // Block illegal parameters.
    if (length <= 0) return NULL;
    
    Element_t *head = NULL;
    Element_t *prev = NULL;
    Element_t *e = NULL;
    for (int i=0; i<length; i++) {
        e = createElementForSLList(i);
        if (i == 0) {
            head = e;
        }
        else {
            prev->next = e;
        }
        prev = e;
    }
    return head;
}

bool createIntersection(Element_t *list1, Element_t *list2, int intersectionID1, int intersectionID2) {
    // Block illegal parameters.
    if ((intersectionID1 < 0) || (intersectionID2 < 0)) return false;
    
    Element_t *prev1 = NULL;
    Element_t *prev2 = NULL;
    Element_t *e = NULL;
    Element_t *prev = NULL;
    Element_t *ie = NULL;
    
    // find prev element of intersection on list1.
    prev = NULL;
    e = list1;
    while (e != NULL) {
        if (e->id == intersectionID1) {
            prev1 = prev;
            ie = e;
            break;
        }
        prev = e;
        e = e->next;
    }
    
    // find prev element of intersection on list2.
    prev = NULL;
    e = list2;
    while (e != NULL) {
        if (e->id == intersectionID2) {
            prev2 = prev;
            break;
        }
        prev = e;
        e = e->next;
    }
    
    // Block illegal parameters.
    if ((prev1 == NULL) || (prev2 == NULL)) return false;
    
    // create intersection with two list.
    e = prev2->next;
    while (e != NULL) {
        Element_t *t = e->next;
        free(e);
        e = t;
    }
    prev2->next = prev1->next;
    
#ifdef DEBUG
    printf("\n");
    
    int count = 0;
    
    Element_t *e1 = list1;
    count = 0;
    while (e1 != NULL) {
        printf("[%s] List1 element %2d ID : %4d", __func__, count, e1->id);
        if (e1 == ie) {
            printf(" -> %d <- intersection.\n", e1->next->id);
        }
        else {
            if (e1->next != NULL) {
            printf(" -> %d\n", e1->next->id);
            }
            else {
                printf(" -> null\n");
            }
        }
        e1 = e1->next;
        count++;
    }
    
    printf("\n");
    
    Element_t *e2 = list2;
    count = 0;
    while (e2 != NULL) {
        printf("[%s] List2 element %2d ID : %4d", __func__, count ,e2->id);
        if (e2 == ie) {
            printf(" -> %d <- intersection.\n", e2->next->id);
        }
        else {
            if (e2->next != NULL) {
                printf(" -> %d\n", e2->next->id);
            }
            else {
                printf(" -> null\n");
            }
        }
        e2 = e2->next;
        count++;
    }
    
    printf("\n");
#endif
    
    return true;
}

void destroyTwoLists(Element_t *list1, Element_t *list2) {
    // mark elements of list1.
    if (list1 != NULL) {
        Element_t *e = list1;
        while (e != NULL) {
            e->id = -1;
            e = e->next;
        }
    }
    
    // destroy list2.
    if (list2 != NULL) {
        Element_t *e = list2;
        while (e != NULL) {
            if (e->id < 0) break;
            Element_t *t = e->next;
            free(e);
            e = t;
        }
    }
    
    // destroy list1.
    if (list1 != NULL) {
        Element_t *e = list1;
        while (e != NULL) {
            Element_t *t = e->next;
            free(e);
            e = t;
        }
    }
}

Element_t *createElementForSLList(int value) {
    Element_t *e = malloc(sizeof(Element_t));
    if (e == NULL) return NULL;
    
    e->id = value;
    e->next = NULL;
    
    return e;
}
