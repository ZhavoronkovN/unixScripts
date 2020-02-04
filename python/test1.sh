. assert.sh

mkdir /tmp/test1
touch /tmp/test1/1.no_del
touch /tmp/test1/1.delete
touch /tmp/test1/1.also_no_del
file='python3 Task_unix.py'
assert_raises "$file" 2
assert_raises "$file test test test" 2
assert_raises "$file -h"
assert "ls /tmp/test1 | wc -l" "3"
assert "$file /tmp/test1 delete &&ls /tmp/test1 | wc -l" "2"
assert_end test1
rm /tmp/test1/1.no_del
rm /tmp/test1/1.also_no_del
rmdir /tmp/test1

