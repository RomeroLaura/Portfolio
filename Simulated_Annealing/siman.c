/***********************************************
*
*	Simulated Annealing
*
************************************************/
#include <stdio.h>

// Laura Romero

int getDist(char * value, char * goal);
double acceptance(int energy, int newEnergy, double temperature);



int main(){

	//spoiler alert for zero escape: zero time dilemma
	char * start = "zerotimedilemma";
	char *  goal = "meimzeroimdelta";

	double temp = 100000;
	double coolRate = 0.0003;

	char * current = start;

	char * best = current;

	while(temp > 1) {

		char * next = current;

		int pos1 = rand() % sizeof(goal);
		int pos2 = rand() % sizeof(goal);

		swap(next[pos1], next[pos2]);

		int currentEnergy = getDist(current, goal);
		int nextEnergy = getDist(next, goal);

		double ac = acceptance(currentEnergy, nextEnergy, temp);
		double acrand = rand() % 1;
		bool cond = ac > acrand;
		if(ac > acrand ) {
			current = next;
		}

		if(nextEnergy <= getDist(best, goal) ){
			best = next;
		}

		temp *= (1-coolRate);


    printf("best ");
    printf(best );
    printf("\n");
    printf("current ");
    printf(current );
    printf("\n" );


	}
  printf("Final ");
  printf(best );
  printf("\n" );

  printf("Final distance ");
  printf(getDist(best,goal));
  printf("\n");

}


void swap(int * a, int * b)
{
   int temp;

   temp = * b;
   * b = * a;
   * a = temp;
}


int getDist(char * value, char * goal){
    if (strcmp(value, goal){
      return 0;
    }
    else{
      double dist = 0;
      int i;
      for(i = 0; i < sizeof(goal); i++){
        char letter = goal[i];
        int pos = strchr(value, letter) - strchr(value, value[0]);
        dist += abs(i - pos);

      }
      return dist*1000;

    }
  }



double acceptance(int energy, int newEnergy, double temperature) {
  if (newEnergy < energy) {
              return 1.0;
        }
        else{
         return exp((energy - newEnergy) / temperature);
  }
}
