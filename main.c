#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100
#define MAX_RESOURCES 50

// Custom data type using CS50-style typedef struct
typedef struct {
    int id;
    char title[MAX_STRING];
    char author[MAX_STRING];
    char subject[MAX_STRING];
} Resource;

// Function prototypes
void add_resource(Resource repository[], int *count);
void display_resources(const Resource repository[], int count);
void search_by_subject(const Resource repository[], int count);
void save_to_file(const Resource repository[], int count, const char *filename);

int main(void) {
    Resource repository[MAX_RESOURCES];
    int count = 0;
    int choice;

    while (1) {
        printf("\n====================================\n");
        printf(" EDUCATIONAL RESOURCE REPOSITORY\n");
        printf("====================================\n");
        printf("1. Add New Resource\n");
        printf("2. View All Resources\n");
        printf("3. Search Resources by Subject\n");
        printf("4. Export Resources to File\n");
        printf("5. Exit\n");
        printf("Enter choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting...\n");
            break;
        }
        getchar(); // Clear trailing newline from buffer

        switch (choice) {
            case 1:
                add_resource(repository, &count);
                break;
            case 2:
                display_resources(repository, count);
                break;
            case 3:
                search_by_subject(repository, count);
                break;
            case 4:
                save_to_file(repository, count, "repository.txt");
                break;
            case 5:
                printf("Exiting system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please select 1-5.\n");
        }
    }
    return 0;
}

void add_resource(Resource repository[], int *count) {
    if (*count >= MAX_RESOURCES) {
        printf("\nError: Repository capacity reached (%d items).\n", MAX_RESOURCES);
        return;
    }

    Resource new_res;
    new_res.id = *count + 1;

    printf("\nEnter Resource Title: ");
    fgets(new_res.title, MAX_STRING, stdin);
    new_res.title[strcspn(new_res.title, "\n")] = '\0'; // Trim newline

    printf("Enter Author/Instructor: ");
    fgets(new_res.author, MAX_STRING, stdin);
    new_res.author[strcspn(new_res.author, "\n")] = '\0';

    printf("Enter Subject (e.g., CS50, Math, Physics): ");
    fgets(new_res.subject, MAX_STRING, stdin);
    new_res.subject[strcspn(new_res.subject, "\n")] = '\0';

    repository[*count] = new_res;
    (*count)++;

    printf("Success: Resource added with ID #%d!\n", new_res.id);
}

void display_resources(const Resource repository[], int count) {
    if (count == 0) {
        printf("\nRepository is currently empty.\n");
        return;
    }

    printf("\n%-5s %-30s %-25s %-20s\n", "ID", "Title", "Author", "Subject");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-30s %-25s %-20s\n", 
               repository[i].id, 
               repository[i].title, 
               repository[i].author, 
               repository[i].subject);
    }
}

void search_by_subject(const Resource repository[], int count) {
    if (count == 0) {
        printf("\nRepository is currently empty.\n");
        return;
    }

    char query[MAX_STRING];
    printf("\nEnter subject to search for: ");
    fgets(query, MAX_STRING, stdin);
    query[strcspn(query, "\n")] = '\0';

    int found = 0;
    printf("\n--- Search Results for '%s' ---\n", query);
    for (int i = 0; i < count; i++) {
        // Case-sensitive substring search (CS50 Week 2 / string techniques)
        if (strstr(repository[i].subject, query) != NULL) {
            printf("ID: %d | Title: %s | Author: %s\n", 
                   repository[i].id, 
                   repository[i].title, 
                   repository[i].author);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching resources found for subject '%s'.\n", query);
    }
}

void save_to_file(const Resource repository[], int count, const char *filename) {
    // Basic File I/O (CS50 Week 4)
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "ID: %d | Title: %s | Author: %s | Subject: %s\n",
                repository[i].id, 
                repository[i].title, 
                repository[i].author, 
                repository[i].subject);
    }

    fclose(file);
    printf("Saved %d item(s) to '%s' successfully!\n", count, filename);
}
