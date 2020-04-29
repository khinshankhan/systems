#include <stdio.h>
#include <stdlib.h>
//struct declaration
struct node { int i; struct node *next;};

void print_list(struct node * current_node) {
  printf("ITEMS IN LINKED LIST:\n");
  while(current_node) {
    printf("%d -> ", (*current_node).i);
    current_node = (*current_node).next;
  }
  printf("NULL\n");
}

struct node * insert_front(struct node *current_node, int value){
  struct node *temp = (struct node *) malloc(sizeof(struct node));
  temp->i = value;
  temp->next = current_node;
  return temp;
}

struct node * free_list(struct node *current_node){
  struct node *temp = current_node;
  while (temp) {
    struct node *temp2 = temp->next;
    free(temp);
    temp = temp2;
  }
  current_node->next = 0;
  return 0;
}

int main () {
  printf("\nInserting %d\n", 4);
  struct node *list = insert_front(0, 4);
  print_list(list);
  int index;
  //Testing insert_front & print_list
  for(index = 3; index >= 0; index--){   
    printf("\nInsert: %d to front\n", index);
    list = insert_front(list, index);
    print_list(list);
  }
  //testing free_list and confirming list is reusable
  printf("\nList Freed\n");
  list = free_list(list);
  print_list(list);

  for(index = 3; index >= 0; index--){   
    printf("\nInsert: %d to front\n", index);
    list = insert_front(list, index);
    print_list(list);
  }

  printf("\nList Freed\n");
  list = free_list(list);
  print_list(list);

  printf("DONE!");
}
