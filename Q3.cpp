#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

class UnionFind
{
public:
    vector<int> parent, rank;

    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unionSet(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
{
    unordered_map<string, int> emailToIndex;   // Maps email to account index
    unordered_map<string, string> emailToName; // Maps email to name
    int n = accounts.size();
    UnionFind uf(n);

    // Step 1: Map emails to indices and union accounts with common emails
    for (int i = 0; i < n; ++i)
    {
        string name = accounts[i][0];
        for (int j = 1; j < accounts[i].size(); ++j)
        {
            string email = accounts[i][j];
            emailToName[email] = name;
            if (emailToIndex.count(email))
            {
                uf.unionSet(i, emailToIndex[email]);
            }
            else
            {
                emailToIndex[email] = i;
            }
        }
    }

    // Step 2: Group emails by their root index
    unordered_map<int, vector<string>> indexToEmails;
    for (const auto &pair : emailToIndex)
    {
        string email = pair.first;
        int idx = pair.second;
        int root = uf.find(idx);
        indexToEmails[root].push_back(email);
    }

    // Step 3: Build the result
    vector<vector<string>> mergedAccounts;
    for (const auto &pair : indexToEmails)
    {
        int index = pair.first;
        vector<string> emails = pair.second;
        sort(emails.begin(), emails.end()); // Sort emails
        vector<string> account;
        account.push_back(emailToName[emails[0]]); // Add the name
        account.insert(account.end(), emails.begin(), emails.end());
        mergedAccounts.push_back(account);
    }

    return mergedAccounts;
}

int main()
{
    // Example usage
    vector<vector<string>> accounts = {
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"John", "johnnybravo@mail.com"},
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"Mary", "mary@mail.com"}};

    vector<vector<string>> result = accountsMerge(accounts);
    for (const auto &account : result)
    {
        for (const string &field : account)
        {
            cout << field << " ";
        }
        cout << endl;
    }

    return 0;
}
