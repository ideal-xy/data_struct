#include <string>
#include <vector>


std::vector<int> pos;
std::vector<bool> col,diag1,diag2;
int n;
std::vector<std::vector<std::string>> ans;

void dfs(int row)
{
    if (row == n)
    {
        std::vector<std::string> path;
        for (int i = 0;i < n;i++) path[i][pos[i]] = 'Q';
        ans.push_back(path);
        return;
    }

    for (int c = 0;c < n;c++)
    {
        if (col[c] || diag1[c] || diag2[c]) continue;
        pos[row] = c;
        col[c] = diag1[c] = diag2[c] = true;
        dfs(row + 1);
        col[c] = diag1[c] = diag2[c] = false;
    }
}


int main(int argc,char** argv)
{
    n = std::stoi(argv[1]);
    pos.resize(n);
    col.assign(n, false);
    diag1.assign(2*n - 1, false);
    diag2.assign(2*n - 1, false);

    dfs(0);
}