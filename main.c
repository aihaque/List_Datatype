#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static void pItemFreeFn(void *pItem)
{
    return;
}

static bool pComparator(void *pItem, void *pArg)
{
    return (pItem == pArg);
}

int main()
{
    List *pList1 = List_create();
    List *pList2 = List_create();
    List *pList3 = List_create();
    List *pList4 = List_create();
    List *pList5 = List_create();
    List *pList6 = List_create();
    List *pList7 = List_create();
    List *pList8 = List_create();
    List *pList9 = List_create();
    List *pList10 = List_create();
    List *pList11 = List_create();

    assert(pList1 != NULL);
    assert(List_count(pList1) == 0);
    assert(pList2 != NULL);
    assert(List_count(pList2) == 0);
    assert(pList3 != NULL);
    assert(List_count(pList3) == 0);
    assert(pList4 != NULL);
    assert(List_count(pList4) == 0);
    assert(pList5 != NULL);
    assert(List_count(pList5) == 0);
    assert(pList6 != NULL);
    assert(List_count(pList6) == 0);
    assert(pList7 != NULL);
    assert(List_count(pList7) == 0);
    assert(pList8 != NULL);
    assert(List_count(pList8) == 0);
    assert(pList9 != NULL);
    assert(List_count(pList9) == 0);
    assert(pList10 != NULL);
    assert(List_count(pList10) == 0);
    assert(pList11 == NULL);
    printf("10 empty list successfully created and during 11th creation it returns null as expected\n");
    assert(List_first(pList1) == NULL);
    assert(List_last(pList1) == NULL);
    assert(List_next(pList1) == NULL);
    assert(List_prev(pList1) == NULL);
    assert(List_curr(pList1) == NULL);
    assert(List_remove(pList1) == NULL);
    assert(List_trim(pList1) == NULL);
    List_concat(pList1,pList2); //pList2 get freed for future use
    List *pList12 = List_create(); //Now calling list create will not return NULL
    assert(List_count(pList12) == 0);
    assert(pList12 != NULL);
    assert(List_create() == NULL); //now not any list left free from the pool
    printf("all list current item moving fuction asserted for empty list case\n");

    int num1 = 1;
    int num2 = 2;
    int num3 = 3;

    assert(List_add(pList1,&num1) == 0);
    assert(List_add(pList2,&num2) == 0); //I asserted making LIST_MAX_NUM_NODES = 1 that it fails for ckecking node overload
    assert(List_first(pList1) == &num1);
    assert(List_last(pList1) == &num1);
    assert(List_curr(pList1) == &num1);
    assert(pList1->after_end == false);
    assert(pList1->before_start == false);
    assert(List_next(pList1) == NULL);
    assert(pList1->after_end == true);
    assert(List_prev(pList2) == NULL);
    assert(pList2->before_start == true);
    assert(List_prev(pList1) == &num1);
    assert(List_remove(pList1) == &num1);
    assert(List_trim(pList1) == NULL);
    assert(List_next(pList2) == &num2);
    assert(List_trim(pList2) == &num2);
    assert(List_remove(pList2) == NULL);
    assert(List_trim(pList2) == NULL);
    printf("all list current item moving verified add fuction--- asserted for single item list case\n");

    assert(List_add(pList1,&num1) == 0);
    assert(List_add(pList2,&num2) == 0);
    List_concat(pList1,pList2); //pList2 get freed for future use
    List *pList13 = List_create(); //Now calling list create will not return NULL
    assert(List_count(pList13) == 0);
    assert(pList13 != NULL);
    assert(List_curr(pList1) == &num1);
    assert(List_first(pList1) == &num1);
    assert(List_last(pList1) == &num2);
    assert(List_count(pList1) == 2);
    assert(List_count(pList2) == 0);
    printf("Concat verified for single item lists\n");
    assert(List_next(pList1) == NULL);
    assert(List_prev(pList1) == &num2);
    assert(List_prev(pList1) == &num1);
    assert(List_prev(pList1) == NULL);
    assert(List_next(pList1) == &num1);
    assert(List_next(pList1) == &num2);
    assert(List_next(pList1) == NULL);
    printf("Current moving verified for multiple items list\n");

    assert(List_trim(pList1) == &num2);
    assert(List_trim(pList1) == &num1);
    assert(List_trim(pList1) == NULL);

    assert(List_insert(pList1,&num3) == 0);
    assert(List_insert(pList1,&num2) == 0);
    assert(List_insert(pList1,&num1) == 0); 
    assert(List_curr(pList1) == &num1);

    printf("all list current item moving verified with insert fuction\n");

    List_free(pList1,pItemFreeFn);
    List_append(pList1,&num3);
    List_prepend(pList1,&num1);
    List_append(pList1,&num2);
    List_free(pList1,pItemFreeFn);
    assert(List_count(pList1) == 0);
    printf("list free succesfully verified\n");

    assert(List_search(pList1,pComparator,&num2) == NULL);
    assert(List_curr(pList1) == NULL);
    assert(pList1->after_end == true);

    List_append(pList1,&num3);
    List_prepend(pList1,&num1);
    List_add(pList1,&num2);
    List_first(pList1);
    assert(List_search(pList1,pComparator,&num2) == &num2);
    assert(List_curr(pList1) == &num2);

    assert(List_search(pList1,pComparator,&num1) == NULL);
    assert(List_curr(pList1) == NULL);
    assert(pList1->after_end == true); 

    assert(List_search(pList1,pComparator,&num3) == NULL);
    assert(List_curr(pList1) == NULL);
    assert(pList1->after_end == true);

    List_first(pList1);
    List_prev(pList1);
    assert(List_search(pList1,pComparator,&num1) == &num1);
    assert(List_curr(pList1) == &num1);
    printf("comparison succesfully verified\n");
    printf("Good Bye Have a great day\n");
    return 0;
}