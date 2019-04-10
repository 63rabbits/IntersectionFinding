#ifndef IntersectionFinding_h
#define IntersectionFinding_h

//////////////////////////////////////////////////
typedef struct Element {
    int id;
    struct Element *next;
} Element_t;

//////////////////////////////////////////////////
int findIntersection(Element_t *list1, Element_t *list2);
int lengthOfList(Element_t *list);

#endif
