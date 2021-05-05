#include<bits/stdc++.h>
using namespace std;


#define ll long long

ofstream plotxt;

void detectdeadlock(vector<set<ll>>wfg){
    ll nodes=wfg.size()-1;



    queue<pair<ll,ll>> co;                  //CO Channel

    map<pair<ll,ll>,queue<pair<ll,ll>>> fifo;   //FIFO Channel

    vector<pair<ll,ll>> nonfifo;            //NON-FIFO Channel

    set<ll>vis;
    ll numprobesco=0;ll numprobesfifo=0;ll numprobesnonfifo=0;

    bool knot=false;
    ll index=-1;


    /*KNOT PREDETECTION*/
    
    vector<set<ll>>reachable;
    for(ll i=0;i<=nodes;i++)
        reachable.push_back(vis);
    
    for(ll i=1;i<=nodes;i++){
        vector<bool>invis(nodes+1,false);
        queue<ll>bfs;
        bfs.push(i);
        while(!bfs.empty()){
            ll now=bfs.front();
            reachable[i].insert(now);
            invis[now]=true;
            bfs.pop();
            for(auto x:wfg[now])
            {   
                if(invis[x])
                    continue;
                bfs.push(x);
            }
        }
    }
    

    /**/

    for(ll i=1;i<=nodes;i++)
    {    
        /*CHECKING WHETHER DEADLOCK WILL BE DETECTED FROM THIS NODE*/
        bool can=true;
        set<ll>check=reachable[i];
        for(auto x:reachable[i]){
            if(check!=reachable[x])
            {
                can=false;
                break;
            }
        }
        if(!can || wfg[i].size()==0)
            continue;
        
        /**/



        
        /*CAUSAL ORDER DELIVERY*/
        
        while(!co.empty())
            co.pop();
        numprobesco=0;
        
        
        
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
            if(vis.find(dest)!=vis.end())
                continue;
            
            vis.insert(dest);
            
            
            for(auto x:wfg[dest])   
                co.push({init,x});    
            
        }
        numprobesco*=2;
        cout<<"CO:"<<" "<<numprobesco<<"\n";

        /**/
        









        /*FIFO DELIVERY*/


        fifo.clear();
        numprobesfifo=0;
        
    
        ll count=0;
        vis.clear();
        
        vis.insert(i);
        count+=wfg[i].size();
        for(auto x:wfg[i])
            fifo[{i,x}].push({i,x});
    
        
        
        while(count>0){
            for(auto x:fifo){
                if(x.second.empty())
                    continue;
                ll init=x.second.front().first;
                ll dest=x.second.front().second;
                // cout<<x.first.first<<" "<<x.first.second<<":"<<init<<" "<<dest<<"\n";
                numprobesfifo++; 
                fifo[x.first].pop();
                if(vis.find(dest)!=vis.end())    
                    continue;
                vis.insert(dest);
                for(auto y:wfg[dest]){    
                    fifo[{dest,y}].push({init,y});
                    
                }
            }
            count=0;
            for(auto x:fifo)
                count+=x.second.size();
        }
        numprobesfifo*=2;
        
        cout<<"FIFO:"<<" "<<numprobesfifo<<"\n";
        
        /**/

        
        







        /*NONFIFO DELIVERY*/

        nonfifo.clear();
        numprobesnonfifo=0;
        
        vis.clear();
        
        for(auto x:wfg[i]){
            
            nonfifo.push_back({i,x});
        }
    
        vis.insert(i);
        
        while(!nonfifo.empty()){
            ll index=rand()%(nonfifo.size());
            ll init=nonfifo[index].first;
            ll dest=nonfifo[index].second;
            // cout<<init<<" "<<dest<<"\n";
            numprobesnonfifo++;
            nonfifo[index]=nonfifo[nonfifo.size()-1];
            nonfifo.pop_back();

            if(vis.find(dest)!=vis.end())
                continue;
            vis.insert(dest);
            
            
            for(auto x:wfg[dest]){
                nonfifo.push_back({init,x});    
                
            }
            
        }
        
        numprobesnonfifo*=2;
        
        cout<<"NONFIFO:"<<" "<<numprobesnonfifo<<"\n";

        /**/

        plotxt<<nodes<<" "<<numprobesco<<" "<<numprobesfifo<<" "<<numprobesnonfifo<<"\n";


        break;

    }

}



int main(){

    plotxt.open ("./CMHOR.txt");
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
            ll more=rand()%(min(nodes/4,(ll)3));
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

    // set<ll>hoho;
    // for(ll i=0;i<=5;i++)
    //     graph.push_back(hoho);
    // for(ll i=1;i<=3;i++)
    //     graph[i].insert(i+1);
    // graph[4].insert(1);
    // graph[3].insert(5);

    // detectdeadlock(graph);
    
    plotxt.close();
}