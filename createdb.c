#include "header.h"

int createdb(m_node **arr, node *head)
{
    char buff[50];
    int index;
    int s_found, m_found;

    /* Traverse file list */
    while (head)
    {
        /* Skip already indexed files (after Update) */
        if (is_file_present(head->link, head->fname))
        {
            head = head->link;
            continue;
        }

        FILE *fp = fopen(head->fname, "r");
        if (!fp)
        {
            perror("Error");
            head = head->link;
            continue;
        }

        /* Read words from file */
        while (fscanf(fp, "%49s", buff) != EOF)
        {
            /* Hash index calculation */
            if (buff[0] >= 'a' && buff[0] <= 'z')
                index = buff[0] - 'a';

            else if (buff[0] >= 'A' && buff[0] <= 'Z')
                index = buff[0] - 'A';

            else if (isdigit(buff[0]))
                index = 26;

            else
                index = 27;

            m_node *mtemp = arr[index];
            m_node *mprev = NULL;
            m_found = 0;

            /* Search main list */
            while (mtemp)
            {
                if (strcmp(mtemp->word, buff) == 0)
                {
                    s_node *stemp = mtemp->slink;
                    s_node *sprev = NULL;
                    s_found = 0;

                    /* Search sub list */
                    while (stemp)
                    {
                        if (strcmp(stemp->file, head->fname) == 0)
                        {
                            stemp->wcount++;
                            s_found = 1;
                            break;
                        }
                        sprev = stemp;
                        stemp = stemp->slink;
                    }

                    /* New file for existing word */
                    if (!s_found)
                    {
                        s_node *snew = malloc(sizeof(s_node));
                        if (!snew)
                        {
                            fclose(fp);
                            return FAILURE;
                        }

                        strcpy(snew->file, head->fname);
                        snew->wcount = 1;
                        snew->slink = NULL;

                        sprev->slink = snew;
                        mtemp->fcount++;
                    }

                    m_found = 1;
                    break;
                }
                mprev = mtemp;
                mtemp = mtemp->mlink;
            }

            /* New word */
            if (!m_found)
            {
                s_node *snew = malloc(sizeof(s_node));
                m_node *mnew = malloc(sizeof(m_node));

                if (!mnew || !snew)
                {
                    free(mnew);
                    free(snew);
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(snew->file, head->fname);
                snew->wcount = 1;
                snew->slink = NULL;

                strcpy(mnew->word, buff);
                mnew->fcount = 1;
                mnew->slink = snew;
                mnew->mlink = NULL;

                if (arr[index] == NULL)
                    arr[index] = mnew;
                else
                    mprev->mlink = mnew;
            }
        }

        fclose(fp);
        head = head->link;
    }

    return SUCCESS;
}
