//////////////////////////////////////////////////
//
//                  Find Intersection !!
//                        ↓
//      *->*->*->*->*->*->●->*->*->*->*->*
//                       /
//             *->*->*->*
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "IntersectionFinding.h"

//////////////////////////////////////////////////
int findIntersection(Element_t *list1, Element_t *list2) {
    // Block illegal parameters.
    if (list1 == NULL) return -1;
    if (list2 == NULL) return -1;
    
    int lengthOfList1 = lengthOfList(list1);
    int lengthOfList2 = lengthOfList(list2);
    
    Element_t *e1 = list1;
    Element_t *e2 = list2;
    if (lengthOfList1 > lengthOfList2) {
        for (int i=0; i<(lengthOfList1 - lengthOfList2); i++) {
            e1 = e1->next;
        }
    }
    else {
        for (int i=0; i<(lengthOfList2 - lengthOfList1); i++) {
            e2 = e2->next;
        }
    }
    
    while ((e1 != NULL) && (e2 != NULL)) {
        if (e1 == e2) {
            return e1->id;
        }
        e1 = e1->next;
        e2 = e2->next;
    }
    
    return -1;
}

int lengthOfList(Element_t *head) {
    int length = 0;
    Element_t *e = head;
    while (e != NULL) {
        length++;
        e = e->next;
    }
    return length;
}
