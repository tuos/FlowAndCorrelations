
f = open("size1Mlist.txt")
lines = f.readlines()
num=0
for line in lines:
    num+=1
#    print line

print num
#print lines[499]

for i in range(155):
  fileName='listFiles_jb'+str(i)+'.txt'
  filesI=open(fileName, 'w')
  for j in range(30):
    if(i*30+j<4638):
      filesI.write(lines[i*30+j])
  filesI.close()
  #print(fileName)


