#include <bits/stdc++.h>
#include <fstream>

using namespace std;

#define TAM_INI_CLAUS 1000
#define TAM_INI_VAR 1000
#define ADD_VAL 100

class TwoSAT {
private:
    int numVars;
    vector<vector<int>> implications, implicationsT; //lista de adjascencia para resolver 2SAT com kosaraju
    vector<bool> visited;
    vector<int> parentComponent;
    stack <int> kosarajuStack;

    vector<int> assignment;
    unordered_map<string, int> varMap; //Hashmap dicionario de variaveis


    void dfs1(int u){
        visited[u] = true;
        for (int x: implications[u]){
            if(!visited[x]) dfs1(x);
        }
        kosarajuStack.push(u);
    }

    void dfs2(int u, int componentIndex) {
        visited[u] = true;
        parentComponent[u] = componentIndex;
        for (int x : implicationsT[u]) {
            if (!visited[x]) {
                dfs2(x, componentIndex);
            }
        }
    }

    //Recebe nome da variavel e retorna seu indice
    int getVarIndex(const string& var){
        //se nao encontrarmos a variavel vamos mapea-la
        if(varMap.find(var) == varMap.end()){
            int index = varMap.size();
            varMap[var] = index;
            return index;
        }

        return varMap[var];
    }

    //dado o indice de uma variavel, retornaremos o indice de sua versao negada
    int getNotVarIndex(int varIndex){
        return varIndex ^ 1;
    }

public:
    // construtor da classe TwoSAT
    // implications tem o dobro de tamanho considerando 
    // que cada variavel tem sua correspondente negada
    TwoSAT(int n) : numVars(n), implications(2 * n), implicationsT(2 * n), visited(2 * n, false) {}

    void addClause(const string& var1, bool reau1, const string& var2, bool reau2){
        int id1 = getVarIndex(var1) * 2 + !reau1;
        int id2 = getVarIndex(var2) * 2 + !reau2;

        implications[getNotVarIndex(id1)].push_back(id2); // !id1 => id2
        implications[getNotVarIndex(id2)].push_back(id1); // !id2 => id1

        //grafo reverso para realizar kosaraju
        implicationsT[id2].push_back(getNotVarIndex(id1));
        implicationsT[id1].push_back(getNotVarIndex(id2));
    }

    bool solve(){
        fill(visited.begin(), visited.end(), false);
        for (int i = 0; i < 2 * numVars; ++i) {
            if (!visited[i]) {
                dfs1(i);
            }
        }

        fill(visited.begin(), visited.end(), false);
        parentComponent.assign(2 * numVars, -1);
        int componentIndex = 0;

        while (!kosarajuStack.empty()) {
            int v = kosarajuStack.top();
            kosarajuStack.pop();
            if (!visited[v]) {
                dfs2(v, componentIndex++);
            }
        }

        assignment.assign(numVars, -1);  // -1 = não atribuído
        for (int i = 0; i < numVars; ++i) {
            if (parentComponent[2 * i] == parentComponent[2 * i + 1]) {
                return false;  // variável e sua negação estão na mesma componente
            }
            assignment[i] = (parentComponent[2 * i] > parentComponent[2 * i + 1]);
        }
        return true;
    }

    vector<int> getAssignment() const {
        return assignment;
    }
};

// Função para gerar uma variável aleatória "x1", "x2", ...
string generateRandomVariable(int n) {
    int varIdx = rand() % n;
    return "x" + to_string(varIdx + 1);
}

// Função para gerar arquivos de entrada e saída
void generateTestCases(int numCases) {
    for (int t = 0; t < numCases; ++t) {
        int n = rand() % (TAM_INI_VAR + t*ADD_VAL) + 1;     // Número de variáveis
        int m = rand() % (TAM_INI_CLAUS + 5*t*ADD_VAL) + 1;     // Número de cláusulas

        TwoSAT solver(n);

        // Arquivo de saída para o caso t
        ofstream outFile("testcase_" + to_string(t + 1) + ".txt");

        outFile << n << " " << m << endl;

        for (int i = 0; i < m; ++i) {
            string var1 = generateRandomVariable(n);
            string var2 = generateRandomVariable(n);
            bool reau1 = rand() % 2;
            bool reau2 = rand() % 2;

            solver.addClause(var1, reau1, var2, reau2);

            outFile << var1 << " " << reau1 << " " << var2 << " " << reau2 << endl;
        }

        bool hasSolution = solver.solve();
        if (hasSolution) {
            outFile << "SIM" << endl;
            auto assignment = solver.getAssignment();
            for (int i = 0; i < n; ++i) {
                outFile << "x" << (i + 1) << "=" << assignment[i] << " ";
            }
            outFile << endl;
        } else {
            outFile << "NÃO" << endl;
        }

        outFile.close();
    }
}

int main() {
    srand(time(0));
    int numCases = 50; // Número de casos de teste que queremos gerar
    generateTestCases(numCases);
    cout << "Casos de teste gerados!" << endl;
    return 0;
}