#include <stdio.h>
#include <string.h>

void createFile()
{
    char filename[100];
    FILE *fp;
    printf("Enter file name: ");
    scanf("%s", filename);
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("File cannot be created!\n");
        return;
    }
    fclose(fp);
    printf("File created successfully.\n");
}

void copyFile()
{
    char s[100], d[100], buf[1024];
    size_t n;
    FILE *fs, *fd;
    printf("Enter source file: ");
    scanf("%s", s);
    printf("Enter destination file: ");
    scanf("%s", d);
    fs = fopen(s, "rb");
    if (!fs)
    {
        printf("Source file not found!\n");
        return;
    }
    fd = fopen(d, "wb");
    if (!fd)
    {
        printf("Destination file cannot be created!\n");
        fclose(fs);
        return;
    }
    while ((n = fread(buf, 1, sizeof(buf), fs)) > 0)
        fwrite(buf, 1, n, fd);
    fclose(fs);
    fclose(fd);
    printf("File copied successfully.\n");
}

void deleteFile()
{
    char f[100];
    FILE *fp;
    printf("Enter file name: ");
    scanf("%s", f);
    fp = fopen(f, "wb");
    if (!fp)
    {
        printf("File not found!\n");
        return;
    }
    fclose(fp);
    printf("File content deleted (simulated).\n");
}

void moveFile()
{
    char s[100], d[100], buf[1024];
    size_t n;
    FILE *fs, *fd;
    printf("Enter source file: ");
    scanf("%s", s);
    printf("Enter destination file: ");
    scanf("%s", d);
    fs = fopen(s, "rb");
    if (!fs)
    {
        printf("Source file not found!\n");
        return;
    }
    fd = fopen(d, "wb");
    if (!fd)
    {
        fclose(fs);
        printf("Destination file cannot be created!\n");
        return;
    }
    while ((n = fread(buf, 1, sizeof(buf), fs)) > 0)
        fwrite(buf, 1, n, fd);
    fclose(fs);
    fclose(fd);
    fs = fopen(s, "wb");
    if (fs)
        fclose(fs);
    printf("File moved successfully (simulated).\n");
}

void renameFile()
{
    char o[100], nn[100], buf[1024];
    size_t n;
    FILE *fo, *fn;

    printf("Enter old file name: ");
    scanf("%s", o);

    printf("Enter new file name: ");
    scanf("%s", nn);

    fo = fopen(o, "rb");

    if (!fo)
    {
        printf("Old file not found!\n");
        return;
    }

    fn = fopen(nn, "wb");

    if (!fn)
    {
        fclose(fo);
        printf("New file cannot be created!\n");
        return;
    }

    while ((n = fread(buf, 1, sizeof(buf), fo)) > 0)
    {
        fwrite(buf, 1, n, fn);
    }

    fclose(fo);
    fclose(fn);

    if (remove(o) == 0)
        printf("Old file deleted successfully.\n");
    else
        printf("Old file could not be deleted.\n");

    printf("File renamed successfully (simulated).\n");
}

void updateFile()
{
    char f[100], data[200];
    FILE *fp;
    printf("Enter file name: ");
    scanf("%s", f);
    fp = fopen(f, "ab");
    if (!fp)
    {
        printf("File not found!\n");
        return;
    }
    getchar();
    printf("Enter text to append: ");
    fgets(data, sizeof(data), stdin);
    fwrite(data, 1, strlen(data), fp);
    fclose(fp);
    printf("File updated successfully.\n");
}

// void updateFile()
// {
//     char f[100], u[100], buf[1024];
//     size_t n;

//     FILE *fp, *fu;

//     printf("Enter file to update: ");
//     scanf("%99s", f);

//     printf("Enter file to append: ");
//     scanf("%99s", u);

//     /* Open target file in append-binary mode */
//     fp = fopen(f, "ab");

//     if (!fp)
//     {
//         printf("File cannot be opened!\n");
//         return;
//     }

//     /* Open source file in read-binary mode */
//     fu = fopen(u, "rb");

//     if (!fu)
//     {
//         printf("Append file not found!\n");
//         fclose(fp);
//         return;
//     }

//     /* Copy binary data from source to target */
//     while ((n = fread(buf, 1, sizeof(buf), fu)) > 0)
//     {
//         if (fwrite(buf, 1, n, fp) != n)
//         {
//             printf("Error while updating file!\n");
//             fclose(fu);
//             fclose(fp);
//             return;
//         }
//     }

//     fclose(fu);
//     fclose(fp);

//     printf("File updated successfully.\n");
// }

int main()
{
    int c;
    do
    {
        printf("\n1.Create\n2.Copy\n3.Delete\n4.Move\n5.Rename\n6.Update\n7.Exit\nChoice: ");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            createFile();
            break;
        case 2:
            copyFile();
            break;
        case 3:
            deleteFile();
            break;
        case 4:
            moveFile();
            break;
        case 5:
            renameFile();
            break;
        case 6:
            updateFile();
            break;
        case 7:
            printf("Program End.\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (c != 7);
    return 0;
}
