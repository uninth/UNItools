/*
 *   iTop - a top-like interrupt load monitor
 *
 *   Homepage: http://hunz.org
 *
 *   Copyright (C) 2001 Benedikt 'Hunz' Heinz (hunz@hunz.org)
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *   It's quite simple but it does its job.
 *
 *    -Hunz
 *
 */

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "config.h"

#define CLEAR "\033[;H\033[2J"
#define VERSION "iTop v0.1 by Hunz <hunz@hunz.org> (http://hunz.org)"

struct interrupt {
  unsigned int last_count;
  unsigned int count;
  int max_rate;
  char name[MAX_NAME_LEN+1];
};

int read_ints(struct interrupt *interrupts, int calc_max) {
  char buf[256];
  int cur_no=0,count=-1;
  FILE *proc;

  if((proc=fopen("/proc/interrupts","rt"))==NULL) {
    fprintf(stderr,"cannot open /proc/interrupts for reading\n");
    return -1;
  }
  if (fgets(buf,sizeof(buf),proc)==NULL)
    return -1;
  while(cur_no<MAX_INTS) {
    char *tmpptr;
    if (fgets(buf,sizeof(buf),proc)==NULL) 
      break;
    buf[strlen(buf)-1]=0;
    buf[3]=0;
    buf[15]=0;
    tmpptr=buf;
    while(tmpptr[0]==' ') tmpptr++;
    cur_no=atoi(tmpptr);
    if(!(cur_no>count)) 
      break;
    tmpptr=buf+4;
    while(tmpptr[0]==' ') tmpptr++;
    count=atoi(tmpptr);
    interrupts[cur_no].last_count=interrupts[cur_no].count;
    interrupts[cur_no].count=count;
    strncpy(interrupts[cur_no].name,buf+33,MAX_NAME_LEN+1);
    interrupts[cur_no].name[MAX_NAME_LEN]=0;
    if ((calc_max) && (interrupts[cur_no].last_count>0) && ((interrupts[cur_no].count-interrupts[cur_no].last_count)>interrupts[cur_no].max_rate))
      interrupts[cur_no].max_rate=interrupts[cur_no].count-interrupts[cur_no].last_count;
    count=cur_no;
  }
  interrupts[count+1].max_rate=-1;
  fclose(proc);
  return 0;
}

void print_ints(struct interrupt *interrupts,int active) {
  int count;
  
  printf("%3s  %18s  %12s      %10s\n","INT","NAME","RATE","MAX");
  for(count=0;(count<MAX_INTS) && (interrupts[count].max_rate>=0);count++)
    if ((strlen(interrupts[count].name)>0) || (interrupts[count].count>0))
      if ((interrupts[count].count-interrupts[count].last_count) || (!active))
	printf("%3d [%18s] %5u Ints/s     (max: %5d)\n",count,interrupts[count].name,interrupts[count].count-interrupts[count].last_count,interrupts[count].max_rate);
}

void ihelp(int active) {
  char buf;
  printf("%s%s\nshow active ints only: %s\n\nInteractive commands are:\n\nh or ?  Print this list\na       toggle display of active only interrupts\nt       launch normal top\nq       Quit\n\nPress any key to continue",CLEAR,VERSION,(active != 0 ? ("yes") : ("no")));
  fflush(stdout);
  fread(&buf,1,1,stdin);
}

void help(char *name) {
  printf("%s\nusage: %s (-n iterations) (-a for all -not only active- ints)\n",VERSION,name);
  exit(0);
}

int main(int argc, char **argv) {
  struct termios term;
  struct interrupt interrupts[MAX_INTS];
  int loop=-1,active=1,count;
  char key;
  
  memset(interrupts,0,sizeof(interrupts));
  for(count=1;count<argc;count++) {
    if (strcmp(argv[count],"-a")==0)
      active=0;
    else if ((strcmp(argv[count],"-n")==0) && (count+1<argc)){
      loop=atoi(argv[++count]);
    }
    else
      help(argv[0]);
  }
  if (loop<0) {
    tcgetattr(fileno(stdin)/* i DO KNOW it's 0 but this is 'nicer' */,&term);
    term.c_lflag &= ~(ICANON);
    tcsetattr(fileno(stdin),0,&term);
    fcntl(fileno(stdin),F_SETFL,O_NONBLOCK);
  }
  read_ints(interrupts,0);
  sleep(1);
  while(loop) {
    if ((loop<0) && (read(fileno(stdin),&key,1)==1)) {
      switch(key) {
      case 'a':
	if (active != 0) active=0;
	else active=1;
	break;
      case 't':
	system("top");
	break;
      case 'q':
	loop=0;
	break;
      default:
	fcntl(fileno(stdin),F_GETFL,count);
	fcntl(fileno(stdin),F_SETFL,count&~O_NONBLOCK);
	ihelp(active);
	fcntl(fileno(stdin),F_SETFL,O_NONBLOCK);
	break;
      }
      read_ints(interrupts,0);
    }
    else {
      read_ints(interrupts,1);
      if (loop)
	printf(CLEAR);
      print_ints(interrupts,active);
    }
    if (loop)
      sleep(1);
    if (loop>0)
      loop--;
  }
  fcntl(fileno(stdin),F_GETFL,count);
  fcntl(fileno(stdin),F_SETFL,count&~O_NONBLOCK);
  term.c_lflag |= ICANON;
  tcsetattr(fileno(stdin),0,&term);
  printf("\n");
  return 0;
}
