import matplotlib.pyplot as plt
  
nodes = []
causal = []
fifo = []
nonfifo = []
nodes1 = []
causal1 = []
fifo1 = []
nonfifo1 = []
nodes2 = []
causal2 = []
fifo2 = []
nonfifo2 = []


for line in open('MMSR.txt', 'r'):
   
    
    lines = [i for i in line.split()]
    
    if int(lines[0]) >=250 and int(lines[0])<=300:
        nodes.append(int(lines[0]))
        causal.append(int(lines[1]))
        fifo.append(int(lines[2]))
        nonfifo.append(int(lines[3]))










for line in open('CMHAND.txt', 'r'):
   
    
    lines = [i for i in line.split()]
    
    if int(lines[0]) >=250 and int(lines[0])<=300:
        nodes1.append(int(lines[0]))
        causal1.append(int(lines[1]))
        fifo1.append(int(lines[2]))
        nonfifo1.append(int(lines[3]))

    

for line in open('CMHOR.txt', 'r'):
   
    
    lines = [i for i in line.split()]
    
    if int(lines[0]) >=250 and int(lines[0])<=300:
        nodes2.append(int(lines[0]))
        causal2.append(int(lines[1]))
        fifo2.append(int(lines[2]))
        nonfifo2.append(int(lines[3]))


      

fig, ax = plt.subplots(3)
 

ax[0].set_title("Mitchell Merritt's Algo")
# ax[0].set_xlabel('Number of Nodes')
# ax[0].set_ylabel('Number of Messages')
ax[0].plot(nodes, fifo, c= 'y', linestyle='dashed' , label='FIFO')
ax[0].plot(nodes, nonfifo, c= 'r', linestyle='dashed', label= 'Non-FIFO')
ax[0].plot(nodes, causal, c = 'g', linestyle='dashed', label='CAUSAL ORDERING')
ax[0].legend()




ax[1].set_title("Chandy Misra Haas's Algo (AND Model)")
# ax[1].set_xlabel('Number of Nodes')
ax[1].set_ylabel('Number of Messages')
ax[1].plot(nodes1, fifo1, c= 'y', linestyle='dashed' , label='FIFO')
ax[1].plot(nodes1, nonfifo1, c= 'r', linestyle='dashed', label= 'Non-FIFO')
ax[1].plot(nodes1, causal1, c = 'g', linestyle='dashed', label='CAUSAL ORDERING')
ax[1].legend()




ax[2].set_title("Chandy Misra Haas's Algo (OR Model)")
ax[2].set_xlabel('Number of Nodes')
# ax[2].set_ylabel('Number of Messages')
ax[2].plot(nodes2, fifo2, c= 'y', linestyle='dashed' , label='FIFO')
ax[2].plot(nodes2, nonfifo2, c= 'r', linestyle='dashed', label= 'Non-FIFO')
ax[2].plot(nodes2, causal2, c = 'g', linestyle='dashed', label='CAUSAL ORDERING')
ax[2].legend()


plt.show()