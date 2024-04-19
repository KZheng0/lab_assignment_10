#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int isWord;
    int occurrences;
    struct Trie* next[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* myTrie = malloc(sizeof(struct Trie));
    myTrie->isWord = 0;
    myTrie->occurrences = 0;
    for (int i = 0; i < 26; i++)
    {
        myTrie->next[i] = NULL;
    }
    return myTrie;
}


// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int i = 0; // Initialize i
    while (word[i] != '\0') 
    {
        int nextIndex = word[i] - 'a';
        if (pTrie->next[nextIndex] == NULL)
        {
            pTrie->next[nextIndex] = createTrie();
        }
        pTrie = pTrie->next[nextIndex];
        i++;
    }
    pTrie->isWord = 1;
    pTrie->occurrences++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int i = 0;
    while (word[i] != '\0') 
    {
        int nextIndex = word[i] - 'a';
        if (pTrie->next[nextIndex] == NULL)
        {
            return 0;
        }
        pTrie = pTrie->next[nextIndex];
        i++;
    }
    return pTrie->occurrences;;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie) 
    {
        for (int i = 0; i < 26; i++)
        {
            pTrie->next[i] = deallocateTrie(pTrie->next[i]);
        }
        free(pTrie);
    }
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int wordSz = 0;
    FILE* inFile = fopen(filename, "r");
    fscanf(inFile, "%d\n", &wordSz);
    
    for (int i = 0; i < wordSz; i++) 
    {
        pInWords[i] = malloc(100 * sizeof(char));
        fscanf(inFile, "%s", pInWords[i]);
    }

    return wordSz;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}