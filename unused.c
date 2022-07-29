#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Search_in_File1(char *fname) {
  FILE *ifp, *ofp;
  char *find_ptr, temp, read[102];
  char *buff_ptr;
  int flag = 0;
  size_t find_len = strlen("#");

  ifp = fopen(fname, "r+");
  ofp = fopen("op.c", "w+");
  if (ifp == NULL || ofp == NULL) {
    printf("Can't open file.");
    exit(0);
  }
  rewind(ifp);

  while (!feof(ifp)) {
    fgets(read, 100, ifp);
    buff_ptr = read;
    while ((find_ptr = strstr(buff_ptr, "#"))) {
      flag = 1;
      while (buff_ptr < find_ptr) {
        fputc((int)*buff_ptr++, ofp);
      }
      fputs("//#", ofp);
      buff_ptr += find_len;
      fputs(buff_ptr, ofp);
    }
    if (flag == 0) {
      fputs(buff_ptr, ofp);
    } else {
      flag = 0;
      continue;
    }
  }

  fclose(ifp);
  fclose(ofp);
}

int Search_in_File2(char *fname, char *str) {
  FILE *fp;
  FILE *fpptr;
  char temp[512];
  char *p;
  if ((fp = fopen(fname, "r")) == NULL) {
    return (-1);
  }
  fpptr = fopen("file1.txt", "w");
  while (fgets(temp, 512, fp) != NULL) {
    if ((p = strstr(temp, str)) != NULL) {

      for (int i = 10; *(p + i) != '>'; i++) {
        fprintf(fpptr, "%c", *(p + i));
      }
      fprintf(fpptr, "\n");
    }
  }
  if (fp) {
    fclose(fp);
  }
  if (fpptr) {
    fclose(fpptr);
  }
  return (0);
}
int Search_in_File3(char *fname, char *str) {
  FILE *fp;
  FILE *ftr;
  char temp[512];
  char *p;
  if ((fp = fopen(fname, "r")) == NULL) {
    return (-1);
  }
  ftr = fopen("file2.txt", "w");
  while (fgets(temp, 512, fp) != NULL) {
    if ((p = strstr(temp, str)) != NULL) {

      for (int i = 12; *(p + i) != '>'; i++) {
        fprintf(ftr, "%c", *(p + i));
      }
      fprintf(ftr, "\n");
    }
  }
  if (fp) {
    fclose(fp);
  }
  if (ftr) {
    fclose(ftr);
  }
  return (0);
}
int main(int argc, char **argv) {

  Search_in_File1(argv[1]);
  Search_in_File2(argv[1], "#include <");
  char filename[200] = "gcc ";
  strcat(filename, "op.c");
  strcat(filename, " 2> out.txt");
  const char *command = filename;
  FILE *fptr;
  fptr = fopen("out.txt", "w+");
  system(command);
  Search_in_File3("out.txt", "include ‘<");
  printf("\nThe Unused headers in the project are:\n");
  system("sort file1.txt > file4.txt");
  system("sort file2.txt > file3.txt");
  system("comm -23 file4.txt file3.txt");
  remove("op.c");
  remove("file1.txt");
  remove("file2.txt");
  remove("file3.txt");
  remove("file4.txt");
  remove("out.txt");
  return 0;
}
