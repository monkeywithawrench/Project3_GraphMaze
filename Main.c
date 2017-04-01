/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: Main.c
 * Assignment Number: 3
 * Date Due: Mar 13, 2016
 * 
 *  Created on: Mar 7, 2016
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 ***************************************************************/


#include "Graph.h"
#include "Maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/** Returns the square root of the number passed if it's a perfect square, or 0 if not.
 * @param {int} num - the number to find the square root of
 * @return int either the square root or 0 if not a perfect square
 */
int getSqrt(int num);


/**
 * the main function
 */
int main(int argc, char *argv[])
{
	if ( (argc==2) && (strcmp(argv[1],"-Debug")==0) )
		fprintf(stdout,"Debug not implemented\n");


	int graphSize;	//the number of nodes in the graph. (must be a perfect square)
	int root; //the root of the graphSize

	do {
		fprintf(stdout, "Please enter the number of nodes in the graph(maze, must be a perfect square) or -1 to exit: ");
		fscanf(stdin, "%d", &graphSize);
		root = getSqrt(graphSize);
		if (root !=0 )
		{
			GraphP graph = newGraph(graphSize, root);
			//fprintf(stdout, "\n");
			//printGraph(graph);
			//fprintf(stdout, "\n\n");
			primsAlgorithm(graph);
			//printGraph(graph);
			fprintf(stdout, "\n");
			FILE *outFile = fopen("Maze.txt","w");
			if( outFile == NULL )
			{
				fprintf(stderr, "file \"Maze.txt\" could not be open!!! Program exiting!\n");
				exit(0);
			}
			printMaze(graph, stdout);
			printMaze(graph, outFile);
			fclose(outFile);
			printPPM(graph);
		}
	} while ( graphSize != -1);

	/*
	//srandom( (unsigned int)time(NULL) );
	//int n = (int)random();
	//time_t t  = time(NULL);
	//srand((unsigned int)t);
	//int n = (int)rand();
	//int i;
	//for(i = 0; i<10; i++)
	//fprintf(stdout, "Random Number = %d\n", (int)rand());
	//fprintf(stdout, "Random Number = %d\n", (int)(t%RAND_MAX));
	//fprintf(stdout, "\nRan_MAX = %d\n", RAND_MAX); //RAND_MAX is 32767 in this case. max 16bit signed int.
	*/
	return(0);
}



/** Returns the square root of the number passed if it's a perfect square, or 0 if not.
 * @param {int} num - the number to find the square root of
 * @return int either the square root or 0 if not a perfect square
 */
int getSqrt(int num)
{
	if (num <=0 )
		return( 0 );
	double root = sqrt( (double)num );
	int intRoot = (int)root;
	if ( intRoot*intRoot == num )
		return( intRoot );
	else if ( (intRoot+1) * (intRoot+1) == num)
		return( intRoot+1 );
	else if ( (intRoot-1) * (intRoot-1) == num)
		return( intRoot-1 );
	else
		return( 0 );
}

