#include <iostream>
#include <cstdlib>
#include <ctime>

int** genGraph(int matrixSize, int** gridField)
{
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            gridField[i][j] = rand() % 2;
        }
    }
    return gridField;
}

void outGraph(int matrixSize, int** gridField)
{
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            std::cout<<gridField[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

int** reorganizeGraph(int matrixSize, int** gridField)
{
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            if(gridField[i][j]==0)
                gridField[i][j]=-2;
            else
                gridField[i][j]=-1;
        }
    }
    return gridField;
}

int lee(int inX, int inY, int tgX, int tgY, int matrixSize, int** gridField) //Lee alg
{
    int dx[4] = {1, 0, -1, 0}; //right, up, left, down
    int dy[4] = {0, 1, 0, -1};
    const int blocked = -1, notVisited = -2;
    bool stop;
    if (gridField[inX][inY] == blocked || gridField[tgX][tgY] == blocked) return -1; //if start or finish is blocked
    if (inX == tgX && tgY == inX) return 0; //if start equals to finish
    int d = 0;
    gridField[inX][inY] = 0;
    do
    {
        stop = true;
        for (int x = 0; x<matrixSize; x++)
        {
            for (int y=0; y<matrixSize; y++)
            {
                if (gridField[x][y] == d)
                {
                    for (int k=0; k<4; k++)
                    {
                        int newX = x + dx[k];
                        int newY = y + dy[k];
                        if (newX < matrixSize && newY < matrixSize && newX>=0 && newY>=0 && gridField[newX][newY] == notVisited)
                        {
                            stop = false;
                            gridField[newX][newY] = d + 1;
                        }
                    }
                }
            }
        }
        d++;
    }
    while(!stop && gridField[tgX][tgY] == notVisited);
    if (gridField[tgX][tgY]==notVisited) //no path found
        return -1;
    else //restore the path
    {
        d = gridField[tgX][tgY];
        int kPrev = -1; //direction of previous step
        int x = tgX, y = tgY, moves = 1;
        while (d>0)
        {
            d--;
            for (int k = 0; k < 4; ++k)
            {
                int newX = x + dx[k];
                int newY = y + dy[k];
                if ( newY >= 0 && newY < matrixSize && newX >= 0 && newX < matrixSize && gridField[newX][newY] == d)
                {
                    x = x + dx[k];
                    y = y + dy[k];
                    if (k!=kPrev && kPrev!=-1)
                        moves++;
                    kPrev = k;
                    break;
                }
            }
        }
        return moves;
    }
}

void searchPath(int matrixSize, int** gridField)
{
    try
    {
        std::cout<<"Please insert coordinates of initial cell: "<<std::endl;
        int inX, inY, tgX, tgY;
        try
        {
            std::cin>>inX>>inY;
            if (inX < 0 || inY<0 || inX>=matrixSize || inY>=matrixSize)
                throw 1;
        }
        catch(int ex)
        {
            std::cout<<"Error!"<<std::endl;
            while(inX < 0 || inY<0 || inX>=matrixSize || inY>=matrixSize)
                std::cin>>inX>>inY;
        }
        std::cout<<"Please insert coordinates of target cell: "<<std::endl;
        try
        {
            std::cin>>tgX>>tgY;
            if (tgX < 0 || tgY<0 || tgX>=matrixSize || tgY>=matrixSize)
                throw 2;
        }
        catch(int ex)
        {
            while (tgX < 0 || tgY<0 || tgX>=matrixSize || tgY>=matrixSize)
                    std::cin>>tgX>>tgY;
        }
        //we are going to use Lee algorithm, that's why it's better to reorganize our matrix to make code easier
        //blocked cells will be marked as -1; empty not visited - -2
        gridField = reorganizeGraph(matrixSize, gridField);
        int moves = lee(inX, inY, tgX, tgY, matrixSize, gridField);
        std::cout<<"Answer: "<<moves<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Wrong input!"<<std::endl;
    }
}

int main()
{
    int matrixSize; // matrix size
    int** gridField;
    std::cout<<"Press 1 for test example, any other letter/number for generating random grid "<<std::endl;
    char mode;
    std::cin>>mode;
    if (mode=='1')
    {
        matrixSize = 3;
        gridField = new int *[matrixSize]; //A
        for (int i = 0; i < matrixSize; i++)
            gridField[i] = new int [matrixSize];
        for (int i=0; i<matrixSize; i++)
        {
            for (int j=0; j<matrixSize; j++)
                gridField[i][j] = 0;
        }
        gridField[1][1] = 1;
        gridField[1][0] = 1;
        std::cout<<"Example grid: "<<std::endl;
    }
    else
    {
        std::cout<<"Please, specify size of grid (S): ";
        if(!(std::cin>>matrixSize && matrixSize>1))
        {
            std::cout<<"Wrong input!"<<std::endl;
            while(matrixSize<2)
                std::cin>>matrixSize;
        }
        gridField = new int *[matrixSize]; //A
        for (int i = 0; i < matrixSize; i++)
            gridField[i] = new int [matrixSize];
        srand(time(0));
        gridField = genGraph(matrixSize, gridField); //generate a random graph
        std::cout<<"Generated grid: "<<std::endl;
    }

    outGraph(matrixSize, gridField);

    searchPath(matrixSize, gridField);

    for (int i = 0; i < matrixSize; i++)
        delete[] gridField[i];
    delete [] gridField;

    return 0;
}
