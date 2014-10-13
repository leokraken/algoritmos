GA_DIR=../rep/GA/res
CHC_DIR=../rep/CHC/res

for dir in $( ls $GA_DIR); do
	#recorro los directorios de los casos
	echo item: $dir
	octave --silent --eval "rip('$GA_DIR/$dir', 'GA')"
	octave --silent --eval "ripfitness('$GA_DIR/$dir', 'GA')"
done

for dir in $( ls $CHC_DIR); do
	echo item: $dir
	octave --silent --eval "rip('$CHC_DIR/$dir', 'CHC')" 
	octave --silent --eval "ripfitness('$CHC_DIR/$dir', 'CHC')" 
done

for dir in $( ls $CHC_DIR); do
	echo item: $dir
	octave --silent --eval "rip2('$GA_DIR/$dir','$CHC_DIR/$dir' , 'GA-CHC')" 
done

	octave --silent --eval "rip3('$GA_DIR','$CHC_DIR')" 
	octave --silent --eval "BestCase('$GA_DIR/28', 'GA')"
	octave --silent --eval "BestCase('$CHC_DIR/28', 'CHC')"
