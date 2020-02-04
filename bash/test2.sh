. assert.sh

mkdir test2
cd test2
touch 1.no_del
touch 1.delete
touch 1.also_del
touch 2.delete
touch 2.no_del
cd ..
file='./task2.sh'
assert_raises "$file" 1
assert_raises "$file test test test" 2
assert_raises "$file -h"
assert "ls test2 | wc -l" "5"
assert "$file test2 no_del &&ls test2 | wc -l" "2"
assert_end test2
cd test2
rm 1.no_del
rm 2.no_del
cd ..
rmdir test2
