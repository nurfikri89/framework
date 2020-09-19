filename=example_ttbar_2lep
#
#
#
rm -rf ${filename}
#
#
#
g++ $(root-config --cflags --evelibs) -std=c++17 -O3 -Wall -Wextra -Wpedantic -Werror -Wno-float-equal -Wno-sign-compare -I ../plugins/ -I ../src/ -o ${filename} ${filename}.cc
