for file in $(find $1/* -printf '%Ts\t%p\n' | sort -nr | cut -f2)
do
	if [ -f $file ]
	then
		size=$(stat -c%s "$file")
		if [ $size -gt $2 ]
		then
			echo "$file"
			break
		fi
	fi
done
