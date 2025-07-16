#include <iostream>
#include <queue.h>

struct position
{
    int row;
    int col;
};

void labelComponents(int size)
{
    int** pixel = new int*[size+1];
    position neighbor[4];
    neighbor[0].row = 0;neighbor[0].col = 1;
    neighbor[1].row = 1;neighbor[1].col = 0;
    neighbor[2].row = 0;neighbor[2].col = -1;
    neighbor[3].row = -1;neighbor[3].col = 0;

    for (int i = 0;i<=size+1;++i)
    {
        pixel[0][i] = pixel[size+1][i] = 0;
        pixel[i][0] = pixel[i][size+1] = 0;
    }

    int numOfNrs = 4;
    queue<position> q;
    position here,nbr;
    int id = 1;

    for (int r=1;r<=size;++r)
    {
        for(int c=1;c<=size;++c)
        {
            if(pixel[r][c] == 1)
            {
                pixel[r][c] == ++id;
                here.row = r;
                here.col = c;

                while(true)
                {
                    for(int i=0;i<numOfNrs;++i)
                    {
                        nbr.row = here.row + neighbor[i].row;
                        nbr.col = here.col + neighbor[i].col;

                        if(pixel[nbr.row][nbr.col] == 1)
                        {
                            pixel[nbr.row][nbr.col] == id;
                            q.push(nbr);
                        }
                    }

                    if(q.empty()) break;
                    here = q.front();
                    q.pop();
                }\   
            }

        }
    }
    
}