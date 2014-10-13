#ifndef INC_REQ_newGA
#define INC_REQ_newGA
#include "newGA.hh"
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


skeleton newGA
{

	// Problem ---------------------------------------------------------------

	Problem::Problem ():_cantidad_trabajos(0)
	{	
		_costos= Matriz(0);
		_cantidad_operaciones=NULL;
	}


	Problem& Problem::operator= (const Problem &pbm)
	{
		_cantidad_maquinas= pbm._cantidad_maquinas;
		_cantidad_trabajos= pbm._cantidad_trabajos;
		_costos= Matriz(_cantidad_trabajos);		
		_cantidad_operaciones = new int[_cantidad_trabajos];
		
		for(int j=0; j<_cantidad_trabajos;j++){
			_cantidad_operaciones[j]= pbm._cantidad_operaciones[j];
			_costos[j]= Fila(_cantidad_operaciones[j]);
			for(int i=0; i<pbm._cantidad_operaciones[j];i++){
				_costos[j][i]=pbm._costos[j][i];				
			}
		}
		return *this;
	}


	ostream& operator<< (ostream& os, const Problem& pbm)
	{
		os 	<< endl << endl << "Machines: " << pbm._cantidad_maquinas
		   	<< endl
			<< "Jobs: " << pbm._cantidad_trabajos
			<< endl;


			for(int j=0; j<pbm._cantidad_trabajos;j++){
				for(int i=0; i<pbm._cantidad_operaciones[j];i++){

					for(int m=0; m<pbm._costos[j][i].size();m++){
					os 	<< get<0>(pbm._costos[j][i][m])
						<< " "
						<<get<1>(pbm._costos[j][i][m])
						<< " ";
					}
				}
			os << endl;
			}
		return os;
	}



	istream& operator>> (istream& is, Problem& pbm)
	{ 

		//Fila Inicial
		is >> pbm._cantidad_trabajos;
		is >> pbm._cantidad_maquinas;
		pbm._dimension=0;
		pbm._cantidad_operaciones= new int[pbm._cantidad_trabajos];
		pbm._costos= Matriz(pbm._cantidad_trabajos);

		//Itero sobre trabajos
		for(int i=0; i<pbm._cantidad_trabajos; i++){

		is >> pbm._cantidad_operaciones[i]; //operaciones
		pbm._dimension+= pbm._cantidad_operaciones[i];
		Fila aux(pbm._cantidad_operaciones[i]);

		//Itero sobre cantidad operaciones del trabajo
		for(int j=0; j<pbm._cantidad_operaciones[i]; j++){
		int m;
		is >> m;//maquinas permitidas
		Lista lista(m);

			for(int cant_m=0; cant_m<m; cant_m++){
				int nro_maquina;
				int tiempo_inicio;
				is >> nro_maquina;
				is >> tiempo_inicio;
				lista[cant_m]=make_tuple(nro_maquina-1,tiempo_inicio);
			}
		aux[j]=lista;
		}

		pbm._costos[i]=aux;
		}

		return is;
	}




	bool Problem::operator== (const Problem& pbm) const
	{	
		if(_cantidad_maquinas!=pbm.cantidad_maquinas() ||
			_cantidad_trabajos!=pbm.cantidad_trabajos()
		)return false;

		
		for(int i=0;i<pbm._cantidad_trabajos;i++){
			if(_cantidad_operaciones[i]!=pbm._cantidad_operaciones[i]) return false;
				for(int j=0;j<pbm._cantidad_operaciones[i];j++){
					for(int m=0; m<pbm._costos[i][j].size();m++){
					if(_costos[i][j][m]!=pbm._costos[i][j][m]) return false;
					}
				}
		}

		return true;
	}

	bool Problem::operator!= (const Problem& pbm) const
	{
		return !(*this == pbm);
	}

	Direction Problem::direction() const
	{
		return minimize;
	}
	
	int Problem::dimension() const
	{
		return _dimension;
	}

	int Problem::cantidad_maquinas() const
	{
		return _cantidad_maquinas;
	}

	int Problem::cantidad_trabajos() const
	{
		return _cantidad_trabajos;
	}
	
	int* Problem::cantidad_operaciones() const
	{
		return _cantidad_operaciones;
	}	

	int Problem::get_costos(const int i, const int j, const int m) const
	{	
		bool ok=false;
		int it=0;
		while(!ok && it<_costos[i][j].size()){
			if((get<0>(_costos[i][j][it]))==m){
			ok=true;
			
			}else{
			it++;
			}
		}

		return get<1>(_costos[i][j][it]);

	}

	int Problem::maquinas_operacion(const int j, const int i) const
	{
		return _costos[j][i].size();
	}


	int Problem::get_maquina_index(const int j, const int i, const int index) const
	{
		return get<0>(_costos[j][i][index]);
	}


	Problem::~Problem()
	{ 
	}




	// Solution --------------------------------------------------------------


	Solution::Solution (const Problem& pbm):_pbm(pbm)
	{
		_solucion= Rarray<Tupla>(pbm.dimension());
	}

	const Problem& Solution::pbm() const
	{
		return _pbm;
	}

	Solution::Solution(const Solution& sol):_pbm(sol.pbm())
	{
		*this=sol;
	}

	istream& operator>> (istream& is, Solution& sol) //cuando se usa esto?
	{
		//for (int i=0;i<sol.pbm().dimension();i++)
		//	is >> sol._var[i];
		return is;
	}


	ostream& operator<< (ostream& os, const Solution& sol)
	{
		for (int i=0;i<sol.pbm().dimension();i++){
			os 
				<< get<0>(sol._solucion[i]) //job
				<< " " 
				<< get<1>(sol._solucion[i]) //op				
				<< " "	
				<< get<2>(sol._solucion[i]) //machine
				<< " "
				<< get<3>(sol._solucion[i]) //deadline
				<< endl;		
		}

		os << endl;

		return os;
	}

	NetStream& operator << (NetStream& ns, const Solution& sol)
	{
		//for (int i=0;i<sol._var.size();i++)
		//	ns << sol._var[i];
		return ns;
	}

	NetStream& operator >> (NetStream& ns, Solution& sol)
	{
		//for (int i=0;i<sol._var.size();i++)
		//	ns >> sol._var[i];
		return ns;
	}

 	Solution& Solution::operator= (const Solution &sol)
	{
		_solucion= Rarray<tuple<int,int,int,int>>(sol._pbm.cantidad_trabajos());
		_solucion= sol._solucion;
		return *this;
	}

	bool Solution::operator== (const Solution& sol) const
	{
		if (sol.pbm() != _pbm) return false;

		for(int i=0; i<_pbm.dimension();i++){
			if(_solucion[i]!=sol._solucion[i]) return false;

		}
		return true;
	}

	bool Solution::operator!= (const Solution& sol) const
	{
		return !(*this == sol);
	}

	
	void Solution::repair()
	{
		int *sched_time_mach= new int[_pbm.cantidad_maquinas()];
		int *sched_time_job= new int[_pbm.cantidad_trabajos()];
		int *cont_operaciones= new int[_pbm.cantidad_trabajos()];

		//limpio vectores
		for(int i=0; i<_pbm.cantidad_maquinas();i++) 
			sched_time_mach[i]=0;
		for(int i=0; i<_pbm.cantidad_trabajos();i++){
			sched_time_job[i]=0;
			cont_operaciones[i]=0;
		}
		
		int cantM=_pbm.cantidad_maquinas();
		for(int i=0; i<_pbm.dimension();i++){

			//define deadline operation
			int Job=get<0>(_solucion[i]);
			int Op=cont_operaciones[Job];
			int rand= rand_int(0,_pbm.maquinas_operacion(Job,cont_operaciones[Job])-1); //elijo una maquina para op
			int Mach= _pbm.get_maquina_index(Job,Op,rand); //coherente a restricciones del problema.
			int deadline;

			if(sched_time_job[Job]>sched_time_mach[Mach]){
				deadline=sched_time_job[Job];
				sched_time_job[Job]+=_pbm.get_costos(Job,Op,Mach);
				sched_time_mach[Mach]=sched_time_job[Job];
			}else{
				deadline=sched_time_mach[Mach];
				sched_time_mach[Mach]+= _pbm.get_costos(Job,Op,Mach);
				sched_time_job[Job]=sched_time_mach[Mach];
			}
		
			_solucion[i]= make_tuple(Job,Op,Mach,deadline);
			cont_operaciones[Job]++;
		}


		delete [] sched_time_mach;
		delete [] sched_time_job;
		delete [] cont_operaciones;	

	}



	void Solution::initialize()
	{
		_solucion= Rarray<tuple<int,int,int,int> >(_pbm.dimension());	
		int k=0;
		for(int j=0;j<_pbm.cantidad_trabajos();j++){
			for(int i=0;i<_pbm.cantidad_operaciones()[j];i++){
				int rand= rand_int(0,_pbm.maquinas_operacion(j,i)-1);
				int Mach= _pbm.get_maquina_index(j,i,rand);
				_solucion[k]= make_tuple(j,i,Mach,0);
				k++;
			}
		}

		//aleatoriamente permuto la combinacion
		for(int k=0;k<_pbm.dimension();k++){
		int rand= rand_int(0,_pbm.dimension()-1);
		int rand2= rand_int(0,_pbm.dimension()-1);
		tuple<int,int,int,int> aux=_solucion[rand];
		_solucion[rand]=_solucion[rand2];
		_solucion[rand2]=aux;	
		}

		repair();
	}


	double Solution::fitness () const
	{
       		int fitness = 0;

		for(int k=0; k<_pbm.dimension();k++){
			int Job= get<0>(_solucion[k]);
			int Op= get<1>(_solucion[k]);
			int Mach= get<2>(_solucion[k]);
			int deadline= get<3>(_solucion[k]);
			fitness=max(fitness,deadline + _pbm.get_costos(Job,Op,Mach));
		}

		return fitness;
	}


	char *Solution::to_String() const
	{
		return (char *)_solucion.get_first();
	}

	void Solution::to_Solution(char *_string_)
	{ 
		tuple<int,int,int,int> *ptr=(tuple<int,int,int,int> *)_string_;

		for (int i=0;i<_pbm.dimension();i++)
		{
			_solucion[i]=*ptr;
			ptr++;
		}
	}

	unsigned int Solution::size() const
	{
		return (_pbm.dimension() * sizeof(tuple<int,int,int,int>));	
	}
	
	Tupla & Solution::solucion(const int index)
	{
		return _solucion[index];
	}

	Rarray<Tupla> & Solution::array_solucion()
	{
		return _solucion;
	}	

	void Solution::swap_tupla(const int a, const int b,const int k,Tupla swap)
	{
		//aux es victima de busqueda
		bool ok=false;
		int it=0;
		int index;

		while(!ok && it<_solucion.size()){
			int j= get<0>(_solucion[it]);
			int op= get<1>(_solucion[it]);
			int j_find=get<0>(swap);
			int op_find=get<1>(swap);
			if(j==j_find && op==op_find){
			ok=true;
			index=it;
			}
		it++;
		}

		//index es swap en la solucion actual, lo reemplazo por k
		_solucion[index]=_solucion[k];
		_solucion[k]=swap;
	}


	Solution::~Solution()
	{
	}

	// UserStatistics -------------------------------------------------------

	UserStatistics::UserStatistics ()
	{}

	ostream& operator<< (ostream& os, const UserStatistics& userstat)
	{

		for (int i=0;i< userstat.result_trials.size();i++)
		{
			os 
			   << userstat.result_trials[i].best_cost_trial
			   << "\t" << userstat.result_trials[i].nb_iteration_best_found_trial
			   << "\t" << userstat.result_trials[i].time_spent_trial
			   <<endl;
		}
		return os;
	}

	UserStatistics& UserStatistics::operator= (const UserStatistics& userstats)
	{
		result_trials=userstats.result_trials;
		return (*this);
	}

	void UserStatistics::update(const Solver& solver)
	{
		if( (solver.pid()!=0) || (solver.end_trial()!=true)
		  || ((solver.current_iteration()!=solver.setup().nb_evolution_steps())
		       && !terminateQ(solver.pbm(),solver,solver.setup())))
			return;

		struct user_stat *new_stat;

		if ((new_stat=(struct user_stat *)malloc(sizeof(struct user_stat)))==NULL)
			show_message(7);
		new_stat->trial         		 		 = solver.current_trial();
		new_stat->nb_evaluation_best_found_trial = solver.evaluations_best_found_in_trial();
		new_stat->nb_iteration_best_found_trial  = solver.iteration_best_found_in_trial();
		new_stat->worst_cost_trial     		 	 = solver.worst_cost_trial();
		new_stat->best_cost_trial     		 	 = solver.best_cost_trial();
		new_stat->time_best_found_trial		 	 = solver.time_best_found_trial();
		new_stat->time_spent_trial 		 		 = solver.time_spent_trial();

		result_trials.append(*new_stat);
	}

	void UserStatistics::clear()
	{
		result_trials.remove();
	}

	UserStatistics::~UserStatistics()
	{
		result_trials.remove();
	}

// Intra_operator  --------------------------------------------------------------

	Intra_Operator::Intra_Operator(const unsigned int _number_op):_number_operator(_number_op),probability(NULL)
	{}

	unsigned int Intra_Operator::number_operator() const
	{
		return _number_operator;
	}

	Intra_Operator *Intra_Operator::create(const unsigned int _number_op)
	{
		switch (_number_op)
		{
			case 0: return new Crossover;break;
			case 1: return new Mutation();break;
		}
	}

	ostream& operator<< (ostream& os, const Intra_Operator& intra)
	{
		switch (intra.number_operator())
		{
			case 0: os << (Crossover&)intra;break;
			case 1: os << (Mutation&)intra;break;
		}
		return os;
	}

	Intra_Operator::~Intra_Operator()
	{}



//  Crossover:Intra_operator -------------------------------------------------------------

	Crossover::Crossover():Intra_Operator(0)
	{
		probability = new float[1];
	}

	void Crossover::cross(Solution& sol1,Solution& sol2) const
	{   
		int a = rand_int(0,sol1.pbm().dimension()-1);
		int b = rand_int(0,sol1.pbm().dimension()-1);
		int Job_inf=min(a,b);
		int Job_sup=max(a,b);

		Rarray<Tupla> swap1= Rarray<Tupla>(Job_sup-Job_inf+1);
		Rarray<Tupla> swap2= Rarray<Tupla>(Job_sup-Job_inf+1);

		//guardo datos
		int j=0;
		for(int k=Job_inf;k<=Job_sup;k++){
			swap1[j]=sol1.solucion(k);
			swap2[j]= sol2.solucion(k);
			j++;
		}
		
		j=0;
		for(int k=Job_inf;k<=Job_sup;k++){
			sol1.swap_tupla(Job_inf,Job_sup,k,swap2[j]);
			sol2.swap_tupla(Job_inf,Job_sup,k,swap1[j]);
			j++;
		}

		sol1.repair();
		sol2.repair();
	}


	void Crossover::execute(Rarray<Solution*>& sols) const
	{
		for (int i=0;i+1<sols.size();i=i+2){

		 	if (rand01()<=probability[0]){
			cross(*sols[i],*sols[i+1]);
			}
		}

	}

	ostream& operator<< (ostream& os, const Crossover&  cross)
	{
		 os << "Crossover." << " Probability: "
                    << cross.probability[0]
		    << endl;
		 return os;
	}

	void Crossover::RefreshState(const StateCenter& _sc) const
	{
		_sc.set_contents_state_variable("_crossover_probability",(char *)probability,1,sizeof(float));
	}

	void Crossover::UpdateFromState(const StateCenter& _sc)
	{
		 unsigned long nbytes,length;
		 _sc.get_contents_state_variable("_crossover_probability",(char *)probability,nbytes,length);
	}

	void Crossover::setup(char line[MAX_BUFFER])
	{
		int op;
		sscanf(line," %d %f ",&op,&probability[0]);
		assert(probability[0]>=0);
	}

	Crossover::~Crossover()
	{
		delete [] probability;
	}

	//  Mutation: Sub_operator -------------------------------------------------------------


	Mutation::Mutation():Intra_Operator(1)
	{
		probability = new float[2];
	}

	void Mutation::mutate(Solution& sol) const
	{   
		//randomica
		int Swap;
		int Op=rand_int(0,sol.pbm().dimension()-1);
		
		do{
		Swap=rand_int(0,sol.pbm().dimension()-1);
		}while(Swap==Op);
	
		Tupla aux=sol.solucion(Op);
		sol.solucion(Op)=sol.solucion(Swap);
		sol.solucion(Swap)=aux; //cambie Swap por Op
		sol.repair();
	}

	void Mutation::execute(Rarray<Solution*>& sols) const
	{
		for (int i=0;i<sols.size();i++)
			if(rand01() <= probability[1]){
			mutate(*sols[i]);
			}
	}

	ostream& operator<< (ostream& os, const Mutation&  mutation)
	{
		os << "Mutation." << " Probability: " << mutation.probability[0]
		   << " Probability1: " << mutation.probability[1]
		   << endl;
		return os;
	}

	void Mutation::setup(char line[MAX_BUFFER])
	{
		int op;
		sscanf(line," %d %f %f ",&op,&probability[0],&probability[1]);
		assert(probability[0]>=0);
		assert(probability[1]>=0);
	}

	void Mutation::RefreshState(const StateCenter& _sc) const
	{
		_sc.set_contents_state_variable("_mutation_probability",(char *)probability,2,sizeof(probability));
	}

	void Mutation::UpdateFromState(const StateCenter& _sc)
	{
		unsigned long nbytes,length;
		_sc.get_contents_state_variable("_mutation_probability",(char *)probability,nbytes,length);
	}

	Mutation::~Mutation()
	{
		delete [] probability;
	}

// StopCondition_1 -------------------------------------------------------------------------------------

	StopCondition_1::StopCondition_1():StopCondition()
	{}

	bool StopCondition_1::EvaluateCondition(const Problem& pbm,const Solver& solver,const SetUpParams& setup)
	{
		return ((int)solver.best_cost_trial() == pbm.dimension());
	}

	StopCondition_1::~StopCondition_1()
	{}

	//------------------------------------------------------------------------
	// Specific methods ------------------------------------------------------
	//------------------------------------------------------------------------

	bool terminateQ (const Problem& pbm, const Solver& solver,
			 const SetUpParams& setup)
	{
		StopCondition_1 stop;
		return stop.EvaluateCondition(pbm,solver,setup);
	}
}
#endif

