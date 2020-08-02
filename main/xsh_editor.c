/* xsh_editor.c - xsh_editor */

#include <xinu.h>
#include <stdio.h>

// #include "text_buffer.h"
#define NLINES 8
#define LINE_LEN 32
#define BUFFER_LEN  (NLINES*LINE_LEN)

const __flash char editor_banner0[] = "text editor - page:";
const __flash char editor_banner1[] = "-- [SAVE] & EXIT: press ESC then ! --";

/* editor_insert:
 *   b : buffer
 *   c : ascii
 *   i : index
 */
void editor_insert(char * buf, char c, int line, int i)
{
	int j;
	char * b = buf + (line*LINE_LEN);
	for (j=(LINE_LEN-1); j>i; j--)
		*(b+j) = *(b+j-1);
	*(b+i) = c;
	for (j=i; j<LINE_LEN; j++)
		if ((*(b+j)) == 0)
			break;
		else
			printf("%c", *(b+j));
	for (j=j-i-1; j>0; j--)
		printf("\033[D");
}

void editor_del(char * buf, int line, int i)
{
	int j;
	char * b = buf + (line*LINE_LEN);
	printf("\033[D");
	for (j=i; j<(LINE_LEN); j++) {
		*(b+j) = *(b+j+1);
		
		if ((*(b+j)) == 0) {
			printf(" ");
			printf("\033[D");
			break;
		} else
			printf("%c", *(b+j));
	}
	*(b+j+1) = 0;
	printf(" ");
	for (j=j-i; j>=0; j--)
		printf("\033[D");
	//for (j=0; j<LINE_LEN-i;j++)
	//	printf("\033[D");
}

static void clear(void)
{
	fprintf(0, "\033[2J");
	fprintf(0, "\033[H");
}

void printnl(void)
{
	printf("\n\r");
}



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
	char buffer[NLINES*LINE_LEN];
	int page = 0;
	int i = 0;
	int j = 0;
	int dev = 0;
	int c;
	int line = 0;
	int col = 0;

	clear();
	fprintf(dev, "%S %i\n", editor_banner0, page);

	for (i=0; i<LINE_LEN; i++)
		printf("-");
	printnl();
	for (i=0; i<NLINES*LINE_LEN; i++) {
		buffer[i] = 0;
		printf(" ");
		if (i % LINE_LEN == 0)
			printnl();
	}
	printnl();
	fprintf(dev, "%S", editor_banner1);
	fprintf(dev, "\033[H");
	fprintf(dev, "\033[2B");

	// control(dev, TC_NOECHO, 0, 0);
 
	control(dev, TC_MODER, 0, 0);

        while (TRUE) {
		// c = -1;
		c = getc(0);
//		printf("%i \n", c);
		switch (c) {
		case 27:		/* ESC */
			c = getc(0);
			if (c == '[') {
				c = getc(0);
				switch (c) {
				case 'A': 		/* UP */
					if (line == 0)
						break;
					col = 0;
					line--;
					printf("\033[A");
					printf("\r");
					break;
				case 'B': 		/* DOWN */
					if (line == (NLINES-1))
						break;
					col = 0;
					line++;
					printf("\033[B");
					printf("\r");
					break;
				case 'D': 
					if (col == 0)
						break;
					col--;
					printf("\033[D");
					break;
				case 'C': 
					if (col == LINE_LEN)
						break;
					col++;
					printf("\033[C");
					break;
				default:
					break;
				}
			} else if (c == '!') { 		/* EXIT */
					/* SAVE ? */
					control(dev, TC_MODEC, 0, 0);
					clear();
					return 0;
			}
			continue;
			break;
		case 127:
			if (col == 0)
				break;
		//	fprintf(dev, "\033[1D");
			col--;
			editor_del(buffer, line, col);
			break;
		case '\r':
			if (line == NLINES-1) {	/* NEXT PAGE */
				/* SAVE ? */
				break;
			}
			line++;
			col = 0;
			printnl();
			break;
		default:
			if (col == LINE_LEN)
				break;
			editor_insert(buffer, c, line, col);
			col++;
			break;
		}
					

/*
		if (c == '\r') {
			for (i=col;i<LINE_LEN;i++)
				printf(" ");
			printf("\n");
			col=0;
			line++;
			if (line > NLINES) {
				// pasar_pagina();
			}
		//	for (j=line;j<NLINES;j++)
		}
		printf("%c", c);

		buffer[line*LINE_LEN+col] = c;
		col++;
		if (col > LINE_LEN) {
			col = 0;
			line++;
			printf("\n\r");
			if (line > NLINES) {
				// pasar_pagina();
			}
		}
*/
			
	}
		

                // RAFA
	return 0;
}
