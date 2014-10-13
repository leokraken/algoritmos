function rip(path, algoritmo)
#path string con direccion a archivos de salida
	files= ls(path);
	#Head=["F_{b}";"F_{avg}";"\sigma";"T_{avg}";"DA"];
	Nvar= [];#cellstr(Head);
	Time= 1.0e+6;
	[_,caso,_]=fileparts(path);
	outfile = strcat('../../latex/tablas/tabla',caso,'-',algoritmo,'-fitness.tex');
	outfile2 = strcat('../../latex/tablas/tabla',caso,'-',algoritmo,'-time.tex');
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
		if fid2 == -1; error('Cannot open file: %s', outfile2); end
		fprintf(fid2, '%s &  ', header{:});
		fclose(fid2);

		Data=dlmread(path_file, "\t");
		Fitness_min= min(Data(:,1));
		Fitness_avg= mean(Data(:,1));
		Time_min= min(Data(:,3));
		Time_avg= mean(Data(:,3));


		#print table fitness and times
		Aux = [Data(:,1)', Fitness_min, Fitness_avg]
		dlmwrite (outfile, Aux, "delimiter", " & ", "newline", " \\\\tabularnewline\\n", '-append')
		#print table fitness and times
		Aux2 = [Data(:,3)', Time_min, Time_avg]
		dlmwrite (outfile2, Aux2./Time, "delimiter", " & ", "newline", " \\\\tabularnewline\\n", '-append')
	endfor
	
endfunction
