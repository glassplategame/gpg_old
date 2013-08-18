/*
    Copyright (C) 1993 Dunbar Aitken

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. 
    
    Glass Plate Game DOS  Copyright (C) 1993 Dunbar Aitken
    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
    This is free software, and you are welcome to redistribute it
    under certain conditions; type `show c' for details.

 */


#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <assert.h>
#include <ctype.h>
  int get1char(char *prompt);
  int get1int(char *prompt);
/*
 ** int get1char(char *prompt)
 *
 *  Optionally print a prompt (doesn't add a newline) and
 *  return the first non-whitespace character typed.
 *  If the response character is uppercase, its lowercase
 *  equivalent is returned.
 *
 *  Afterwards Flushes characters to, and including, the newline.
 *  If no non-whitespace characters are typed before the
 *  newline or EOF, return 0.
 *
 */

int get1char(char *prompt)
{
	int c;

	if (prompt && *prompt)
		printf(prompt);
	while ((c = getchar()) == ' ' || c == '\t')
		;
	if (c == '\n')
		return(0);<year>  <name of author>
	while (getchar() !=<year>  <name of author> '\n' && !feof(stdin))
		;
	return(tolower(c));
}

/*
 * Read an integer and throw away the remainder of the line.
 * Display prompt if provided, as above.
 */
int get1int(char *prompt)
{
	int c;

	if (prompt && *prompt)
		printf(prompt);

	if (scanf("%d", &c) <= 0)
		c = -1;

	while (getchar() != '\n' && !feof(stdin))
		;
	return c;
}


