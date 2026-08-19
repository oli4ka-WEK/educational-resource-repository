#include <stdio.h>
#include <string.h>

// Максимален брой символи за заглавие автор и предмет
#define MAX_STRING 100
// Максимален брой ресурси в хранилището
#define MAX_RESOURCES 50

// Структура обединяваща данните за един учебен ресурс
typedef struct {
    int id;
    char title[MAX_STRING];
    char author[MAX_STRING];
    char subject[MAX_STRING];
} Resource;

// Функция за добавяне на нов ресурс
void add_resource(Resource repository[], int *count) {
    if (*count >= MAX_RESOURCES) {
        printf("\nError: Repository capacity reached (%d items).\n", MAX_RESOURCES);
        return;
    }

    Resource new_res;
    new_res.id = *count + 1;

    printf("\nEnter Resource Title: ");
    fgets(new_res.title, MAX_STRING, stdin);
    new_res.title[strcspn(new_res.title, "\n")] = '\0';

    printf("Enter Author: ");
    fgets(new_res.author, MAX_STRING, stdin);
    new_res.author[strcspn(new_res.author, "\n")] = '\0';

    printf("Enter Subject (e.g., Biology, Math, Physics): ");
    fgets(new_res.subject, MAX_STRING, stdin);
    new_res.subject[strcspn(new_res.subject, "\n")] = '\0';

    repository[*count] = new_res;
    (*count)++;

    printf("Success: Resource added with ID #%d!\n", new_res.id);
}

// Функция за показване на всички ресурси
void display_resources(Resource repository[], int count) {
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

// Функция за търсене на ресурси по предмет
void search_by_subject(Resource repository[], int count) {
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

// Функция за записване на данните във файл
void save_to_file(Resource repository[], int count) {
    FILE *file = fopen("repository.txt", "w");
    if (file == NULL) {
        printf("Error: Could not save file.\n");
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
    printf("Saved %d item(s) to 'repository.txt' successfully!\n", count);
}

int main(void) {
    // Списък с ресурсите и брояч за тях
    Resource repository[MAX_RESOURCES];
    int count = 0;
    int choice;

    // Главно меню на програмата
    while (1) {
        printf("\n=== EDUCATIONAL RESOURCE REPOSITORY ===\n");
        printf("1. Add New Resource\n");
        printf("2. View All Resources\n");
        printf("3. Search Resources by Subject\n");
        printf("4. Save Resources to File\n");
        printf("5. Exit\n");
        printf("Enter choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting...\n");
            break;
        }
        getchar();

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
                save_to_file(repository, count);
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
