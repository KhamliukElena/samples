#include <iostream>
#include <cstdlib>
#include <ctime>

int** genGraph(int n, int** A)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = rand() % 2;
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

int** reorganizeGraph(int n, int** A)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(A[i][j]==0)
                A[i][j]=-2;
            else
                A[i][j]=-1;
        }
    }
    return A;
}

int lee(int inX, int inY, int tgX, int tgY, int n, int** A) //Lee alg
{
    int dx[4] = {1, 0, -1, 0}; //right, up, left, down
    int dy[4] = {0, 1, 0, -1};
    const int blocked = -1, notVisited = -2;
    bool stop;
    if (A[inX][inY] == blocked || A[tgX][tgY] == blocked) return -1; //if start or finish is blocked
    if (inX == tgX && tgY == inX) return 0; //if start equals to finish
    int d = 0;
    A[inX][inY] = 0;
    do
    {
        stop = true;
        for (int x = 0; x<n; x++)
        {
            for (int y=0; y<n; y++)
            {
                if (A[x][y] == d)
                {
                    for (int k=0; k<4; k++)
                    {
                        int newX = x + dx[k];
                        int newY = y + dy[k];
                        if (newX < n && newY < n && newX>=0 && newY>=0 && A[newX][newY] == notVisited)
                        {
                            stop = false;
                            A[newX][newY] = d + 1;
                        }
                    }
                }
            }
        }
        d++;
    }
    while(!stop && A[tgX][tgY] == notVisited);
    if (A[tgX][tgY]==notVisited) //no path found
        return -1;
    else //restore the path
    {
        d = A[tgX][tgY];
        int kPrev = -1; //direction of previous step
        int x = tgX, y = tgY, moves = 1;
        while (d>0)
        {
            d--;
            for (int k = 0; k < 4; ++k)
            {
                int newX = x + dx[k];
                int newY = y + dy[k];
                if ( newY >= 0 && newY < n && newX >= 0 && newX < n && A[newX][newY] == d)
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

void searchPath(int n, int** A)
{
    try
    {
        std::cout<<"Please insert coordinates of initial cell: "<<std::endl;
        int inX, inY, tgX, tgY;
        try
        {
            std::cin>>inX>>inY;
            if (inX < 0 || inY<0 || inX>=n || inY>=n)
                throw 1;
        }
        catch(int ex)
        {
            std::cout<<"Error!"<<std::endl;
            while(inX < 0 || inY<0 || inX>=n || inY>=n)
                std::cin>>inX>>inY;
        }
        std::cout<<"Please insert coordinates of target cell: "<<std::endl;
        try
        {
            std::cin>>tgX>>tgY;
            if (tgX < 0 || tgY<0 || tgX>=n || tgY>=n)
                throw 2;
        }
        catch(int ex)
        {
            while (tgX < 0 || tgY<0 || tgX>=n || tgY>=n)
                    std::cin>>tgX>>tgY;
        }
        //we are going to use Lee (или волновой) algorithm, that's why it's better to reorganize our matrix to make code easier
        //blocked cells will be marked as -1; empty not visited - -2
        A = reorganizeGraph(n, A);
        int moves = lee(inX, inY, tgX, tgY, n, A);
        std::cout<<"Answer: "<<moves<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Wrong input!"<<std::endl;
    }
}

int main()
{
    int n; // matrix size
    int** A;
    std::cout<<"Press 1 for test example, any other letter/number for generating random grid "<<std::endl;
    char mode;
    std::cin>>mode;
    if (mode=='1')
    {
        n = 3;
        A = new int *[n]; //A
        for (int i = 0; i < n; i++)
            A[i] = new int [n];
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
                A[i][j] = 0;
        }
        A[1][1] = 1;
        A[1][0] = 1;
        std::cout<<"Example grid: "<<std::endl;
    }
    else
    {
        std::cout<<"Please, specify size of grid (S): ";
        if(!(std::cin>>n && n>1))
        {
            std::cout<<"Wrong input!"<<std::endl;
            while(n<2)
                std::cin>>n;
        }
        A = new int *[n]; //A
        for (int i = 0; i < n; i++)
            A[i] = new int [n];
        srand(time(0));
        A = genGraph(n, A); //generate a random graph
        std::cout<<"Generated grid: "<<std::endl;
    }

    outGraph(n, A);

    searchPath(n, A);

    for (int i = 0; i < n; i++)
        delete[] A[i];
    delete [] A;

    return 0;
}
