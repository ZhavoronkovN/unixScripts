. assert.sh

mkdir /tmp/test2
touch /tmp/test2/1.no_del
touch /tmp/test2/1.delete
touch /tmp/test2/1.also_del
touch /tmp/test2/2.delete
touch /tmp/test2/2.no_del
file='./task2'
assert_raises "$file" 1
assert_raises "$file test test test" 2
assert_raises "$file -h"
assert "ls /tmp/test2 | wc -l" "5"
assert "$file /tmp/test2 .no_del &&ls /tmp/test2 | wc -l" "2"
assert_end test2
rm /tmp/test2/1.no_del
rm /tmp/test2/2.no_del
rmdir /tmp/test2
