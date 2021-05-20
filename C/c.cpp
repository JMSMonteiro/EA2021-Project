#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

int main() {
  // Fast(er) C++ I/O | https://git.dei.uc.pt/snippets/25
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  // End of Fast(er) I/O
  int testCases;
  int pointsOfInterest, connections, questionNumber;
  int startPoint, endPoint, distance;

  std::cin >> testCases;

  for (int i = 0; i < testCases; ++i) {
    std::cin >> pointsOfInterest >> connections >> questionNumber;

    for (int j = 0; j < connections; ++j) {
      std::cin >> startPoint >> endPoint >> distance;
    }
  }

  return 0;
}