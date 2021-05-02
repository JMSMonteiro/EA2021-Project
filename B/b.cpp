#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#define MOD 1000000007

using uint = unsigned int;
uint arches = 0;
std::vector<uint> table;

constexpr int modAbs(const int &a) { return ((a % MOD) + MOD) % MOD; }
constexpr int modAdd(const int &a, const int &b) {
  return (modAbs(a) + modAbs(b)) % MOD;
}
constexpr int modSub(const int &a, const int &b) { return modAdd(a, -b); }
constexpr int modMul(const int &a, const int &b) {
  long long int la = modAbs(a);
  long long int lb = modAbs(b);
  long long int lm = MOD;
  return (int)((la * lb) % lm);
}

void printTable(int blockNumber, int maxHeight) {
  for (int j = 0; j < maxHeight; ++j) {
    for (int i = 0; i < blockNumber; ++i) {
      std::cout << table[i + j * blockNumber] << "\t";
    }
    std::cout << "\n";
  }
}

void buildAscending(int blockNumber, int blockHeight, int maxHeight) {
  int currentLevelElements = 1;
  int index = 0;
  int currentIndex = 0;
  int val = 0;
  int diff = 0;
  int midValue = 0;
  int startValue = 1;

  for (int currentHeight = 1; currentHeight < maxHeight; ++currentHeight) {
    startValue = (currentHeight) / (blockHeight - 1);
    if (startValue >= blockNumber) {
      break;
    }
    for (int currentPiece = startValue; currentPiece < blockNumber - 1;
         ++currentPiece) {
      if (currentHeight + blockHeight > maxHeight) {
        return;
      }
      currentLevelElements = 1 + (currentPiece * (blockHeight - 2));
      if (currentHeight >= currentPiece + currentLevelElements) {
        continue;
      }

      index = currentPiece + (currentHeight * blockNumber);
      val = 0;

      midValue = currentPiece + (currentLevelElements - 1 / 2);

      if (currentHeight > midValue) {
        diff = currentHeight - midValue;
        currentIndex = currentPiece + ((midValue - diff) * blockNumber);
        table[index] = table[currentIndex];
      } else {
        for (int i = 1; i < blockHeight; ++i) {
          currentIndex = (index - (blockNumber * i)) - 1;
          if (currentIndex >= 0) {
            val = modAdd(val, table[currentIndex]);
          }
        }
        table[index] = val;
      }
    }
  }
}

void makeArches(int blockNumber, int blockHeight, int maxHeight) {
  int retro = 0;
  uint leftmost = 0;
  uint leftmost1 = 0;
  uint line = 1;
  uint col = 0;
  uint first = 0;
  uint jfirst = 0;

  for (int i = blockNumber + 1; i < maxHeight * blockNumber; ++i) {
    if (leftmost == 0) {
      first = i;
    }
    leftmost++;
    leftmost1 = 0;
    retro = ((i / blockNumber) - (blockHeight - 1)) * blockNumber;

    if (retro <= 0) {
      retro = 0;
    } else {
      retro += 1;
    }

    if (table[i]) {

      for (int j = retro; j / blockNumber < i / blockNumber; ++j) {
        if (table[j] == 0) {
          continue;
        }
        if (leftmost1 == 0) {
          jfirst = j;
        }
        leftmost1++;
        if ((j % blockNumber) + (i % blockNumber) >= blockNumber - 1) {
          continue;
        }
        if (table[j]) {
          arches = modAdd(arches, modMul(table[i], table[j]));
        }
        if (table[j + 1] == 0) {
          if (table[j + blockNumber - (j - jfirst)] == 0) {
            j = j + blockNumber - (j - jfirst);
          } else {
            j = j + blockNumber - leftmost1;
          }
          leftmost1 = 0;
          if (table[j + 1] == 0 && table[j + 1 + blockNumber] == 0 &&
              (j + 1) % blockNumber == 0) {
            break;
          }
        }
      }
    }

    if (table[i + 1] == 0) {
      if (table[i + blockNumber - (i - first)] == 0) {
        i = i + blockNumber - (i - first);
      } else {
        i = i + blockNumber - leftmost;
      }
      leftmost = 0;
      col = 0;
      line++;
      if (table[i + 1] == 0 && table[i + 1 + blockNumber]) {
        break;
      }
    }
    col++;
  }
}

void calculateArch(int blockNumber, int blockHeight, int maxHeight) {
  // If block height == room height    => Impossible (blocks can't go up)
  // If blockNumber < 3                => Impossible (not enough blocks)
  if (blockHeight >= maxHeight || blockNumber < 3) {
    arches = 0;
    return;
  }
  // If block height == maxHeight - 1, only one unique arch can be created
  else if (blockHeight == (maxHeight - 1) && blockNumber >= 3) {
    arches = 1;
    return;
  }
  table[0] = 1;
  buildAscending(blockNumber, blockHeight, maxHeight);
  makeArches(blockNumber, blockHeight, maxHeight);
}

int main() {
  // Fast(er) C++ I/O | https://git.dei.uc.pt/snippets/25
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  // End of Fast(er) I/O

  int testCases, blockNumber, blockHeight, maxHeight;

  std::cin >> testCases;

  for (int i = 0; i < testCases; ++i) {
    arches = 0;
    table.clear();
    std::cin >> blockNumber >> blockHeight >> maxHeight;
    table.resize((blockNumber) * (maxHeight), 0);
    calculateArch(blockNumber, blockHeight, maxHeight);
    std::cout << arches << "\n";
  }
  return 0;
}