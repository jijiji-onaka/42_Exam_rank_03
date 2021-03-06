mkdir result
gcc your_micro_code.c -o yours -Wall -Werror -Wextra -lm
./utils/our_micro_paint micro_operation_file/error1 > result/mine1
./utils/our_micro_paint micro_operation_file/error2 > result/mine2
./utils/our_micro_paint micro_operation_file/error3 > result/mine3
./utils/our_micro_paint micro_operation_file/error4 > result/mine4
./utils/our_micro_paint micro_operation_file/error5 > result/mine5
./utils/our_micro_paint micro_operation_file/error6 > result/mine6
./utils/our_micro_paint micro_operation_file/op1 > result/mine7
./utils/our_micro_paint micro_operation_file/op2 > result/mine8
./utils/our_micro_paint micro_operation_file/op3 > result/mine9

./yours micro_operation_file/error1 > result/yours1
./yours micro_operation_file/error2 > result/yours2
./yours micro_operation_file/error3 > result/yours3
./yours micro_operation_file/error4 > result/yours4
./yours micro_operation_file/error5 > result/yours5
./yours micro_operation_file/error6 > result/yours6
./yours micro_operation_file/op1 > result/yours7
./yours micro_operation_file/op2 > result/yours8
./yours micro_operation_file/op3 > result/yours9


COUNT=0
bash ./utils/diff_check.sh result/mine1 result/yours1 micro_operation_file/error1
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash ./utils/diff_check.sh result/mine2 result/yours2 micro_operation_file/error2
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash ./utils/diff_check.sh result/mine3 result/yours3 micro_operation_file/error3
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash ./utils/diff_check.sh result/mine4 result/yours4 micro_operation_file/error4
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash ./utils/diff_check.sh result/mine5 result/yours5 micro_operation_file/error5
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash ./utils/diff_check.sh result/mine6 result/yours6 micro_operation_file/error6
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash ./utils/diff_check.sh result/mine7 result/yours7 micro_operation_file/op1
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash ./utils/diff_check.sh result/mine8 result/yours8 micro_operation_file/op2
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

bash ./utils/diff_check.sh result/mine9 result/yours9 micro_operation_file/op3
if test $? -eq 1; then
    COUNT=$(( COUNT + 1 ))
fi

if test $COUNT -eq 9; then
        echo -e "[English]\n\n\033[0;32m$USER san!!\nIt's written correctly! Perfect!!!\nLet's keep this up and do well on the Exam!!!!\033[0;39m\n\n\
[한국어]\n\n\033[0;32m$USER san!!\n제대로 작성되어 있습니다! 완벽 해! \nn이것을 유지하고 시험을 잘합시다 !!!!\n\n\033[0;39m\n\
[日本語]\n\n\033[0;32m$USER san！！ちゃんと書けてます！！完璧！！\nExamもこの調子で頑張ってください！！\033[0;39m\n"
else
    echo -e  "[English]\n\n\033[0;31mThere are differences above, so rewrite the code!!!\033[0;m\n\n\
[한국어]\n\n\033[0;31m위의 차이점이 있으므로 코드를 다시 작성하십시오!!!\n\n\033[0;39m\n\
[日本語]\n\n\033[0;31m上にdiffがあるので書き直してみてください！！！\033[0;39m\n"

fi

rm -rf result
rm -f yours