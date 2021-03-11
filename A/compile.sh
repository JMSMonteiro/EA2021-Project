echo '>> Starting Compilation <<'
g++ -o "$1" -std=c++17 -Wall -Wextra -O2 "$1.cpp" -lm
echo '>> Ended Compilation <<'
