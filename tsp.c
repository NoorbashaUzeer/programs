#include <stdio.h>
#include <conio.h>

#define MAX 20
#define INF 9999

int n;
int cost[MAX][MAX];

int visited[MAX];
int bestPath[MAX];
int currentPath[MAX];

int minCost = INF;

/* Find the minimum edge from a city */
int firstMin(int i)
{
    int j;
    int min = INF;

    for (j = 0; j < n; j++)
    {
        if (i != j && cost[i][j] < min)
            min = cost[i][j];
    }

    return min;
}

/* Find the second minimum edge from a city */
int secondMin(int i)
{
    int j;
    int first = INF;
    int second = INF;

    for (j = 0; j < n; j++)
    {
        if (i == j)
            continue;

        if (cost[i][j] <= first)
        {
            second = first;
            first = cost[i][j];
        }
        else if (cost[i][j] < second)
        {
            second = cost[i][j];
        }
    }

    return second;
}

/* Branch and Bound function */
void TSPRec(int level, int currentCost, int bound)
{
    int i;
    int newBound;
    int newCost;

    /* If all cities are visited */
    if (level == n)
    {
        /* Add cost of returning to starting city */
        if (cost[currentPath[level - 1]][currentPath[0]] != 0)
        {
            newCost = currentCost +
                      cost[currentPath[level - 1]][currentPath[0]];

            if (newCost < minCost)
            {
                minCost = newCost;

                for (i = 0; i < n; i++)
                    bestPath[i] = currentPath[i];
            }
        }

        return;
    }

    /* Try every unvisited city */
    for (i = 0; i < n; i++)
    {
        if (cost[currentPath[level - 1]][i] != 0 &&
            visited[i] == 0)
        {
            newCost = currentCost +
                      cost[currentPath[level - 1]][i];

            newBound = bound;

            /*
             * Calculate new lower bound.
             * Use first and second minimum edges.
             */
            if (level == 1)
            {
                newBound -= (firstMin(currentPath[level - 1])
                             + firstMin(i)) / 2;
            }
            else
            {
                newBound -= (secondMin(currentPath[level - 1])
                             + firstMin(i)) / 2;
            }

            /*
             * Continue only if the estimated cost
             * can improve the current best solution.
             */
            if (newCost + newBound < minCost)
            {
                currentPath[level] = i;
                visited[i] = 1;

                TSPRec(level + 1, newCost, newBound);

                /* Backtrack */
                visited[i] = 0;
            }
        }
    }
}

/* Start Branch and Bound */
void TSP()
{
    int i;
    int bound = 0;

    /*
     * Calculate initial lower bound.
     */
    for (i = 0; i < n; i++)
    {
        bound += firstMin(i) + secondMin(i);
    }

    /*
     * Divide by 2 because every edge is counted twice.
     */
    bound = (bound + 1) / 2;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    currentPath[0] = 0;
    visited[0] = 1;

    TSPRec(1, 0, bound);
}

int main()
{
    int i, j;

    

    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("\nEnter the cost matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
        }
    }

    TSP();

    printf("\n\n------------------------------");
    printf("\nMinimum Cost = %d", minCost);

    printf("\n\nOptimal Tour: ");

    for (i = 0; i < n; i++)
        printf("%d -> ", bestPath[i] + 1);

    printf("%d", bestPath[0] + 1);

    printf("\n------------------------------");

    getch();
    return 0;
}
