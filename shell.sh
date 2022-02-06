git clone https://github.com/chronikum/printf42_mandatorytester
make
cd printf42_mandatorytester
mv main.c tmp
echo "#include <stdio.h>" >> main.c
cat tmp >> main.c
cp ../*.a .
cp ../ft_printf.h .
gcc -L./ -lftprintf main.c 2> /dev/null
./a.out
cd ..
make fclean

echo -e "\033[32;1m"ft_printf_tester"\033[m"
git clone https://github.com/paulo-santana/ft_printf_tester
make
cd ft_printf_tester
cp ../*.a .
sh test m
# sh test b1
# sh test b2
cd ..
make fclean

echo -e "\033[32;1m"printfTester"\033[m"
git clone https://github.com/Tripouille/printfTester
cd printfTester
make m
# make b
# make a
cd ..
make fclean


#
# --------------- OLD VERSION ---------------
#


# echo -e "\033[32;1m"pft"\033[m"
# git clone https://github.com/gavinfielder/pft.git
# cd pft
# sed -i "" 's/IGNORE_RETURN_VALUE=0/IGNORE_RETURN_VALUE=1/' options-config.ini
# make
# ./test
# cd ..
# make fclean

# # this test have dependancy on pft
# echo -e "\033[32;1m"PFT_2019"\033[m"
# cd pft
# git clone https://github.com/cclaude42/PFT_2019.git
# rm unit_tests.c options-config.ini
# cp PFT_2019/unit_tests.c .
# cp PFT_2019/options-config.ini .
# rm -rf PFT_2019
# make re
# ./test
# cd ..
# make fclean

# # this test have dependancy on pft
# echo -e "\033[32;1m"PFT_EXAM"\033[m"
# cd pft
# git clone https://github.com/cclaude42/PFT_EXAM.git
# rm unit_tests.c options-config.ini
# cp PFT_EXAM/unit_tests.c .
# cp PFT_EXAM/options-config.ini .
# rm -rf PFT_EXAM
# make re
# ./test
# cd ..
# make fclean

# echo -e "\033[32;1m"42TESTERS-PRINTF"\033[m"
# git clone https://github.com/Mazoise/42TESTERS-PRINTF.git
# cd 42TESTERS-PRINTF
# bash runtest.sh
# cd ..

# echo -e "\033[32;1m"PRINTF_TESTER"\033[m"
# git clone https://github.com/Kwevan/PRINTF_TESTER.git
# cd PRINTF_TESTER
# bash run.sh
# cd ..

# echo -e "\033[32;1m"printf_lover_v2"\033[m"
# git clone https://github.com/charMstr/printf_lover_v2.git
# cd printf_lover_v2
# ./printf_lover.sh
# cd ..
# make fclean

# echo -e "\033[32;1m"printf-tester"\033[m"
# git clone https://github.com/AntoineBourin/printf-tester.git
# make
# cd printf-tester
# cp ../*.a .
# cp ../ft_printf.h .
# echo "\033[32;1m"YOU SHOULD FIX THIS IN printf-test/test.sh line number 6~8"\033[m
# 	cp newmain.c ft.c
# 	sed 's/printf/ft_printf/g' ft.c > ft_printf.c
# 	rm ft.c
# TO
# 	cp newmain.c ft.c
# 	sed 's/printf/ft_printf/g' ft.c > tmp.c
# 	sed 's/\#include <stdio.h>/\#include \"ft_printf.h\"/g' tmp.c > ft_printf.c
# 	rm ft.c tmp.c
# "
# read $a
# zsh test.sh
# cd ..
# make fclean

echo -e "\033[32;1m"FINISHED enter will remove testers and diff results, ctrl + c to check remain"\033[m"
read $a
# new version
rm -rf printf42_mandatorytester ft_printf_tester printfTester
# old version
rm -rf pft 42TESTERS-PRINTF PRINTF_TESTER printf_lover_v2 printf-tester
