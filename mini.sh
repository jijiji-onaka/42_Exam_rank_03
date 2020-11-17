mkdir result2
gcc your_mini_code.c -o yours2 -Wall -Werror -Wextra -lm
./utils/our_mini_paint mini_operation_file/error1 > result2/mine1
./utils/our_mini_paint mini_operation_file/error2 > result2/mine2
./utils/our_mini_paint mini_operation_file/error3 > result2/mine3
./utils/our_mini_paint mini_operation_file/error4 > result2/mine4
./utils/our_mini_paint mini_operation_file/error5 > result2/mine5
./utils/our_mini_paint mini_operation_file/error6 > result2/mine6
./utils/our_mini_paint mini_operation_file/op1 > result2/mine7
./utils/our_mini_paint mini_operation_file/op2 > result2/mine8
./utils/our_mini_paint mini_operation_file/op3 > result2/mine9

./yours2 mini_operation_file/error1 > result2/yours1
./yours2 mini_operation_file/error2 > result2/yours2
./yours2 mini_operation_file/error3 > result2/yours3
./yours2 mini_operation_file/error4 > result2/yours4
./yours2 mini_operation_file/error5 > result2/yours5
./yours2 mini_operation_file/error6 > result2/yours6
./yours2 mini_operation_file/op1 > result2/yours7
./yours2 mini_operation_file/op2 > result2/yours8
./yours2 mini_operation_file/op3 > result2/yours9

COUNT=0
bash utils/diff_check.sh result2/mine1 result2/yours1 mini_operation_file/error1
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash utils/diff_check.sh result2/mine2 result2/yours2 mini_operation_file/error2
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash utils/diff_check.sh result2/mine3 result2/yours3 mini_operation_file/error3
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash utils/diff_check.sh result2/mine4 result2/yours4 mini_operation_file/error4
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash utils/diff_check.sh result2/mine5 result2/yours5 mini_operation_file/error5
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash utils/diff_check.sh result2/mine6 result2/yours6 mini_operation_file/error6
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash utils/diff_check.sh result2/mine7 result2/yours7 mini_operation_file/op1
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash utils/diff_check.sh result2/mine8 result2/yours8 mini_operation_file/op2
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash utils/diff_check.sh result2/mine9 result2/yours9 mini_operation_file/op3
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

if test $COUNT -eq 9; then
    echo -e "\n\033[0;32m$USER さん！\nちゃんと書けています！完璧！！！\nExamもこの調子で頑張りましょう！！！\033[0;39m\n"
else
    echo -e  "\n\033[0;31m上にdiffがあるので書き直してみてください！！\033[0;m\n"
fi

rm -rf result2
rm -f yours2