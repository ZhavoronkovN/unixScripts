. assert.sh

mkdir /tmp/test3
touch /tmp/test3/1.test
touch /tmp/test3/2.test
touch /tmp/test3/3.test
touch /tmp/test3/4.test
touch /tmp/test3/5.test
touch /tmp/test3/6.test
touch /tmp/test3/7.test
touch /tmp/test3/8.test
touch /tmp/test3/9.test
touch /tmp/test3/0.test
file='python3 Task3_unix.py'
assert_raises "$file" 2
assert_raises "$file test test" 2
assert_raises "$file -h"
let "num = $(find /tmp/test3 -not -path '*/\.*' -type f -mmin -60| wc -l) + 13"
assert "$file /tmp/test3 | wc -l" "$num"
assert "ls /tmp/test3/backup | wc -l" "10"
assert_end test3
for i in /tmp/test3/backup/*
do
	rm $i
done
rmdir /tmp/test3/backup
for i in /tmp/test3/*
do
	rm $i
done
rmdir /tmp/test3