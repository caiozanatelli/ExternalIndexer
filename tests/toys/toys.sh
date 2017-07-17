PROG='../../bin/ExternalIndexer'

for i in $(seq 0 9); do
	echo "[TOY $i]"
	$PROG < 'input/toy_'$i'_input';
	diff 'indices/toy_'$i'/index_esperado' 'indices/toy_'$i'/index'
done
