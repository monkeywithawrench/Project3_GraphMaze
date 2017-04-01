/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: Maze.h
 * Assignment Number: 3
 * Date Due: Mar 13, 2016
 * 
 *  Created on: Mar 9, 2016
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 ***************************************************************/

#ifndef MAZE_H_
#define MAZE_H_

#include "Graph.h"
#include <stdio.h>

#define MAZE_CHARACTER '*'

/**
 * Prints out the maze to the file pointer passed
 * @param {GraphP} graph - the graph to print the maze from
 * @param {FILE *} outFile - the file to print to
 */
void printMaze( GraphP graph, FILE *outFile);


/**
 * Prints out the maze to Maze.ppm in PPM format
 * @param {GraphP} graph - the graph to print the maze from
 */
void printPPM( GraphP graph);


#endif /* MAZE_H_ */
