#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLIP_SIZE 1000

char clip[CLIP_SIZE];

void create(char *f) {
    FILE *p = fopen(f, "w");
    if (!p) {
        printf("Error: could not create file.\n");
        return;
    }
    fclose(p);
}

void add(char *f) {
    FILE *p = fopen(f, "w");
    if (!p) {
        printf("Error: could not open file for writing.\n");
        return;
    }
    char s[256];
    while (fgets(s, sizeof(s), stdin) && strcmp(s, "END\n") != 0) {
        fputs(s, p);
    }
    fclose(p);
}

void append(char *f) {
    FILE *p = fopen(f, "a");
    if (!p) {
        printf("Error: could not open file for appending.\n");
        return;
    }
    char s[256];
    while (fgets(s, sizeof(s), stdin) && strcmp(s, "END\n") != 0) {
        fputs(s, p);
    }
    fclose(p);
}

void view(char *f) {
    FILE *p = fopen(f, "r");
    if (!p) {
        printf("Error: file not found.\n");
        return;
    }
    int c;
    while ((c = fgetc(p)) != EOF) {
        putchar(c);
    }
    fclose(p);
}

void copy(char *f) {
    FILE *p = fopen(f, "r");
    if (!p) {
        printf("Error: file not found.\n");
        return;
    }
    int i = 0, c;
    while (i < CLIP_SIZE - 1 && (c = fgetc(p)) != EOF) {
        clip[i++] = (char)c;
    }
    clip[i] = '\0';

    if (c != EOF) {
        printf("Warning: file too large, clipboard truncated to %d bytes.\n", CLIP_SIZE - 1);
    }

    fclose(p);
}

void paste(char *f) {
    FILE *p = fopen(f, "w");
    if (!p) {
        printf("Error: could not open file for pasting.\n");
        return;
    }
    fprintf(p, "%s", clip);
    fclose(p);
}

void del(char *f) {
    if (remove(f) != 0) {
        printf("Error: could not delete file.\n");
    }
}

int main() {
    int c;
    char f[256];

    while (1) {
        printf("\n1.Create 2.Add 3.Append 4.View 5.Copy 6.Paste 7.Delete 8.Exit > ");

        if (scanf("%d", &c) != 1) {
            // Clear invalid input from the buffer
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Invalid input, please enter a number.\n");
            continue;
        }
        getchar(); // consume leftover newline

        if (c == 8) break;

        if (c < 1 || c > 7) {
            printf("Invalid choice.\n");
            continue;
        }

        printf("File: ");
        fgets(f, sizeof(f), stdin);
        f[strcspn(f, "\n")] = 0;

        if (c == 1) create(f);
        else if (c == 2) add(f);
        else if (c == 3) append(f);
        else if (c == 4) view(f);
        else if (c == 5) copy(f);
        else if (c == 6) paste(f);
        else if (c == 7) del(f);
    }

    return 0;
}
