#include "newGA.hh"
#include <random>
#include <sstream>
using skeleton newGA;




void massCross(const Problem &pbm){
	using skeleton newGA;
	
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
	
	for(int i=0; i<100;i++)
		I->execute(population);

cout << "SON::1" << endl << *population[0] << endl;
cout << "FITNESS:: "<<population[0]->fitness() <<endl;
cout << "SON::2" << endl << *population[1] << endl;
cout << "FITNESS:: "<<population[1]->fitness() <<endl;
}

void massMutation(const Problem &pbm){
	using skeleton newGA;
	Solution * F1= new Solution(pbm);
	F1->initialize();
	Solution * copy = new Solution(*F1);
	Rarray<Solution*> population(1);
	population[0]=F1;
cout << "FATHER::1" << endl << *F1 << endl;
cout << "FITNESS:: "<<F1->fitness() <<endl;
	Intra_Operator *I= Intra_Operator::create(1);
	cout << "OK"<< endl;
	for(int i=0; i<100;i++)
		I->execute(population);
cout << "SON::1" << endl << *population[0] << endl;

cout << "FITNESS:: "<<population[0]->fitness() <<endl;
	//printArray(population[0]->array_solucion(),pbm.cantidad_trabajos(),pbm.cantidad_maquinas());
	if(*copy!=*population[0]) cout << "MUTATION!" << endl;
}

void testDelete(const Problem &pbm){
	using skeleton newGA;
	Solution * F1= new Solution(pbm);
	F1->initialize();

	Rarray<Solution*> population(1);
cout << "ok" <<endl;
	population[0]=new Solution(pbm);
	*population[0]=*F1;
	cout << *population[0]<<endl;


}

void first(const Problem &pbm){
	using skeleton newGA;
	Solution * F1= new Solution(pbm);
	Solution * F2= new Solution(pbm);
	F1->initialize();

	F2->to_Solution(F1->to_String());
	cout << *F1 << endl;
	cout << *F2 << endl;
	
}

int **get_machines(char **argv){
	ifstream is(argv[1]);
	string buffer;
	getline(is,buffer);
	int null;
	int _cantidad_trabajos, _cantidad_maquinas;

	istringstream iss(buffer);
	iss >> _cantidad_trabajos;
	iss >> _cantidad_maquinas;

	int ** M= new int*[_cantidad_trabajos+1];

	
	for(int i=0; i<_cantidad_trabajos; i++){
		getline(is,buffer);
		istringstream parse(buffer);
	M[i]= new int[_cantidad_maquinas+1];
		for(int j=0; j<_cantidad_maquinas; j++){
			int aux;
			int null;
			parse >> aux;
			parse >> null;
			M[i][j]=aux;
		}
	}

	return M;

	}


void test1(char **argv){
//crea un problema y lo imprime
using skeleton newGA;

	ifstream f1(argv[1]);
	if (!f1) show_message(12);
	
	Problem pbm;


	f1 >> pbm;
	cout << "OKK" << endl;
	f1.close();

	cout << pbm;

}


int main (int argc, char** argv)
{
	using skeleton newGA;

	ifstream f1(argv[1]);
	if (!f1) show_message(12);
	
	Problem pbm;
	f1 >> pbm;
	cout << "OKK" << endl;
	f1.close();

	cout << pbm;




Solution * Sol= new Solution(pbm);
cout<<"redfd"<<endl;
Sol->initialize();

cout<<"ok2"<<endl;
Sol->repair();
cout <<*Sol<<endl;
cout <<"ok sol"<<endl;
int fitness=Sol->fitness();
cout <<"FITNESS:: "<<fitness<<endl;
//cout<<pbm;
cout <<"FITNESS:: "<<fitness<<endl;




Solution *Sol2= new Solution(pbm);
Sol2->initialize();
cout<< pbm;





cout << "fin";
massCross(pbm);
cout << "FINISHED::CROSS" << endl;
//cout << pbm << endl;


massMutation(pbm);
cout << "FINISHED::MUTATION" << endl;
/*
testDelete(pbm);


Solution *Sol2 = new Solution(pbm);
Sol2->fromProblem(pbm);
Sol2->repair();
cout <<*Sol2 <<endl;
cout << Sol2->fitness() <<endl;
*/


	return(0);
}
