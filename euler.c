# include <stdio.h>

/*
  If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

  Find the sum of all the multiples of 3 or 5 below 1000.
*/

int problem1(int max, int ignore1, int ignore2){
  int sum;
  int i;
  for (sum = 0, i = 0; i < max; i++) {
    if(i % ignore1 == 0 || i % ignore2 == 0)
      sum += i;
  }
  return sum;
}

/*
  2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

  What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

int problem5(int min, int max){
  int i;
  int j;
  for(i = 1;; i++)
    for(j = min; j <= max; j++)
      if(i % j == 0){
	if(j == max)
	  goto end;
      }else{
	break;
      }
 end:
  return i;
}

int main(){
  int prob1 = problem1(1000,3,5);
  printf("Problem 1: %d\n", prob1);
  int prob5 = problem5(1,20);
  printf("Problem 5: %d\n", prob5);
}
