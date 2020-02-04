. assert.sh

mkdir test
mkdir test/test1
touch test/test1/1.no_del
touch test/test1/1.delete
touch test/test1/1.also_no_del
file='./task1.exe'
assert_raises "$file" 1
assert_raises "$file test test test" 2
assert_raises "$file -h"
assert "ls test/test1 | wc -l" "3"
$file test .delete
assert "ls test/test1 | wc -l" "2"
assert_end test1
rm test/test1/1.no_del
rm test/test1/1.also_no_del
rmdir test/test1
rmdir test

