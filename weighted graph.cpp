#include <iostream>
#include <cstdlib>
#include <ctime>

int** genGraph(int matrixSize, int** adjacencyMatrix)
{
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            if (i==j)
                adjacencyMatrix[i][j] = 0;
            else
            {
                adjacencyMatrix[i][j] = rand() % 2;
            }
        }
    }
    return adjacencyMatrix;
}

void outGraph(int matrixSize, int** adjacencyMatrix)
{
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            std::cout<<adjacencyMatrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void dfs(int v, int matrixSize, int **adjacencyMatrix, char visited[]) //in depth
{
    visited[v] = 1;
    for (int i = 0; i < matrixSize; i++) {
        if (visited[i] == 0 && (adjacencyMatrix[v][i] == 1 || A[i][v] == 1))
            dfs(i, matrixSize, adjacencyMatrix, visited);
    }
}

int main()
{
    int matrixSize; // matrix size
    std::cout<<"Please, specify size of matrix:";
    std::cin>>matrixSize;
    while (matrixSize<2)
    {
        std::cout<<"Error!"<<std::endl;
        std::cin>>matrixSize;
    }
    int** adjacencyMatrix = new int *[matrixSize]; //adjacency matrix, 1 - vertices are connected; 0 - no connection, may be oriented, but w/o route from a node to itself
    for (int i = 0; i < matrixSize; i++)
        adjacencyMatrix[i] = new int [matrixSize];


    srand(time(0));
    adjacencyMatrix = genGraph(matrixSize, adjacencyMatrix); //generate a random graph
    std::cout<<"Generated graph:"<<std::endl;
    outGraph(matrixSize, adjacencyMatrix);

    int cnt = 0; //connected components
    char visited[matrixSize]; //vertices that were visited
    for (int i = 0; i < matrixSize; i++)
    {
        if (visited[i] == 0) {
            dfs(i, matrixSize, adjacencyMatrix, visited);
            cnt++;
        }
    }
    std::cout<<"There are "<<cnt<<" connected components of the graph"<<std::endl;
    for (int i = 0; i < matrixSize; i++)
        delete[] adjacencyMatrix[i];
    delete [] adjacencyMatrix;

    return 0;
}
