#include "tsp.h"
#include <stdio.h>
#include <string.h>

void tsp_free(struct tsp* tsp)
{
	if (tsp->coords)
		free(tsp->coords);
}

void tsp_init(struct tsp* tsp)
{
	tsp->input_file = NULL;
	tsp->model_source = 0;
	tsp->coords = NULL;
}

/*
 * Parses command line arguments for the tsp instance
 * returns:
 * -1 if parse fails
 * 0 otherwise
 * */
int tsp_parse_arguments(int argc, char** argv, struct tsp* tsp)
{
	int modelSource = -1; // 0 random, 1 file load
	int userSetSeed = 0;
	int userSetNnodes = 0;
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-random")) {
			printf("Generating a random model\n");
			if (modelSource != -1) {
				perror("Can't use more than 1 mode\n");
				return -1;
			}
			modelSource = 0;
		} else if (!strcmp(argv[i], "-seed")) {
			printf("Setting seed for random model\n");
			tsp->seed = atoi(argv[++i]);
			userSetSeed = 1;
		} else if (!strcmp(argv[i], "-nnodes")) {
			printf("Setting number of nodes for random model\n");
			tsp->nnodes = atoi(argv[++i]);
			userSetNnodes = 1;
		} else if (!strcmp(argv[i], "-inputfile")) {
			printf("Setting input file for instance\n");
			tsp->input_file = argv[++i];
			if (modelSource != -1) {
				perror("Can't use more than 1 mode\n");
				return -1;
			}
			modelSource = 1;
		}
	}

	if (modelSource == 0) {
		if (userSetSeed == 0 | userSetNnodes == 0) {
			perror(
			    "Set seed and nnodes to user random generation\n");
			return -1;
		}
		tsp->model_source = 1;
	}

	else if (modelSource == 1) {
		if (tsp->input_file == NULL) {
			perror("Set an input file to use model loading\n");
			return -1;
		}
		tsp->model_source = 2;
	} else if (modelSource == -1) {
		perror("Please specify a mode to load the file\n");
		return -1;
	}

	return 0;
}

void debug_print(struct tsp* tsp)
{
	printf("nnodes: %d\n", tsp->nnodes);

	printf("model_source: ");
	if (tsp->model_source == 1)
		printf("random\n");
	else if (tsp->model_source == 2)
		printf("input_file\n");
	else
		printf("NOT SET\n");

	printf("seed: %d\n", tsp->seed);
	printf("input_file: %s\n", tsp->input_file);
}

void debug_print_coords(struct tsp* tsp)
{
	printf("%d nodes:\n", tsp->nnodes);
	for (int i = 0; i < tsp->nnodes; i++) {
		printf("%d: (%lf, %lf)\n", i + 1, tsp->coords[i].x,
		       tsp->coords[i].y);
	}
}
