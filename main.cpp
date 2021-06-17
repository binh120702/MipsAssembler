#include <bits/stdc++.h>

using namespace std;
struct  data{
    int lineNum;
    string line[1000];
    void    push(string u){
        line[++lineNum] = u;
    }
};

const long long dataStart = 268500992;
data    code, backUp;
map<string, long long> labelAddress;

void    GetRawInput(){
    freopen("data.asm","r",stdin);
    string s;
    while (getline(cin,s)) code.push(s);
    backUp = code;
}

void    DeleteComment(){
    for(int i = 1; i <= code.lineNum; i++){
        int pos = code.line[i].find('#');
        if (pos!=-1)
            code.line[i].erase(code.line[i].begin()+pos, code.line[i].end());
    }
}

void    RemoveRedundantSpace(){
    for(int i = 1; i <= code.lineNum; i++){
        while ((int)code.line[i].find("  ") != -1)      // xoa space
            code.line[i].erase((int)code.line[i].find("  "), 1);
        if (!code.line[i].empty() && code.line[i][0]==' ')
            code.line[i].erase(code.line[i].begin());
        if (!code.line[i].empty() && code.line[i].back()==' ')
            code.line[i].erase(code.line[i].end()-1);
        while ((int)code.line[i].find(9) != -1)        // xoa tab-character
            code.line[i].erase(code.line[i].find(9), 1);
    }
}

int     getPosition(string s){
    int pos = -1;
    for(int i = 1; i <= code.lineNum; i++)
        if (code.line[i].find(s)==0){
            pos = i; break;
        }
    return pos;
}

void    GetDataSegment(){
    int firstPos = getPosition(".data");
    int secondPos = getPosition(".text");
    if (firstPos == -1) return;
    long long currentAddress = dataStart;
    for(int i = firstPos+1; i < secondPos; i++){
        int pos = code.line[i].find(':');
        if (pos == -1) continue;
        string label = code.line[i].substr(0,pos);
        string type = "";
        long long cntBytes = 0;
        pos++;
        if (code.line[i][pos]==' ') pos++;
        pos++;
        while (code.line[i][pos] <= 'z' && code.line[i][pos] >= 'a')
            type = type + code.line[i][pos++];
        if (code.line[i][pos]==' ') pos++;
        if (type == "ascii" || type == "asciiz"){
            string str = code.line[i].substr(pos+1);
            str.erase(str.end()-1,str.end());
            //cout << label << " ** " << type << ' ' << str <<  '\n';
            int cntEndl = 0;
            for(int j = 0; j < int(str.length())-1; j++)
                if (int(str[j]) == 92 && str[j+1] == 'n') cntEndl++;
            //cout << str.length()-cntEndl;
            cntBytes = str.length()-cntEndl;
            if (type=="asciiz") cntBytes++;
        } else
        if (type == "space") {
            int num = 0;
            while (code.line[i][pos] <= '9' && code.line[i][pos] >= '0'){
                num = num*10 + code.line[i][pos]-'0';
                pos++;
            }
            cntBytes = num;
        } else
        { // half, word, byte,
            int cntColon = 0;
            int cntComma = 0;
            for(int j = pos; j < (int)code.line[i].length(); j++)
                if (code.line[i][j] == ',') cntComma++; else
                if (code.line[i][j] == ':') cntColon++;
            int num = 0;
            if (cntColon){
                while (code.line[i][pos]!=':') pos++;
                pos++;
                while (code.line[i][pos] <= '9' && code.line[i][pos] >= '0'){
                    num = num*10 + code.line[i][pos]-'0';
                    pos++;
                }
            } else num = cntComma + 1;
            if (type == "half") {
                cntBytes = 2*num;
                while (currentAddress%2!=0) currentAddress++;
            } else
            if (type == "word") {
                cntBytes = 4*num;
                while (currentAddress%4!=0) currentAddress++;
            } else cntBytes = num;
        }
        cout << label << " ** " << type << " ** " << currentAddress << '\n';
        currentAddress+= cntBytes;
    }
}

void    GetTextSegment(){
    int pos = getPosition(".text");
    if (pos == -1) pos = 1;
}

void    GetLabelAddress(){
    GetDataSegment();
    GetTextSegment();
}

void    PreProcess(){
    DeleteComment();        // xoa comment
    RemoveRedundantSpace(); // xoa khoang cach thua
    GetLabelAddress();      // tim dia chi cua cac label
}

void    Process(){

}

void    ExportData(){
    freopen("binaryCode.txt","w",stdout);
    for(int i = 1; i <= code.lineNum; i++){
        cout << code.line[i] << '\n';
    }
}

int 	main()
{
    GetRawInput();  // nhap du lieu
    PreProcess();   // tien xu li
    Process();      // xu li lenh
    ExportData();   // xuat du lieu
	return 0;
}
