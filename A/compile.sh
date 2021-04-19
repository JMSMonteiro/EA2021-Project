echo '>> Starting Compilation <<'
g++ -o "$1.out" -std=c++17 -Wall -Wextra -O2 "$1.cpp" -lm
echo '>> Ended Compilation <<'
