#include<stdio.h>
#include "DLL.h"
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[]){
    dlist *head1 = NULL; //initialize the header to NULL
	dlist *tail1 = NULL;
    dlist *head2 = NULL; 
	dlist *tail2 = NULL; 
    dlist *res_head=NULL;
    dlist *res_tail=NULL;
    dlist *res2_head=NULL;
    dlist *res2_tail=NULL;
    dlist *res3_head=NULL;
    dlist *res3_tail=NULL;
    int ch;
    if(store_list1(argv[1], &head1, &tail1) != success){
        printf("Error: Invalid input for list1.\n");
        return 1; 
    }
    if(store_list1(argv[3],&head2,&tail2) != success){
        printf("Error: Invalid input for list2.\n");
        return 1; 
    }
    // print_list(head1);
    // print_list(head2);

    if(argv[2][0]=='+'){
       if(addition(&head1,&head2,&tail1,&tail2 ,&res_head,&res_tail)!=success){
          printf("Addition failed\n");
          return failure;
       }
    }
    else if(argv[2][0]=='-'){
        if(subtraction(&head1,&head2,&tail1,&tail2 ,&res_head,&res_tail)!=success){
            printf("Subtraction failed\n");
            return failure;
        }
        else{
           printf("DONE\n");
        }
    }
    else if(argv[2][0]=='x'){
        if(multiplication(&head1,&head2,&tail1,&tail2 ,&res_head,&res_tail,&res2_head,&res2_tail,&res3_head,&res3_tail)!=success){
            printf("multiplication failed\n");
            return failure;
        }
        else{
            printf("Multiplication successful\n");
        }
    }
    else if(argv[2][0]=='/'){
        if(division(&head1,&head2,&tail1,&tail2 ,&res_head,&res_tail)!=success){
            printf("division failed\n");
            return failure;
        }
        else{
           printf("Division Successful\n");
        }
    }
    print_list(res_head);
    
}
    
    

