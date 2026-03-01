#include "header.h"

int validation(char *argv[], int argc, node **head)
{
    /* At least one file is required */
    if (argc < 2)
    {
        return 4;
    }

    /* Check all the files */
    for (int i = 1; i < argc; i++)
    {
        if (is_txt_file(argv[i]) == FAILURE)
        {
            printf("❌ %-8s : %s : Not a .txt file\n", "Error", argv[i]);
            continue;
        }

        /* Open file to check the file status */
        FILE *fp = fopen(argv[i], "r");
        if (!fp)
        {
            printf("❌ %-8s : No such File in Directory %s\n", "Error", argv[i]);
            continue;
        }

        /* Check empty file */
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0)
        {
            printf("❌ %-8s : %s is an empty file\n", "Error", argv[i]);
            fclose(fp);
            continue;
        }

        fclose(fp);  

        /* Allocate new node */
        node *new = malloc(sizeof(node));
        if (!new)
        {
            printf("❌ %-8s : Memory Allocation failed!!!!!\n", "Error");
            return FAILURE;
        }

        strcpy(new->fname, argv[i]);
        new->link = NULL;

        /* If head is NULL, insert directly */
        if (*head == NULL)
        {
            *head = new;
            continue;
        }

        /* Check for duplicate file */
        node *temp = *head;
        while (temp)
        {
            if (strcmp(temp->fname, argv[i]) == 0)
            {
                printf("⚠️  %-8s : %s is a duplicate file\n", "Warning", argv[i]);
                free(new);
                new = NULL;
                break;
            }
            temp = temp->link;
        }

        if (new == NULL)
            continue;

        /* Insert at beginning */
        new->link = *head;
        *head = new;
    }
    return SUCCESS;
}