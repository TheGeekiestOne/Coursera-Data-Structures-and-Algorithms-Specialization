#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*********************************
******                      ******
***        Ayran Olckers       ***
**                              **
**            07/2019           **
******                      ******
**********************************/


using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
private:
    int bucket_count;
    vector<string> elems;
    vector<vector<string>> Hashmap = vector<vector<string>>(bucket_count);
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }
    
public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}
    
    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }
    
    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }
    
    void processQuery(const Query& query) {
        if (query.type == "check") {
            if (Hashmap[query.ind].size() != 0) {
                for (int i = static_cast<int>(Hashmap[query.ind].size()) - 1; i >= 0; --i)
                    cout << Hashmap[query.ind][i] << " ";
            }
            cout << "\n";
        } else {
            size_t ind = hash_func(query.s);
            vector<string>::iterator it = std::find(Hashmap[ind].begin(), Hashmap[ind].end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != Hashmap[ind].end());
            else if (query.type == "add") {
                if (it == Hashmap[ind].end())
                    Hashmap[ind].push_back(query.s);
            } else if (query.type == "del") {
                if (it != Hashmap[ind].end())
                    Hashmap[ind].erase(it);
            }
        }
    }
    
    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}