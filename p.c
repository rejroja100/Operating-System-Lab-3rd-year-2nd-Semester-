#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for close(), read(), write()
#include <fcntl.h>   // for open()

// Function to copy a file
void copy_file() {
    char source[100], dest[100];
    int source_fd, dest_fd;
    char buffer[1024];
    int bytes_read;
    
    printf("Enter source file name: ");
    scanf("%s", source);
    printf("Enter destination file name: ");
    scanf("%s", dest);
    
    // Open source file (read only)
    source_fd = open(source, O_RDONLY);
    if (source_fd == -1) {
        printf("Error: Cannot open source file\n");
        return;
    }
    
    // Create destination file (write only, create if not exists, truncate if exists)
    dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        printf("Error: Cannot create destination file\n");
        close(source_fd);
        return;
    }
    
    // Copy data from source to destination
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        write(dest_fd, buffer, bytes_read);
    }
    
    // Close both files
    close(source_fd);
    close(dest_fd);
    
    printf("File copied successfully!\n");
}

// Function to create a new file
void create_file() {
    char filename[100];
    int fd;
    char content[1000];
    
    printf("Enter file name to create: ");
    scanf("%s", filename);
    
    // Create the file
    fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        printf("Error: File already exists or cannot be created\n");
        return;
    }
    
    printf("Enter content (press Enter then Ctrl+D when done):\n");
    getchar(); // Clear newline
    fgets(content, sizeof(content), stdin);
    
    // Write content to file
    write(fd, content, strlen(content));
    
    close(fd);
    printf("File created successfully!\n");
}

// Function to delete a file
void delete_file() {
    char filename[100];
    
    printf("Enter file name to delete: ");
    scanf("%s", filename);
    
    if (unlink(filename) == 0) {
        printf("File deleted successfully!\n");
    } else {
        printf("Error: Cannot delete file (file may not exist)\n");
    }
}

// Function to move/rename a file
void move_file() {
    char source[100], dest[100];
    int source_fd, dest_fd;
    char buffer[1024];
    int bytes_read;
    
    printf("Enter source file name: ");
    scanf("%s", source);
    printf("Enter new file name/location: ");
    scanf("%s", dest);
    
    // Try to rename first (if same filesystem)
    if (rename(source, dest) == 0) {
        printf("File moved successfully!\n");
        return;
    }
    
    // If rename fails, copy and delete
    printf("Renaming failed, copying and deleting...\n");
    
    // Open source file
    source_fd = open(source, O_RDONLY);
    if (source_fd == -1) {
        printf("Error: Cannot open source file\n");
        return;
    }
    
    // Create destination file
    dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        printf("Error: Cannot create destination file\n");
        close(source_fd);
        return;
    }
    
    // Copy data
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        write(dest_fd, buffer, bytes_read);
    }
    
    // Close files
    close(source_fd);
    close(dest_fd);
    
    // Delete source file
    if (unlink(source) == 0) {
        printf("File moved successfully!\n");
    } else {
        printf("File copied but could not delete source\n");
    }
}

// Main menu
int main() {
    int choice;
    
    while(1) {
        printf("\n===== FILE OPERATIONS MENU =====\n");
        printf("1. Copy file\n");
        printf("2. Create file\n");
        printf("3. Delete file\n");
        printf("4. Move file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                copy_file();
                break;
            case 2:
                create_file();
                break;
            case 3:
                delete_file();
                break;
            case 4:
                move_file();
                break;
            case 5:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}