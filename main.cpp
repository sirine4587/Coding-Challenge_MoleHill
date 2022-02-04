#include <string>
#include <iostream>
using namespace std;
string line[20];
bool visited[20][20];

inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}

template<typename T = int>
inline T in(){
    char c=nc();T x=0; int f=1;
    for(;c>'9'||c<'0';c=nc())if(c=='-')f=-1;
    for(;c>='0'&&c<='9';x=x*10+c-'0',c=nc()); x*=f;
    return x;
}


/*This function returns the number of mole hills inside gardens.
 It takes as parameters i (ligne's number), j (column's number) and a character c which validates if we are inside the garden or not */
int dp(int i, int j,char c ){

    if (visited[i][j]){
        return 0;
    }
    if (line[i][j] =='-' || line[i][j] =='+' ||line[i][j] =='|' ||line[i][j] =='.' ){
        return 0;
    }

    visited[i][j]= true;
    bool k = (line[i][j]=='o' && c =='C');
    line[i][j] =c;
    return (k ?1 : 0 )+ dp(i-1,j,c) + dp(i+1,j,c)+dp(i, j-1,c)+dp(i, j+1,c);


}
/* We will extract each line and verify :
1- if there is a white space then we are inside a garden so we call the function dp.
2- if there is a mountain hill we have to verify its contour. 
3- if the mole hill we found is outside the garden we assume that all its adjacent mole hill are also outside the garden 
(so we replace it by a dot)*/

void solve(){
    int nb = 0 ;
    for (int i = 1; i <17; i++) {

        string &ch = line[i];

        int j ;
        while(ch.find(' ')!= string::npos){
            j = ch.find(' ');
            nb += dp(i,j,'C');
        }
        while(ch.find('o')!= string::npos){
            j = ch.find('o');
            int k1 = j;
            int k2 = i;
           
            if (line[i-1][j]=='.' || line[i-1][j]=='C'){
                nb += dp(i,j,line[i-1][j]);
                continue;
            }
            if (ch[j-1]=='C' || ch[j-1]=='.'){
                nb += dp(i,j, ch[j-1]);
                continue;
            }
            while(line[k2][j] =='o'){
                    k2++;
            }
            while(ch[k1] =='o'){
                    k1++;
            }
            if (line[i-1][j]=='-' && line[i-2][j] =='C'&& ch[j-1]=='|'&& ch[j-2]=='C'){
                nb += dp(i,j,'.'); //corner case if two gardens are inside each other so we take the outside one.
                continue;
            }
            if(line[k2][j]!='.' && ch[k1]!='.' ) 
            {

                nb += dp(i,j,'C');
             
            }
            else{
                nb += dp(i,j,'.');
                
            }
        }
       
        }

    cout<<nb<<endl;
}



int main()
{

    line[0] ="..................";  // We add a contour of points to the area so that we can treat the area's real contour's cases
    line[17] ="..................";

    for (int i = 1; i <=16; i++) {

        string ch;
        getline(cin, ch);
        line[i] ='.' + ch+ '.'; 
    }
    for (int i = 0;i<=17;i++){
        for(int j = 0; j <=17 ; j++){
            visited[i][j] = false;
        }
    }

    solve();
    return 0;
}
