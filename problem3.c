/*
problem3.c

Driver function for Problem 3.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>

/* Constants */
#define OLDCHIP 0
#define NEWCHIP 1
#define MAXNUMERATOR 100
#define MAXDENOMINATOR 100

/* Used to store all the statistics for a single chip. */
struct statistics;

/* Used to store all the statistics for both chips for each problem. */
struct chipStatistics;

struct statistics {
  int operations;
  int instances;
  int minOperations;
  double avgOperations;
  int maxOperations;
};

struct chipStatistics {
  struct statistics oldChipEuclid;
  struct statistics newChipEuclid;
  struct statistics oldChipSieve;
  struct statistics newChipSieve;
};

/* Set all statistics to 0s */
void initialiseStatistics(struct statistics *stats);

/* Collects the minimum, average and maximum operations from running all
combinations of numerators from 1 to the given maxNumerator and 1 to the given
maxDenominator. */
void collectStatistics(struct chipStatistics *chipStats, int maxNumerator,
  int maxDenominator);

/* Divides the number of operations by the number of instances. */
void calculateAverage(struct statistics *stats);

/* Prints out the minimum, average and maximum operations from given
statistics. */
void printStatistics(struct statistics *stats);

/* Calculates the number of operations required for Euclid's algorithm given the
numerator and denominator when running on the given chip type (one of OLDCHIP
and NEWCHIP) by moving through the steps of the algorithm and counting each
pseudocode operation. */
void euclid(int numerator, int denominator, int chip, struct statistics *s);

/* Calculates the number of operations required for the sieve of Eratosthenes
given the numerator and denominator when running on the given chip type (one of
OLDCHIP and NEWCHIP) by moving through the steps of the algorithm and counting
each pseudocode operation. */
void eratosthenes(int numerator, int denominator, int chip,
  struct statistics *s);

int main(int argc, char **argv){
  struct chipStatistics summaryStatistics;

  collectStatistics(&summaryStatistics, MAXNUMERATOR, MAXDENOMINATOR);

  printf("Old chip (Euclid):\n");
  printStatistics(&(summaryStatistics.oldChipEuclid));
  printf("\n");
  printf("New chip (Euclid)\n");
  printStatistics(&(summaryStatistics.newChipEuclid));
  printf("\n");
  printf("Old chip (Sieve)\n");
  printStatistics(&(summaryStatistics.oldChipSieve));
  printf("\n");
  printf("New chip (Sieve)\n");
  printStatistics(&(summaryStatistics.newChipSieve));
  printf("\n");

  return 0;
}

void collectStatistics(struct chipStatistics *chipStats, int maxNumerator,
  int maxDenominator){
  int numerator, denominator;
  /* Initialise all statistics */
  initialiseStatistics(&(chipStats->oldChipEuclid));
  initialiseStatistics(&(chipStats->newChipEuclid));
  initialiseStatistics(&(chipStats->oldChipSieve));
  initialiseStatistics(&(chipStats->newChipSieve));

  for(numerator = 1; numerator <= maxNumerator; numerator++){
    for(denominator = 1; denominator <= maxDenominator; denominator++){
      /* Run algorithms for all combinations of numerator and denominator. */
      euclid(numerator, denominator, OLDCHIP,
        &(chipStats->oldChipEuclid));
      euclid(numerator, denominator, NEWCHIP,
        &(chipStats->newChipEuclid));
      eratosthenes(numerator, denominator, OLDCHIP,
        &(chipStats->oldChipSieve));
      eratosthenes(numerator, denominator, NEWCHIP,
        &(chipStats->newChipSieve));
    }
  }
  calculateAverage(&(chipStats->oldChipEuclid));
  calculateAverage(&(chipStats->newChipEuclid));
  calculateAverage(&(chipStats->oldChipSieve));
  calculateAverage(&(chipStats->newChipSieve));
}

void calculateAverage(struct statistics *stats){
  stats->avgOperations = (double) stats->operations / stats->instances;
}

void initialiseStatistics(struct statistics *stats){
  stats->operations = 0;
  stats->instances = 0;
  stats->minOperations = INT_MAX;
  stats->avgOperations = 0;
  stats->maxOperations = 0;
}

void euclid(int numerator, int denominator, int chip, struct statistics *s){
  /* IMPLEMENT THIS */
  int n_operations = 0;
  int b = numerator;
  int a = denominator;
  n_operations +=2;

  while (b!=0){
    int t = b;
    b = a % b;
    a = t;
    n_operations +=9;
  }

  if (n_operations < s-> minOperations){
    s->minOperations = n_operations;

  if (n_operations > s->maxOperations){
    s->maxOperations = n_operations;
  }

  
  }

  s->instances += 1;
  s->operations += n_operations;
}

void eratosthenes(int numerator, int denominator, int chip, struct statistics *s){
  /* IMPLEMENT THIS */
  int n_operations = 0;
  int num = numerator;
  int den = denominator;
  n_operations +=2;

  int numCandidates = 0;

  if (num < den){
    numCandidates = num;
  } else{

    numCandidates = den;
  }
  n_operations +=2;

  int* primes = (int*)malloc(sizeof(int)*numCandidates);

  
  int j;
  for(j = 0;j < numCandidates; j++){

    primes[j] = 1;
  }
  int i = 1;
  n_operations += numCandidates + 2;

  while( i < numCandidates){
    i = i +1;
    n_operations += 1;
    if (primes[i]){
      int j = i + i;
      n_operations += 1;
    
      while(j < numCandidates){
        if (((j/i) > 1) && (j % i == 0)){
          primes[j] = 0;
        }
        if(chip == OLDCHIP){
        n_operations += 11;

        }

        j = j + 1;
      }

      if( chip == NEWCHIP){
        n_operations += 1;
      }

      while (num % i == 0 && den % i ==0){

        num = num / i;
        den = den/ i;
        n_operations += 24;
      }
    }
  }

  if (n_operations > s->maxOperations){
    s->maxOperations = n_operations;
  }

  if (n_operations < s->minOperations){

    s->minOperations = n_operations;
  }
  s->instances += 1;
  s->operations += n_operations;


}
  



void printStatistics(struct statistics *stats){
  printf("Minimum operations: %d\n", stats->minOperations);
  printf("Average operations: %f\n", stats->avgOperations);
  printf("Maximum operations: %d\n", stats->maxOperations);
}

