#ifndef INC_REQ_CHC
#define INC_REQ_CHC
#include "CHC.hh"
#include <math.h>
#include <vector>

skeleton CHC
{

	// Problem ---------------------------------------------------------------

	Problem::Problem ():_cantidad_trabajos(0)
	{	
		_costos= Matriz(0);
		_cantidad_operaciones=NULL;
		_operaciones_fijas= vector<int>(0);
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
		os 	<< endl
			<< endl
			<< "Machines: " 
			<< pbm._cantidad_maquinas
		   	<< endl
			<< "Jobs: "
			<< pbm._cantidad_trabajos
			<< endl;

			for(int j=0; j<pbm._cantidad_trabajos;j++){
				for(int i=0; i<pbm._cantidad_operaciones[j];i++){
					for(int m=0; m<pbm._costos[j][i].size();m++){
					os 	<< get<0>(pbm._costos[j][i][m])
						<< " "
						<< get<1>(pbm._costos[j][i][m])
						<< " ";
					}
				}
			os << endl;
			}

		return os;
	}



	istream& operator>> (istream& is, Problem& pbm) //homogenea
	{ 
		//Fila Inicial
		is >> pbm._cantidad_trabajos;
		is >> pbm._cantidad_maquinas;

		int K= pbm._cantidad_trabajos*pbm._cantidad_maquinas;
		pbm._dimension= K * (K - 1) / 2;
		pbm._cantidad_operaciones= new int[pbm._cantidad_trabajos];
		int it_op=0;
		int *operaciones= new int[K];

		pbm._costos= Matriz(pbm._cantidad_trabajos);

		//Itero sobre trabajos
		for(int i=0; i<pbm._cantidad_trabajos; i++){

			is >> pbm._cantidad_operaciones[i]; //operaciones
			Fila aux(pbm._cantidad_operaciones[i]);
			//Itero sobre cantidad operaciones del trabajo

			for(int j=0; j<pbm._cantidad_operaciones[i]; j++){
				int m;
				is >> m;//maquinas permitidas
				Lista lista(m);//(m);
				operaciones[it_op]=i;
				it_op++;

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

		//operaciones
		it_op=0;
		for(int j=0; j<K; j++){
			for(int i=j+1; i<K; i++){
				if(operaciones[j]==operaciones[i])
					pbm._operaciones_fijas.push_back(it_op);
				it_op++;
			}
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

	//dado un trabajo y una maquina devuelve la operacion que le corresponde
	int Problem::get_operation(const int j, const int m) const
	{
		for(int op=0; op<_cantidad_operaciones[j];op++){
			for(int m_=0; m_<_costos[j][op].size();m_++){
				if(get<0>(_costos[j][op][m_])==m){
				return op;
				}
			}
		}
	}

	vector<int> Problem::get_operaciones_fijas() const
	{
		return _operaciones_fijas;
	}

	Problem::~Problem()
	{ 

	}


	// Solution --------------------------------------------------------------

	Solution::Solution (const Problem& pbm):_pbm(pbm),_var(pbm.dimension())
	{
	}


	const Problem& Solution::pbm() const
	{
		return _pbm;
	}

	Solution::Solution(const Solution& sol):_pbm(sol.pbm())
	{
		*this=sol;
	}


	istream& operator>> (istream& is, Solution& sol)
	{
		for (int i=0;i<sol.pbm().dimension();i++)
			is >> sol._var[i];
		
		return is;
	}

	ostream& operator<< (ostream& os, const Solution& sol)
	{

		int Size = sol._pbm.cantidad_trabajos() * sol._pbm.cantidad_maquinas();
		int * mach_deadline = new int[sol._pbm.cantidad_maquinas()];
		int * job_deadline = new int[sol._pbm.cantidad_trabajos()];
		int * operaciones_count = new int[sol._pbm.cantidad_trabajos()];

		for (int i=0; i<sol._pbm.cantidad_trabajos();i++){
			job_deadline[i]=0;
			operaciones_count[i]=0;
		}
		for (int i=0; i<sol._pbm.cantidad_maquinas();i++){
			mach_deadline[i]=0;
		}


		int * ordenado= sol.get_ordenado();
		for (int i=0; i<Size;i++){
			int job= ordenado[i];
			int m= sol._pbm.get_maquina_index(job,operaciones_count[job],0);
			int costo=sol._pbm.get_costos(job,operaciones_count[job],m);
			int deadline;

			if(job_deadline[job]>mach_deadline[m]){
				deadline=job_deadline[job];
				job_deadline[job]+=costo;
				mach_deadline[m]=job_deadline[job];

			}else{
				deadline=mach_deadline[m];
				mach_deadline[m]+=costo;
				job_deadline[job]=mach_deadline[m];

			}

			os	<<ordenado[i]
				<<" "
				<<operaciones_count[ordenado[i]]
				<<" "
				<<sol._pbm.get_maquina_index(ordenado[i],operaciones_count[ordenado[i]],0)
				<<" "
				<<deadline
				<<endl;

			operaciones_count[job]++;
		}

		//elimino auxiliares
		delete [] job_deadline;
		delete [] mach_deadline;
		delete [] ordenado;
		delete [] operaciones_count;

		return os;
	}

	NetStream& operator << (NetStream& ns, const Solution& sol)
	{
		for (int i=0;i<sol._var.size();i++)
			ns << sol._var[i];
		return ns;
	}


	NetStream& operator >> (NetStream& ns, Solution& sol)
	{
		for (int i=0;i<sol._var.size();i++)
			ns >> sol._var[i];
		return ns;
	}


 	Solution& Solution::operator= (const Solution &sol)
	{
		_var=sol._var;
		return *this;
	}


	bool Solution::operator== (const Solution& sol) const
	{
		if (sol.pbm() != _pbm) return false;
		return true;
	}

	bool Solution::operator!= (const Solution& sol) const
	{
		return !(*this == sol);
	}



	void Solution::initialize()
	{
		for (int i=0;i<_pbm.dimension();i++)
			_var[i]=rand_int(0,1);
	}


	int *Solution::get_ordenado() const
	{
		int Size= _pbm.cantidad_trabajos()*_pbm.cantidad_maquinas();
		int * ordenado= new int[Size];
		int ** matrix = new int *[Size];
		int ** hashed = new int *[Size];
		int *unos = new int[Size];
		bool *visitados = new bool[Size];


		for (int i=0; i<Size;i++){
			matrix[i]= new int[Size];
			hashed[i]= new int[Size];
		}

		//LOCAL HARMONIZATION

		int it=0;

		for(int z=0; z<Size;z++){
			unos[z]=0; //inicializo en 0 vector
			visitados[z]=false;			
		}
		
		for(int j=0; j<Size-1;j++){

			for(int l=j+1; l<Size;l++){
				matrix[j][l]=_var[it];
				matrix[l][j]=1-_var[it];
				//hasheo
				hashed[j][l]=it;
				hashed[l][j]=it; 
				if(_var[it]==1){
				unos[j]+=_var[it];
				}else{
				unos[l]+=1;
				}

				it++;
			}
		}

		//busco reparar
		int max;
		int stack= Size-1;

		while(stack>=0){
			//busco maximo
			int max_val=-1;
		
			for(int j=0; j<Size;j++){
				if(unos[j]>max_val && unos[j]<=stack){
					max=j;
					max_val=unos[j];
				}
			}

			visitados[max]=true;

			if(unos[max]!=stack){ //es menor a stack

				//busco un 0 y lo cambio por 1
				bool find=false;
				int pos=0;
				while(!find){
					if(pos!=max && !visitados[pos] && matrix[max][pos]==0){
						find=true;
					}else{
					pos++;
					}

				}

				//tengo la posicion
				matrix[max][pos]=1;
				matrix[pos][max]=0; //flip
				unos[max]++;
				unos[pos]--;

				if(unos[max]==stack){ //encontre maximo
					stack--;
				}

			}else{
			//quiere decir que ya esta evaluado
			stack--;
			}

		}//while 

		//creo orden
		int op_it=0;
		for(int j=0; j<_pbm.cantidad_trabajos();j++){
			for(int op=0; op<_pbm.cantidad_operaciones()[j]; op++){
				int pos= Size-unos[op_it]-1;
				ordenado[pos]=j;
				op_it++;
			}
		}

		//elimino todo
		for (int i=0; i<Size;i++){
			delete [] matrix[i];
			delete [] hashed[i];
		}

		delete [] matrix;
		delete [] hashed;
		delete [] unos;
		delete [] visitados;

		return ordenado;
	}


	int *Solution::repair()const
	{
		int Size= _pbm.cantidad_trabajos()*_pbm.cantidad_maquinas();
		int * ordenado= new int[Size];
		int ** matrix = new int *[Size];
		int ** hashed = new int *[Size];

		int *unos = new int[Size];
		bool *visitados = new bool[Size];

		for(int i=0; i<_pbm.get_operaciones_fijas().size();i++)
			_var[_pbm.get_operaciones_fijas()[i]]=1;


		for (int i=0; i<Size;i++){
			matrix[i]= new int[Size];
			hashed[i]= new int[Size];
		}

		//LOCAL HARMONIZATION

		int it=0;

		for(int z=0; z<Size;z++){
			unos[z]=0; //inicializo en 0 vector
			visitados[z]=false;			
		}
		
		for(int j=0; j<Size-1;j++){

			for(int l=j+1; l<Size;l++){
				matrix[j][l]=_var[it];
				matrix[l][j]=1-_var[it];
				//hasheo
				hashed[j][l]=it;
				hashed[l][j]=it;
				if(_var[it]==1){
				unos[j]+=_var[it];
				}else{
				unos[l]+=1;
				}
				it++;
			}
		}

		//busco reparar
		int max;
		int stack= Size-1;


		while(stack>=0){

		//busco maximo
		int max_val=-1;
		
		for(int j=0; j<Size;j++){
			if(unos[j]>max_val && unos[j]<=stack){
			max=j;
			max_val=unos[j];
			}
		}

		visitados[max]=true;

		if(unos[max]!=stack){ //es menor a stack
		//busco un 0 y lo cambio por 1
		bool find=false;
		int pos=0;
		while(!find){
			if(pos!=max && !visitados[pos] && matrix[max][pos]==0){
				find=true;
			}else{
			pos++;
			}

		}

		//tengo la posicion
		if(pos>max){
		_var[hashed[max][pos]]=1; //reparo _var
		}else{
		_var[hashed[max][pos]]=0; //reparo _var
		}
		
		matrix[max][pos]=1;
		matrix[pos][max]=0; //flip	
		unos[max]++;
		unos[pos]--;

		if(unos[max]==stack){ //encontre maximo
			stack--;
		}

		}else{//if
		//quiere decir que ya esta evaluado
		stack--;
		}

		}//while

		//creo orden
		int op_it=0;
		for(int j=0; j<_pbm.cantidad_trabajos();j++){
			for(int op=0; op<_pbm.cantidad_operaciones()[j]; op++){
				int pos= Size-unos[op_it]-1;
				ordenado[pos]=j;
				op_it++;
			}
		}

		//elimino todo
		for (int i=0; i<Size;i++){
			delete [] matrix[i];
			delete [] hashed[i];
		}

		delete [] matrix;
		delete [] hashed;
		delete [] unos;
		delete [] visitados;

		return ordenado;
	}


	double Solution::fitness () const
	{
		int * ordenado= repair();
		int fitness= calculate_fitness(ordenado);
		return fitness;
	}



	double Solution::calculate_fitness(int * &ordenado) const
	{
       	double fitness = 0.0;
		int Size = _pbm.cantidad_trabajos() * _pbm.cantidad_maquinas();
		int * mach_deadline = new int[_pbm.cantidad_maquinas()];
		int * job_deadline = new int[_pbm.cantidad_trabajos()];
		int * operaciones_count = new int[_pbm.cantidad_trabajos()];

		for (int i=0; i<_pbm.cantidad_trabajos();i++){
			job_deadline[i]=0;
			operaciones_count[i]=0;
		}
		for (int i=0; i<_pbm.cantidad_maquinas();i++){
			mach_deadline[i]=0;
		}

		for (int i=0; i<Size;i++){
			int job= ordenado[i];
			int m= _pbm.get_maquina_index(job,operaciones_count[job],0);
			int costo=_pbm.get_costos(job,operaciones_count[job],m);
			int deadline;
			if(job_deadline[job]>mach_deadline[m]){
				job_deadline[job]+=costo;
				mach_deadline[m]=job_deadline[job];
				deadline=job_deadline[job];
			}else{
				mach_deadline[m]+=costo;
				job_deadline[job]=mach_deadline[m];
				deadline=mach_deadline[m];
			}
			if(deadline>fitness) fitness=deadline;
			operaciones_count[job]++;

		}

		delete [] job_deadline;
		delete [] mach_deadline;
		delete [] operaciones_count;
		delete [] ordenado;

		return fitness;
	}

	char *Solution::to_String() const
	{
		return (char *)_var.get_first();
	}


	void Solution::to_Solution(char *_string_)
	{
		int *ptr=(int *)_string_;
		for (int i=0;i<_pbm.dimension();i++)
		{
			_var[i]=*ptr;
			ptr++;
		}
	}

	unsigned int Solution::size() const
	{
		return (_pbm.dimension() * sizeof(int));
	}

	int Solution::lengthInBits() const
	{
		return _pbm.dimension();
	}

	void Solution::flip(const int index)
	{
		_var[index] = 1 - _var[index]; 
	}

	bool Solution::equalb(const int index,Solution &s)
	{
		return _var[index] == s._var[index];
	}

	void Solution::swap(const int index, Solution &s)
	{
		int aux = s._var[index];
		s._var[index] = _var[index];
		_var[index] = aux;		
	}

	void Solution::invalid()
	{
		_var[0] = 2;
	}

	int& Solution::var(const int index)
	{
		return _var[index];
	}


	Rarray<int>& Solution::array_var()
	{
		return _var;
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
			   << "\t"<< userstat.result_trials[i].nb_iteration_best_found_trial
			   << "\t"<< userstat.result_trials[i].time_spent_trial
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
		new_stat->trial         				 = solver.current_trial();
		new_stat->nb_evaluation_best_found_trial = solver.evaluations_best_found_in_trial();
		new_stat->nb_iteration_best_found_trial  = solver.iteration_best_found_in_trial();
		new_stat->worst_cost_trial     			 = solver.worst_cost_trial();
		new_stat->best_cost_trial     			 = solver.best_cost_trial();
		new_stat->time_best_found_trial			 = solver.time_best_found_trial();
		new_stat->time_spent_trial 				 = solver.time_spent_trial();

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

	//  User_Operator:Intra_operator ---------------------------------------------------------

	User_Operator::User_Operator(const unsigned int _number_op):Intra_Operator(_number_op)
	{}

	void User_Operator::execute(Rarray<Solution*>& sols) const
	{}

	void User_Operator::setup(char line[MAX_BUFFER])
	{}

	Intra_Operator *User_Operator::create(const unsigned int _number_op)
	{
		return new User_Operator(_number_op);
	}

	ostream& operator<< (ostream& os, const User_Operator&  u_op)
	{
		 os << "User Operator.";
		 return os;
	}

	void User_Operator::RefreshState(const StateCenter& _sc) const
	{}

	void User_Operator::UpdateFromState(const StateCenter& _sc)
	{}

	User_Operator::~User_Operator()
	{}


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

