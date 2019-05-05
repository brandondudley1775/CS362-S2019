make cardtest4
lcov -c -d . -o coverage.info
echo cardtest4 > coverage.txt
genhtml coverage.info --output-directory out >> coverage.txt
echo "-----------------------------------------------------" >> coverage.txt
