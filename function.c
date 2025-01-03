#include<stdio.h>
#include<stdlib.h>
#include "DLL.h"
int flag=0;
int insert_at_last(dlist **head,dlist **tail,int data){
     // Allocate memory for the new node
    dlist *new=malloc(sizeof(dlist));
    // Initialize the new node
    new->prev=NULL;
    new->next=NULL;
    new->data=data;
    if(new==NULL){
        return failure;// Allocation failed
    }
     // If the list is empty, set the new node as both head and tail
    if(*head == NULL){
       *head=new;
       *tail = new;
       return success;
    }
    dlist *temp=*head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
     // Use the tail pointer to insert at the end
    temp->next=new;
    new->prev=temp;
    *tail=new;
    return success;
}
int insert_at_first(dlist **head, dlist **tail, int data){
  // Allocates memory for a new node.

   dlist *new=malloc(sizeof(dlist));
    if(new == NULL){
        return failure;
    }
   // Sets the prev and next pointers of the new node to NULL.
   //Stores the data in the new node.
    new->prev=NULL;
    new->next=NULL;
    new->data=data;
    if(*head == NULL){
        *head=*tail=new;
        return success;
    }
    new->next=*head;
    (*head)->prev=new;
    *head=new;
   return success;
}

int dl_delete_first(dlist **head, dlist **tail)
{
    if(*head==NULL){
        return failure;
    }
     dlist *temp=*head;
     *head=(*head)->next;
     free(temp);
     return success;
}
int dl_delete_list(dlist **head, dlist **tail)
{
    if(*head == NULL){
       return failure;
    }
    while(*head!=NULL){
         dl_delete_first(head,tail);
    }
    return success;
}

int store_list1(char *str,dlist **head,dlist **tail){
   int i=0;
   int res;
   while(str[i]!='\0'){
      res=str[i]-'0';
      if(insert_at_last(head,tail,res)!=success){
         return failure;
      }
      i++;
   }
   return success;
}

int addition(dlist **head1, dlist **head2,dlist **tail1,dlist **tail2 ,dlist **res_head,dlist **res_tail){
   dlist *temp1=*tail1;
   dlist *temp2=*tail2;

   int num1,num2,carry=0,res=0;
   //Traverses both lists from the end (least significant digit).
   while(temp1!=NULL || temp2!=NULL || carry!=0){
      if(temp1==NULL){
        num1=0;
      }
      else{
       num1=temp1->data;
      }
      if(temp2==NULL){
        num2=0;
      }
      else{
        num2=temp2->data;
      }
      //Performs digit-by-digit addition with carry handling.
      res = num1 + num2 + carry;
      carry=res/10;
      res=res%10;
      //Inserts the result of each addition at the beginning of the res_head list.
      if(insert_at_first(res_head,res_tail,res)!=success){
         return failure;
      }
      if(temp1!=NULL)
      temp1=temp1->prev;
      if(temp2!=NULL)
      temp2=temp2->prev;
   }
   return success;
}
int compare(dlist **head1, dlist **head2){
   dlist *temp1=*head1;
   dlist *temp2=*head2;
   while(temp1!=NULL || temp2!=NULL){
      if(temp1->data <temp2->data){
         return -1;
      }
         temp1=temp1->next;
         temp2=temp2->next;
   }
   return success;
}
void swap(dlist **head1, dlist **head2,dlist **tail1,dlist **tail2){
   dlist *swap=*head1;
   dlist *swaptail=*tail1;
  // Uses a temporary variable to efficiently swap the head and tail pointers of both lists.
   *head1 = *head2;
   *head2 = swap;
   *tail1 = *tail2;
   *tail2 = swaptail;
   
}
void remove_zeros(dlist **head,dlist **tail){
   //Traverses the list and deletes the first node as long as its data is 0.
   dlist *temp=*head;
   while(temp->next!=NULL ){
      if(temp->data !=0){
         return;
      }
      else{
         dl_delete_first(head,tail);
      }
      temp=temp->next;
   }
}
int subtraction(dlist **head1, dlist **head2,dlist **tail1,dlist **tail2 ,dlist **res_head,dlist **res_tail){
   dlist *temp1=*tail1;
   dlist *temp2=*tail2;
   int num1,num2,borrow=0,res;
   int  count1=0,count2=0;
   // count nodes in both lists
   temp1=*head1;
   while(temp1!=NULL){
      temp1=temp1->next;
      count1++;
   }
   temp2= *head2;
   while(temp2!=NULL){
      temp2=temp2->next;
      count2++;
   }
   //determine which list represents the larger number
   if(count2>count1 ){
      flag=1;
      swap(head1,head2,tail1,tail2);
   }
   else if(count1==count2 && compare(head1,head2)==-1){
         flag=1;
        swap(head1,head2,tail1,tail2);
   }
   temp1= *tail1;
   temp2 = *tail2;
   // Perform subtraction  
   while(temp1!=NULL || temp2!=NULL ){
       num1 = (temp1 != NULL) ? temp1->data : 0;
        num2 = (temp2 != NULL) ? temp2->data : 0;
      if(borrow==1){
         num1=num1-1;
      }
      if(num1<num2){
         borrow=1;
         num1=num1+10;
      }
      else{
         borrow=0;
      }
      res=num1-num2;
      if(insert_at_first(res_head,res_tail,res)!=success){
         return failure;
      }
      if(temp1!=NULL)
      temp1=temp1->prev;
      if(temp2!=NULL)
      temp2=temp2->prev;
   }
   remove_zeros(res_head,res_tail);
   // handle the special case of 0
   if (*res_head == NULL) {
      insert_at_first(res_head, res_tail, 0);
   }
   return success;
}
int multiplication(dlist **head1, dlist **head2,dlist **tail1,dlist **tail2,dlist **res_head,dlist **res_tail,dlist **res2_head,
dlist **res2_tail,dlist **res3_head,dlist **res3_tail){
   dlist *temp1=*tail1, *temp2=*tail2;
   int carry=0,res=0;
   int count=0;
   while(temp2!=NULL){
      carry=0;
      for(int i=0;i<count;i++){
         insert_at_first(res2_head,res2_tail,0);
      }
    
      while(temp1!=NULL){
          res=(temp1->data * temp2->data )+ carry;
          carry=res/10;
          res=res%10;

          if(temp2->next==NULL){
            if(insert_at_first(res_head,res_tail,res)!=success){
              return failure;
            }
          }
          else{
            if(insert_at_first(res2_head,res2_tail,res)!=success){
            return failure;
          }
          }
          temp1=temp1->prev;
      }
      if(carry>0){
         if(insert_at_first(res_head,res_tail,carry)!=success){
            return failure;
          }
       }
      if(temp2->next!=NULL){
         
         if(addition(res_head,res2_head,res_tail,res2_tail,res3_head,res3_tail)!=success){
           return failure;
         }
         dl_delete_list(res_head,res_tail);
        *res_head=*res3_head;
        *res_tail=*res3_tail;
        dl_delete_list(res2_head,res2_tail);
       *res3_head=NULL;
       *res3_tail=NULL;
      }
      temp2=temp2->prev;
      temp1=*tail1;
      count++;
   }
   return success;
}
int division(dlist **head1, dlist **head2,dlist **tail1,dlist **tail2 ,dlist **res_head,dlist **res_tail){
   dlist *temp1=*head1;
   dlist *temp2=*head2;
   int num1=0,num2=0,sub;
   int count=0;
   while(temp1!=NULL){
      num1=(num1*10)+temp1->data;
      temp1=temp1->next;
   }
   printf("%d\n",num1);
   while(temp2!=NULL){
      num2=(num2*10)+temp2->data;
      temp2=temp2->next;
   }
    printf("%d\n",num2);
   if(num1<num2){
      if(insert_at_last(res_head,res_tail,0)!=success){
         return failure;
      }
   }
   if(num1==num2){
      if(insert_at_last(res_head,res_tail,1)!=success){
         return failure;
      }
   }
   if(num1>num2){
      sub=num1;
      count=0;
      while(sub>=num2){
        sub=sub-num2;  
        count++;
      }
      if(insert_at_last(res_head,res_tail,count)!=success){
         return failure;
      }
   }
   return success;
}

void print_list(dlist *head)
{
   if(flag==1){
       printf("-");
   }
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
      
      while (head)		
	   {
         printf("%d", head -> data);
		   head = head -> next;
      }
      printf("\n");
    }
}