#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct settings
{
    int n; //number of columns
    int m; //number of rows
    int mineNum; // number of mines must be <= n*m-1  
};
struct coordinates
{
    int x; //coordinates on the x axis
    int y; //coordinates on the y axis
};

void clear();
void printfMatrix(int n, int m, int a[n][m]);
void swapInt(int *a, int *b);
void swapCoor(struct coordinates *a, struct coordinates *b);
struct settings setSettings(int n, int m, int mineNum);
struct coordinates setCoordinates(int x, int y);
struct settings inputSettings();
void populateTable(struct settings set, int a[set.n][set.m]);
void gameLoop();

int main()
{
    srand(time(0));
    printf("Welcome to Minesweeper (Console edition) by JovanS\n\n");
    while(1)
    {
        printf("Select an option\n");
        printf("1. Play game\n");
        printf("2. Exit\n");
        
        int select = 3;
        scanf("%d", &select);
        clear();

        if(select == 1)
        {
            struct settings sett;
            //sett = setSettings(10,10,10);
            sett = inputSettings();
            int minefield[sett.m][sett.n];        
            memset(minefield,0, sett.m * sett.n * sizeof(int));

            populateTable(sett,minefield);
            //system("clear");
            printf("\nThe minefield you got looks like this: \n");
            printfMatrix(sett.m,sett.n, minefield);
            printf("\n");
            printf("You still cant play but would be appreciated if youd check the validity of the matrix\n");
            printf("Feel free to generate another one\n\n");
        }
        else if(select == 2) return 0;
        else printf("please step away from the computer before you break anything\n");
    }
}

void clear()
{
    while(getchar() != '\n');
}
void printfMatrix(int n, int m, int a[n][m])
{
    int j,jj;
    for(j = 0; j < n; j++)
    {
        for(jj = 0; jj < m; jj++)
        {
            if(a[j][jj] < 0) printf("%c ",'*');
            else printf("%d ",a[j][jj]);
        } 
        printf("\n");
    }
    
}
void swapInt(int *a, int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}
void swapCoor(struct coordinates *a, struct coordinates *b)
{
    swapInt(&a -> x, &b -> x);
    swapInt(&a -> y, &b -> y);
}
struct settings setSettings(int n, int m, int mineNum)
{
    struct settings set;
    set.n = n;
    set.m = m;
    set.mineNum = mineNum;

    return set;
}
struct settings inputSettings()
{
    struct settings set;
    int select;
    while(1) //while loop for inputing n(width)
    {
        printf("Choose table width (3 <= n <= 15): ");
        scanf("%d",&set.n);
        clear();

        if(set.n >= 3 && set.n <= 15) break;
        else printf("Why am i surounded by idiots that catn read\n");
    }
    while(1) //while loop for inputing m(height)
    {
        printf("Choose table height (3 <= m <= 15): ");
        scanf("%d",&set.m);
        clear();

        if(set.m >= 3 && set.m <= 15) break;
        else printf("Try not to guess the correct input\n");
    }
    while(1) //while loop for inputing the number of mines
    {
        printf("Choose difficulty(number of mines)\n");
        printf("1. Easy(~10%% mines)\n");
        printf("2. Normal(~20%% mines)\n");
        printf("3. Hard(~50%% mines)\n");
        printf("4. Custom number of mines\n");
        
        scanf("%d",&select);
        clear();

        bool brek = true;
        if(select == 1) set.mineNum = (set.n * set.m) * 0.1;
        else if(select == 2) set.mineNum = (set.n * set.m) * 0.2;
        else if(select == 3) set.mineNum = (set.n * set.m) * 0.5;
        else if(select == 4)
        {
            while(1)
            {
                printf("Select custom number of mines (x < %d (%d * %d)): ",set.n*set.m, set.n, set.m);
                scanf("%d", &set.mineNum);
                clear();

                if(set.mineNum > 0 && set.mineNum < set.n*set.m) break;
                else printf("*sigh*...\n");
            }
        }
        else
        {
            printf("There there. Youll learn how to count soon enough\n");
            brek = false;
        }
        if(brek) break;   
    }
    return set;
}
struct coordinates setCoordinates(int x, int y)
{
    struct coordinates set;
    set.x = x;
    set.y = y;

    return set;
}
void populateTable(struct settings set, int a[set.n][set.m])
{
    int j,jj;
    struct coordinates freeSpace[set.n*set.m];
    int freeSpaceSize = 0;
    for(j = 0; j < set.n; j++)
    {
        for(jj = 0; jj < set.m; jj++)
        {
            if(a[j][jj] == 0)
            {
                freeSpace[freeSpaceSize] = setCoordinates(jj,j);
                freeSpaceSize++;
            }
        }
    }

    int mineNum = set.mineNum;
    while(mineNum > 0)
    {
        int random = rand() % freeSpaceSize;
        a[freeSpace[random].y][freeSpace[random].x] = -1;
        
        for(j = -1; j <= 1; j++)
        {
            if(freeSpace[random].y + j < 0 || freeSpace[random].y + j >= set.n) continue;
            for(jj = -1; jj <= 1; jj++)
            {
                if(freeSpace[random].x + jj < 0 || freeSpace[random].x + jj >= set.m) continue;

                if(j == 0 && jj == 0) continue;

                if(a[freeSpace[random].y + j][freeSpace[random].x + jj] != -1) a[freeSpace[random].y + j][freeSpace[random].x + jj]++;
            }
        }
        
        while(random < freeSpaceSize - 1)
        {
            swapCoor(&freeSpace[random], &freeSpace[random + 1]);
            random++;
        }
        freeSpaceSize--;
        mineNum--;
    }
}