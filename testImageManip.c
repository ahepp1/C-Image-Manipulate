// test_search_functions.c
// <STUDENT: ADD YOUR INFO HERE: name, JHED, etc.>

/*


#include <stdio.h>
#include <assert.h>
#include "imageManip.h"


/*
 * Declarations for tester functions whose definitions appear below.
 * (You will need to fill in the function definition details, at the
 * end of this file, and add comments to each one.)
 * Additionally, for each helper function you elect to add to the
 * provided search_functions.h, you will need to supply a corresponding
 * tester function in this file.  Add a declaration for it here, its
 * definition below, and a call to it where indicated in main.
 * /
void test_file_eq();      // This one is already fully defined below.
void test_populate_grid();
void test_find_right();
void test_find_left();
void test_find_down();
void test_find_up();
void test_find_all();


/*
 * Main method which calls all test functions.
 * /
int main() {
  printf("Testing file_eq...\n");
  test_file_eq();
  printf("Passed file_eq test.\n\n");

  printf("Running search_functions tests...\n");

  test_populate_grid();
  printf("Passed search_functions populate tests!!!\n");
  test_find_right();
  printf("Passed search_functions right tests!!!\n");
  test_find_left();
  printf("Passed search_functions left tests!!!\n");
  test_find_down();
  printf("Passed search_functions down tests!!!\n");
  test_find_up();
  printf("Passed search_functions up tests!!!\n");
  test_find_all();
  printf("Passed search_functions all tests!!!\n");
  /* You may add calls to additional test functions here. * /

  printf("Passed search_functions tests!!!\n");
}



/*
 * Test file_eq on same file, files with same contents, files with
 * different contents and a file that doesn't exist.
 * Relies on files test1.txt, test2.txt, test3.txt being present.
 * /
void test_file_eq() {
  FILE* fptr = fopen("test1.txt", "w");
  fprintf(fptr, "this\nis\na test\n");
  fclose(fptr);

  fptr = fopen("test2.txt", "w");
  fprintf(fptr, "this\nis\na different test\n");
  fclose(fptr);

  fptr = fopen("test3.txt", "w");
  fprintf(fptr, "this\nis\na test\n");
  fclose(fptr);

  assert( file_eq("test1.txt", "test1.txt"));
  assert( file_eq("test2.txt", "test2.txt"));
  assert(!file_eq("test2.txt", "test1.txt"));
  assert(!file_eq("test1.txt", "test2.txt"));
  assert( file_eq("test3.txt", "test3.txt"));
  assert( file_eq("test1.txt", "test3.txt"));
  assert( file_eq("test3.txt", "test1.txt"));
  assert(!file_eq("test2.txt", "test3.txt"));
  assert(!file_eq("test3.txt", "test2.txt"));
  assert(!file_eq("", ""));  // can't open file
}


void test_populate_grid(){

   char grid[MAX_SIZE][MAX_SIZE];
   char *files[] = {"5x4.txt","space_grid.txt","search1.txt","misshapen.txt"};
  int expect[] = {-2,-2,4,-2};
  int result;


    for (int i = 0; i < 4; i++) {
      result = populate_grid(grid,files[i]);
      if (result != expect[i]) {
	       printf("populate_grid failed for: %s, returned: %d\n", files[i], result);
      }
      assert(result == expect[i]);
    }
}


void test_find_right(){

  char grid[MAX_SIZE][MAX_SIZE];
  int result;
  FILE* output = fopen("output.txt","w");

  char file[] = "search1.txt";
  char *word[] = {"tip","pop","key","nope"};
  int expect[] = {0,0,1,0};

  int n = populate_grid(grid, file);

  //loop through all inputs
  for (int i = 0; i < 4; i++) {
    result = find_right(grid,n,word[i],output);

    //print error
    if (result != expect[i]) {
      printf("failed at word: %s, returned: %d\n",word[i],result);
    }

    //check assert
    assert(result == expect[i]);
  }
}




void test_find_left(){
  char grid[MAX_SIZE][MAX_SIZE];
  int result;
  FILE* output = fopen("output.txt","w");

  char file1[] = "search1.txt";
  char *word[] = {"tip","pop","key","nope"};
  int expect[] = {1,0,0,0};

  int n = populate_grid(grid,file1);
  //loop through all inputs
  for (int i = 0; i < 4; i++) {
    result = find_left(grid,n,word[i],output);
    //print error
    if (result != expect[i]) {
      printf("failed at word: %s, returned: %d\n",word[i],result);
    }
    //check assert
    assert(result == expect[i]);
  }

  //case for overlapping words

}


void test_find_down(){
  char grid[MAX_SIZE][MAX_SIZE];
  int result;
  FILE* output = fopen("output.txt","w");

  char file1[] = "search1.txt";
  char *word[] = {"tip","pop","key","nope"};
  int expect[] = {0,1,1,0};

  int n = populate_grid(grid,file1);
  //loop through all inputs
  for (int i = 0; i < 4; i++) {
    result = find_down(grid,n,word[i],output);
    //print error
    if (result != expect[i]) {
      printf("failed at word: %s, returned: %d\n",word[i],result);
    }
    //check assert
    assert(result == expect[i]);
  }

}


void test_find_up(){
  char grid[MAX_SIZE][MAX_SIZE];
  int result;
  FILE* output = fopen("output.txt","w");

  char file1[] = "search1.txt";
  char *word[] = {"tip","pop","key","nope"};
  int expect[] = {0,1,0,0};

  int n = populate_grid(grid,file1);
  //loop through all inputs
  for (int i = 0; i < 4; i++) {
    result = find_up(grid,n,word[i],output);
    //print error
    if (result != expect[i]) {
      printf("failed at word: %s, returned: %d\n",word[i],result);
    }
    //check assert
    assert(result == expect[i]);
  }


}


void test_find_all(){

  FILE* output = fopen("output.txt","w");
  FILE* fptr = fopen("search1_out.txt","w");
  fprintf(fptr,"tip 0 2 L\npop 0 0 D\npop 2 0 U\nkey 2 1 R\n key 0 3\n");

  char grid[MAX_SIZE][MAX_SIZE];
  char file1[] = "search1.txt";
  char *word[] = {"tip","pop","key","nope"};
  int expect[] = {1,2,2,0};
  int result;
  int n = populate_grid(grid,file1);

   for (int i = 0; i < 4; i++) {
    result = find_all(grid,n,word[i],output);
    if (result != expect[i]) {
      printf("find_all failed at i:%d, returned:%d\n",i,result);
    }
    assert(result == expect[i]);
    assert(file_eq("output.txt","search1_out.txt"));
    }


  //case for overlapping words

}
*/
