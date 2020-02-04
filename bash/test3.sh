. assert.sh

file='./task3.sh'
touch ~/1.test
touch ~/2.test
touch ~/3.test
touch ~/4.test
touch ~/5.test
touch ~/6.test
touch ~/7.test
touch ~/8.test
touch ~/9.test
touch ~/0.test
assert_raises "$file test" 1
assert_raises "$file -h"
let "num = $(find ~ -not -path '*/\.*' -type f -mmin -60| wc -l) + 11"
assert "$file | wc -l" "$num"
assert "ls ~/backup | wc -l" "10"
assert_end test3
for i in ~/backup/*
do
	rm $i
done
cd ..
rmdir ~/backup
