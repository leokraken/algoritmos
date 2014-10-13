#include <iostream>
#include <fstream>
#include "CHC.hh"

int main (int argc, char** argv)
{
	using skeleton CHC;

	system("clear");

	if(argc < 4)
		show_message(1);

	ifstream f1(argv[1]);
	if (!f1) show_message(11);

	ifstream f2(argv[2]);
	if (!f2) show_message(12);

	Problem pbm;
	f2 >> pbm;

	Operator_Pool pool(pbm);
	SetUpParams cfg(pool);
	f1 >> cfg;
	cout<<cfg;
	Solver_Seq solver(pbm,cfg);
	solver.run();

	if (solver.pid()==0)
	{
		solver.show_state();
		int *o=solver.global_best_solution().get_ordenado();
		cout << "Solution" << solver.global_best_solution() << endl
		     << " Fitness: " << solver.global_best_solution().calculate_fitness(o) << endl;
		cout << "\n\n :( ---------------------- THE END --------------- :) " <<endl;

		ofstream fexit(argv[3]);
		if(!fexit) show_message(13);
		fexit << solver.userstatistics();
		
		//para gantt
		ofstream gantt(argv[4]);
		gantt << solver.global_best_solution();

	}
	return(0);
}
