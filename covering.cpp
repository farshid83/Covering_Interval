/*
 * covering.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: user
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct interval
{
	int min;
	int max;
	int state; // 0
	int length;
};

interval target;
interval* intervals;
int size;

int GetMinIntervals(int min, int max)
{
	if(min >= max)
		return 0;
	int longest_length = 0;
	int longest_index = -1;
	for(int i = 0; i < size; i++)
	{
		if((intervals[i].max >= min)
				&& (intervals[i].min <= min)
				&& (longest_length < intervals[i].max - min))
		{// intervals[i] cover min point and it's longest?
			longest_length = intervals[i].max - min;
			longest_index = i;
		}
	}
	if(longest_length > 0)
	{
		printf("[%d,%d]\n", intervals[longest_index].min, intervals[longest_index].max);
		if(intervals[longest_index].max >= max)
		{
			return 1;
		}
		else
		{
			int recMin = GetMinIntervals(intervals[longest_index].max, max);
			if(recMin > 0)
				return 1 + recMin;
			else
				return 0;
		}
	}
	else
	{
		return 0;
	}

}


int main ( int arc, char **argv ) // target_interval other_intervals size -> 10 90 0 100 1000
{
	if(arc != 6)
		exit(EXIT_FAILURE);

	//char* argv[6] = {"app", "1", "100", "0", "100", "10"};

	srand (time(NULL)); // init random generator

	target.min = atoi(argv[1]);
	target.max = atoi(argv[2]);
	target.state = 0;
	target.length = target.max - target.min;

	int Imin = atoi(argv[3]);
	int length = (int)(atoi(argv[4] - Imin));
	size = atoi(argv[5]);
	intervals = new interval [size];
	for(int i = 0; i < size; i++)
	{
		int a = rand()%length + Imin;
		int b = a + rand()%(target.length/10);
		intervals[i].min = a;
		intervals[i].max = b;
		//printf("[%d,%d)\n", a, b);
	}

	printf("[%d,%d] can be covered with %d intervals!\n", target.min, target.max, GetMinIntervals(target.min, target.max));

	return 0;
}

