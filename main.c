#include <stdio.h>
#include <string.h>

/////////////////////////////////////
#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char *allocp=allocbuf;

char *alloc(int n);
void afree(char *p);

//////////////////////////////////////

#define MAXLEN 1000
#define MAXLINES 5000

int my_getline(char *s, int lim);
int readlines(char *ptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *v[], int left, int right);
void my_swap(char *v[], int i, int j);

char *lineptr[MAXLINES];

int main()
{
    int nlines;
    if((nlines=readlines(lineptr, MAXLINES))>=0){
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    }else{
        printf("error: input too big to sort\n");
        return  1;
    }
}

int my_getline(char s[], int lim)
{
    int i, c;
    for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i){
        s[i]=c;
    }
    if(c=='\n'){
        s[i]='\n';
        ++i;
    }
    s[i]='\0';
    return  i;
}

int readlines(char *lineptr[], int maxlines)
{
    char line[MAXLEN];
    int len;
    char *p;
    int nlines=0;
    while((len=my_getline(line, MAXLINES))>0)
    {
        if(nlines >= maxlines || (p=alloc(len))==NULL){
            return -1;
        }else{
            line[len-1]='\0';
            strcpy(p, line);
            lineptr[nlines++]=p;
        }
    }
    return nlines;
}

///////////////////////////////////////
char *alloc(int n)
{
    if(allocbuf + ALLOCSIZE - allocp >= n){
        allocp += n;
        return allocp - n;
    }else{
        return 0;
    }
}

void afree(char *p)
{
    if(p >= allocbuf && p < allocbuf +ALLOCSIZE){
        allocp=p;
    }
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- >0)
    {
        printf("%s\n", *lineptr++);
    }
    
}

void qsort(char *v[], int left, int right)
{
    int i, last;
    if(left>=right){
        return;
    }
    my_swap(v, left, (left+right)/2);
    last=left;
    for(i=left+1; i<=right; i++){
        if(strcmp(v[i], v[left])<0){
            my_swap(v, ++last, i);
        }
    }
    my_swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void my_swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i]=v[j];
    v[j]=temp;
}



