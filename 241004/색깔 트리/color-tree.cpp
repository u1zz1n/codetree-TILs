#include <iostream>
#include <vector>

using namespace std;

struct info{
    int m_id;
    int p_id;
    int color;
    int max_depth;
    bool exsist;
};

struct checkInfo{
    int currDepth;
    int p_id;
};

int Q, cmd, m_id, p_id, color, max_depth;
vector<info> nodesInfo(100001, {-1, -1, -1, -1, false});
vector<int> childs[100001];
vector<int> existNode;
int root = 100001;

void addNode(){
    cin >> m_id >> p_id >> color >> max_depth;

    if(p_id == -1)
        root = m_id;

    if(p_id != -1 && nodesInfo[p_id].max_depth == 1)
        return;

    info tmp({m_id, p_id, color, max_depth, true});
    nodesInfo[m_id] = tmp;
    if(p_id != -1)
        childs[p_id].push_back(m_id);
    existNode.push_back(m_id);
}

void changeColInSubTree(int curr){
    nodesInfo[curr].color = color;

    for(int i = 0; i < childs[curr].size(); i++){
        changeColInSubTree(childs[curr][i]);    
    }
}

void changeCol(){
    cin >> m_id >> color;
    changeColInSubTree(m_id);
}

void printCol(){
    cin >> m_id;
    cout << nodesInfo[m_id].color << "\n";
}

vector<bool> DP(int curr, vector<int>& dp){

    vector<bool> colVis(6, false);
    colVis[nodesInfo[curr].color] = true;

    for(int i = 0; i < childs[curr].size(); i++){
        vector<bool> tmp = DP(childs[curr][i], dp);
        for(int j = 1; j <= 5; j++){
            if(tmp[j])
                colVis[j] = true;
        }
    }

    for(int j = 1; j <= 5; j++){
        if(colVis[j])
            dp[curr]++;
    }
    return colVis;
}
void printScore(){
    
    vector<int> dp(100001, 0);
    int score = 0;

    if(root == 100001)
    {
        cout << "0\n";
        return;
    }

    DP(root, dp);

    for(int i = 0; i < existNode.size(); i++){
        int idx = existNode[i];
        score += (dp[idx] * dp[idx]);
    }

    cout << score << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> Q;

    while(Q--){
        cin >> cmd;
        
        switch(cmd){
            case 100:
                addNode();
            break;
            case 200:
                changeCol();
            break;
            case 300:
                printCol();
            break;
            case 400:
                printScore();
            break;
        }
    }
    return 0;
}