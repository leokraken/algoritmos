function rip(path, algoritmo)
#path string con direccion a archivos de salida
	files= ls(path);
	#Head=["F_{b}";"F_{avg}";"\sigma";"T_{avg}";"DA"];
	Nvar= [];#cellstr(Head);
	Time= 1.0e+6;
	[_,caso,_]=fileparts(path);
	outfile = strcat('../../latex/tablas/tabla',caso,'-',algoritmo,'.tex');
	outfile2 = strcat('../../latex/tablas/tabla',caso,'-',algoritmo,'time-fitness.tex');
	Orden=cellstr(files);
	Orden=sort(Orden);

	Prob=dlmread('./BestFitness.txt',"\t");
	Fitness=Prob(:,3);

	for i= 1:rows(files)
		path_file=strcat(path,"/",char(Orden(i)));
		##ENCABEZADO
		[_,name,_]=fileparts(path_file);
		header={name};
		fid = fopen(outfile, 'a');
		if fid == -1; error('Cannot open file: %s', outfile); end
		fprintf(fid, '%s &  ', header{:});
		fclose(fid);

		fid2 = fopen(outfile2, 'a');
		if fid2 == -1; error('Cannot open file: %s', outfile); end
		fprintf(fid, '%s &  ', header{:});
		fclose(fid);

		Data=dlmread(path_file, "\t");
		Fitness_min= min(Data(:,1));
		Fitness_avg= mean(Data(:,1));
		Time_exec_avg= mean(Data(:,3))/Time;
		Desv_std= std(Data(:,1),1); #sprintf("%5.4f", std(Data(:,1),1))
		DA=Dagostino(Data(:,1)'); ##sprintf("%5.4f", Dagostino(Data(:,1)'))
		if (DA>=0.2662 && DA<=0.2866) 
			Normal=1;
		else
			Normal=0;
		endif
		if (Desv_std==0) 
			Normal=1;
		endif
		if (Desv_std==0)
			Aux=[Fitness(i), Fitness_min,Fitness_avg,Desv_std,Time_exec_avg];
		else
			Aux=[Fitness(i), Fitness_min,Fitness_avg,Desv_std,Time_exec_avg,DA];
		endif
		#Nvar=[Nvar;Aux];
		if(Normal==1)
		if (Desv_std==0)
			dlmwrite (outfile, Aux, "delimiter", " & ", "newline", "& * &$ Si $ \\\\tabularnewline\\n", '-append')
		else
			dlmwrite (outfile, Aux, "delimiter", " & ", "newline", "&$ Si $ \\\\tabularnewline\\n", '-append')
		endif
		else
		dlmwrite (outfile, Aux, "delimiter", " & ", "newline", "&$ No $ \\\\tabularnewline\\n", '-append')
		endif

		#print table fitness and times
				
	endfor
	
endfunction
