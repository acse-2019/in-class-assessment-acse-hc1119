#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// CID 01800836
// email hc1119@ic.ac.uk
// v studio
// windows
// lp = 12
// serial time = 12.6774
// parallel time = 12.0612

using namespace std;

//Note that this is a serial implementation with a periodic grid
vector<vector<bool>> grid, new_grid;
int imax, jmax;
int max_steps = 100;

int num_neighbours(int ii, int jj)
{
	int ix, jx;
	int cnt = 0;
#pragma omp parallel for collapse(2)
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (i != 0 || j != 0)
			{
				ix = (i + ii + imax) % imax;
				jx = (j + jj + jmax) % jmax;
				if (grid[ix][jx]) cnt++;
			}
	return cnt;
}

int num_neighbours0(int ii, int jj)
{
	int ix, jx;
	int cnt = 0;
#pragma omp parallel sections num_threads(8) default(shared)
	{
#pragma omp section
		{
			ix = (-1 + ii + imax) % imax;
			jx = (-1 + jj + jmax) % jmax;
			if (grid[ix][jx]) cnt++;
			//cout << "id = " << omp_get_thread_num() << endl;
		}
#pragma omp section
		{
			ix = (-1 + ii + imax) % imax;
			jx = (0 + jj + jmax) % jmax;
			if (grid[ix][jx]) cnt++;
			//cout << "id = " << omp_get_thread_num() << endl;
		}
#pragma omp section
		{
			ix = (-1 + ii + imax) % imax;
			jx = (1 + jj + jmax) % jmax;
			if (grid[ix][jx]) cnt++;
		}
#pragma omp section
		{
			ix = (0 + ii + imax) % imax;
			jx = (-1 + jj + jmax) % jmax;
			if (grid[ix][jx]) cnt++;
		}
#pragma omp section
		{
			ix = (0 + ii + imax) % imax;
			jx = (1 + jj + jmax) % jmax;
			if (grid[ix][jx]) cnt++;
		}
#pragma omp section
		{
			ix = (1 + ii + imax) % imax;
			jx = (-1 + jj + jmax) % jmax;
			if (grid[ix][jx]) cnt++;
		}
#pragma omp section
		{
			ix = (1 + ii + imax) % imax;
			jx = (0 + jj + jmax) % jmax;
			if (grid[ix][jx]) cnt++;
		}
#pragma omp section
		{
			ix = (1 + ii + imax) % imax;
			jx = (1 + jj + jmax) % jmax;
			if (grid[ix][jx]) cnt++;
		}
	}
	return cnt;
}

void grid_to_file(int it)
{
	stringstream fname;
	fstream f1;
	fname << "output" << "_" << it << ".dat"; 

	// we can't use parallel omp here since we need to output in certain order
	// so that we need to use omp critical, which won't speed up the code.

	f1.open(fname.str().c_str(), ios_base::out);
	for (int i = 0; i < imax; i++)
	{
		for (int j = 0; j < jmax; j++)
			f1 << grid[i][j] << "\t";
		f1 << endl;
	}
	f1.close();
}

void do_iteration(void)
{
#pragma omp parallel for collapse(2) // use #pragma omp for collapse(2) to paralize the nested for loop.
	for (int i = 0; i < imax; i++)
		for (int j = 0; j < jmax; j++)
		{
			new_grid[i][j] = grid[i][j];
			int num_n = num_neighbours(i, j);
			if (grid[i][j])
			{
				if (num_n != 2 && num_n != 3)
					new_grid[i][j] = false;
			}// shouldn't use omp critical here since it won't speed up the code.
			else if (num_n == 3) new_grid[i][j] = true;
		}
	grid.swap(new_grid);
}

void do_iteration0(void)
{
    omp_set_nested(1);
#pragma omp parallel for shared(grid)
    for (int i = 0; i < imax; i++)
#pragma omp parallel for shared(grid)
        for (int j = 0; j < jmax; j++)
        {
            new_grid[i][j] = grid[i][j];
            int num_n = num_neighbours(i, j);
            if (grid[i][j])
            {
                if (num_n != 2 && num_n != 3)
                    new_grid[i][j] = false;
            }// shouldn't use omp critical here since it won't speed up the code.
            else if (num_n == 3) new_grid[i][j] = true;
        }
    grid.swap(new_grid);
}

void do_iteration1(void)
{
    for (int i = 0; i < imax; i++)
#pragma omp parallel for firstprivate(grid) // the grids in different threads are independent.
        for (int j = 0; j < jmax; j++)
        {
            new_grid[i][j] = grid[i][j];
            int num_n = num_neighbours(i, j);
            if (grid[i][j])
            {
                if (num_n != 2 && num_n != 3)
                    new_grid[i][j] = false;
            }// shouldn't use omp critical here since it won't speed up the code.
            else if (num_n == 3) new_grid[i][j] = true;
        }
    grid.swap(new_grid);
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	imax = 100;
	jmax = 100;

	double start = omp_get_wtime(); //start time measurement

	grid.resize(imax, vector<bool>(jmax));
	new_grid.resize(imax, vector<bool>(jmax));

	//set an initial random collection of points - You could set an initial pattern
	omp_set_nested(1); // use a nested omp parallel here.
#pragma omp parallel shared(grid)
	{
#pragma omp for
		for (int i = 0; i < imax; i++)
#pragma omp parallel shared(grid)
		{
#pragma omp for
			for (int j = 0; j < jmax; j++) grid[i][j] = (rand() % 2);
		}
	}// since each grid is independent, we can generate each one at the same time.

	for (int n = 0; n < max_steps; n++)
	{
		cout << "it: " << n << endl;
		do_iteration();
		grid_to_file(n);
	}

	double end = omp_get_wtime(); //end time measurement
	double all = end - start;
	std::cout << "all " << all << std::endl;

	return 0;
}
