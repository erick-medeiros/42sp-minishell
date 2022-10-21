clear
#-----compile

echo
echo "(compile)"
echo
make

#-----norm

echo
echo "(norm)"
echo
norminette src/* include/* | grep Error

#-----leak

echo
echo "(leak)"
echo
cd ./tests/leak
make report
cd ../..

#-----unit

echo
echo "(unit)"
echo
cd ./tests/unit
make
./run_test.out
cd ../..

#------

echo