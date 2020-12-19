#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//Structure of Results
typedef struct Results
{
    char * result;
} Results;

//Structure of Phrases
typedef struct Phrases
{
    long long int numberOfSearch;
    char *phrase;
    char *phraseInLower;
} Phrases;

int cmpfunc (const void * a, const void * b) {
   return ( *(long long int*)a - *(long long int*)b );
}

//Search Function
void SearchNabidky(Phrases *phrases,long long int CounterOfLine)
{
    size_t bufsize = 32;
    long long int nmax =CounterOfLine;
    char *SearchPhrase = (char *)calloc(bufsize, sizeof(char));
    Results *results = (Results *)calloc(nmax, sizeof(Results));
    long long int counterOfNalezeno=0;
    while (1)
    {
        getline(&SearchPhrase,&bufsize,stdin);
        if (feof(stdin))
        {
            free(SearchPhrase);
            break;
        }
        for(unsigned long long int i = 0; i<strlen(SearchPhrase); i++)
        {
            SearchPhrase[i] = tolower(SearchPhrase[i]);
        }

        //SEARCH
        strtok(SearchPhrase, "\n");
        for(long long int i=CounterOfLine-1; i>=0;i--)
        {
            if(strstr(phrases[i].phraseInLower, SearchPhrase))
            {
                if(counterOfNalezeno == 0)
                {
                    results[counterOfNalezeno].result = (char *)calloc(strlen(phrases[i].phrase)+1, sizeof(char));
                     strcpy(results[counterOfNalezeno].result,phrases[i].phrase);
                }
                else
                {
                    results[counterOfNalezeno].result = (char *)calloc(strlen(phrases[i].phrase)+1, sizeof(char));
                    strcpy(results[counterOfNalezeno].result,phrases[i].phrase);
                }
                counterOfNalezeno++;
            }
        }
        printf("Nalezeno: %lld\n",counterOfNalezeno);
        for( long long int i=0; i<counterOfNalezeno; i++)
        {
            printf("> %s",results[i].result);
        }
        for( long long int i=0; i<counterOfNalezeno; i++)
        {
            free(results[i].result);
        }
            counterOfNalezeno=0;
    }
    free(results);
}

int main (void)
{
    int checkOfVstup =0;
    long long int nmax =100;
    //Memory allocation
    Phrases *phrases = (Phrases*)calloc(nmax,sizeof(Phrases));
    long long int counterOfLine = 0;
    size_t bufsize = 32;
    char *phrase = (char *)calloc(bufsize, sizeof(char));
    char c;
    long double numberOfSearchtmp =0;
    long long int numberOfSearch =0;
    int read1=0;
    printf("Casto hledane fraze:\n");
    //Reading while cycle
    while (1)
    {
        read1 = scanf("%Lf %c",&numberOfSearchtmp,&c);
       numberOfSearch = (int)numberOfSearchtmp;
       if(read1 == -1 || read1 ==0)
        {
             if(counterOfLine == 0)
            {
                for(long long int i=0; i<counterOfLine; i++)
                {
                     free(phrases[i].phrase);
                     free(phrases[i].phraseInLower);
                }
                //free allocated memory
                free(phrases);
                checkOfVstup++;
                free(phrase);
                printf("Nespravny vstup.\n");
                return 1;
            }
            if (feof(stdin))
            {
		//IF end of file - free allocated memory
                for(long long int i=0; i<counterOfLine; i++)
                {
                     free(phrases[i].phrase);
                     free(phrases[i].phraseInLower);
                }
                free(phrases);
                free(phrase);
                printf("Nespravny vstup.\n");
                return 1;
            }
            break;
        }
        getline(&phrase,&bufsize,stdin);
        if((read1 != 2 || c!=':') && ((read1!=-1) || (read1!=0)))
        {
	     //control
            for(long long int i=0; i<counterOfLine; i++)
            {
                 free(phrases[i].phrase);
                 free(phrases[i].phraseInLower);
            }
            free(phrases);
            free(phrase);
            checkOfVstup++;
            printf("Nespravny vstup.\n");
            return 1;
        }
        if(counterOfLine == nmax)
        {
            nmax *=2;
            phrases = (Phrases*)realloc(phrases,nmax*sizeof(Phrases));
        }

        phrases[counterOfLine].numberOfSearch = numberOfSearch;
        phrases[counterOfLine].phrase = (char *)calloc(strlen(phrase)+1, sizeof(char));
        strcpy(phrases[counterOfLine].phrase, phrase);
        phrases[counterOfLine].phraseInLower = (char *)calloc(strlen(phrase)+1, sizeof(char));
        strcpy(phrases[counterOfLine].phraseInLower, phrase);
        for(unsigned long long int i = 0; i<strlen(phrases[counterOfLine].phraseInLower); i++)
        {
            phrases[counterOfLine].phraseInLower[i] = tolower(phrases[counterOfLine].phraseInLower[i]); 
        }
        strtok(phrases[counterOfLine].phraseInLower, "\n");
        counterOfLine++;
    }
    if (checkOfVstup ==0){
	    //Sorting if does not have data
	    qsort (phrases, counterOfLine, sizeof(Phrases), cmpfunc);
	    printf("Hledani:\n");
	    SearchNabidky(phrases,counterOfLine);
}
    //Free last allocated memory
     free(phrase);
     for(long long int i=0; i<counterOfLine; i++)
     {
         free(phrases[i].phrase);
         free(phrases[i].phraseInLower);
     }
    free(phrases);
}
