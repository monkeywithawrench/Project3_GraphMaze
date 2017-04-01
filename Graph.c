/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: Graph.c
 * Assignment Number: 3
 * Date Due: Mar 13, 2016
 * 
 *  Created on: Mar 7, 2016
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 ***************************************************************/

#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>





/**
 * initializes all the elements of a an adjacency matrix for a grid graph
 * @param {**matrix} matrix - the adjacency matrix
 * @param {int} graphSize - the size of the graph
 * @param {int} width - the width of the graph
 */
void initializeAdjacencyMatrix( int **matrix, int graphSize, int width);



/**
 * Creates, allocates, and initializes a new graph
 * @param {int} graphSize - the size of the graph
 * @param {int} width - the width of the graph
 * @return GraphP the newly created graph
 */
GraphP newGraph( int graphSize, int width)
{
	GraphP graph = /* (Graph) */ malloc(sizeof(Graph));
	if(graph == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Graph Malloc failed!");
		return(graph);
	}
	graph->graphSize = graphSize;
	graph->width = width;

	graph->adjacencyMatrix =malloc(sizeof(int *)*graphSize);
	if(graph->adjacencyMatrix == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Matrix outside array Malloc failed!");
		return(graph);
	}

	int i;
	for(i=0; i<graphSize; i++)
	{
		int *temp = malloc(sizeof(int)*graphSize);
		graph->adjacencyMatrix[i] = temp;// malloc(sizeof(int)*graphSize);
		if(graph->adjacencyMatrix[i] == NULL)	//Checks malloc success.
		{
			fprintf(stderr, "ERROR! Matrix inside array Malloc failed!");
			return(graph);
		}
	}

	initializeAdjacencyMatrix( graph->adjacencyMatrix, graphSize, width); //initialize list
	//all done here, return the graph
	return( graph );
}


/**
 * initializes all the elements of a an adjacency matrix for a grid graph
 * @param {**matrix} matrix - the adjacency matrix
 * @param {int} graphSize - the size of the graph
 * @param {int} width - the width of the graph
 */
void initializeAdjacencyMatrix( int **matrix, int graphSize, int width)
{
	srand((unsigned int)time(NULL)); //seed rand()
	int i=0, j=0;
	for(i=0; i<graphSize; i++) //initialize matrix to INFINITY
	{
		for(j=0; j<graphSize; j++)
			matrix[i][j] = INFINITY;
	}

	for(i=0; i<graphSize; i++)
	{
		if( i+width < graphSize) //set the outside bands
		{
			int random = rand();
			matrix[i][i+width] = random;
			matrix[i+width][i] = random;
		}
		if( (i+1 < graphSize) && ((i+1)%width) ) //set the inside bands
		{
			int random = rand();
			matrix[i][i+1] = random;
			matrix[i+1][i] = random;

		}
	}


	return;
}


/**
 * prints out the graph passed in csv format.
 * @param {GraphP} graph - the graph to print
 */
void printGraph( GraphP graph)
{

	int i, j;
	for(i=0; i<graph->graphSize; i++) //initialize matrix to INFINITY (-1)
	{
		for(j=0; j<graph->graphSize; j++)
		{
			int x = graph->adjacencyMatrix[i][j];
			fprintf(stdout, "%d, ", x);
		}
		fprintf(stdout, "\n");
	}
}


/**
 * Creates a MST of the graph passed using Prim's Algorithm
 * @param {GraphP} graph - the graph to generate a MST for
 */
void primsAlgorithm( GraphP graph)
{
	int matrix[graph->graphSize][3]; // (Known | Weight | Path) You already know the vertex, since it's the key.
	int i,j;
	for( i=0; i<graph->graphSize; i++)
	{
		matrix[i][0] = FALSE;
		matrix[i][1] = INFINITY;
		matrix[i][2] = -1; //-1 is not a vertex
	}
	int isFinished = FALSE;
	int isFirst = TRUE;

	while (!isFinished)
	{
		if(isFirst)
		{
			matrix[0][0] = TRUE;
			matrix[0][1] = 0;
			matrix[0][2] = -1; //still not a vertex, as it would just be a path to itself. Dummy.
			isFirst = FALSE;
			for( i=0; i<graph->graphSize; i++)
			{
				if( graph->adjacencyMatrix[0][i] != INFINITY)
				{
					matrix[i][1] = graph->adjacencyMatrix[0][i];
					matrix[i][2] = 0;
				}
			}

		}
		//INITIALIZATION IS NOW DONE. THANK GOD.
		int tempV;
		int tempW = INFINITY; //temp var.
		for (i=0; i<graph->graphSize; i++) //finding the lowest weight edge to an unknown vertex
		{
			if( (matrix[i][1] < tempW) && (matrix[i][0] == FALSE) )
			{
				tempV = i; //tempV is a vertex here.
				tempW = matrix[i][1];
			}
		}
		//now that we have the vertex with the lowest connecting weight that is unknown, process it.
		matrix[tempV][0] = TRUE; //known now.
		for( i=0; i<graph->graphSize; i++)
		{
			if( (graph->adjacencyMatrix[tempV][i] != INFINITY) && (graph->adjacencyMatrix[tempV][i] < matrix[i][1]) && (matrix[i][0] == FALSE) )
			{ //if there is an edge here and the weight is LESS than the currently known weight for this edge
				matrix[i][1] = graph->adjacencyMatrix[tempV][i];
				matrix[i][2] = tempV;
			}
		}


		isFinished = TRUE; //temporary, pay attention to next few lines.
		for( i=0; i<graph->graphSize; i++) //now we check to see if every vertex has been found.
		{
			if( matrix[i][0] == FALSE )
				isFinished = FALSE;
		}
		// now we iterate once again.
	}
	// CONGRATULATIONS! WE NOW HAVE A MINIMAL SPANNING TREE STORED IN matrix!
	// Now we just have to send it somewhere as an adjacency matrix!

	/* PRINT MATRIX
	fprintf(stderr, "\n");
	for( i=0; i<graph->graphSize; i++)
	{
		fprintf(stderr, "Vertex: %d, Known: %d, Weight: %d, Path: %d\n", i, matrix[i][0], matrix[i][1], matrix[i][2] );
	}
	*/

	//We're just gonna apply the MST to the existing adjacency matrix
	for( i=0; i<graph->graphSize; i++) //initialize new matrix
	{
		for( j=0; j<graph->graphSize; j++)
			graph->adjacencyMatrix[i][j] = INFINITY;
	}
	for( i=1; i<graph->graphSize; i++) //apply MST to matrix
	{
		j = matrix[i][2]; //store the connected vertex in j
		graph->adjacencyMatrix[i][j] = matrix[i][1]; //store weight
		graph->adjacencyMatrix[j][i] = matrix[i][1]; //store weight
	}
}


/**
 * Checks to see if there is a connection between the 2 vertices passed in the graph passed
 * @param {GraphP} graph - the graph to search
 * @param {int} vert1 - the first vertex
 * @param {int} vert2 - the second vertex
 */
int isLink( GraphP graph, int vert1, int vert2)
{
	if(graph->adjacencyMatrix[vert1][vert2] != INFINITY)
		return(TRUE);
	else
		return(FALSE);
}
