clear
#-----compile

echo
echo "(compile)"
echo
make
cd ./tests/unit
make
cd ../leak
make
cd ../..


#-----norm

echo
echo "(norm)"
echo
norminette include/ libft/ src/ | grep Error

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
./run_test.out
cd ../..

#------

echo