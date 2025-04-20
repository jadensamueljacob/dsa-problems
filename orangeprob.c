#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIDS 100
#define MAXMESSAGES 100

typedef struct {
    char ID[10];
    char messagecontent[200];
} Message;

typedef struct {
    int userID;
    char name[50];
    Message messages[MAXMESSAGES];
    int countofmessages;
} User;

User users[MAXIDS];
int totalUsers = 0;

void creatingnewuser(int uID, char *uname) {
    users[totalUsers].userID = uID;
    strcpy(users[totalUsers].name, uname);
    users[totalUsers].countofmessages = 0;
    totalUsers++;
}

void sending(int senderID, char *msgcontent) {
    for (int i = 0; i < totalUsers; i++) {
        if (users[i].userID == senderID) {
            int msgIndex = users[i].countofmessages;
            strcpy(users[i].messages[msgIndex].ID, users[i].name);
            strcpy(users[i].messages[msgIndex].messagecontent, msgcontent);
            users[i].countofmessages++;
            return;
        }
    }
}

void displayinghistory(int uID) {
    for (int i = 0; i < totalUsers; i++) {
        if (users[i].userID == uID) {
            if (users[i].countofmessages == 0) {
                printf("No messages found for user ID %d\n", uID);
                return;
            }
            printf("Chat History for User ID %d:\n", uID);
            for (int j = 0; j < users[i].countofmessages; j++) {
                printf("%d: %s\n", j + 1, users[i].messages[j].messagecontent);
            }
            return;
        }
    }
    printf("User ID %d not found!\n", uID);
}

int main() {
    int numberOfUsers, uID;
    char uname[50];
    int totalMessages;
    int senderID;
    char msgcontent[200];

    printf("Enter number of users to create: ");
    scanf("%d", &numberOfUsers);

    for (int i = 0; i < numberOfUsers; i++) {
        printf("Enter User ID: ");
        scanf("%d", &uID);
        printf("Enter Username: ");
        scanf("%s", uname);
        creatingnewuser(uID, uname);
    }

    printf("Enter number of messages to send: ");
    scanf("%d", &totalMessages);

    for (int i = 0; i < totalMessages; i++) {
        printf("Enter Sender ID: ");
        scanf("%d", &senderID);
        printf("Enter Message Content: ");
        scanf(" %[^\n]", msgcontent);
        sending(senderID, msgcontent);
    }

    for (int i = 0; i < numberOfUsers; i++) {
        printf("Enter User ID to display chat history: ");
        scanf("%d", &uID);
        displayinghistory(uID);
    }

    return 0;
}
