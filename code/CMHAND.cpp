#include<bits/stdc++.h>
using namespace std;

#define ll long long


ofstream plotxt;

void detectdeadlock(vector<set<ll>> &wfg){
    ll nodes=wfg.size()-1;
   
    bool detectedco=false,detectedfifo=false,detectednfifo=false;


    

    queue<pair<ll,ll>> co;                  //CO Channel

    map<pair<ll,ll>,queue<pair<ll,ll>>> fifo;   //FIFO Channel

    vector<pair<ll,ll>> nonfifo;            //NON-FIFO Channel

    ll numprobesco=0;   ll numprobesfifo=0;ll numprobesnonfifo=0;

    set<ll>vis;

    for(ll i=1;i<=nodes;i++){

        /*CHECKING WHETHER DEADLOCK WILL BE DETECTED FROM THIS NODE*/

        stack<ll>dfs;
        dfs.push(i);
        bool can=false;
        vector<bool>invis(nodes+1,false);
        while(!dfs.empty()){
            ll now=dfs.top();
            invis[now]=true;
            dfs.pop();
            for(auto x:wfg[now])
            {
                if(x==i)
                {
                    can=true;
                    break;
                }
                else if(!invis[x])
                    dfs.push(x);
            }
            if(can)
                break;
        }


        if(!can)
            continue;

        /**/







        
        /*CAUSAL ORDER DELIVERY*/
        
        
        while(!co.empty())
            co.pop();
        numprobesco=0;
        detectedco=false;
        vis.clear();
        vis.insert(i);
     
            
        for(auto x:wfg[i])
            co.push({i,x});
      
        while(!co.empty()){
            ll init=co.front().first;
            ll dest=co.front().second;
            // cout<<init<<" "<<dest<<"\n";
            numprobesco++;
            co.pop();
            if(init==dest){
                detectedco=true;
                break;
            }
            else if(vis.find(dest)!=vis.end())
                continue;
            vis.insert(dest);
            for(auto x:wfg[dest]){
                
                co.push({init,x});
            }
            
        }
        
        cout<<"CO:"<<" "<<numprobesco<<"\n";
        
        /**/
        
    


    
        /*FIFO DELIVERY*/


        fifo.clear();
        numprobesfifo=0;
        detectedfifo=false;
        vis.clear();
        vis.insert(i);
     
        for(auto x:wfg[i])
            fifo[{i,x}].push({i,x});
            

        while(!detectedfifo){
            for(auto x:fifo){
                if(x.second.empty())
                    continue;
                ll init=x.second.front().first;
                ll dest=x.second.front().second;
                // cout<<x.first.first<<" "<<x.first.second<<":"<<init<<" "<<dest<<"\n";
                numprobesfifo++;
                fifo[x.first].pop();
                if(init==dest){
                    detectedfifo=true;
                    break;
                }
                else if(vis.find(dest)!=vis.end())
                    continue;
                vis.insert(dest);
                for(auto y:wfg[dest]){
                    
                    fifo[{dest,y}].push({init,y});
                }
                
            }
        }

        cout<<"FIFO:"<<" "<<numprobesfifo<<"\n";

        /**/

       
        
    
    
        /*NONFIFO DELIVERY*/


        nonfifo.clear();
        numprobesnonfifo=0;
        detectednfifo=false;
        vis.clear();
        vis.insert(i);
            
        for(auto x:wfg[i])
            nonfifo.push_back({i,x});
        
        while(!nonfifo.empty()){
            ll index=rand()%(nonfifo.size());
            ll init=nonfifo[index].first;
            ll dest=nonfifo[index].second;
            // cout<<init<<" "<<dest<<"\n";
            nonfifo[index]=nonfifo[nonfifo.size()-1];
            nonfifo.pop_back();
            numprobesnonfifo++;
            if(init==dest){
                detectednfifo=true;
                break;
            }
            else if(vis.find(dest)!=vis.end())
                continue;
            vis.insert(dest);
            for(auto x:wfg[dest]){
                
                nonfifo.push_back({init,x});
            }
            
        }
        
        cout<<"NONFIFO:"<<" "<<numprobesnonfifo<<"\n";
        

        /**/

        plotxt<<nodes<<" "<<numprobesco<<" "<<numprobesfifo<<" "<<numprobesnonfifo<<"\n";

       
        break;
    }
       
}

int main(){

    plotxt.open ("./CMHAND.txt");
    srand(time(0));
    
    ll nodes=5;
    set<ll>temp;
    vector<set<ll>>graph;  
    while(nodes<=1000){
        
        temp.clear();
        graph.clear();
        for(ll i=0;i<=nodes;i++)
            graph.push_back(temp);
        
        /*RANDOM GRAPH GENERATION*/

        
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
                        graph[i].insert(ran);
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                    else{
                        ran=*notused.begin();
                        if(ran==i)
                            ran=-(*neg.begin());
                        graph[i].insert(ran);
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                }
                else
                {   
                    ll ran=-(*neg.lower_bound(-value));
                    if(ran!=i)
                    {
                        graph[i].insert(ran);
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                    else{
                        ran=*notused.begin();
                        if(ran==i)
                            ran=-(*neg.begin());
                        graph[i].insert(ran);
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
                        graph[i].insert(ran);
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                    else{
                        ran=*notused.begin();
                        if(ran==i)
                            ran=-(*neg.begin());
                        graph[i].insert(ran);
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                }
                else
                {
                    ll ran=*notused.lower_bound(value);
                    if(ran!=i)
                    {
                        graph[i].insert(ran);
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                    else{
                        ran=*notused.begin();
                        if(ran==i)
                            ran=-(*neg.begin());
                        graph[i].insert(ran);
                        notused.erase(ran);
                        neg.erase(-ran);
                    }
                }
                
            }
        }
        for(ll i=1;i<=nodes;i++){
            ll more=rand()%(min(nodes/4,(ll)5));
            while(more--){
                ll value=rand()%(nodes+1);
                while(value==0 || value==i)
                    value=rand()%(nodes+1);
                if(graph[i].find(value)==graph[i].end() and value!=i)
                    graph[i].insert(value);
            }
        }
        cout<<nodes<<"\n";
        detectdeadlock(graph);
        cout<<"\n";
        
        
        /**/
        
 

        nodes++;
    }
    //     set<ll>hoho;
    // for(ll i=0;i<=5;i++)
    //     graph.push_back(hoho);
    // for(ll i=1;i<=3;i++)
    //     graph[i].insert(i+1);
    
    // graph[3].insert(5);

    // detectdeadlock(graph);
    plotxt.close();
}