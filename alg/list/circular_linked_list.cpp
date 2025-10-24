#include <iostream>
#include <string>
#include <limits>
#include <string.h>
#include <stdio.h> // For perror
#include <stdlib.h> // For malloc/free

struct linked_list {
	char *string;
	struct linked_list *prox;
};

typedef struct linked_list item;

void
free_list(item* head)
{
    item *actual = head->prox; // Start with the first actual item
    item *tb_removed = NULL;
    while (actual != head) {
        tb_removed = actual;
        actual = actual->prox;
        free(tb_removed->string);
        free(tb_removed);
    }
    // Finally, free the head dummy node itself
    free(head);
}

void
remove_item(item* head, int index)
{
    if (index <= 0) {
        std::cout << "You can't remove an item with an invalid index.\n" << std::endl;
        return;
    }

    item *actual = head;

    int i = 0;

    while ((i < (index - 1)) && (actual->prox != head)){
        actual = actual->prox;
        i++;
    }

    if (actual->prox == head){
        std::cout << "You can't remove an item that doesn't exist.\n" << std::endl;
        return;
    }

    item *tb_removed = actual->prox;

    actual->prox = tb_removed->prox;

    free(tb_removed->string);
    free(tb_removed);
}

void
add_item(item* head, int index, char* value)
{
    if (index <= 0) {
        std::cout << "Cannot insert at an invalid index. Please use an index of 1 or greater.\n" << std::endl;
        free(value); // Prevent memory leak if index is invalid
        return;
    }

    item *novo = (item*) (malloc(sizeof(item)));
    if (novo == NULL) {
        perror("Failed to allocate memory for new item");
        free(value); // Prevent memory leak on malloc failure
        return;
    }

    novo->string = value;

    item *actual = head;

    int i = 1;

    while ((i < index) && (actual->prox != head)){
        actual = actual->prox;
        i++;
    }

    novo->prox = actual->prox;
    actual->prox = novo;
}

void
print_list(item* head)
{
    item *actual = head->prox;

    if (actual == head){
        std::cout << "The list is empty.\n" << std::endl;
        return;
    }

    int i = 1;

    while (actual != head){
        printf("Item: %d -- Value: %s\n", i, actual->string);
        actual = actual->prox;
        i++;
    }
    std::cout << std::endl; // For better spacing
}

int
main()
{
    char x; //choice
    int index;

    item *head = (item*) (malloc(sizeof(item)));
    if (head == NULL) {
        perror("Failed to allocate memory for list head");
        return 1;
    }
    head->prox = head;

    std::cout << "Hi, select one of the following keys:\n" << std::endl;

    while (true) {
        std::cout << "[P] Print || [I] Insert || [D] Delete || [E] Exit\n" << std::endl;

        std::cin >> x;

        if (x == 'p' or x == 'P'){
            print_list(head);
        }
        else if (x == 'i' or x == 'I'){
            // cleaning the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            char *value = (char*) (malloc(sizeof(char) * 256));
            if (value == NULL) {
                perror("Failed to allocate memory for input string");
                continue; // Continue to next loop iteration
            }

            std::cout << "Write the string to add in the linked list:\n" << std::endl;

            if (fgets(value, 256, stdin) != NULL) {
                value[strcspn(value, "\n")] = '\0';
            } else {
                free(value); // Don't leak if fgets fails
                continue;
            }

            std::cout << "Now, write the index to insert the element:\n" << std::endl;
            std::cin >> index;

            if (std::cin.fail()) {
                std::cout << "Invalid index. Please enter a number.\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                free(value); // Free the allocated string before continuing
                continue;
            }

            add_item(head, index, value);
        }
        else if (x == 'd' or x == 'D'){
            std::cout << "Write the index of the item to delete:\n" << std::endl;
            std::cin >> index;
            
            if (std::cin.fail()) {
                std::cout << "Invalid index. Please enter a number.\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            remove_item(head, index);
        }
        else if (x == 'e' or x == 'E'){
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
        else{
            std::cout << "Pick one of the options listed.\n" << std::endl;
        }
    }

    free_list(head); // Deallocate the entire list

    return 0;
}