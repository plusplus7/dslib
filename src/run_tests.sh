for testfile in `ls *_test.c`
do
    gcc -o "$testfile".test $testfile
    if [ $? -ne 0 ]; then
        echo "* ""Got some trouble with compiling ""$testfile"" *"
        exit 1
    fi
    ./"$testfile".test
    if [ $? -ne 0 ]; then
        echo "* ""Got some trouble with running ""$testfile"" *"
        exit 1
    fi
    rm "$testfile".test
done
echo "* All test cases \033[32mPASSED\033[00m *"
exit 0
