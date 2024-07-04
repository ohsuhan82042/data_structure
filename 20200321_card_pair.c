#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _stacknode {
  char card;
  struct _stacknode* link; 
} stack;

typedef stack* stack_pointer;

void init(stack_pointer* top) {
    *top = NULL;
}

int isempty(stack_pointer* top) {
    if (*top == NULL) {
        printf("stack is NULL\n");
        return 1;
    }
    return 0;
}

void push(stack_pointer* top, char item) {
    stack* temp = (stack*)malloc(sizeof(stack));
    temp->card = item;
    temp->link = *top;
    *top = temp; 
}

char pop(stack_pointer* top) {
    if (isempty(top)) {
        printf("Stack underflow!\n");
        exit(1); 
    }
    stack* temp = *top;
    char item = temp->card;
    *top = temp->link;
    free(temp);
    return item; 
}

int main() 
{
  char str[20];
  fgets(str,20,stdin);
  stack_pointer top;
  init(&top);
  for(int i =0;i<strlen(str);i++)
  {
    if (str[i] == '(' || str[i] == '[')
    {
      push(&top,str[i]);
    }
    else if (str[i]==')')
    {
      int k =0;
      while(pop(&top)!='(')
      {
        k++;
        if(isempty(&top)){
          printf("%d", 0);
          return 0;
        }
      }
      for (int i =0;i<k;i++)
      {
        push(&top,'[');
      }
    }
    else if (str[i]==']')
    {
      int j =0;
      while(pop(&top)!='[')
      {
        j++;
        if(isempty(&top)){
          printf("%d", 0);
          return 0;
        }
      }
      for (int i =0;i<j;i++)
      {
        push(&top,'(');
      }      
    }
  }

  if (isempty(&top))
  {
    printf("%d",1);
    return 1;
  }
  else
  {
  printf("%d", 0);
  return 0;
  }

}
