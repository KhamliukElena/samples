#include <iostream>
#include <cstdlib>
#include <ctime>

int** genGraph(int n, int** A)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i==j)
                A[i][j] = 0;
            else
            {
                A[i][j] = rand() % 2;
            }
        }
    }
    return A;
}

void outGraph(int n, int** A)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout<<A[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void dfs(int v, int n, int **A, char visited[]) //in depth
{
    visited[v] = 1;
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0 && (A[v][i] == 1 || A[i][v] == 1))
            dfs(i, n, A, visited);
    }
}

int main()
{
    int n; // matrix size
    std::cout<<"Please, specify size of matrix:";
    std::cin>>n;
    while (n<2)
    {
        std::cout<<"Error!"<<std::endl;
        std::cin>>n;
    }
    int** A = new int *[n]; //adjacency matrix, 1 - vertices are connected; 0 - no connection, may be oriented, but w/o route from a node to itself
    for (int i = 0; i < n; i++)
        A[i] = new int [n];


    srand(time(0));
    A = genGraph(n, A); //generate a random graph
    std::cout<<"Generated graph:"<<std::endl;
    outGraph(n, A);

    int cnt = 0; //connected components
    char visited[n]; //vertices that were visited
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0) {
            dfs(i, n, A, visited);
            cnt++;
        }
    }
    std::cout<<"There are "<<cnt<<" connected components of the graph"<<std::endl;
    for (int i = 0; i < n; i++)
        delete[] A[i];
    delete [] A;

    return 0;
}
