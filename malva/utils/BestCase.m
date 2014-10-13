function Nvar= BestCase(path, algoritmo)
#path string con direccion a archivos de salida
	files= ls(path);
	Nvar= [];
	Time= 1.0e+6;
	#[_,caso,_]=fileparts(path);
	outfile = strcat('../../latex/tablas/tabla5000G-',algoritmo,'.tex');

	Prob=dlmread('./BestFitness.txt',"\t");
	Fitness=Prob(:,3);


	Orden=cellstr(files);
	Orden=sort(Orden);
	for i= 1:rows(files)
		path_file=strcat(path,"/",char(Orden(i)));
		##ENCABEZADO
		[_,name,_]=fileparts(path_file);
		header={name};
		fid = fopen(outfile, 'a');
		if fid == -1; error('Cannot open file: %s', outfile); end
		fprintf(fid, '%s &  ', header{:});
		fclose(fid);

		Data=dlmread(path_file, "\t");
		Fitness_min= min(Data(:,1));
		Fitness_avg= mean(Data(:,1));
		Time_exec_avg= mean(Data(:,3))/Time;

		Aux=[Fitness(i), Fitness_min, Fitness_avg, Time_exec_avg];
		Nvar=[Nvar;Aux];
		dlmwrite (outfile, Aux, "delimiter", " & ", "newline", " \\\\tabularnewline\\n", '-append')			
	endfor
endfunction
