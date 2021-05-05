#include<bits/stdc++.h>
using namespace std;

#define ll long long

ll nodes;
ofstream plotxt;

void detectdeadlock(ll wfg[])
{
    vector<pair<ll,ll>> labels(nodes+1,{1,1}); //first->public , second->private


    ll sr=2;

    vector<ll>wfgreverse[nodes+1];   //edge reversed wfg

    for(ll i=1;i<=nodes;i++){
        wfgreverse[wfg[i]].push_back(i);
        labels[i].first=sr;
        labels[i].second=sr++;
    
    }
    

    ll COcount=0;                 // number of transmits before deadlock detection CO channels
    ll Nonfifocount=0;              // number of transmits before deadlock detection NON-FIFO channels
    ll Fifocount=0;                 // number of transmits before deadlock detection FIFO channels
    bool doneco=false,donenfifo=false,donefifo=false;

  
    for(ll i=1;i<=nodes;i++)
    {
         /*CHECKING WHETHER DEADLOCK WILL BE DETECTED FROM THIS NODE*/

        stack<ll>dfs;
        dfs.push(i);
        bool can=false;
        vector<bool>invis(nodes+1,false);
        while(!dfs.empty()){
            ll now=dfs.top();
            invis[now]=true;
            dfs.pop();
            
            if(wfg[now]==i)
            {
                can=true;
                break;
            }
            else if(!invis[wfg[now]])
                dfs.push(wfg[now]);
        }


        if(!can)
            continue;

        /**/

        




        queue<ll>bfs;                   //CO channel

        vector<ll>probes;               //Non-FIFO channel;

        map<pair<ll,ll>,queue<ll>> fifo;      //FIFO Channel

        

            sr=2;
            for(ll j=1;j<=nodes;j++)
            {
                labels[j].first=1;
                labels[j].second=1;
            }

            for(ll j=1;j<=nodes;j++){
                labels[j].first=sr;
                labels[j].second=sr++;
            
            }
    

    
            /*CAUSAL ORDERING DETECTION*/
            
            labels[i].first=sr;
            labels[i].second=sr++;
            
            for(ll j=0;j<wfgreverse[i].size();j++)
                bfs.push(wfgreverse[i][j]);

            while(!bfs.empty()){
                ll cur=bfs.front();
                
            
                COcount++;
                bfs.pop();
                if(labels[cur].first>labels[wfg[cur]].first)
                    continue;
                else if(labels[cur].first<labels[wfg[cur]].first)
                    labels[cur].first=labels[wfg[cur]].first;
                else if(labels[cur].second==labels[wfg[cur]].first)
                {
                    doneco=true;
                    break;
                }
            
                for(ll j=0;j<wfgreverse[cur].size();j++)
                    bfs.push(wfgreverse[cur][j]);
                    
            
            }
            
            cout<<"CO:" <<COcount<<"\n";
            

            /**/
      
            sr=2;
            for(ll j=1;j<=nodes;j++)
            {
                labels[j].first=1;
                labels[j].second=1;
            }

            for(ll j=1;j<=nodes;j++){
                labels[j].first=sr;
                labels[j].second=sr++;
            
            }
    

    
            /*FIFO DETECTION*/
            
            labels[i].first=sr;
            labels[i].second=sr++;

    
            
        
            for(ll j=0;j<wfgreverse[i].size();j++)
                fifo[{i,wfgreverse[i][j]}].push(wfgreverse[i][j]);

            while(!donefifo){
                for(auto x: fifo)
                {
                    if(x.second.empty())
                        continue;
                    ll cur=x.second.front();
                
                    Fifocount++;
                    fifo[x.first].pop();
                    if(labels[cur].first>labels[wfg[cur]].first)
                        continue;
                    else if(labels[cur].first<labels[wfg[cur]].first)
                        labels[cur].first=labels[wfg[cur]].first;
                    else if(labels[cur].second==labels[wfg[cur]].first)
                    {
                        donefifo=true;
                        break;
                    }
                
                    for(ll j=0;j<wfgreverse[cur].size();j++)
                        fifo[{cur,wfgreverse[cur][j]}].push(wfgreverse[cur][j]);
                        
                }
            }
            cout<<"FIFO: "<<Fifocount<<"\n";
            
            
            /**/

        
            sr=2;
            for(ll j=1;j<=nodes;j++)
            {
                labels[j].first=1;
                labels[j].second=1;
            }

            for(ll j=1;j<=nodes;j++){
                labels[j].first=sr;
                labels[j].second=sr++;
            
            }

            /*NON-FIFO DETECTION*/

            labels[i].first=sr;
            labels[i].second=sr++;

    
            
            for(ll j=0;j<wfgreverse[i].size();j++)
                probes.push_back(wfgreverse[i][j]);

            
            while(!probes.empty()){
                ll value=rand()%probes.size();
                ll cur=probes[value];
                probes[value]=probes[probes.size()-1];
                probes.pop_back();
                Nonfifocount++;
                if(labels[cur].first>labels[wfg[cur]].first)
                    continue;
                else if(labels[cur].first<labels[wfg[cur]].first)
                    labels[cur].first=labels[wfg[cur]].first;
                else if(labels[cur].second==labels[wfg[cur]].first)
                    break;
            
                for(ll j=0;j<wfgreverse[cur].size();j++)
                    probes.push_back(wfgreverse[cur][j]);
                    

            }
            
            cout<<"NONFIFO: "<<Nonfifocount<<"\n";
            
            /**/

            plotxt<<nodes<<" "<<COcount<<" "<<Fifocount<<" "<<Nonfifocount<<"\n";

        
        break;
        
    }


}


int main(){
    
    plotxt.open ("./MMSR.txt");

    nodes=5;
    srand(time(0));
    while(nodes<=1000){
        
        /*RANDOM GRAPH GENERATION*/

        ll adj[nodes+1];
        set<ll>notused;
        set<ll>neg;
        for(ll i=1;i<=nodes;i++)
        {
            notused.insert(i);
            neg.insert(-i);
        }
      
        for(ll i=1;i<=nodes;i++){
            ll value=rand()%(nodes+1);
            if(rand()%2==0){
                if(notused.lower_bound(value)!=notused.end())
                {
                    ll ran=*notused.lower_bound(value);
                    if(ran!=i)
                    {
                        adj[i]=ran;
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                    else{
                        ran=*notused.begin();
                        if(ran==i)
                            ran=-(*neg.begin());
                        adj[i]=ran;
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                }
                else
                {
                    ll ran=-(*neg.lower_bound(-value));
                    if(ran!=i)
                    {
                        adj[i]=ran;
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                    else{
                        ran=*notused.begin();
                        if(ran==i)
                            ran=-(*neg.begin());
                        adj[i]=ran;
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                }
            }
            else{
                if(neg.lower_bound(value)!=neg.end())
                {
                    
                    ll ran=-(*neg.lower_bound(-value));
                    if(ran!=i)
                    {
                        adj[i]=ran;
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                    else{
                        ran=*notused.begin();
                        if(ran==i)
                            ran=-(*neg.begin());
                        adj[i]=ran;
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                }
                else
                {
                    ll ran=*notused.lower_bound(value);
                    if(ran!=i)
                    {
                        adj[i]=ran;
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                    else{
                        ran=*notused.begin();
                        if(ran==i)
                            ran=-(*neg.begin());
                        adj[i]=ran;
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                }
                
            }
        }
        /**/

        cout<<nodes<<"\n";

        detectdeadlock(adj);

        cout<<"\n";
        nodes++;
    }
    plotxt.close();
}