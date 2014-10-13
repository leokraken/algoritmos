GA_DIR=../rep/GA/res
CHC_DIR=../rep/CHC/res

for dir in $( ls $GA_DIR); do
	#recorro los directorios de los casos
	echo item: $dir
	octave --silent --eval "ripfitness('$GA_DIR/$dir', 'GA')"
done


