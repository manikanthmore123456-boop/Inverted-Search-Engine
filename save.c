#include "header.h"

int save(m_node **arr)
{
    char bkpfname[100];
    FILE *fp;
    int choice;

    while (1)
    {
        printf("x----------------------------------------------x\n");
        printf("➡️  Enter the Backup_File name: ");
        scanf(" %99s", bkpfname);
        printf("x----------------------------------------------x\n");

        if (is_txt_file(bkpfname) == FAILURE)
        {
            printf("\n⚠️  %-8s : Please enter a valid \".txt\" file.\n", "Warning");
            continue;
        }

        fp = fopen(bkpfname, "r");
        if (fp)
        {
            fseek(fp, 0, SEEK_END);
            if (ftell(fp) == 0)
            {
                fclose(fp);
                break;
            }
            printf("\n⚠️  %-8s : Backup file already contains data\n", "Warning");
            printf("x----------------------------------------------x\n");
            printf(" [1]. Overwrite\n [2]. New_FILE\n [3]. Cancel\n");
            printf("x----------------------------------------------x\n");
            printf("➡️  Enter Your Choice: ");
            scanf(" %d", &choice);
            printf("x----------------------------------------------x\n");

            fclose(fp);

            if (choice == 1)
                break;
            else if (choice == 2)
                continue;
            else
                return FAILURE;

            fclose(fp);
            break;
        }
        else
        {
            break; // file doesn't exist → create new
        }
    }

    fp = fopen(bkpfname, "w");
    if (!fp)
    {
        perror("File open failed");
        return FAILURE;
    }

    fprintf(fp, "BACK_UP_FILE\n");

    for (int i = 0; i < 28; i++)
    {
        for (m_node *mnode = arr[i]; mnode; mnode = mnode->mlink)
        {
            int first = 1;
            for (s_node *snode = mnode->slink; snode; snode = snode->slink)
            {
                if (first)
                {
                    fprintf(fp, "#%d;%s;%d;%s;%d",
                            i, mnode->word, mnode->fcount,
                            snode->file, snode->wcount);
                    first = 0;
                }
                else
                {
                    fprintf(fp, ";%s;%d", snode->file, snode->wcount);
                }
            }
            fprintf(fp, "#\n");
        }
    }

    fclose(fp);
    printf("\n✅ %-8s : Data saved successfully\n", "INFO");
    return SUCCESS;
}
