function rip2(path,path2, algoritmo)
#path string con direccion a archivos de salida
	files= ls(path);
	#Head=["F_{b}";"F_{avg}";"\sigma";"T_{avg}";"DA"];
	Nvar= [];#cellstr(Head);
	Time= 1.0e+6;
	[_,caso,_]=fileparts(path);
	outfile = strcat('../../latex/tablas/tabla',caso,'-',algoritmo,'.tex');
	outfileStat = strcat('../../latex/tablas/tabla',caso,'t_u-',algoritmo,'.tex');
	Orden=cellstr(files);
	Orden=sort(Orden);
	for i= 1:rows(files)
		path_file=strcat(path,"/",char(Orden(i)));
		path_file2=strcat(path2,"/",char(Orden(i)));
		##ENCABEZADO
		[_,name,_]=fileparts(path_file);
		header={name};
		fid = fopen(outfile, 'a');
		if fid == -1; error('Cannot open file: %s', outfile); end
		fprintf(fid, '%s &  ', header{:});
		fclose(fid);

		#para archivo estadistico
		fid = fopen(outfileStat, 'a');
		if fid == -1; error('Cannot open file: %s', outfileStat); end
		fprintf(fid, '%s &  ', header{:});
		fclose(fid);

		Data=dlmread(path_file, "\t");
		Data2=dlmread(path_file2, "\t");
		Fitness_min= min(Data(:,1));
		Fitness_avg= mean(Data(:,1));
		Time_exec_avg= mean(Data(:,3))/Time;
		Desv_std= std(Data(:,1),1); #sprintf("%5.4f", std(Data(:,1),1))
		DA=Dagostino(Data(:,1)'); ##sprintf("%5.4f", Dagostino(Data(:,1)'))
##data2
		Fitness_min2= min(Data2(:,1));
		Fitness_avg2= mean(Data2(:,1));
		Time_exec_avg2= mean(Data2(:,3))/Time;
		Desv_std2= std(Data2(:,1),1); #sprintf("%5.4f", std(Data(:,1),1))
		DA2=Dagostino(Data2(:,1)'); ##sprintf("%5.4f", Dagostino(Data(:,1)'))
		if (DA>=0.2662 && DA<=0.2866) 
			Normal=1;
		else
			Normal=0;
		endif
		if (Desv_std==0) 
			Normal=1;
		endif
		if (DA2>=0.2662 && DA2<=0.2866) 
			Normal2=1;
		else
			Normal2=0;
		endif
		if (Desv_std2==0) 
			Normal2=1;
		endif

		if(Normal==1 && Normal2==1)
		#perform t student test  u1-u2>0, if p>alfa -> u1>u2
		[pvalue,_,_]= t_test_2(Data(:,1),Data2(:,1),"<");
		#[pvalue2,_,_]= t_test_2(Data2(:,1),Data(:,1),"<");
		if(Desv_std==0 && Desv_std2==0)
		dlmwrite (outfileStat, 0.5, "delimiter", " & ", "newline", " & $t\\\\_test$ \\\\tabularnewline\\n", '-append')
		else
		dlmwrite (outfileStat, pvalue, "delimiter", " & ", "newline", " & $t\\\\_test$ \\\\tabularnewline\\n", '-append')
		endif

		else
		[pvalue,_]= u_test (Data(:,1),Data2(:,1),">")
		#[pvalue2,_]= u_test (Data2(:,1),Data(:,1),"<")
		dlmwrite (outfileStat, pvalue, "delimiter", " & ", "newline", " & $u\\\\_test$ \\\\tabularnewline\\n", '-append')
		endif



		Aux=[Fitness_min,Fitness_min2,Fitness_avg,Fitness_avg2,Desv_std,Desv_std2,Time_exec_avg,Time_exec_avg2];
		Nvar=[Nvar;Aux];
		dlmwrite (outfile, Aux, "delimiter", " & ", "newline", "\\\\tabularnewline\\n", '-append')
		%if(Normal==1 && Normal2==1)
		%dlmwrite (outfile, Aux, "delimiter", " & ", "newline", "&$ Si $ & $ Si $ \\\\tabularnewline\\n", '-append')
		%elseif(Normal==1 && Normal2==0)
		%dlmwrite (outfile, Aux, "delimiter", " & ", "newline", "&$ Si $ & $ No $ \\\\tabularnewline\\n", '-append')
		%elseif(Normal==0 && Normal2==1)
		%dlmwrite (outfile, Aux, "delimiter", " & ", "newline", "&$ No $ & $ Si $ \\\\tabularnewline\\n", '-append')
		%else
		%dlmwrite (outfile, Aux, "delimiter", " & ", "newline", "&$ No $ & $ No $ \\\\tabularnewline\\n", '-append')
		%endif				
	endfor
endfunction
