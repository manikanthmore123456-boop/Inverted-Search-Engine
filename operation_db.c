#include "header.h"

/* Function to check valid .txt file or not */
int is_txt_file(char *filename)
{
    int len = strlen(filename);

    if (len < 5)
        return FAILURE;

    /* Check last 4 characters */
    if (strcmp(filename + len - 4, ".txt") == 0)
        return SUCCESS;

    return FAILURE;
}

/* Function to display the files present in List */
void display(node *head)
{
    if (head == NULL)
    {
        return;
    }

    int i = 1;
    printf("\n✅  %-8s : Inserted Files\n", "INFO");
    while (head)
    {
        printf("[%d] - %s\n", i, head->fname);
        head = head->link;
        i++;
    }
}

int is_file_present(node *head, const char *fname)
{
    while (head)
    {
        if (strcmp(head->fname, fname) == 0)
            return 1;
        head = head->link;
    }
    return 0;
}

/* Remove the files present in both main list and updated list */
void remove_extra(node **crhead, node *uphead)
{
    if (crhead == NULL || uphead == NULL)
        return;

    node *temp = *crhead;
    node *prev = NULL;
    int found;
    while (temp)
    {
        node *u = uphead;
        found = 0;

        while (u)
        {
            if (strcmp(temp->fname, u->fname) == 0)
            {
                found = 1;
                break;
            }

            u = u->link;
        }

        if (found)
        {
            if (prev == NULL)
            {
                *crhead = temp->link;
                free(temp);
                temp = *crhead;
            }

            else
            {
                prev->link = temp->link;
                free(temp);
                temp = prev->link;
            }
        }

        else
        {
            prev = temp;
            temp = temp->link;
        }
    }
}

/* Function to display database */
void display_data(m_node **arr)
{
    int empty = 1;

    printf("\n                🖥️🖥️  DISPLAY DATA_BASE 🖥️🖥️\n");
    printf("x-------------------------------------------------------------x\n");
    printf("|%-6s %-12s %-12s %-15s %-12s|\n",
           "Index", "Word", "File_Count", "File_name", "Word_Count");
    printf("x-------------------------------------------------------------x\n");

    for (int i = 0; i < 28; i++)
    {
        if (arr[i] == NULL)
            continue;

        empty = 0;
        m_node *mnode = arr[i];

        while (mnode)
        {
            int first = 1;
            s_node *snode = mnode->slink;

            while (snode)
            {
                if (first)
                {
                    printf("|%-6d %-12s %-12d %-15s %-12d|\n", i, mnode->word, mnode->fcount, snode->file, snode->wcount);
                    first = 0;
                }
                else
                {
                    printf("|%-6s %-12s %-12s %-15s %-12d|\n", "", "", "", snode->file, snode->wcount);
                }
                snode = snode->slink;
            }
            mnode = mnode->mlink;
        }
    }

    if (empty)
        printf("❌ |%-58s|\n", "Error : DATABASE IS EMPTY");

    printf("x-------------------------------------------------------------x\n");
}

/* Function to search a word */
int search(m_node **arr, char *word)
{
    int index;

    /* Convert first character to lowercase for consistent hashing */
    char ch = word[0];

    if (ch >= 'a' && ch <= 'z')
        index = ch - 'a';

    else if (ch >= 'A' && ch <= 'Z')
        index = ch - 'A';

    else if (ch >= '0' && ch <= '9')
        index = 26;

    else
        index = 27;

    if (arr[index] == NULL)
    {
        printf("❌ %-8s : Word not present in the Data_base!!!\n", "Error");
        return FAILURE;
    }

    m_node *mnode = arr[index];

    printf("\n                       🔍🔍  SEARCH  🔎🔎\n");
    printf("x--------------------------------------------------------------------x\n");
    printf("|%-13s %-12s %-12s %-12s %-15s|\n",
           "Status", "Word", "File_count", "File_name", "Word_count");
    printf("x--------------------------------------------------------------------x\n");

    while (mnode)
    {
        if (strcmp(mnode->word, word) == 0)
        {
            s_node *snode = mnode->slink;
            while (snode)
            {
                printf("|%-13s %-12s %-12d %-12s %-15d|\n", "Word Found", word, mnode->fcount, snode->file, snode->wcount);
                snode = snode->slink;
            }
            printf("x--------------------------------------------------------------------x\n");
            return SUCCESS;
        }
        mnode = mnode->mlink;
    }

    printf("\n❌ %-8s : Word not present in the Data_base!!!\n", "Error");
    return FAILURE;
}

#include "header.h"

/* Function to free entire database */
void free_db(m_node **arr)
{
    for (int i = 0; i < 28; i++)
    {
        m_node *mtemp = arr[i];

        while (mtemp)
        {
            /* Free sub list */
            s_node *stemp = mtemp->slink;
            while (stemp)
            {
                s_node *sfree = stemp;
                stemp = stemp->slink;
                free(sfree);
            }

            /* Free main node */
            m_node *mfree = mtemp;
            mtemp = mtemp->mlink;
            free(mfree);
        }

        arr[i] = NULL;
    }
}

void free_head(node **head)
{

    while (*head)
    {
        node *temp = *head;
        *head = (*head)->link;
        free(temp);
    }
}