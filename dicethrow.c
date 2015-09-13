/*
 *    This file is part of dicethrow
 *
 *    Copyright (C) 2015 T.v.Dein.
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    You can contact me by mail: <tom AT vondein DOT org>.
 */

#include "dicethrow.h"

int usage() {
  fprintf(stderr,
	  "Generate a random numbers seeded by dice throws\n"
	  "Usage: dicethrow [-tcfvhd]\n"
	  "Options: \n"
	  "-t --humantoss            Asks interactively for rolled dices\n"
	  "-c --count <count>        Number of numbers (default: 4)\n"
	  "-f --randfile <randfile>  Random source to use (default:\n"
	  "                          /dev/urandom)\n"
	  "-l --minlen <count>       Minimum number (default: 1)\n"
	  "-m --maxlen <count>       Maximum number (default: 256)\n"
	  "-d --debug                Enable debug output\n"
	  "-v --version              Print program version\n"
	  "-h -? --help              Print this help screen\n"
	  );
  return 1;
}

int main (int argc, char **argv)  {
  int count = 4;
  char *randfile = NULL;
  int opt;

  WMIN = 1;
  WMAX = 256;
  humantoss = 0;
  verbose = 0;
  verbose_tostdout = 0;
  
  static struct option longopts[] = {
    { "count",     required_argument, NULL,           'c' },
    { "minlen",    required_argument, NULL,           'l' },
    { "maxlen",    required_argument, NULL,           'm' },
    { "humantoss", required_argument, NULL,           't' },    
    { "randfile",  required_argument, NULL,           'f' },
    { "version",   no_argument,       NULL,           'v' },
    { "help",      no_argument,       NULL,           'h' },
    { "debug",     no_argument,       NULL,           'd' },
    { "debug-stdout", no_argument,    NULL,           'D' },
  };

   while ((opt = getopt_long(argc, argv, "l:m:tf:c:vh?dD", longopts, NULL)) != -1) {
     switch (opt) {
     case 'v':
       fprintf(stderr, "This is %s version %s\n", argv[0], VERSION);
       return 1;
       break;
     case 'h':
     case '?':
       return usage();
       break;
     case 'c':
       count = atoi(optarg);
       break;
     case 'l':
       WMIN = atoi(optarg);
       break;
     case 'm':
       WMAX = atoi(optarg);
       break;
     case 't':
       humantoss = 1;
       break;
     case 'd':
       verbose++;
       break;
     case 'D':
       verbose++;
       verbose_tostdout = 1;
       break;
     case 'f':
       randfile = malloc(strlen(optarg));
       strncpy(randfile, optarg, strlen(optarg));
       break;
     default:
      return usage();
      break;
     }
   }

   if(randfile == NULL) {
     randfile = "/dev/urandom";
   }

   debug("     using randfile: %s", randfile);
   debug("      numbers range: %d <=> %d", WMIN, WMAX);
   if(humantoss)
     debug("user rolls dices");
   else
     debug("program rolls dices");
   
   getwords(randfile, count);

   return 0;
}

void getwords(char *randfile, int count) {
  /*
    initiate dice tossing, extract matching numbers
    from the list and print it.
   */
  unsigned char *words;
  int i, pos, one, two, three, four, five;
  int *tossed;
  unsigned char *tosses;
  
  words = fetch_dict(randfile, WMIN, WMAX);

  tossed = malloc(count * sizeof(int));
  
  for(i=0; i<count; i++) {
    tosses = toss(5, i);

    one    = tosses[0] * 10000;
    two    = tosses[1] *  1000;
    three  = tosses[2] *   100;
    four   = tosses[3] *    10;
    five   = tosses[4];
    
    pos = one + two + three + four + five;

    tossed[i] = pos;

    free(tosses);
  }

  for(i=0; i<count; i++) {
    fprintf(stdout, "%2d ", words[tossed[i]]);
  }

  fprintf(stdout, "\n");
  
  free(tossed);
  free(words);
}
