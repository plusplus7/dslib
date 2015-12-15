for testfile in `ls *_test.c`
do
    gcc -o "$testfile".test $testfile
    if [ $? -ne 0 ]; then
        echo "* ""Got some trouble with compiling ""$testfile"" *"
        exit 1
    fi
done
for testfile in `ls *_test.cpp`
do
    g++ -o "$testfile".test $testfile
    if [ $? -ne 0 ]; then
        echo "* ""Got some trouble with compiling ""$testfile"" *"
        exit 1
    fi
done
for testfile in `ls *.test`
do
    ./"$testfile"
    if [ $? -ne 0 ]; then
        echo "* ""Got some trouble with running ""$testfile"" *"
        exit 1
    fi
    rm "$testfile"
done

echo "* All test cases \033[32mPASSED\033[00m *"
exit 0
