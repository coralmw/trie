/*
 * Implemeantation of a trie
 * from cs.bu.edu
 * thomas parks
 */
 
typedef bool trieValueT;
 
typedef struct trieCDT *trieADT;

bool TrieIsMember(trieADT trie, const char keys[]);

/* creates a trie with constant depth. returns pointer to the tree. */
trieADT TrieCreate();

bool TrieDestroy(trieADT trie);

bool TrieAdd(trieADT trie, char keys[]);

bool TrieRemove(char keys[]);

bool TrieFree(trieADT trie);
