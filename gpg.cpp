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

/* +++++++++++++++++++++++
   File: GPG.CPP Version 39        revised August 3, 1993
++++++++++++++++++++++++++  */

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

       /*  variable type and variable declarations  */



/* =====================================================================
The game uses cubes whose record here contains the roster number of the
player originally placing it.  Also in the record: a number indicates the
card on which it was placed; a number notes the chain of thought (color) it
extended; a number notes the face to which it was last turned (state); and a
number shows the cube from which it extended the chain or branched.   The
cubes themselves have the lettered sides, "C", "P", and "O", and a blank
side, "void", showing by which side is facing upwards (its current "state)".
There are 24 cubes, numbered for bringing them into use consecutively.
======================================================================== */

#define allowed 1
#define disallowed 0
typedef struct
{
int player;
int card;
int color;
int state;
int from_what_cube;
int player_p_c;
int player_o_v;
char comment1a[81], comment1b[81], comment1c[81];
char comment2a[81], comment2b[81];
char comment3a[81];
} cube_status;

char sure;

char * gifs[41] = {"none", "Ambivalence", "Anthropomorphism",
 "Art vs. Nature","fundamental Theorem of Calculus", "City as Artifact",
 "Coding", "Contemplation","Creation","Education",
 "Emotional Manipulation", "Freedom", "Gestalt", "harmony", "Struggle",
 "Hidden Potential", "Intuition", "Joy", "Magic",
 "Multiplication of Mechanical Advantage", "metamorphosis","Monetary Value",
 "Myth", "Nature Tending Towards Perfection",
 "Ontogeny Recapitulating Phylogeny", "Perspective",
 "Reaching out / Trying", "Return", "Society as Active / Passive Hierarchy",
 "Structural Strength", "Structured Improvisation", "Struggle", "Synergy",
 "syntax", "Unwanted Relationships", "Wavicle", "...", "...", "...", "..."};

char * gifs2[41] = {"Ambivalenz","Anthropomorphismus","Kunst und Natur",
 "UnerwÅnschte Verbindungen","Die Stadt als Kunstwerk","Coding",
 "Kontemplation","Sch"pfung","Ausbildung","GefÅhlmanipulation",
 "Freiheit","Gestalt","Harmonie","Kampf","Versteckte M"glichkeiten",
 "Intuition","Freude","Magik","Multiplikation des mechanishen Vorteils",
 "Metamorphose","Geldwert","Mythen","Natur entwickelt sich zur Perfektion",
 "Ontogenie wiederholt Phylogenie","Perspektive",
 "Sich ausstrecken","RÅckkehr","...","StÑrke der Struktur",
 "Strukturelle Improvisation","...","Synergetik","Syntax","...",
 "Welle-Teilchen Dualismus"};



int i, j, k, l, m, players, disk_choice, keep_playing;
int stats = 1;
int cube_of_move = 1;
int previous_player = 0;
int ruling, move_request;
int request_cnt = 0;
char line_response[10];
previous_of_color[5] = {0, 0, 0, 0, 0};
typedef cube_status cubes_status[25];
cubes_status cubes, cubes2, moves;
const char side[6] = {'#','p','c','o',' '};
const char hue[6] = {'r','b','g','y','o'};
const char action[8] = {'-','s','x','b','p','c','o','v'};
char * gif_e;
char * gif_g;
char moves_screen[80*24*2];
char card_list[80*24*2];
char * filenames[3] = {"A:REPLAY", "B:REPLAY.TXT", "C:REPLAY.TXT"};
char str_response[10];
char comment[260];
char language;
int is_replay = 0;
int replay_cube = 1;
int turnings_for_cube = 0;
int next_turning = 0;
int get_Move();
int rule_on_move(int, int, int, int, int, int, int);
void update(int, int, int, int, int, int);
int get1char( char *);
int get1int(char *);
void store_transcript( cubes_status &moves, char * filename);
void get_transcript( cubes_status &moves, char * filename);
void print_cards(char language);
void menue_or_not(char * response, int language_mnot);
void get_comment(int, int);

/* end of global declarations; beginning of function bodies */


void main()
{
  char  response_mn = 'z';
  clrscr();
   do {
    response_mn = get1char("Which language? German or English (G/E)");
    sure = get1char("Are you sure? ");
  }
  while ((response_mn != 'g') && (response_mn != 'e') &&
    (response_mn !='G') && (response_mn != 'E') &&
    (sure != 'Y')  && (sure != 'y'));

  language = response_mn;
  clrscr();
  if(language == 'E')
     language = 'e';
  if(language == 'G')
     language = 'g';
  if(language == 'e')
  {
    printf(" GLASS PLATE GAME(R)  Copyright (C), 1993, by Dunbar");
    printf(" Aitkens\n\n");
    printf("This program is for study of rules to The Glass Plate");
    printf(" Game\n");
    printf("(R), a board game, and to test the program as an idea");
    printf(" for\n");
    printf("developing a a computer assisted version or counterpart");
    printf(" of/to \n");
    printf("the board game.\n\n");

    printf("Minimal hardware is sufficient, an XT or compatable with 360\n");
    printf("disk drive and MDA monitor.  Input has these bounds: 1 - 8\n;");
    printf("color: R, Y, O, B, G; cube: 1-24; cube side: 'P', 'C', 'O'");
    printf(" or \n");
    printf("'V'; card: 1 - 40\n\n");

    printf("copies / updates of this program are available");
    printf(" by anonymous \n");
    printf("FTP to 128.192.2.13, directory pub/gaming");
    printf("/glass-plate-game.\n");
    printf("Internet messages about this program or about the");
    printf(" Glass Plate\n");
    printf("Game / playings should be mailed to caploc@csos.orst.edu.");
    printf("\n\n");


  }

  if(language == 'g')
  {
    printf("Glassplattenspiel\n\n");
    printf("Dieses Programm ist zum Studieren der Regeln des");
    printf(" Glassplattenspiel als\n");
    printf("Brettspiel, und zum Test des Programmes als erste Stufe");
    printf(" zur\n");
    printf("Entwicklung einer computerisierten Version des Brettspieles.\n\n");

    printf("Einfachste Hardware ist ausreichend: ein XT (oder Kompatibler)");
    printf(" mit 360 KB\n");
    printf("Disketten Laufwerk und MDA Monitor.  Die Eingabe M\"glichkeiten");
    printf(" sind: 1-8\n");
    printf("Spieler; Farben: R,B,G,Y,O (wobei 'Y' gelb darstellt);  1-24");
    printf(" WÅrfel; die\n");
    printf("WÅrfel Seiten sind: 'B', 'F', 'E','A','G'', 'U'; es gibt 40");
    printf(" Karten.\n\n");

    printf("Kopieren oder Updates dieses Programmes Sind");
    printf(" Åber anonymous ftp erhÑltlich\n");
    printf("FTP nach 128.193.2.13, Verzeichnis pub/gaming/glass-plate-game.");
    printf(" Damit\n");
    printf("zusammenhangerde text- und gif-files sind in");
    printf(" Unterverzeichnissen davon.\n");
    printf("Anmerkungen und Fragen bitte an Caploc@csos.orst.edu.\n\n");
  }
  do {
    if(language == 'e')
    {
       printf("loading your program from what drive?(A,B,C)\n");
       response_mn = get1char("");
       sure = get1char("Are you sure? ");
    }
    if(language == 'g')
    {
       printf("Von welches Laufwerke laden Sie das Programm? (A.B,C)\n");
       response_mn = get1char("");
       sure = get1char("Sind Sie sicher? ");
       if((sure == 'j') || (sure == 'J'))
	 sure = 'y';
    }
  }
  while ((response_mn != 'a') && (response_mn != 'b') &&
    (response_mn != 'c') || (sure != 'y'));
  switch(response_mn)
  {
    case 'a' :
    {
      disk_choice = 0;  /* File for transcript will be A:REPLAY.TXT. */
      break;
    }
    case 'b' :
    {
      disk_choice = 1;  /* File for transcript will be B:REPLAY.TXT. */
      break;
    }
    case 'c' :
    {
      disk_choice = 2;  /* File for transcript will be C:REPLAY.TXT. */
      break;
    }
  }

 do {
    if((language == 'e') || (language == 'E'))
    {
       response_mn = get1char("Want to play, review, or quit? (p,r,q): ");
    }
    if((language == 'g') || (language == 'G'))
    {
       printf("Wollen Sie spielen, ein altes Spiel wiederholen oder");
       printf(" aufh\"ren?  (S,W,E)\n");
       response_mn = get1char("");
       if((language == 'g') || (language == 'G'))
       switch(response_mn)
       {
	 case 's' : ;
	 case 'S' :
	 {
	   response_mn = 'p';
	   break;
	 }
	 case 'w' : ;
	 case 'W' :
	 {
	   response_mn = 'r';
	   break;
	 }
	 case 'e' : ;
	 case 'E' :
	 {
	   response_mn = 'q';
	   break;
	 }
       }
    }
}
while ((response_mn != 'p') && (response_mn != 'q') &&
  (response_mn != 'r'));

if (response_mn != 'q')
   {
     if (response_mn == 'r')
     {
       is_replay = 1;
       window(1,1,80,24);
       clrscr();
       printf("Wait ... disk being accessed.");
       get_transcript(cubes2, filenames[disk_choice]);
     }
     else
     {
	 is_replay = 0;
	 if((language == 'e') || (language == 'G'))
	 {
	   players = get1char("More than 3 playing (y, n)");
	   if((language == 'g') || (language == 'G'))
	   {
	      players = get1char("Spieln mehr als drei? (j,n)");
	      if (players == 'j')
		players = 'y';
	   }
	 }
	 while((players != 'y')  && (players != 'n'))
	 {
	   if((language == 'e') || (language == 'E'))
	      players = get1char("( y,n )");
	   if((language == 'g') || (language == 'G'))
	   {
	      players = get1char("( j, n)");
	      if((players == 'j') || (players == 'J'))
		players = 'y';
	   }
	 }
     }
     clrscr();
     printf("     action   cube   player   card    color   side    from");
     stats = 3;
     keep_playing = 1;
     window(1,11,80,24);
     clrscr();
     while (keep_playing)
     {
	 window(1,11,80,24);
	 printf("\n");
	 keep_playing = get_Move();
     }
   }
   window(1,1,80,25);
   clrscr();
   printf("wait ... disk being accessed.");
   if (is_replay == 0)
   {
      store_transcript(cubes, filenames[disk_choice]);
   }
   get_transcript(cubes2, filenames[disk_choice]);
   window(1,1,80,25);
   clrscr();
   printf("cube  player card color side from\n");
   for (j = 1; j <= 12; j++)
   {
      window(1,j+1,40,24);
      printf(" %-2d      %d     %-2d   ",j,cubes2[j].player,cubes2[j].card);
      printf("%d    %d    ", cubes2[j].color, cubes2[j].state);
      printf("%-2d  \n",      cubes2[j].from_what_cube);
   }    /* Works fine for just raw data from the cubes array */
   window(40,1,80,24);
   printf("cube  player card color side from\n");
   j = 1;
   for (k = 13; k <= 24; k++)
   {
      j++;
      window(40,j,80,24);
      printf(" %-2d      %d     %-2d   ",k,cubes2[k].player,cubes2[k].card);
      printf("%d    %d    ", cubes2[k].color,  cubes2[k].state);
      printf("%-2d  \n",  cubes2[k].from_what_cube);
   }    /* Works fine for just raw data from the cubes array */
}


int rule_on_move( int move_type_r, int cube_r, int player_r, int card_r,
 int color_r, int state_r, int from_what_cube_r)     /* stub at this point */
{


/*   printf("     This is rule_On_Move(). Get_Move() called me.\n");  */


/* --------------------------------------------------------------------
  A. Rule on moves giving appropriate help message for disallowed moves,
     for any move present player could not also have been previous player.

    1.  start (of a chain of thought)
	Check to see if color already used.  If so disallow.
    2.  connection (extending a chain of thought or branching)
	Check to see if cube already at end of the chain is turned to P/O.
	If so disallow.
    3.  cube_turning (permit, challeng, O.K., void)
	For P, C, O, or blank check to see if cube was on #, #, C, or C,
	respectively.  In cases of O or P, player can not be same as player
	who placed the cube being turned.  In case of P, player can not be
	player who placed cube being turned or the previous one in that
	line of thought  (under which that color was placed).
    -------------------------------------------------------------- */
    assert((card_r >= 0) && (card_r <= 40));    /* 40 cards in the deck */
    assert((cube_r >= 0) && (cube_r <= 24));    /* 24 cubes in the box */
    assert((color_r >= 0) && (color_r <= 5));   /* 5 colors in the box */
    assert((player_r >= 0) && (player_r <= 8)); /* max 8 people play */
    assert((state_r >= 0) && (state_r <= 5));   /* 5 cube sides differ */
    assert((from_what_cube_r >= 0) &&
       (from_what_cube_r < cube_r));        /* cube used in previous turn */

char * error[2][30];
char * chai_r[2];
char * chai_end_r[2];
chai_r[0] = "Chain =";
chai_r[1] = "Kette =";
chai_end_r[0] = "Chain end is ";
chai_end_r[1] = "Ende der Kette ist ";

error[0][1] = "The previous connection must have been permited.\n";
error[1][1] = "Die vorherige Verbindung muss erlaubt werden.\n";
error[0][2] = "The cube needs to use an unused color. Branch perhaps?\n";
error[1][2] =
     "Dieser WÅrfel benutzt eine andere Farbe. Vieleicht verzweigen?\n";
error[0][3] = "Branching requires a new color?\n";
error[1][3] = "Verzweigen erfordet eine neue Farbe.\n";
error[0][4] = "A cube that starts a chain, can not be turned.\n";
error[1][4] =
    "Ein WÅrfel der eine Kette startet, kann nicht gedreht werden.\n";
error[0][5] = "That cube is already turned to 'O'\n";
error[1][5] = "Dieser WÅrfel ist schon auf 'G' gedreht.\n";
error[0][6] = "After a cube has been turned to 'O','P', or blank may not\n";
error[1][6] =
    "Nachdem ein WÅrfel zu 'G', 'E' oder 'leer' gedreht wurde, kann er\n";
error[0][7] = "be turned.\n";
error[1][7] = "nicht mehr gedreht werden.\n";
error[0][8] = "You may not permit a connection that you made yourself or\n";
error[1][8] =
   "Sie k\"nnen keine Verbindung erlauben, die Sie selbst gemacht haben oder\n";
error[0][9] = "if you set the cube from which the connection was made.\n";
error[1][9] = "bei der sie den WÅrfel gesetzt haben von der sie ausging.\n";
error[0][10] ="That cube has already been turned to 'P'.\n";
error[1][10] = "Dieser WÅrfel ist schon auf 'E' gedreht.\n";
error[0][11] ="That cube has already been turned to 'C'.\n";
error[1][11] = "Dieser WÅrfel ist schon auf 'A' gedreht.\n";
error[0][12] = "That cube has already been turned to blank.\n";
error[1][12] = "Dieser WÅrfel ist schon auf 'leer' gedreht.\n";
error[0][13] = "Colors change only for branching.\n";
error[1][13] = "Farben Ñndern sich nur bei Verzweigungen.\n";
error[0][14] = "Not a chain end \n";
error[1][14] = "Nicht das Ende einer Kette. \n";
error[0][15] = "From C a cube can be turned to only 'O' or 'blank'.";
error[1][15] = "Von 'A' kann ein WÅrfel nur auf 'G' oder 'U' gedreht werden.";
error[0][16] = "Extend a chain only from its end.";
error[1][16] = "Eine Kette kann nur von ihrem Ende fortgefÅhrt werden.";
error[0][17] = "Branch maybe?";
error[1][17] = "Vielleicht Verzweigen?";
error[0][18] = "Can't permit a connection you've made.";
error[1][18] = "Eine Verbindung die Sie gemacht haben k\"nnen Sie nicht erlauben.";
error[0][19] = "A cube can be O.K.'d only from 'C'";
error[1][19] = "Ein WÅrfel kann nur von 'A' aus auf 'G' gedreht werden.";
error[0][20] = "A player can't turn to 'O' a cube he/she placed.";
error[1][20] = "Ein Spieler kann keinen WÅrfel auf 'G' drehen, den er/sie gesetzt hat.";
error[0][21] = "That cube is already turned to blank.";
error[1][21] = "Dieser WÅrfel ist schon auf 'leer' gedreht.";
error[0][22] = "A cube can be blanked only from 'C'";
error[1][22] = "Ein WÅrfel kann nur von 'A' aus auf 'leer' gedreht werden.";
error[0][23] = "If you mean to start a new chain, use an unused color.\n";
error[1][23] = "Benutzen Sie eine unbenÅtzte Farbe, um eine neue Kette zu beginnen.\n";
		      
int language_row_r;

if((language == 'e') || (language == 'E'))
    language_row_r = 0;
if((language == 'g') || (language == 'G'))
    language_row_r = 1;

    window(1,13,80,24);
    ruling = allowed;
    if (move_type_r == 0)
       ruling = disallowed;
    else
	switch (move_type_r)
	{
	   case 1 :  /*start */
	   {

	      if (previous_of_color[color_r] != 0)
	      {
		 printf(error[language_row_r][23]);
		 printf("%s %d \n", chai_r[language_row_r],color_r);
		 printf("%s",chai_end_r[language_row_r]);
		 printf(" %d ", previous_of_color[color_r]);
		 ruling = disallowed;
	      }
	      else
		 ruling = allowed;
	      break;
	   }
	   case 2 : ;  /* extend */
	   {
	      if (cubes[from_what_cube_r].color == color_r)
	      {
		 if(previous_of_color[color_r] == from_what_cube_r)
		 {
		    if (cubes[from_what_cube_r].from_what_cube  != 0)
		    {
		       if ((cubes[from_what_cube_r].state != 2) &&
			  (cubes[from_what_cube_r].state != 4))
		       {
			  printf(error[language_row_r][1]);
			  ruling = disallowed;
		       }
		       else
		       {
			 ruling = allowed;
		       }
		    }
		    else
		    {
		       ruling = allowed;
		    }
		}
		else
		{
		   printf(error[language_row_r][16]);
		       printf(error[language_row_r][17]);
		       ruling = disallowed;
		}
	      }
	      else
	      {
		 printf(error[language_row_r][13]);
		 ruling = disallowed;
	      }
	      break;
	   }
	   case 3 :   /* branch */
	   {
	      if(previous_of_color[color_r] == 0)
	      {
		 if (cubes[from_what_cube_r].from_what_cube  != 0)
		 {
		    if ((cubes[from_what_cube_r].state != 2) &&
		       (cubes[from_what_cube_r].state != 4))
		    {
		       printf (error[language_row_r][1]);
		       ruling = disallowed;
		    }
		 }
		 else
		    ruling = allowed;
	      }
	      else
	      {
		 printf(error[language_row_r][3]);
		 ruling = disallowed;
	      }
	      break;
	   }
	   case 4  :   /* permit */
	   {
	      ruling = allowed;
	      if(cubes[cube_r].from_what_cube == 0)
	      {
		  printf(error[language_row_r][4]);
		  ruling = disallowed;
	      }
	      if  (cubes[cube_r].state == 3)
	      {
		 printf(error[language_row_r][15]);
		 ruling = disallowed;
	      }
	      if (state_r == cubes[cube_r].state)
	      {
		 printf(error[language_row_r][10]);
		 ruling = disallowed;
	      }
	      else if ((cubes[cube_r].state == 4) ||
	       (cubes[cube_r].state == 5))
	       {
		 printf (error[language_row_r][6]);
		 ruling = disallowed;
	       }
	      if(players == 'y')
	      {
		 if ((cubes[cube_r].player == player_r) ||
		 (cubes[cubes[cube_r].from_what_cube].player ==
		 player_r))
		 {
		    printf(error[language_row_r][8]);
		    printf(error[language_row_r][9]);
		    ruling = disallowed;
		 }
	      }
	      else
	      {
		 if (cubes[cube_r].player == player_r)
		 {
		    printf(error[language_row_r][18]);
		    ruling = disallowed;
		 }
	      }
	      break;
	   }
	   case 5  :    /* challenge */
	   {
	      ruling = allowed;
	      if(cubes[cube_r].from_what_cube == 0)

	      {
		  printf(error[language_row_r][4]);
		  ruling = disallowed;
	      }
	      if (cubes[cube_r].state == state_r)
	      {
		 printf(error[language_row_r][11]);
		 ruling = disallowed;
	      }
	      if ((cubes[cube_r].state == 2) ||
		 (cubes[cube_r].state == 4) ||
		 (cubes[cube_r].state == 5))
	      {
		  printf(error[language_row_r][6]);
		  printf(error[language_row_r][7]);
		  ruling = disallowed;
	      }
	      break;
	   }
	   case 6  :    /* ok  */
	   {
	      ruling = allowed;
	      if(cubes[cube_r].from_what_cube == 0)
	      {
		  printf(error[language_row_r][4]);
		  ruling = disallowed;
	      }
	      if (cubes[cube_r].state == state_r)
	      {
		 printf(error[language_row_r][5]);
		 ruling = disallowed;
	      }
	      else
		 if (cubes[cube_r].state != 3)
		 {
		     printf(error[language_row_r][19]);
		     ruling = disallowed;
		 }

	      if ((cubes[cube_r].state == 2) ||
		 (cubes[cube_r].state == 5))
	      {
		 printf(error[language_row_r][6]);
		 printf(error[language_row_r][7]);
		 ruling = disallowed;
	      }
	      if (cubes[cube_r].player == player_r)
	      {
		 printf(error[language_row_r][20]);
		 ruling = disallowed;
	      }
	      break;
	   }
	   case 7  :  /* void */
	   {
	      ruling = allowed;
	      if(cubes[cube_r].from_what_cube == 0)
	      {
		  printf(error[language_row_r][4]);
		  ruling = disallowed;
	      }
	      if (cubes[cube_r].state == state_r)
	      {
		 printf(error[language_row_r][21]);
		 ruling = disallowed;
	      }
	      else
		 if (cubes[cube_r].state != 3)
		 {
		     printf(error[language_row_r][22]);
		     ruling = disallowed;
		 }

	      if ((cubes[cube_r].state == 2) ||
		 (cubes[cube_r].state == 4))
	      {
		 printf(error[language_row_r][12]);
		 ruling = disallowed;
	      }
	      break;
	   }
	   default :
	      ruling = disallowed;
	}
    return(ruling);
}

void update( int cube_u, int player_u, int card_u, int color_u, int state_u,
   int from_what_cube_u)
{
  /*  printf("       This is update(). get_Move() called me.\n");   */


      assert((card_u >= 0) && (card_u <= 40));    /* 40 cards in the deck */
    assert((cube_u >= 0) && (cube_u <= 24));    /* 24 cubes in the box */
    assert((color_u >= 0) && (color_u <= 5));   /* 5 colors in the box */
    assert((player_u >= 0) && (player_u <= 8)); /* max 8 people play */
    assert((state_u >= 0) && (state_u <= 5));   /* 5 cube sides differ */
    assert((from_what_cube_u >= 0) &&
       (from_what_cube_u < cube_u));            /* cube used in previous
						    turn */

   /*  Upate cube record with any new data reflecting the move.  */

       if (state_u != 0)
	   cubes[cube_u].state = state_u;
       if (card_u != 0)
	   cubes[cube_u].card = card_u;
       if ((player_u != 0) && (card_u != 0))
	   cubes[cube_u].player = player_u;
       if (color_u != 0)
	   cubes[cube_u].color = color_u;
       if (from_what_cube_u != 0)
	   cubes[cube_u].from_what_cube = from_what_cube_u;
       if ((state_u == 2) || (state_u == 3))
	  cubes[cube_u].player_p_c = player_u;
       if ((state_u == 4) || (state_u == 5))
	  cubes[cube_u].player_o_v = player_u;

    /*  Make whoever is current_player the previous_player.  */

       previous_player = player_u;


}


int get_Move()
{
   int player_m = 0;
   char response_m;
   int move_type_m = 0;
   int color_m = 0;
   int card_m = 0;
   int state_m = 0;
   int from_what_cube_m = 0;
   int cube_m;
     int language_row_m;
   if((language == 'e') || (language == 'E'))
	language_row_m = 0;
   if((language == 'g') || (language == 'G'))
	language_row_m = 1;
   char * types_menue[2][10];
   char * rtrn_m[2];
   char  * y_n_m[2];
   char y_n_j_n_m[2][2];
   char  * h_any_m[2];
   char * relatn[2];
   char * ch[2];
   char * ch_response[2];
   char * reject_m[2];
char move_choice_m[2][10] =
{'s','x','b','p','c','o','v','z','z','z','b','f','v','e','a','g','u'};
char side[2][6] =
{'#','p','c','o','- ',' ','# ','e ','a ','g ','u ',' '};
// check the "side" letters for german version
char hue[2][6] = {'r','b','g','y','o',' ','r','b','g','y','o',' '};
  // needs german "hue" choices
char action[2][8] =
 {'-','s','x','b','p','c','o','v','-','b','f','v','e','a','g','u'};

types_menue[0][1] = "S - Start\n";
types_menue[1][1] = "B - Begin\n";
types_menue[0][2] = "X - Extend\n";
types_menue[1][2] = "F - FortfÅhren\n";
types_menue[0][3] = "B - Branch\n";
types_menue[1][3] = "V - Verzweigen\n";
types_menue[0][4] = "P - Permit\n";
types_menue[1][4] = "E - Erlauben\n";
types_menue[0][5] = "C - Challenge\n";
types_menue[1][5] = "A - Anzweifeln\n";
types_menue[0][6] = "O - O.K.\n";
types_menue[1][6] = "G - GÅltig\n";
types_menue[0][7] = "V - Void\n";
types_menue[1][7] = "U - UngÅltig\n";

char * prompt[2][30];
rtrn_m[0] = "\nPress return.";
rtrn_m[1] = "\nReturn Taste";
y_n_m[0] = "\nAre you sure? (y,n)";
y_n_m[1] = "\nSind Sie sicher? (j,n)";
h_any_m[0] = "Hit any key.";
h_any_m[1] = "Eine beliebige Taste";
relatn[0] = "Relation";
relatn[1] = "Verbindung:";
ch[0] = "Challenge";
ch[1] = "Anzweifeln.";
ch_response[0] = "Response to challenge";
ch_response[1] = "Antwort";


y_n_j_n_m[0][0] = 'y';
y_n_j_n_m[1][0] = 'j';
y_n_j_n_m[0][1] = 'n';
y_n_j_n_m[1][1] = 'n';
reject_m[0] = "rejected";
reject_m[1] = "abgelehnt";

prompt[0][1] = "Only one to eight may play. Continue game?\n";
prompt[1][1] = "Nur ein bis acht Spieler sind m\"glich.  Weiterspielen?\n";
prompt[0][2] = "Two consecutive moves not allowed. Continue game?\n";
prompt[1][2] =
  "Zwei aufeinanderfolgende ZÅge sind nicht erlaubt.  Weiterspielen?\n";
prompt[0][3] = "Your move?(s,x,b,p,c,o,v) ";
prompt[1][3] = "Ihr Zug? (b,f,v,e,a,g,u) ";
prompt[0][4] = "-> You have chosen to start a chain of thought.\n";
prompt[1][4] = "-> Sie m\"chten eine Gedankenkette starten.\n";
prompt[0][5] = "What is the color for the chain?(R,B,G,Y,O)\n";
prompt[1][5] = "Wie ist die Farbe der Kette? (R,B,G,Y,O)\n";
prompt[0][6] = "That color is not one provided.\n";
prompt[1][6] = "Diese Farbe gibt es nicht.  Weiterspielen?\n";
prompt[0][7] = "What card?";
prompt[1][7] = "Welche Karte?";
prompt[0][8] = "On what card should the cube be set? (1 - 40)\n";
prompt[1][8] = "Auf welche Karte soll der WÅrfel gesetzt werden? (1 - 40)\n";
prompt[0][9] = "That card is not on the board. Continue game?";
prompt[1][9] = "Diese Karte gibt es nicht. Weiterspielen?\n";
prompt[0][10] = "You have chosen to continue a chain.\n";
prompt[1][10] = "-> Sie m\"chten eine Kette fortfÅhren.\n";
prompt[0][11] = "-> You have chosen to branch to another chain.\n";
prompt[1][11] = "-> Sie m\"chten von einer Kette verzweigen.\n";
prompt[0][12] = "-> You have requested to permit a relation.\n";
prompt[1][12] = "-> Sie m\"chten eine Verbindung erlauben.\n";
prompt[0][13] = "Which cube chould be turned to 'P'\n";
prompt[1][13] = "Welcher WÅrfel soll auf 'E' gedreht werden?\n";
prompt[0][14] = "You have requested a connection be challenged.\n";
prompt[1][14] = "Sie m\"chten eine Verbindung anzweifeln.\n";
prompt[0][15] = "Which cube should be turned to 'C'\n";
prompt[1][15] = "Welcher WÅrfel soll auf 'A' gedreht werden?\n";
prompt[0][16] = "-> You have requested a connection to be O.K.'d.\n";
prompt[1][16] = "-> Sie m\"chten eine Verbindung fÅr gÅltig erklÑren.\n";
prompt[0][17] = "Which cube should be turned to 'O'?\n";
prompt[1][17] = "Welcher WÅrfel soll auf 'G' gedreht werden?\n";
prompt[0][18] = "-> You have requested a connection be voided\n";
prompt[1][18] = "-> Sie m\"chten eine Verbindung fÅr ungÅltig erklaren.\n",
prompt[0][19] = "Which cube should be turned to blank (v)?\n";
prompt[1][19] = "Welcher WÅrfel soll auf 'leer' ('U') gedreht werden?\n";
prompt[0][21] = "From what cube is the connection?\n";
prompt[1][21] = "Von welchem WÅrfel aus soll die Verbindung gemacht werden?\n";
prompt[0][22] = "player(roster position) or q to quit ( # / q)? ";
prompt[1][22] = "Spieler Nummer oder 'q' zum beenden? ( # / q) ";

   if(is_replay == 0)
   {
      cube_m = cube_of_move;
   }
   else
   {
      cube_m = replay_cube;
      if (cubes2[replay_cube].state == 1)
      {
	 turnings_for_cube = 0;
      }
      if((cubes2[replay_cube].state == 2) || (cubes2[replay_cube].state == 3))
      {
	 turnings_for_cube = 1;
      }
      if((cubes2[replay_cube].state == 4) || (cubes[replay_cube].state == 5))
      {
	turnings_for_cube = 2;
      }
   }
   move_request = allowed;
   window(1,11,80,25);
   if (is_replay == 0)
   {
      player_m = get1char(prompt[language_row_m][22]);
      clrscr();
      printf("\n\n");
      if((player_m == 'q') || (player_m == 'Q'))
      {
	 clrscr();
	 return 0;
      }
      player_m = player_m - '0';
   }
   else
   {
      get1char(rtrn_m[language_row_m]);
      printf("\n\n");
      clrscr();
      switch(next_turning)
       {
	   case 0 :     /* Replay will be of the placing of the cube */
	   {
	       player_m = cubes2[replay_cube].player;
	       if(player_m == 0)
	       {
		 clrscr();
		 return 0;
	       }
	       break;
	   }
	   case 1 :     /* Replay will be of 1st time the cube is turned */
	   {            /* If it was turned */

	       player_m = cubes2[replay_cube].player_p_c;
	       if (player_m == 0)
	       {
		 clrscr();
		 return 0;
	       }
	       break;
	   }
	   case 2 :    /* Replay will be of the 2nd time the cube is turned */
	   {           /* if it was turned a 2nd time */
	       player_m = cubes2[replay_cube].player_o_v;
	       if(player_m == 0)
	       {
		 clrscr();
		 return 0;
	       }
	       break;
	   }
       }
   }
   if ((player_m <= 0) || (player_m > 8))
   {
	move_type_m = 0;
	printf("%s",prompt[language_row_m][1]);
	get1char(rtrn_m[language_row_m]);
	clrscr();
	return 1;                /* max 8 people play */
   }
   if((player_m == previous_player) && (players == 'y'))
      {
	 if(players == 'y')
	 {
	   move_type_m = 0;
	   printf("%s\n",prompt[language_row_m][2]);
	   get1char(rtrn_m[language_row_m]);
	   clrscr();
	   return 1;  /* No player may make two consecutive moves. */
	 }
      }
   else
   {
     if (is_replay == 0)  /* Intake current move .. 1st the type of move */
     {
	do
	{
	   clrscr();
	   response_m = get1char(prompt[language_row_m][3]);
	   if(response_m == '?')
	   {
	       clrscr();
	       printf("%s",types_menue[language_row_m][1]);
	       printf("%s",types_menue[language_row_m][2]);
	       printf("%s",types_menue[language_row_m][3]);
	       printf("%s",types_menue[language_row_m][4]);
	       printf("%s",types_menue[language_row_m][5]);
	       printf("%s",types_menue[language_row_m][6]);
	       printf("%s",types_menue[language_row_m][7]);
	       printf("\n\n   %s",rtrn_m[language_row_m]);
	       get1char("");
	       clrscr();

	   }
	   printf("\n");
	}
	while((response_m != move_choice_m[language_row_m][0])&&
	  (response_m != move_choice_m[language_row_m][1])&&
	  (response_m != move_choice_m[language_row_m][2])&&
	  (response_m != move_choice_m[language_row_m][3])&&
	  (response_m != move_choice_m[language_row_m][4])&&
	  (response_m != move_choice_m[language_row_m][5])&&
	  (response_m != move_choice_m[language_row_m][6]));
     }
     else
     /*  *****************************************************************
     Replay. Determine type of move being replayed.
     ***************************************************************** */

     {
	if(cubes2[replay_cube].from_what_cube == 0)
	{
	   response_m = move_choice_m[language_row_m][0];
	}
	else
	switch(next_turning)
	{
	  case 0 :   /* cube has been placed */
	  {
	    if(previous_of_color[cubes2[replay_cube].color] != 0)
	    {
	       response_m = move_choice_m[language_row_m][1];
	    }
	    else
	    {
	      response_m = move_choice_m[language_row_m][2];
	    }
	    break;
	  }

	  case 1 :  /* 1st time cube is turned */
	  {
	    if(cubes2[replay_cube].state == 2)
	      response_m = move_choice_m[language_row_m][3];
	    else
	    {
	      response_m = move_choice_m[language_row_m][4];
	    }
	    break;
	  }
	  case 2 :   /* 2nd time cube was turned, if turned a 2nd time */
	  {
	    if(cubes2[replay_cube].state == 4)
	    {
	      response_m = move_choice_m[language_row_m][5];
	    }
	    if (cubes2[replay_cube].state == 5)
	    {
	      response_m = move_choice_m[language_row_m][6];
	    }
	    break;
	  }
	}
     }
	if(response_m == move_choice_m[language_row_m][0])
	{
	 /*  printf("            Request is to start a chain.\n"); */
	   move_type_m = 1;    /* Move is *start a mew chain.  */
	   state_m = 1;        /* Cube is to be placed with number face up */
	   if(is_replay == 0)
	   {
	      response_m = tolower(get1char(prompt[language_row_m][5]));
	      if(response_m == 'r')  color_m = 1;
	      else
		  if(response_m == 'b') color_m = 2;
		  else
		    if(response_m == 'g') color_m = 3;
		    else
		      if(response_m == 'y') color_m = 4;
		      else
			if(response_m == 'o') color_m = 5;
			else
			  color_m = 0;

	   }
	   else
	   {
		    /* get1char("Getting color from replay file"); */
		 color_m = cubes2[replay_cube].color;
	   }
	   if ((color_m <= 0) || (color_m  > 5))
	   {
		move_type_m = 0;
		printf(prompt[language_row_m][6]);
		get1char(rtrn_m[language_row_m]);
		clrscr();
		return 1;       /* 5 colors in the box */
	   }
       //        printf("chain: %d\n", color_m);
	   if (is_replay == 0)
	   {
	       gettext(1,12,80,24,moves_screen);
	       menue_or_not(&response_m, language);
	       puttext(1,12,80,24,moves_screen);
	   }
	   else
	   {
	      /* get1char("Referring to replay file for card"); */
	      response_m = cubes2[replay_cube].card;
	   }
	   card_m = response_m;
	   if ((card_m <= 0) || (card_m > 40))
	   {
	      move_type_m = 0;
	      printf(prompt[language_row_m][9]);
	      get1char(rtrn_m[language_row_m]);
	      clrscr();
				return 1;          /* 40 cards in the deck */
	   }
	}
	else
	{
	  if(response_m == move_choice_m[language_row_m][1])
	  {   //1
	  /*     printf("    Request is to make a connection.\n"); */
	     move_type_m = 2;   /* Move extends a chain of thought */
	     state_m = 1;       /* cube is placed with number face up. */
	     if(is_replay == 0)
	     {
	       from_what_cube_m = get1int(prompt[language_row_m][21]);
			 }
	     else
	     {
	      /* get1char("Replaying *from what cube*"); */
	       from_what_cube_m = cubes2[replay_cube].from_what_cube;
	     }
	     if ((from_what_cube_m <= 0) ||
	       (from_what_cube_m  >= cube_m))
	     {
		 move_type_m = 0;
		 printf(prompt[language_row_m][9]);
		 get1char(rtrn_m[language_row_m]);
		 clrscr();
		 return 1;      /* cube used in previous turn */
	     }
	     if(is_replay == 0)
	     {
		response_m = get1char(prompt[language_row_m][5]);
		if(response_m == 'r')  color_m = 1;
		else
		  if(response_m == 'b') color_m = 2;
		  else
		    if(response_m == 'g') color_m = 3;
		    else
		      if(response_m == 'y') color_m = 4;
		      else
			if(response_m == 'o') color_m = 5;
			else  ;
	     }
	     else
	     {
		 /* get1char("Getting color from replay file"); */
		 color_m = cubes2[replay_cube].color;
	     }

	     if ((color_m <= 0) || (color_m  > 5))
	     {
		move_type_m = 0;
		printf(prompt[language_row_m][6]);
		get1char(h_any_m[language_row_m]);
		clrscr();
		return 1;       /* 5 colors in the box */
	     }
      //           printf("chain: %d\n", color_m);
	     if (is_replay == 0)
	     {
	       gettext(1,12,80,24,moves_screen);
	       menue_or_not(&response_m, language);
	       puttext(1,12,80,24,moves_screen);
	     }
	     else
	     {
				/* get1char("Referring to replay file for card");  */
		response_m = cubes2[replay_cube].card;
	     }
	     card_m = response_m;
	     if ((card_m <= 0) || (card_m > 40))
	     {
		move_type_m = 0;
		printf(prompt[language_row_m][21]);
		clrscr();
		return 1;          /* 40 cards in the deck */
	     }

	  }
	  else
	  {
	    if(response_m == move_choice_m[language_row_m][2])
	    {
	/*   printf("     Request is to branch from a chain.\n"); */
	      move_type_m = 3;  /* Move is to make branching connection */
	      state_m = 1;     /* cube is placed with number face up. */
	      if(is_replay == 0)
	      {
		from_what_cube_m = get1int(prompt[language_row_m][21]);
	      }
	      else
	      {
				/* get1char("Replaying *from what cube*");  */
		from_what_cube_m = cubes2[replay_cube].from_what_cube;
	      }
	      if ((from_what_cube_m <= 0) ||
	       (from_what_cube_m  >= cube_m))
	      {
		 move_type_m = 0;
		 printf(prompt[language_row_m][23]);
		 get1char(rtrn_m[language_row_m]);
		 clrscr();
		 return 1;      /* cube used in previous turn */
	      }
	      if(is_replay == 0)
	      {
		response_m = get1char(prompt[language_row_m][5]);
		if(response_m == 'r') color_m = 1;
		else
		  if(response_m == 'b') color_m = 2;
		  else
		    if(response_m == 'g') color_m = 3;
		    else
		      if(response_m == 'y') color_m = 4;
		      else
			if(response_m == 'o') color_m = 5;
			else  ;
	      }
	      else
	      {
	      /*   get1char("Getting color from replay file");  */
		 color_m = cubes2[replay_cube].color;
	      }

	      if ((color_m <= 0) || (color_m  > 5))
	      {
		 move_type_m = 0;
		 printf(prompt[language_row_m][6]);
		 get1char(rtrn_m[language_row_m]);
		 clrscr();
		 return 1;       /* 5 colors in the box */
	      }
	//       printf("chain: %d\n", color_m);
	      if (is_replay == 0)
	      {
		gettext(1,12,80,24,moves_screen);
		menue_or_not(&response_m, language);
		puttext(1,12,80,24,moves_screen);
	      }
	      else
	      {
	  /* response_m = get1char("Referring to replay file for card");*/
		response_m = cubes2[replay_cube].card;
	      }
	      card_m = response_m;
	      if ((card_m <= 0) || (card_m > 40))
	      {
		move_type_m = 0;
		printf(prompt[language_row_m][9]);
		get1char(rtrn_m[language_row_m]);
		clrscr();
		return 1;          /* 40 cards in the deck */
	      }



	    }
	    else
	    {
	      if(response_m == move_choice_m[language_row_m][3])
	      {
	/*   printf("       Request is to 'permit' a connection.\n"); */
		move_type_m = 4;   /* Cube is to Permit connection */
		state_m = 2;       /* "P" face up */
		if(is_replay == 0)
		{
		  cube_m = get1int(prompt[language_row_m][13]);
		  if ((cube_m <= 0) || (cube_m >= cube_of_move))
		  {
		    move_type_m = 0;
		    printf(prompt[language_row_m][23]);
		    get1char(rtrn_m[language_row_m]);
		    clrscr();
		    return 1;                 /* 24 cubes in the box */
		  }
		}
		else
		{
	   /*   get1char("Replaying cube to be turned to P"); */
		  cube_m = replay_cube;
		}



	      }
	      else
	      {
		if(response_m == move_choice_m[language_row_m][4])
		{
	 /*  printf("     Request is to challenge a connection.\n"); */
	       move_type_m = 5;   /* Connection being challenged */
	       state_m = 3;       /* cube turned to "C" face up. */
		  if(is_replay == 0)
		  {
		    cube_m = get1int(prompt[language_row_m][15]);
		    if ((cube_m <= 0) || (cube_m >= cube_of_move))
		    {
		      move_type_m = 0;
		      printf(prompt[language_row_m][23]);
		      get1char(rtrn_m[language_row_m]);
		      clrscr();
		      return 1;                 /* 24 cubes in the box */
		    }
		  }
		  else
		  {
	   /*   get1char("Replaying cube to be turned to C"); */
		    cube_m = replay_cube;
		  }



		}
		else
		{
		  if(response_m == move_choice_m[language_row_m][5])
		  {
	 /*  printf("         Request is to O.K. a connection.\n");  */
		    move_type_m = 6;   /* Connection being O.K.'d. */
		    state_m = 4;       /* Cube turned to "O" face up. */
		    if(is_replay == 0)
		    {
		      cube_m = get1int(prompt[language_row_m][17]);
		      if ((cube_m <= 0) || (cube_m >= cube_of_move))
		      {
			move_type_m = 0;
			printf(prompt[language_row_m][23]);
			get1char(h_any_m[language_row_m]);
			clrscr();
			return 1;                 /* 24 cubes in the box */
		      }
		    }
		    else
		    {
	   /*   get1char("Replaying cube to be turned to O"); */
		      cube_m = replay_cube;
		    }

		  }
		  else
		  {
		    if(response_m == move_choice_m[language_row_m][6])
		    {
	 /*  printf("     Request is to void(blank) a connection\n"); */
		      move_type_m = 7;   /* Void connection (block entending of chain) */
		      state_m = 5;       /* Cube turned to blank side up */
		      if(is_replay == 0)
		      {
			cube_m = get1int(prompt[language_row_m][19]);
			if ((cube_m <= 0) || (cube_m >= cube_of_move))
			{
			  move_type_m = 0;
			  printf(prompt[language_row_m][23]);
			  get1char(rtrn_m[language_row_m]);
			  clrscr();
			  return 1;                 /* 24 cubes in the box */
			}
		      }
		      else
		      {
	  /*    get1char("Replaying cube to be turned to V");    */
			cube_m = replay_cube;
		       }


		    }
		    else
		    {
		      move_type_m = 0;
		      printf("Choice had to be S,X,B,P,C,O, or V,");
		      get1char(rtrn_m[language_row_m]);
		      clrscr();
		      return 1;
		    }
		  }
		}
	      }
	    }
	  }
	}

   }
   window(1,11,80,23);  /* clear a screen for report in case of a */
   clrscr();            /* move that is rejected */
   window(1,20,80,24);  /* have any problems report start a ways down */
   clrscr();            /* from the top of that screen area */

   if(rule_on_move(move_type_m, cube_m, player_m, card_m,
      color_m, state_m, from_what_cube_m) && move_request)
   {
      update(cube_m, player_m, card_m, color_m, state_m, from_what_cube_m);
      /* if placing a cube record new end of chain; advance cube # by one */
      if (is_replay == 0)
      {
	 if(move_type_m == 5)
	 {
	    window(1,11,80,24);
	    clrscr();
	    get_comment(move_type_m, cube_m);
	 }
	 if ((move_type_m == 2) || (move_type_m == 3))
	 {
	      window(1,11,80,24);
	      clrscr();
	      get_comment(move_type_m, cube_m);
	 }
      }
      else
      {
	  gif_e = gifs[cubes2[cubes2[replay_cube].from_what_cube].card];
	  gif_g = gifs2[cubes2[cubes2[replay_cube].from_what_cube].card];
	  if((move_type_m == 2) || (move_type_m == 3))
	  {
	      window(1,14,80,24);
	      clrscr();
	      printf("\n",relatn[language_row_m]);
	      printf("%s ->",gif_e);
	      printf(" %s \n\n", gifs[cubes2[replay_cube].card]);
	      printf("%s\n", cubes2[replay_cube].comment1a);
	      printf("%s\n", cubes2[replay_cube].comment1b);
	      printf("%s\n", cubes2[replay_cube].comment1c);
	  }
	  if(move_type_m == 5)
	  {
	      window(1,14,80,24);
	      clrscr();
	      printf("%s ",ch[language_row_m]);
	      printf("%s ->", gif_g);
	      printf(" %s \n\n", gifs2[cubes2[replay_cube].card]);
	      printf("%s\n", cubes2[replay_cube].comment2a);
	      printf("%s\n", cubes2[replay_cube].comment2b);
	      printf("%s \n",ch_response[language_row_m]);
	      printf("%s\n", cubes2[replay_cube].comment3a);
	  }
	  if (next_turning == turnings_for_cube)
	  {
	      replay_cube = replay_cube + 1;
	      next_turning = 0;
	  }
	  else
	  {
	      next_turning = next_turning + 1;
	  }
      }
      previous_of_color[color_m] = cube_m;
      if((move_type_m < 4) && (move_type_m > 0))
	   cube_of_move = cube_of_move + 1;
      window(1,stats,80,11);
      stats++;
      request_cnt++;
      if(stats >= 12)
      {
	  movetext(1,4,80,11,1,3);  /* scroll the stats display to keep */
	  window(1,10,80,11);       /* it from spilling into user dialogue */
	  stats = stats - 1;
      }
	 printf("%2d%c",request_cnt,')');
	 printf("    %-6c", action[language_row_m][move_type_m]);
	 printf(" %-6d  ", cube_m);
	 printf("%-6d  ", player_m);
	 printf("%-6d", card_m);
	 printf("   %-6c", hue[language_row_m][color_m-1]);
	 printf("   %-6c  ", side[language_row_m][state_m-1]);
	 if(from_what_cube_m > 0)
	 {
	   printf("%-6d \n", from_what_cube_m);
	 }
	 else
	 {
	   printf("     ");
	 }
   }
   else
   {
       window(1,22,80,24);
       printf(" ?%c ",')');
       printf("   %-6d", action[language_row_m][move_type_m]);
       printf(" %-6d  ", cube_m);
       printf("%-6d  ", player_m);
       printf("%-6d",card_m);
       printf("   %-6c", hue[language_row_m][color_m-1]);
       printf("   %-6c  ", side[language_row_m][state_m-1]);
       if(from_what_cube_m > 0)
       {
	 printf("%-6d", from_what_cube_m);
       }
       else
       {
	 printf("      ");
       }
       printf(" %s\n",reject_m[language_row_m]);
   }
      return 1;
}




/*==========================================================================
FUNCTIONS  TO BE WRITTEN
  -----------------------------------------------------------------------
  display()
     display the moves on the board / map / chart of the conversation /
     single chains of thought and/or trace.
  get_Roster()
     sign in each player at start of game. assign each a player a
     number corresponding to initials to be entered to request each
     move.
  get_cardlist()
     List card titles, allowing users to alter the list.
  handle_modem()
     Provide way for one person's copy of the Glass Plate Game  program to
     operate as both moderator and local player; the other player(s)'s
     copy acting as client.

  ====================================================================== */


  /*  BUGS
When asked for your roster number type "9", or some other number larger
than 8, the number of players permitted in the game.  Then for a next move,
have the player be #8 on the roster of players.  The program will refuse
player 8's move request, with a message saying that a player may not make two
consecutive moves.  I have searched long for the cuase of this bug already.


 -----------------------------------------------------------------------  */



void store_transcript(cubes_status &moves, char * filename)
{
 FILE *fl;
 fl = fopen(filename,"w");
 rewind(fl);
 fwrite(&moves,sizeof(cubes_status),1,fl);
 fclose(fl);
}


void get_transcript(cubes_status &moves, char * filename)
{
FILE *fl;
fl = fopen(filename,"r");
rewind(fl);
fread(&moves, sizeof(cubes_status),1,fl);
fclose(fl);
}

void menue_or_not(char * response, int language_mnot)
{
  do
  {
    puttext(1,12,80,24,moves_screen);
    window(1,20,80,24);
    clrscr();
    printf("\nPlace cube on what card? Press ? for card list. (1 - 40, ?)");
    gets(line_response);
    if(line_response[0] == '?')
       print_cards(language);
    else
    {
       * response = atoi(line_response);
       printf("%d", * response);
    }
   }while (( * response <= 0) ||(* response > 40));
}

/*
This Function gets up to three lines of text from the user,  A mystery is
why three lines can be processed when the code makes less than three loops
to take in text, line by
line, a condition.
*/
 void get_comment(int move_type_c, int cube_c)      /* variable 'player_comment' would need */
{                   /* declaration for this function to be activated */
   window(1,12,80,24);
   clrscr();
   char response_g;
   char input[80];

   char * ok_to_save[2];
   char * prompt[2][10];
   int language_row_gc;
	 int more_input;

   ok_to_save[0] = "O.K. to save? (y,n)";
   ok_to_save[1] = "Fertig? (j,n)";
   prompt[0][1] =
      "Enter up to three lines, up to 80 characters each.\n";
   prompt[1][1] =
      "Geben Sie drei Zeilen ein, jeweils maximal 80 Zeichen.\n";
   prompt[0][2] = "Make an empty line when done.\n\n";
   prompt[1][2] = "Leere Zeile wenn fertig.\n\n";
   prompt[0][3] = "Relation: ";
   prompt[1][3] = "Verbindung: ";
	 prompt[0][4] = "Challenge: ";
	 prompt[1][4] = "Anzweifeln:";
   prompt[0][5] = "Original player's response to challenge \n";
   prompt[1][5] = "Antwort des ursprÅnglichen Spielers \n ";
   if(language == 'e')
     language_row_gc = 0;
   else
     if(language == 'g')
       language_row_gc =1;
   if((move_type_c == 2) || (move_type_c == 3))
   {
     response_g = 'n';
		 while((response_g != 'y') && (response_g != 'Y')&& (response_g != 'j')
			 && (response_g != 'J'))
		 {
	clrscr();
	printf(prompt[language_row_gc][1]);
	printf(prompt[language_row_gc][2]);
	printf(prompt[language_row_gc][3]);
	if((language == 'e') || (language == 'E'))
	{
	  printf("%s -> ", gifs[cubes[cubes[cube_c].from_what_cube].card]);
	  printf(" %s\n", gifs[cubes[cube_c].card]);
	};
	if((language == 'g') || (language == 'G'))
	{
		printf("%s -> ", gifs2[cubes[cubes[cube_c].from_what_cube].card]);
		printf(" %s\n", gifs2[cubes[cube_c].card]);
	};
	printf("> : ");
	more_input = 1;
	gets(cubes[cube_c].comment1a);
	if(strlen(cubes[cube_c].comment1a) == 0)
	  more_input = 0;
	if(more_input)
	{
	   more_input = 1;
	   printf("> : ");
	   gets(cubes[cube_c].comment1b);
		 if(strlen(cubes[cube_c].comment1b) == 0)
				more_input = 0;
	}
	if(more_input)
	{
	   printf("> : ");
	   gets(cubes[cube_c].comment1c);
	}
	response_g = get1char(ok_to_save[language_row_gc]);
		 }
	 }
	 if(move_type_c == 5)
	 {
			response_g = 'n';
			while((response_g != 'y') && (response_g != 'Y') &&
			 (response_g != 'j') && (response_g != 'J'))
      {
	clrscr();
	printf(prompt[language_row_gc][1]);
	printf(prompt[language_row_gc][2]);
	printf(prompt[language_row_gc][4]);
	if((language == 'e') || (language == 'E'))
	{
	  printf("%s -> ", gifs[cubes[cubes[cube_c].from_what_cube].card]);
	  printf(" %s\n", gifs[cubes[cube_c].card]);
	};
	if((language == 'g') || (language == 'G'))
	{
	  printf("%s -> ", gifs2[cubes[cubes[cube_c].from_what_cube].card]);
	  printf(" %s\n", gifs2[cubes[cube_c].card]);
	};
	{
		 more_input = 1;
	   printf("> : ");
	   gets(cubes[cube_c].comment2a);
	   if(strlen(cubes[cube_c].comment2a) == 0)
	     more_input = 0;
	}
	if(more_input)
	{
		 printf("> : ");
	   gets(cubes[cube_c].comment2b);
	   more_input = 0;
	}
       response_g = get1char(ok_to_save[language_row_gc]);
		 }
   }
   if((move_type_c == 2) || (move_type_c == 3))
   {
      clrscr();
      printf("%s\n", cubes[cube_c].comment1a);
      printf("%s\n", cubes[cube_c].comment1b);
			printf("%s\n", cubes[cube_c].comment1c);
	 }
   if(move_type_c == 5)
   {
      response_g = 'n';
			while((response_g != 'y') && (response_g != 'Y') &&
				(response_g != 'j') && (response_g != 'J'))
			{
	clrscr();
	printf(prompt[language_row_gc][4]);
	if((language == 'e') || (language == 'E'))
	{
		printf("%s -> ", gifs[cubes[cubes[cube_c].from_what_cube].card]);
		printf(" %s\n", gifs[cubes[cube_c].card]);
	};
	if((language == 'g') || (language == 'G'))
	{
	  printf("%s -> ", gifs2[cubes[cubes[cube_c].from_what_cube].card]);
	  printf(" %s\n", gifs2[cubes[cube_c].card]);
	};
	printf("%s\n", cubes[cube_c].comment2a);
	printf("%s\n", cubes[cube_c].comment2b);
	printf("\n");
	printf(prompt[language_row_gc][5]);
	printf("> : ");
	gets(cubes[cube_c].comment3a);
	more_input = 0;
	response_g = get1char(ok_to_save[language_row_gc]);
      }
   }
   move_type_c = 0;
   window(1,11,80,24);
	 clrscr();
}



