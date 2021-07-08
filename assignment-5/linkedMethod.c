#include<stdio.h>
#include <stdlib.h>
#include <string.h>

struct block {
    int value;
    struct block *next;
};

struct fileEntry {
    char *name;
    int start;
    int length;
};

struct block disk[30];
int freeSpace = 30;
struct fileEntry files[3];

int getEmptySlot();

int search(char *name);

void insert(char *name, int blocks);

void delete(char *name);

void displaySize();

void displayDisk();

void displayFiles();

int main() {
    int option;
    char *name = (char *) malloc(20 * sizeof(char));
    int blocks, start;

    int i;
    for (i = 0; i < 3; i++) {
        files[i].name = NULL;
    }
    for (i = 0; i < 30; i++) {
        disk[i].value = 0;
        disk[i].next = NULL;
    }

    printf("Linked File allocation\n");
    printf("\n1. Insert");
    printf("\n2. Delete");
    printf("\n3. Display disk");
    printf("\n4. Display files");
    while (1) {
        displaySize();
        printf("\n option: ");
        scanf_s("%d", &option);
        switch (option) {
            case 1:
                printf("Enter file name: ");
                getchar();
                gets_s(name, 20);
                printf("Enter number of blocks: ");
                scanf_s("%d", &blocks);
                insert(name, blocks);
                break;
            case 2:
                printf("Enter file name to delete: ");
                getchar();
                gets_s(name, 20);
                delete(name);
                break;
            case 3:
                displayDisk();
                break;
            case 4:
                displayFiles();
                break;
            default:
                exit(1);
        }
    }
}

int getEmptySlot() {
    int i;
    for (i = 0; i < 30; i++) {
        if (files[i].name == NULL)
            return i;
    }
    return -1;
}

int search(char *name) {
    int i;
    for (i = 0; i < 30; i++) {
        if (files[i].name != NULL && strcmp(files[i].name, name) == 0)
            return i;
    }
    return -1;
}

void insert(char *name, int blocks) {
    if (blocks > freeSpace) {
        printf("\nFile size too big\n");
        return;
    }
    if (search(name) != -1) {
        printf("\nCannot insert the file\n");
        return;
    }
    int start = -1;
    int i, j, allocated = 0;
    int prev = -1;
    for (i = 0; i < 30; i++) {
        if (disk[i].value == 0) {
            if (start == -1) {
                start = i;
            }
            disk[i].value = 1;
            if (prev != -1)
                disk[prev].next = &disk[i];
            allocated++;
            prev = i;
        }
        if (allocated == blocks) {
            disk[i].next = NULL;
            break;
        }
    }

    int slot = getEmptySlot();
    files[slot].name = malloc(0);
    strcpy(files[slot].name, name);
    files[slot].length = blocks;
    files[slot].start = start;
    freeSpace -= blocks;

    printf("Inserted\n");
}

void delete(char *name) {
    int pos;
    int size = 0;
    if ((pos = search(name)) == -1) {
        printf("\nFile not found\n");
        return;
    }
    disk[files[pos].start].value = 0;
    struct block *temp = disk[files[pos].start].next;
    while (temp != NULL) {
        temp->value = 0;
        size++;
        temp = temp->next;
    }
    freeSpace += size + 1;
    files[pos].name = NULL;
    printf("Deleted\n");

}

void displaySize() {
    printf("Free space in disk = %d", freeSpace);
}

void displayDisk() {
    int i;
    printf("\nDISK:\n\n\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
    for (i = 0; i < 30; i++) {
        if (i % 10 == 0)
            printf("\n%d\t", i);
        printf("%d\t", disk[i].value);

    }
    printf("\n");

}

void displayFiles() {
    int i;
    printf("Files in disk:\n");
    printf("Name\tStart\tLength\n\n");
    for (i = 0; i < 30; i++) {
        if (files[i].name != NULL) {
            printf("%s\t%4d\t%3d\n", files[i].name, files[i].start, files[i].length);
            printf("Blocks: %d -> ", files[i].start);
            struct block *temp = disk[files[i].start].next;
            while (temp != NULL) {
                printf("%d -> ", (temp - disk));
                temp = temp->next;
            }
            printf("NULL\n");
        }

    }

    printf("\n");
}