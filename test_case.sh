#!/bin/bash
if [ $# -ne 1 ];
then
	echo "Usage test_case.sh <#>"
	exit 1
fi

./../rsh < ../test_cases/test$1.in 2>/dev/null > ../mytest$1.out
diff ../mytest$1.out ../test_cases/test$1.out
