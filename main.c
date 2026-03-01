#include "header.h"

int main(int argc, char *argv[])
{
    m_node *arr[28] = {NULL};
    node *crhead = NULL;
    node *uphead = NULL;

    char word[50];
    int choice;
    int db_created = 0, No_files = 0, db_update = 0; /* Database state flag */

    if (validation(argv, argc, &crhead) == 4)
    {
        No_files = 1;
    }
    display(crhead);

    while (1)
    {
        printf("\nx------------------------------------------------------x\n");
        printf("|Enter which operation should be perform:\n");
        printf("x------------------------------------------------------x\n");
        printf("  [1].Create_DB\n  [2].Display\n  [3].Search\n  [4].Save\n  [5].Update\n  [6].Exit\n");
        printf("x------------------------------------------------------x\n");
        printf("|➡️  Please Enter the choice : ");
        

        if (scanf("%d", &choice) != 1)
        {
            printf("\n❌ %-8s : Invalid input\n\n", "Error");
            while (getchar() != '\n'); /* clear buffer */
            continue;
        }
        printf("x------------------------------------------------------x\n");

        switch (choice)
        {
        case 1:
            if (No_files)
            {
                printf("\n❌ %-8s : Please pass at least one .txt file!!\n", "Error");
                printf("⚠️  %-8s : %s f1.txt f2.txt...\n", "USAGE", argv[0]);
                break;
            }

            if (db_created || db_update == 0 && db_created)
            {
                printf("\n❌ %-8s : DataBase is already created!\n\n", "ERROR");
                break;
            }

            remove_extra(&crhead, uphead);
            if (createdb(arr, crhead) == SUCCESS)
            {
                printf("\n✅ %-8s : DataBase Created Successfully...\n", "INFO");
                db_created = 1;
            }
            break;

        case 2:
            if (!db_created && !db_update)
            {
                printf("\n❌ %-8s : Create or Update DB first\n", "ERROR");
                break;
            }
            display_data(arr);
            break;

        case 3:
            if (!db_created && !db_update)
            {
                printf("\n❌ %-8s : Create or Update DB first\n", "ERROR");
                break;
            }

            printf("|x----------------------------------------------x\n");
            printf(" ➡️  Enter the word you want to search: ");
            scanf("%49s", word);
            printf("|x----------------------------------------------x\n");

            /* normalize search word */
            for (int i = 0; word[i]; i++)
                word[i] = tolower(word[i]);

            search(arr, word);
            break;

        case 4:
            if (!db_created && !db_update)
            {
                printf("\n❌ %-8s : Nothing to save\n", "ERROR");
                break;
            }
            save(arr);
            break;

        case 5:
            if (db_created || db_update)
            {
                printf("\n❌ %-8s : DataBase is Already Created!\n", "Error");
                break;
            }

            if (update(arr, &uphead) == SUCCESS)
            {
                printf("\n✅ %-8s : DataBase Updated Successfully...\n", "INFO");
                db_update = 1;
            }
            else
            {
                printf("❌ %-8s : Update Failed\n", "ERROR");
            }
            break;

        case 6:
            free_db(arr);
            free_head(&uphead);
            printf("\n✅ %-8s : Exiting Program\n\n", "INFO");
            exit(0);

        default:
            printf("\n❌ %-8s : Invalid Choice\n", "Error");
        }
    }
}
