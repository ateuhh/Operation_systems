#!/bin/bash
for element in $(find -L $1 -mtime +7)
do
	if $(test -h $element && !(test -e $element));
		then echo $element; fi
done