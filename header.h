#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 1
#define FAILURE 0

/* File list node */
typedef struct node
{
    char fname[50];
    struct node *link;
} node;

/* Sub node */
typedef struct sub
{
    char file[50];
    int wcount;
    struct sub *slink;
} s_node;

typedef struct main
{
    char word[50];
    int fcount;
    s_node *slink;
    struct main *mlink;
} m_node;
/* Main node */

/* Function prototypes */
int validation(char *argv[], int argc, node **head);
int createdb(m_node **arr, node *head);
int is_txt_file(char *filename);
void display_data(m_node **arr);
void display(node *head);
int search(m_node **arr, char *word);
int is_file_present(node *head, const char *fname);
int save(m_node **arr);
int update(m_node **arr, node **head);
void free_db(m_node **arr);
void free_head(node **head);
void remove_extra(node **crhead, node *uphead);

#endif /* HEADER_H */
