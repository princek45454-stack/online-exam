#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_Q 10

struct Question {
    char question[200];
    char optionA[50];
    char optionB[50];
    char optionC[50];
    char optionD[50];
    char correct;
};

struct Question q[MAX_Q];
int totalQ = 0;
int examCode;
int examTime;

void generateCode() {
    srand(time(0));
    examCode = rand() % 9000 + 1000;
}

void hostPanel() {
    int ch;
    char pass[20];

    printf("\nEnter Host Password: ");
    scanf("%s", pass);

    if (strcmp(pass, "admin123") != 0) {
        printf("Invalid Password!\n");
        return;
    }

    do {
        printf("\n--- HOST PANEL ---");
        printf("\n1. Set Question Paper");
        printf("\n2. Set Exam Time");
        printf("\n3. Generate Exam Code");
        printf("\n0. Exit");
        printf("\nChoice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("Enter number of questions (max 10): ");
            scanf("%d", &totalQ);

            for (int i = 0; i < totalQ; i++) {
                printf("\nQ%d: ", i + 1);
                getchar();
                gets(q[i].question);

                printf("A: ");
                gets(q[i].optionA);
                printf("B: ");
                gets(q[i].optionB);
                printf("C: ");
                gets(q[i].optionC);
                printf("D: ");
                gets(q[i].optionD);

                printf("Correct Option (A/B/C/D): ");
                scanf(" %c", &q[i].correct);
            }
        }

        else if (ch == 2) {
            printf("Set exam time (minutes): ");
            scanf("%d", &examTime);
        }

        else if (ch == 3) {
            generateCode();
            printf("Generated Exam Code: %d\n", examCode);
        }

    } while (ch != 0);
}

void studentPanel() {
    int code;
    int score = 0;
    char ans;

    printf("\nEnter Exam Code: ");
    scanf("%d", &code);

    if (code != examCode) {
        printf("Invalid Exam Code!\n");
        return;
    }

    printf("\nExam Started! Time Limit: %d minutes\n", examTime);

    for (int i = 0; i < totalQ; i++) {
        printf("\n\nQ%d: %s", i + 1, q[i].question);
        printf("\nA. %s", q[i].optionA);
        printf("\nB. %s", q[i].optionB);
        printf("\nC. %s", q[i].optionC);
        printf("\nD. %s", q[i].optionD);
        printf("\nAnswer: ");
        scanf(" %c", &ans);

        if (ans == q[i].correct)
            score++;
    }

    printf("\nExam Finished!");
    printf("\nYour Score: %d / %d\n", score, totalQ);

    FILE *fp = fopen("results.txt", "a");
    fprintf(fp, "Score: %d/%d\n", score, totalQ);
    fclose(fp);
}

int main() {
    int choice;

    do {
        printf("\n\n===== ONLINE EXAM SYSTEM =====");
        printf("\n1. Host Login");
        printf("\n2. Student Login");
        printf("\n0. Exit");
        printf("\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1)
            hostPanel();
        else if (choice == 2)
            studentPanel();

    } while (choice != 0);

    return 0;
}
