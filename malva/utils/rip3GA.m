function Nvar= rip3GA(path_,path2_)
#path string con direccion a archivos de salida
	dire= ls(path_);
	Time= 1.0e+6;

	outfile = '../../latex/tablas/Todos_casos.tex';
	Orden_=cellstr(dire);
	Orden_=sort(Orden_);

	Matrix=[];

	Prob=dlmread('./Cases.txt',"\t");
	Probc=Prob(:,2);
	Probm=Prob(:,3);
	NroInd=Prob(:,4);

	for i= 1:rows(dire)
	path= strcat(path_,"/",char(Orden_(i)));
	#path2= strcat(path2_,"/",char(Orden_(i)))
	files= ls(path);
	Orden=cellstr(files);
	Orden=sort(Orden);
	Nvar= [];#cellstr(Head);

	for k= 1:rows(files)
		path_file=strcat(path,"/",char(Orden(k)));
		#path_file2=strcat(path2,"/",char(Orden(k)));

		Data=dlmread(path_file, "\t");
		#Data2=dlmread(path_file2, "\t");
		Fitness_min= min(Data(:,1));
		Fitness_avg= mean(Data(:,1));
		Time_exec_avg= mean(Data(:,3))/Time;
		Desv_std= std(Data(:,1),1); #sprintf("%5.4f", std(Data(:,1),1))
		DA=Dagostino(Data(:,1)'); ##sprintf("%5.4f", Dagostino(Data(:,1)'))
##data2
		#Fitness_min2= min(Data2(:,1));
		#Fitness_avg2= mean(Data2(:,1));
		#Time_exec_avg2= mean(Data2(:,3))/Time;
		#Desv_std2= std(Data2(:,1),1); #sprintf("%5.4f", std(Data(:,1),1))
		#DA2=Dagostino(Data2(:,1)'); ##sprintf("%5.4f", Dagostino(Data(:,1)'))

		#Aux=[Fitness_min,Fitness_min2,Fitness_avg,Fitness_avg2,Desv_std,Desv_std2,Time_exec_avg,Time_exec_avg2,DA,DA2];
		Aux=[Fitness_min,Fitness_avg,Desv_std,Time_exec_avg,DA];		
		Nvar=[Nvar;Aux];
		
	endfor
	Aux= [i,Probc(i),Probm(i),NroInd(i),mean(Nvar(:,2)),mean(Nvar(:,4))];
	Matrix=[Matrix;Aux];
Nvar
	endfor

	dlmwrite (outfile, Matrix, "delimiter", " & ", "newline", "\\\\tabularnewline\\n");

endfunction
