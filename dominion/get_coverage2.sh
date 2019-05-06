make unittest$1
./unittest$1
lcov -c -d . -o coverage.info
genhtml coverage.info --output-directory out
