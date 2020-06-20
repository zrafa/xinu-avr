/* xsh_editor.c - xsh_editor */

#include <xinu.h>
#include <stdio.h>

#define NLINES 10
#define LINE_LEN 24
/*------------------------------------------------------------------------
 * xhs_editor - text editor 
 *------------------------------------------------------------------------
 */
shellcmd xsh_editor(int nargs, char *args[])
{

/*
	int32	i;

	if (nargs > 1) {
		printf("%s", args[1]);

		for (i = 2; i < nargs; i++) {
			printf(" %s", args[i]);
		}
	}
	printf("\n");
*/
	char buffer[NLINES][LINE_LEN+1];
	int page = 0;
	int i = 0;
	int dev = 0;
	int c;
	int cursor = 0;
	int line = 0;

	fprintf(dev, "\033[2J");
	fprintf(dev, "\033[H");
	fprintf(dev, "Text editor. page: %i\n", page);

	memset(buffer, NLINES*(LINE_LEN+1), 0);
	for (i=0; i<LINE_LEN; i++)
		printf("%s\n",buffer[i]);

	// control(dev, TC_NOECHO, 0, 0);
 
	control(dev, TC_MODER, 0, 0);

        while (TRUE) {
		// c = -1;
		c = getc(0);
		//printf("%i \n", c);

		if (c == 27) {
			c = getc(0);
			if (c == '[') {
				c = getc(0);
				switch (c) {
				case 'D': 
					cursor--; if (cursor < 0) cursor = 0;
					printf("\033[D");
					break;
				case 'C': 
					cursor++; 
					printf("\033[C");
					if (cursor > LINE_LEN) {
						cursor = 0;
						line++;
						printf("\n\r");
					}
					break;
				default:
					break;
				}
			}
			continue;
		}

		printf("%c", c);
		buffer[line][cursor] = c;
		cursor++;
		if (cursor > LINE_LEN) {
			cursor = 0;
			line++;
			printf("\n\r");
			if (line > NLINES) {
				// pasar_pagina();
			}
		}
			
	}
		

                // RAFA
	return 0;
}
