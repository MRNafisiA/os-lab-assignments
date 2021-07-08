#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message_buffer {
    long type;
    char text[100];
} message;

int main() {
    key_t key;
    int message_id;
    key = ftok("my-custom-queue", 65);
    message_id = msgget(key, 0666 | IPC_CREAT);
    msgrcv(message_id, &message, sizeof(message), 1, 0);
    printf("Data Received is : %s \n", message.text);
    msgctl(message_id, IPC_RMID, NULL);
    return 0;
}