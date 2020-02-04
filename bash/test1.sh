. assert.sh

mkdir test1
cd test1
touch 1.no_del
touch 1.delete
touch 1.also_no_del
cd ..
file='./task1.sh'
assert_raises "$file" 1
assert_raises "$file test test test" 2
assert_raises "$file -h"
assert "ls test1 | wc -l" "3"
assert "$file . delete &&ls test1 | wc -l" "2"
assert_end test1
cd test1
rm 1.no_del
rm 1.also_no_del
cd ..
rmdir test1

