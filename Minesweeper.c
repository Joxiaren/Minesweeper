#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
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

void gameLoop();
struct settings setSettings(int n, int m, int mineNum);
struct settings inputSettings();
struct coordinates setCoordinates(int x, int y);

int main()
{
    srand(time(0));
    printf("Welcome to Minesweeper (Console edition) by JovanS\n\n");
    while(1)
    {
        printf("Select an option\n");
        printf("1. Play game\n");
        printf("2. Exit\n");
        
        int select;
        scanf("%d", &select);

        if(select == 1)
        {
            struct settings sett;
            sett = inputSettings();

            printf("WIP but congrats for ucessfully getting through the input");
        }
        else if(select == 2) return 0;
        else printf("please step away from the computer before you break anything\n");
    }
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
        
        if(set.n >= 3 && set.n <= 15) break;
        else printf("Why am i surounded by idiots that catn read\n");
    }
    while(1) //while loop for inputing m(height)
    {
        printf("Choose table height (3 <= m <= 15): ");
        scanf("%d",&set.m);
        
        if(set.m >= 3 && set.m <= 15) break;
        else printf("Try not to guess the correct input\n");
    }
    while(1) //while loop for inputing the number of mines
    {
        printf("Choose difficulty(number of mines)\n");
        printf("1. Easy(~20% mines)\n");
        printf("2. Normal(~50% mines)\n");
        printf("3. Hard(~70% mines)\n");
        printf("4. Custom number of mines\n");
        
        scanf("%d",&select);
        bool brek = true;
        if(select == 1) set.mineNum = (set.n * set.m) * 0.2;
        else if(select == 2) set.mineNum = (set.n * set.m) * 0.5;
        else if(select == 3) set.mineNum = (set.n * set.m) * 0.7;
        else if(select == 4)
        {
            while(1)
            {
                printf("Select custom number of mines (x < %d (%d * %d)): ",set.n*set.m, set.n, set.m);
                scanf("%d", &set.mineNum);
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