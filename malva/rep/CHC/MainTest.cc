#include "CHC.hh"
#include <random>
#include <sstream>
using skeleton CHC;

void massCross(const Problem &pbm){
	using skeleton CHC;
	
	for (int i=0;i<5;i++) cout<<endl;
	cout << "MASS::CROSS::INIT" <<endl;

	Solution * F1= new Solution(pbm);
	Solution * F2= new Solution(pbm);
	cout<<"ok"<<endl;
	F1->initialize();
	F2->initialize();
	cout << "FATHER::1" << endl << *F1 << endl;
	cout << "FITNESS:: "<<F1->fitness() <<endl;
	cout << "FATHER::2" << endl << *F2 << endl;
	cout << "FITNESS:: "<<F2->fitness() <<endl;

	Rarray<Solution*> population(2);
	population[0]=F1;
	population[1]=F2;

	Intra_Operator *I= Intra_Operator::create(0);
	int fitness=1000;
	for(int i=0; i<10000;i++){
		I->execute(population);
		if(population[1]->fitness()<fitness) fitness=population[1]->fitness();
		if(population[0]->fitness()<fitness) fitness=population[0]->fitness();
}
cout << "SON::1" << endl << *population[0] << endl;
cout << "FITNESS:: "<<population[0]->fitness() <<endl;
cout << "SON::2" << endl << *population[1] << endl;
cout << "FITNESS:: "<<population[1]->fitness() <<endl;
cout <<"best fitness:"<<fitness<<endl;
}



int main (int argc, char** argv)
{
	using skeleton CHC;

	ifstream f1(argv[1]);
	if (!f1) show_message(12);
	
	Problem pbm;
	f1 >> pbm;
	cout << "OKK" << endl;
	f1.close();

	cout << pbm;
	Solution * Sol= new Solution(pbm);
	cout<<"created"<<endl;

	Sol->initialize();
	cout<<"init"<<endl;
	Sol->repair();
	cout <<*Sol<<endl;
	cout<<"repaired"<<endl;
	
	cout << Sol->fitness()<<endl;
	int *o= Sol->get_ordenado();
	cout << Sol->calculate_fitness(o)<<endl;
	o= Sol->get_ordenado();

	cout << Sol->calculate_fitness(o)<<endl;
	o= Sol->get_ordenado();

	cout << Sol->calculate_fitness(o)<<endl;
	o= Sol->get_ordenado();

	cout << Sol->calculate_fitness(o)<<endl;

	return(0);
}
