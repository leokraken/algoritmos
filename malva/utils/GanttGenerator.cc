#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <random.hh>
#include <Matrix.hh>
#include <Rarray.h>
#include "../rep/GA/newGA.hh"

using namespace std;

typedef Rarray<tuple<int,int,int,int>> List;
typedef Rarray<Rarray<tuple<int,int,int,int>>> Schedule;

using skeleton newGA;

void load(char* filename,const Problem &_pbm , ofstream &os){
	using skeleton newGA;
	ifstream file(filename);

	int cant_job,cant_op,job,op,machine,deadline;

	//leo el problema, uso clase de newGA


	cant_job= _pbm.cantidad_trabajos();
	cant_op= _pbm.dimension();
	
	List list= List(cant_op);
	Schedule schedule = Schedule(cant_job);
	
	//defino los colores de las maquinas

	string colors[10]={"red","blue","yellow","green","fucsia","aqua","black","white","orange","white"};


	for(int i=0; i<cant_op; i++){
		file >> job;
		file >> op;
		file >> machine;
		file >> deadline;
		list[i]=make_tuple(job,op,machine,deadline);
		cout << job << op <<endl;
	}
	//ordeno en matrix
	//inicializo matriz
	for(int i=0; i<cant_job;i++){
		schedule[i]= List(_pbm.cantidad_operaciones()[i]);	
	}

	int fitness=0;
	for(int i=0; i<cant_op; i++){
		int job= get<0>(list[i]);
		int op= get<1>(list[i]);
		int machine= get<2>(list[i]);
		int deadline= get<3>(list[i]);
		schedule[job][op]= make_tuple(0,0,machine,deadline);
		fitness= max(deadline+_pbm.get_costos(job,op,machine),fitness);
	}



//parseo al ofstream
		os 	<<"\\" 
			<<"begin{ganttchart}[x unit=.7cm, y unit title=.6cm, y unit chart=1.5cm]{0}{"
			<<fitness
			<<"}"
			<<endl;
		os 	<<"\\"
			<<"gantttitlelist{1,...,"
			<<fitness
			<<"}{1} \\\\"
			<<endl;

		for(int job=0; job<schedule.size(); job++){
			for(int op=0; op<_pbm.cantidad_operaciones()[job];op++){
				string ganttbar="";
				int machine = get<2>(schedule[job][op]);
				int time_init = get<3>(schedule[job][op]);
				int costo= _pbm.get_costos(job,op,machine);
				int time_end=time_init+costo;

				if(op==0){
				ganttbar="Job ";
				stringstream ss;
				ss<<job;
				ganttbar+=ss.str();
				}
				os	<< "\\"
					<<"gantt" << colors[machine]<<"bar{"<< ganttbar <<"}"<< "{" <<	time_init 	<<	"}"	<<	"{" <<time_end -1<< "}";
			
				if(op==_pbm.cantidad_operaciones()[job]-1){ //ultima operacion agrego //
					os << "\\\\" <<endl;
				}else{ //sino un salto de linea
					os << endl;
				}		


			}
		}

		//termina for
		os 	<< "\\" 
			<< "end{ganttchart}"
			<<endl;
		//fin

	
}



int main (int argc, char** argv){

	//string path="/gantt/data/";
//	string salida= "/gantt/latex/";
	//string problem= "/instances/";
	//path+=argv[1]; //genero path de carga
//	salida+=argv[1]; //genero path de salida
	//problem+=argv[1]; //genero ruta del problema
	

cout<<argv[1]<<endl;
cout<<argv[2]<<endl;
cout<<argv[3]<<endl;
	Problem pbm;
	ofstream fexit(argv[3]);
	ifstream file(argv[1]);
	file >> pbm;
	//creo parser
	cout <<pbm;
cout<<"ok";
	load(argv[2],pbm,fexit); //gantt/data
	fexit.close();



}
