/***********************************************
*
*	Simulated Annealing
*
************************************************/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <functional>  


using std::string;
using std::cout;
using std::endl;
using std::swap;

int getDist(string value, string goal);
double acceptance(int energy, int newEnergy, double temperature);

int main(){
	
	//spoiler alert for zero escape: zero time dilemma
	string start = "zerotimedilemma";
	string goal = "meimzeroimdelta";

	double temp = 100000;
	double coolRate = 0.0003;

	string current = start;
	
	string best = current;
	
	while(temp > 1) {
		
		string next = current;
	
		int pos1 = rand() % goal.size();
		int pos2 = rand() % goal.size();
		
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


		cout <<"best " << best << endl;
		cout <<"current " << current << endl;


	}
	
	cout << "Final " << best << endl;
	cout << "Final distance" << getDist(best,goal) << endl;


}

	int getDist(string value, string goal){
			if (value == goal){
				return 0;
			}
			else{
				double dist = 0;
				int i;
				for(i = 0; i < goal.size(); i++){
					char letter = goal[i];
					int pos =  value.find(letter);
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



