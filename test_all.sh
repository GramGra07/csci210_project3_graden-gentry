for (( i=01; i<10; i++ ))
do
	rm -rf *
	cp ../test_cases/* .
	cp ../rsh .
	echo 0$i
	./../test_case.sh 0$i
done
rm -rf *
cp ../test_cases/* .
cp ../rsh .
echo 10
./../test_case.sh 10
