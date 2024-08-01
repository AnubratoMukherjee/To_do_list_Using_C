#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    int id;
    char description[256];
    struct Task* next;
} Task;

Task* head = NULL;
int current_id = 1;

Task* createTask(const char* description) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (!newTask) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newTask->id = current_id++;
    strcpy(newTask->description, description);
    newTask->next = NULL;
    return newTask;
}

void addTask(const char* description) {
    Task* newTask = createTask(description);
    if (!head) {
        head = newTask;
    } else {
        Task* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newTask;
    }
    printf("Task added successfully\n");
}

void deleteTask(int id) {
    if (!head) {
        printf("No tasks to delete\n");
        return;
    }
    if (head->id == id) {
        Task* temp = head;
        head = head->next;
        free(temp);
        printf("Task deleted successfully\n");
        return;
    }
    Task* current = head;
    Task* previous = NULL;
    while (current && current->id != id) {
        previous = current;
        current = current->next;
    }
    if (!current) {
        printf("Task not found\n");
        return;
    }
    previous->next = current->next;
    free(current);
    printf("Task deleted successfully\n");
}

void viewTasks() {
    if (!head) {
        printf("No tasks to display\n");
        return;
    }
    Task* temp = head;
    while (temp) {
        printf("ID: %d, Description: %s\n", temp->id, temp->description);
        temp = temp->next;
    }
}

void freeTasks() {
    Task* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void displayMenu() {
    printf("To-Do List Application\n");
    printf("1. Add Task\n");
    printf("2. Delete Task\n");
    printf("3. View Tasks\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int choice;
    char description[256];
    int id;

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter task description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0'; 
                addTask(description);
                break;
            case 2:
                printf("Enter task ID to delete: ");
                scanf("%d", &id);
                deleteTask(id);
                break;
            case 3:
                viewTasks();
                break;
            case 4:
                freeTasks();
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
