FILES=$(ls ../include)

for FILE in $FILES
do
	find . -type f -exec sed -i "s/\$(INCLUDE)\/$FILE/\$(INCLUDE)\/no_os_$FILE/g" {} +
	find . -type f -exec sed -i "s/#include \"$FILE\"/#include \"no_os_$FILE\"/g" {} +
	
#	if [ "$(echo $FILE | cut -d"_" -f1)" != "no_os" ]
#	then
#		mv include/$FILE include/noos_$FILE
#	fi

done

