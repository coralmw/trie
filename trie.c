 /*
 * Implemeantation of a trie - pretty minimal!
 * from cs.bu.edu
 * thomas parks
 */
 
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "trie.h"

typedef struct trieNodeTag {
    char key; /* letter at this point in the tree */
    trieValueT value; /* value at this point in the tree - is it the end of a word */
    struct trieNodeTag *next, *children;
} trieNodeT;


typedef struct trieCDT {
    trieNodeT *root;
} trieCDT;

bool TrieIsMember(trieADT trie, const char keys[])
{
    /* go to the top level, and the start of the key */
    trieNodeT *level = trie->root;
    int i = 0;

    for (;;) /* equivlent to while true, but hidious. */
    {
        trieNodeT *found = NULL;
        trieNodeT *curr;
        
        for (curr = level; curr != NULL; curr = curr->next)
        {
            /*find a node with the key keys[i] - the value for this level */
            if (curr->key == tolower(keys[i]))
            {
                //printf("found %c\n", keys[i]);
                found = curr;
                //printf("at pointer %p\n", found);
            }
        }
        //printf("out of loop\n");
        
        /* else if the key is not in the list, bail. key not present. */
        if (found == NULL)
        {
            //printf("did not find %c\n", keys[i]);
            return false;
        }
        
        /* check to see that the final value is a terminator in the trie? */
        if ( (keys[i+1] == '\0') && found->value )
        {
            //printf("is a terminator at %c\n", keys[i]);
            return true;
        }
         
        
        /* advance to next level and keep checking, with the next str key */
        //printf("advancing to %p\n", found->children);
        level = found->children;
        i++;
    }
}

trieADT TrieCreate()
{
    /* just need to create and return a pointer to the root node? */
    trieCDT *CDT = malloc( sizeof(trieCDT) );
    
    trieNodeT *rootnode = malloc( sizeof(trieNodeT) );
    rootnode->key = ' ';
    rootnode->value = false;
    rootnode->next = NULL;
    rootnode->children = NULL;
    CDT->root = rootnode;
    
    return CDT;
}


bool TrieAdd(trieADT trie, char keys[])
{
    trieNodeT *level = trie->root;
    int i = 0;
    
    for (;;)
    {
        trieNodeT *found = NULL;
        trieNodeT *curr;
    
        /* go through the linked list, but leave the final node as curr */
        for (curr = level; curr != NULL; curr = curr->next) 
        {
           //printf("start key %c\n", curr->key);
            if (curr->key == keys[i])
            {
                //printf("found node key:%c at addr:%p \n", keys[i], curr);
                found = curr;
                break;
            }
            if (curr->next == NULL)
                break;
        }
        
        if (found == NULL)
        {
            trieNodeT *newCurrentLevel = malloc( sizeof(trieNodeT) );
            //printf("adding new node key:%c at addr:%p connected to:%p \n", keys[i], newCurrentLevel, curr);
            newCurrentLevel->key = keys[i];
            newCurrentLevel->next = NULL;
            newCurrentLevel->children = NULL;
            newCurrentLevel->value = false;
            curr->next = newCurrentLevel;
            found = newCurrentLevel;

        }
        
        /* now there is a node at this value, in found */
        
        
        if (keys[i+1] == '\0') /*if this is the last value */
        {
            //printf("finished\n");
            found->value = true;
            return true;
        } else if (found->children != NULL)
        {
            //printf("going down a level\n");
            level = found->children;
            i++;
        } else
        {
            //printf("adding next level\n");
            trieNodeT *newNextLevel = malloc( sizeof(trieNodeT) );
            newNextLevel->key = keys[i+1];
            newNextLevel->next = NULL;
            newNextLevel->children = NULL;
            newNextLevel->value = false;
            found->children = newNextLevel;
            level = newNextLevel;
            i++;
        }
    }
}

void NodeFree(trieNodeT *node)
{
    if (node->children != NULL)
        NodeFree(node->children);
    if (node->next != NULL)
        NodeFree(node->next);
    free(node);
}

bool TrieFree(trieADT trie)
{
    NodeFree(trie->root);
    free(trie);
    return true;
}
