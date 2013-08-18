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
#include <conio.h>                       /* trace directory */
extern void print_cards(char language);
extern int get1char(char *prompt);

void print_cards(char language)
{
char list = 'a', response_gl;

if(language == 'e')
 while(response_gl != 'c')
 {

 if(list == 'a')
 {
  window(1,11,80,24);
  clrscr();
  printf("1.  Ambivalence                      20. Metamorphosis\n");
  printf("2.  Anthropomorphism                 21. Monetary Value\n");
  printf("3.  Art vs. Nature                   22. Myth\n");
  printf("4.  Fundamental Theorem of Calculus  23. Nature Tending\n");
  printf("5.  City as Artifact                       Towards Perfection\n");
printf("6.  Coding                           24. Ontogeny Recapitulating\n");
  printf("7.  Contemplation                          Phylogeny\n");
  printf("8   Creation                         25. Perspective\n");
  printf("9   Education                        26. Reaching out / Trying\n");
  printf("10  Emotional Manipulation           27. Return\n");
  printf("                       28. Society as active / Passive Hierarchy\n");
 }
 if(list == 'b')
 {
 window(1,11,80,24);
 clrscr();
 printf("11. Freedom                          29. Structural Strength\n");
printf("12. Gestalt                          30. Structured Improvisation\n");
 printf("13. Harmoney                         31. Struggle\n");
 printf("14. Struggle                         32. Synergy\n");
 printf("15. Hidden Potential                 33. Syntax\n");
 printf("16. Intuition                        34. Unwanted Relationships\n");
 printf("17. Joy                              35. Wavicle\n");
 printf("18. Magic\n");
 printf("19. Multiplicatio of Mechanical Advantage");
 printf("\n");
 }
 printf("\nChoose card? Toggle list? (c,t) ");
 response_gl = getch();
 clrscr();
 if(response_gl == 't')
    {

      if(list == 'a')
	 list = 'b';
      else
	 if(list == 'b')
	 list = 'a';
    }
  }   // endwhile in English
  window(1,11,80,24);
  clrscr();
if(language == 'g')
 while(response_gl != 'c')
 {
  if(list == 'a')
  {
     window(1,11,80,24);
     clrscr();
     printf("1.  Ambivalenz\n");
     printf("2.  Anthropomorphismus\n");
     printf("3.  Der Gegensatz von Kunst und Natur\n");
     printf("4.  UnerwÅnschte Verbindung\n");
     printf("5.  Die Stadt als Kunstwerk\n");
     printf("6.  Coding\n");
     printf("7.  Kontemplation\n");
     printf("8.  Sch"pfung\n");
     printf("9.  Ausbildung und Erziehung\n");
     printf("10. Manipulation von GefÅhlen\n");
  }
  if(list == 'b')
  {
     window(1,11,80,24);
     clrscr();
     printf("11. Freiheit\n");
     printf("12. Gestalt\n");
     printf("13. Harmonie\n");
     printf("14. Kampf\n");
     printf("15. Unentdeckte M"glichkeiten\n");
     printf("16. Intuition\n");
     printf("17. Freude\n");
     printf("18. Magik\n");
     printf("19. Multiplikation des mechanishen Vorteils\n");
     printf("20. Metamorphosis\n");
  }
  if(list == 'c')
      {
      window(1,11,80,24);
      clrscr();
      printf("21. Geldwert\n");
      printf("22. Mythen\n");
      printf("23. Natur entwickelt sich zur Perfektion\n");
      printf("24. Ontogenie wiederholt Phylogenie\n");
      printf("25. Perspektive\n");
      printf("26. Sich Ausstrecken\n");
      printf("27. RÅckkehr\n");
      printf("28.  (like 16)\n");
      printf("29. StÑrke von Struktur\n");
      printf("30. Strukturelle Improvisation\n");
      }
   if(list == 'd')
      {
      window(1,11,80,24);
      clrscr();
      printf("31.  (like some other card)\n");
      printf("32. Synergetik\n");
      printf("33. Syntax\n");
      printf("34.  (like 4)\n");
      printf("35. Welle-Teilchen Dualismus\n");
      }
   printf("\nChoose card? Toggle list? (c,t) ");
   response_gl = getch();
   clrscr();
   if(response_gl == 't')
      {
	switch(list)
	{
	  case 'a' :
	  {
	    list = 'b';
	    break;
	  }
	  case 'b' :
	  {
	    list = 'c';
	    break;
	  }
	  case 'c' :
	  {
	    list = 'd';
	    break;
	  }
	  case 'd' :
	  {
	    list = 'a';
	    break;
	  }
	}
      }  /*  endif toggle  */
  }  /*  endwhile in German */
  window(1,11,80,24);
  clrscr();
}




