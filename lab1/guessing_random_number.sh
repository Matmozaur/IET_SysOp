x=$(($1 + RANDOM % $(($2-$1))))
echo "guess number"
read n
while [ $n -ne $x ] ; do
	if [ $n -le $x ]
	then
		echo "wrong answer, number is too small, guess again"
		read n
	else 
		echo "wrong answer, number is too big, guess again"
		read n
	fi	
done
echo "correct!"
