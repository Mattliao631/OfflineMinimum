#include "Heap.hpp"
#include "DisjointSets.hpp"
#include <cstdlib>
#include <ctime>

#define N 3
string seqs[] = {
    "4,8,E,3,E,9,2,6,E,E,E,1,7,E,5",
    "4,8,11,E,3,9,2,6,E,E,13,12,E,1,7,15,E,14,5,E,10,E,E,16",
    "6,E,8,E,15,14,12,E,E,1,2,E,3,E,E,4,5,7,E,9,10,11,E,13",
};
vector<vector<int> > offlineArr;
vector<vector<int> > OnlineMinimum;
vector<vector<int> > OfflineMinimum;

void Test();
void Output();

int main() {
    srand(time(0));
    Test();
    Output();
}

void Test() {
    OnlineMinimum.resize(N);
    OfflineMinimum.resize(N);
    offlineArr.resize(N);

    
    for (int t = 0; t < N; t++) {
        Heap h = Heap();
        string s = seqs[t];
        int n = s.size();
        int x = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == ',' && x != 0) {
                h.MinPush(x);
                offlineArr[t].push_back(x);
                x = 0;
            }
            else if (s[i] == 'E') {
                OnlineMinimum[t].push_back(h.ExtractMin());
                offlineArr[t].push_back(-1);
            }
            else if (s[i] != ',') {
                x = x * 10 + (s[i] - '0');
            }
        }
        if (x != 0) {
            h.MinPush(x);
            offlineArr[t].push_back(x);
        }
    }
    
    for (int t = 0; t < N; t++) {
        DisjointSets ds = DisjointSets();
        int n = offlineArr[t].size();
        unordered_map<int, int> map;
        int count = 0;
        for (int i = 0; i < n; i++) {

            if (offlineArr[t][i] == -1) {
                ds.MakeSet(count);
                count++;
            } else {
                map[offlineArr[t][i]] = count;
            }
        }
        ds.MakeSet(count);
        n = map.size();
        OfflineMinimum[t].resize(ds.Size() - 1);

        for (int i = 1; i <= n; i++) {
            int j = map[i];
            int u = ds.FindSet(j);
            if (u != count) {
                OfflineMinimum[t][u] = i;
                ds.Union(u + 1, u);
                if (ds.Size() == 1) {
                    break;
                }
            }
        }
    }
}

void Output() {
    for (int i = 0; i < N; i++) {
        cout << "OnlineMinimum[" << i << "]: " << endl;
        for (int j = 0; j < OnlineMinimum[i].size(); j++) {
            cout << OnlineMinimum[i][j] << " ";
        }
        cout << endl;

        cout << "OfflineMinimum[" << i << "]: " << endl;
        for (int j = 0; j < OfflineMinimum[i].size(); j++) {
            cout << OfflineMinimum[i][j] << " ";
        }
        cout << endl;
    }
}