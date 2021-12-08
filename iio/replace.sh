FILES=$(ls ../include/no_os)

for FILE in $FILES
do
#	find . -type f -exec sed -i "s/\$(INCLUDE)\/noos_$FILE/\$(INCLUDE)\/no_os_$FILE/g" {} +
	find . -type f -exec sed -i "s/#include \"no_os_$FILE\"/#include \"no_os\/$FILE\"/g" {} +
	
#	if [ "$(echo $FILE | cut -d"_" -f1)" != "no_os" ]
#	then
#		mv include/$FILE include/noos_$FILE
#	fi

done

