#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>

void printPerms(int binData){
  int n;
  printf("%o\n", binData);
  
  printf("\n");
  printf("-");
  for (n = 8; n >= 0; n--){
    if (binData >> 1){
      if (n % 3 == 2)
	printf("r");
      if (n % 3 == 1)
	printf("w");
      if (n % 3 == 0)
	printf("x");
    }
    else printf("-");
    binData = binData >> 1;
  }
  printf("\n");
}

void printSize(long numBytes){
  
  long remSize = numBytes;
  int gigs = (int) (remSize / (1024 * 1024 * 1024));
  remSize -= gigs * (1024 * 1024 * 1024);
  int megs = (int) (remSize / (1024 * 1024));
  remSize -= megs * (1024 * 1024);
  int kibs = (int) (remSize / 1024);
  remSize -= kibs * 1024;

  printf("size: %d GB, %d MB, %d KB, %d B\n\n", gigs, megs, kibs, remSize);
  
  
}

int analyze(struct dirent * entry){//returns entry size
  
  if (entry->d_type == 0) printf("Directory: \t");
  else printf("Regular File: \t");

  printf("%s\n", entry->d_name);
  
  struct stat curStats;
  stat(entry->d_name, &curStats);
  
  
  return curStats.st_size;
}

void analyzeDirectory(char * dirName){
  printf("\n");
  printf("Printing statistics of %s\n\n", dirName);
  DIR *d = opendir(dirName);
  struct dirent *curEntry; 
  long sizeSum = 0;
  while (curEntry = readdir(d)){//loops through all entries
    sizeSum += analyze(curEntry);
  }
  printf("\nTotal Directory ");
  printSize(sizeSum);
  closedir(d); 
}

int main(){
  printf("\n");
  analyzeDirectory(".");
  return 0;
}
