/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: Maze.c
 * Assignment Number: 3
 * Date Due: Mar 13, 2016
 * 
 *  Created on: Mar 9, 2016
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 ***************************************************************/

#include "Maze.h"
#include <stdio.h>
#include <stdlib.h>


void printWall(FILE *outFile);
void printSpace(FILE *outFile);


/**
 * Prints out the maze to the file pointer passed
 * @param {GraphP} graph - the graph to print the maze from
 * @param {FILE *} outFile - the file to print to
 */
void printMaze( GraphP graph, FILE *outFile)
{
	int width = graph->width;
	int i, j;
	//Print top line
	fprintf(outFile, "\n%c ", MAZE_CHARACTER);
	for( i=0; i<(2*width-1); i++)
		fprintf(outFile, "%c", MAZE_CHARACTER);
	fprintf(outFile, "\n");

	//PRINT BODY
	for( i=0; i<width; i++) //
	{
		fprintf(outFile, "%c ", MAZE_CHARACTER);
		for( j=1; j<width; j++)	//Print horizontal spaces between vertices
		{
			if( isLink(graph, (i*width)+j, (i*width)+j-1) )
				fprintf(outFile, "  ");
			else
				fprintf(outFile, "%c ", MAZE_CHARACTER);
		}
		fprintf(outFile, "%c\n", MAZE_CHARACTER);

		if(i < width-1) 	//Print vertical spaces between vertices
		{
			fprintf(outFile, "%c", MAZE_CHARACTER);
			for( j=0; j<width; j++)
			{
				if( isLink(graph, (i*width)+j, ((i+1)*width)+j) )
					fprintf(outFile, " %c", MAZE_CHARACTER);
				else
					fprintf(outFile, "%c%c", MAZE_CHARACTER, MAZE_CHARACTER);
			}
			fprintf(outFile, "\n");
		}
	}

	//Print last line
	for( i=0; i<(2*width-1); i++)
		fprintf(outFile, "%c", MAZE_CHARACTER);
	fprintf(outFile, " %c", MAZE_CHARACTER);
	fprintf(outFile, "\n\n");
}



/**
 * Prints out the maze to Maze.ppm in PPM format
 * @param {GraphP} graph - the graph to print the maze from
 */
void printPPM( GraphP graph)
{
	FILE *outFile = fopen("Maze.ppm","w");
	if( outFile == NULL )
	{
		fprintf(stderr, "file \"Maze.ppm\" could not be open!!! Program exiting!\n");
		exit(0);
	}
	int width = graph->width;
	int i, j;
	// PRINT HEADER
	fprintf(outFile, "P3\n");
	fprintf(outFile, "# this is a comment\n");
	fprintf(outFile, "%d %d\n", 2*width+1, 2*width+1);
	fprintf(outFile, "255\n\n");
	//Print top line
	//fprintf(stdout, "\n%c ", MAZE_CHARACTER);
	fprintf(outFile, "\n");
	printWall(outFile);
	printSpace(outFile);
	for( i=0; i<(2*width-1); i++)
		printWall(outFile); //fprintf(stdout, "%c", MAZE_CHARACTER);
	fprintf(outFile, "\n");

	//PRINT BODY
	for( i=0; i<width; i++) //
	{

		printWall(outFile); //fprintf(stdout, "%c ", MAZE_CHARACTER);
		printSpace(outFile);
		for( j=1; j<width; j++)	//Print horizontal spaces between vertices
		{
			if( isLink(graph, (i*width)+j, (i*width)+j-1) )
			{
				printSpace(outFile);
				printSpace(outFile);
				//fprintf(stdout, "  ");
			}
			else
			{
				printWall(outFile);
				printSpace(outFile);
				//fprintf(stdout, "%c ", MAZE_CHARACTER);
			}
		}
		printWall(outFile);//fprintf(stdout, "%c\n", MAZE_CHARACTER);
		fprintf(outFile, "\n");

		if(i < width-1) 	//Print vertical spaces between vertices
		{
			printWall(outFile); //fprintf(stdout, "%c", MAZE_CHARACTER);
			for( j=0; j<width; j++)
			{
				if( isLink(graph, (i*width)+j, ((i+1)*width)+j) )
				{
					printSpace(outFile);
					printWall(outFile); //fprintf(stdout, " %c", MAZE_CHARACTER);
				}
				else
				{
					printWall(outFile);
					printWall(outFile); //fprintf(stdout, "%c%c", MAZE_CHARACTER, MAZE_CHARACTER);
				}
			}
			fprintf(outFile, "\n");
		}
	}

	//Print last line
	for( i=0; i<(2*width-1); i++)
		printWall(outFile); //fprintf(stdout, "%c", MAZE_CHARACTER);
	//fprintf(stdout, " %c", MAZE_CHARACTER);
	printSpace(outFile);
	printWall(outFile);
	fclose(outFile);
	//fprintf(outFile, "\n\n");
}


void printWall(FILE *outFile)
{
	fprintf(outFile, "0 0 0 ");
}


void printSpace(FILE *outFile)
{
	fprintf(outFile, "255 255 255 ");
}
