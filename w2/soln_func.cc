#include <iostream>
#include <string>
#include <vector>

using namespace std;

int mm_score(string k, string g, int& b, int& w) {
    if (k.length() != g.length()) {
        return 0;
    }

    b = 0, w = 0;

    vector<bool> k_used(k.length(), false);
    vector<bool> g_used(g.length(), false);

    for (size_t i = 0; i < k.length(); i++) {
        if (k[i] == g[i]) {
            b++;
            k_used[i] = true;
            g_used[i] = true;
        }
    }

    for (size_t i = 0; i < k.length(); i++) {
        if (!g_used[i]) {
            for (size_t j = 0; j < k.length(); j++) {
                if (!k_used[j] && g[i] == k[j]) {
                    w++;
                    k_used[j] = true;
                    break;
                }
            }
        }
    }

    return b > 0 || w > 0 ? 1 : 0;
}

// int main() {
//     string k = "abcd";
//     string g = "dcba";
//     int b = 0, w = 0;

//     cout << mm_score(k, g, b, w) << endl;
//     cout << "b: " << b << " w: " << w << endl;

//     return 0;
// }