/*
 * =====================================================================================
 *
 *       Filename:  ulife_kernel.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/20/2010 03:07:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  huys (hys), huys03@gmail.com
 *        Company:  hu
 *
 * =====================================================================================
 */
#include <iostream>

using std::cout;
using std::endl;

#include "ulife_kernel.h"

int ULifeGame::neighbor_count(int row, int col)
{
    int i, j;
    int count = 0;
    for (i = row-1; i<=row+1; ++i)
    {
        for (j=col-1; j<=col+1; ++j)
        {
            count += grid[i][j];
        }
        count -= grid[row][col]; // Reduce count, since cell is not in its own neighbor
    }
    return count;
}

void ULifeGame::update()
{
    int row, col;
    int new_grid[maxrow+2][maxcol+2];
    for (row=1; row<=maxrow; ++row)
    {
        for (col=1; col<=maxcol; ++col)
        {
            switch (neighbor_count(row, col))
            {
            case 2:
                new_grid[row][col] = grid[row][col];
                break;
            case 3:
                new_grid[row][col] = 1;
                break;
            default:
                new_grid[row][col] = 0; // Cell is now dead.

            }

        }
    }

    for (row=1; row<=maxrow; ++row)
    {
        for (col=1; col<=maxcol; ++col)
        {
            grid[row][col] = new_grid[row][col];
        }
    }

}

void ULifeGame::initialize()
{
    int row, col;
    for (row=0; row<=maxrow; ++row)
    {
        for (col=0; col<=maxcol; ++col)
        {
            grid[row][col] = 0;
        }
    }

    grid[5][5] = 1;
    grid[6][5] = 1;
    grid[7][5] = 1;
    grid[8][5] = 1;
    grid[9][5] = 1;
    grid[10][5] = 1;

}

void ULifeGame::print()
{
    int row, col;
    cout << "\nThe current Life configuration is :" << endl;

    for (row=1; row<=maxrow; ++row)
    {
        for (col=1; col<=maxcol; ++col)
        {
            if (1 == grid[row][col])
            {
                cout << '*';
            }
            else
            {
                cout << 'x';
            }
        }
        cout << endl;
    }
    cout << endl;
}

