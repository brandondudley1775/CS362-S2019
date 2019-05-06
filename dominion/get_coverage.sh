make cardtest$1
./cardtest$1
lcov -c -d . -o coverage.info
echo cardtest$1 > coverage.txt
genhtml coverage.info --output-directory out >> coverage.txt
echo "-----------------------------------------------------" >> coverage.txt
