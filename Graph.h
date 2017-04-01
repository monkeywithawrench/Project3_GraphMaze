/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: Graph.h
 * Assignment Number: 3
 * Date Due: Mar 13, 2016
 * 
 *  Created on: Mar 8, 2016
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 ***************************************************************/

#ifndef GRAPH_H_
#define GRAPH_H_


#define INFINITY INT_MAX
#define TRUE 1
#define FALSE 0


typedef struct Graph
{
	int graphSize, width;
	int **adjacencyMatrix;
}Graph, *GraphP;


/**
 * Creates, allocates, and initializes a new graph
 * @param {int} graphSize - the size of the graph
 * @param {int} width - the width of the graph
 * @return GraphP the newly created graph
 */
GraphP newGraph( int graphSize, int width);


/**
 * prints out the graph passed in csv format.
 * @param {GraphP} graph - the graph to print
 */
void printGraph( GraphP graph);


/**
 * Creates a MST of the graph passed using Prim's Algorithm
 * @param {GraphP} graph - the graph to generate a MST for
 */
void primsAlgorithm( GraphP graph);


/**
 * Checks to see if there is a connection between the 2 vertices passed in the graph passed
 * @param {GraphP} graph - the graph to search
 * @param {int} vert1 - the first vertex
 * @param {int} vert2 - the second vertex
 */
int isLink( GraphP graph, int vert1, int vert2 );



#endif /* GRAPH_H_ */
