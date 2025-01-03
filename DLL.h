#ifndef SLL_H
#define SLL_H

#define failure  0
#define success  1
typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
}dlist;

int store_list1(char *str,dlist **head,dlist **tail);
int insert_at_last(dlist **head,dlist**tail,int data);
int insert_at_first(dlist **head, dlist **tail, int data);
void print_list(dlist *head);
int addition(dlist **head1, dlist **head2,dlist **tail1,dlist **tail2,dlist **res_head,dlist **res_tail);
int subtraction(dlist **head1, dlist **head2,dlist **tail1,dlist **tail2 ,dlist **res_head,dlist **res_tail);
int multiplication(dlist **head1, dlist **head2,dlist **tail1,dlist **tail2 ,dlist **res_head,dlist **res_tail,dlist **res2_head,
dlist **res2_tail,dlist **res3_head,dlist **res3_tail);
int division(dlist **head1, dlist **head2,dlist **tail1,dlist **tail2 ,dlist **res_head,dlist **res_tail);
#endif
