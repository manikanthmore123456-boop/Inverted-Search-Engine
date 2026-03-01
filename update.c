#include "header.h"

int update(m_node **arr, node **head)
{
    char bkpfile[100];

    printf("x----------------------------------------------x\n");
    printf("|➡️  Enter the backup file name: ");
    scanf("%99s", bkpfile);
    printf("x----------------------------------------------x\n");

    if (is_txt_file(bkpfile) == FAILURE)
    {
        printf("\n⚠️  %-8s : Please enter a valid .txt file\n", "Warning");
        return FAILURE;
    }

    FILE *fp = fopen(bkpfile, "r");
    if (!fp)
    {
        perror("File open failed");
        return FAILURE;
    }

    char check_bkp[50];
    if (fscanf(fp, " %49[^\n]\n", check_bkp) != 1)
    {
        fclose(fp);
        return FAILURE;
    }

    if (strcmp(check_bkp, "BACK_UP_FILE") != 0)
    {
        printf("\n❌ %-8s : Invalid backup file\n", "Error");
        fclose(fp);
        return FAILURE;
    }

    char ch;
    if ((ch = getc(fp)) != '#')
    {
        printf("\n❌ %-8s : Invalid backup file\n", "Error");
        fclose(fp);
        return FAILURE;
    }

    fseek(fp, -2, SEEK_END);
    if ((ch = getc(fp)) != '#')
    {
        printf("\n❌ %-8s : Invalid backup file\n", "Error");
        fclose(fp);
        return FAILURE;
    }

    fseek(fp, 13, SEEK_SET);

    int index, w_count, f_count;
    char word[50], f_name[50], sep;

    while (fscanf(fp, " #%d;%49[^;];%d;", &index, word, &f_count) == 3)
    {
        m_node *mnew = malloc(sizeof(m_node));
        if (!mnew)
        {
            fclose(fp);
            return FAILURE;
        }

        strcpy(mnew->word, word);
        mnew->fcount = f_count;
        mnew->mlink = NULL;
        mnew->slink = NULL;

        /* insert main node */
        if (arr[index] == NULL)
        {
            arr[index] = mnew;
        }
        else
        {
            m_node *temp = arr[index];
            while (temp->mlink)
                temp = temp->mlink;
            temp->mlink = mnew;
        }

        s_node *spre = NULL;

        for (int i = 0; i < f_count; i++)
        {
            if (fscanf(fp, "%49[^;];%d%c", f_name, &w_count, &sep) != 3)
            {
                fclose(fp);
                return FAILURE;
            }

            /* If file already exists in head, IGNORE it completely */
            node *temp = *head;
            int already_present = 0;

            while (temp)
            {
                if (strcmp(temp->fname, f_name) == 0)
                {
                    already_present = 1;
                    break;
                }
                temp = temp->link;
            }

            /* Add to head ONLY if it was not present */
            if (!already_present)
            {
                node *up = malloc(sizeof(node));
                if (!up)
                {
                    fclose(fp);
                    return FAILURE;
                }
                strcpy(up->fname, f_name);
                up->link = *head;
                *head = up;
            }

            /* create sub node */
            s_node *snew = malloc(sizeof(s_node));
            if (!snew)
            {
                fclose(fp);
                return FAILURE;
            }

            strcpy(snew->file, f_name);
            snew->wcount = w_count;
            snew->slink = NULL;

            if (!mnew->slink)
                mnew->slink = snew;
            else
                spre->slink = snew;

            spre = snew;

            if (sep == '#')
                break;
        }
    }

    fclose(fp);
    return SUCCESS;
}
