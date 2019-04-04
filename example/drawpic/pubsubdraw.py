#pub-sub draw pic
#result
# 4k 1client [395 7150]
# 4k 5client [1092 4451]
# 4k 10client [2037 6344]
# 40k 1client [755 5565]
# 40k 5client [2733 9834]
# 40k 10client [5155 13881]
# 400k 1client [6133 17831]
# 400k 5client [20302 66571]
# 400k 10client [37943 209672]
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import os
DIRPATH = "/home/lrhcmp/cmpshare/zmq4.3.1/libzmq-4.3.1/example/drawpic/delay/pubsub/400k/"

diff1cli = []
diff5cli = []
diff10cli = []

'''
def drawpic():
  plt.xlim((0, len(difftm4k)))
  plt.ylim((gmin, gmax))
  plt.xlabel('pull-push sample cnt')
  plt.ylabel('us')
  x = range(0, len(difftm4k))
  plt.plot(x, difftm4k, color='red', label='4k')
  plt.plot(x, difftm40k, color='blue', label='40k')
  # plt.plot(x, difftm400k, color='yellow', label='400k')
  plt.legend(loc='upper right')
  plt.savefig("/home/lrhcmp/cmpshare/zmq4.3.1/libzmq-4.3.1/example/drawpic/pullput.png")
'''
def drawpic(vec, labelstr):
  # plt.xlim((0, len(vec)))
  max = 0
  min = 0
  for id in range(0, len(vec)):
    if vec[id] > max:
      max = vec[id]
    if min == 0:
      min = vec[id]
    elif min > vec[id]:
      min = vec[id]
  print "[%d %d]" % (min, max)
  plt.ylim((min, max))
  plt.xlabel('400k sub-pub sample cnt')
  plt.ylabel('us')
  x = range(0, len(vec))
  plt.plot(x, vec, color='red', label=labelstr)
  # plt.plot(x, difftm40k, color='blue', label='40k')
  # plt.plot(x, difftm400k, color='yellow', label='400k')
  plt.legend(loc='upper right')
  plt.savefig("/home/lrhcmp/cmpshare/zmq4.3.1/libzmq-4.3.1/example/drawpic/subpub%s.png" % labelstr)
  plt.close()

def readsinglefile(path):
  fread = open(path, "r")
  vec = []
  while True:
    line = fread.readline()
    if not line:
      break
    line = line.strip()
    if line.find(" ") == -1:
      continue
    sec = int(line.split(' ')[0])
    usec = int(line.split(' ')[1])
    vec.append(sec * 1000000 + usec)
  fread.close()
  return vec

def getlatestdata(nestvec):
  result = []
  size = []
  for vec in nestvec:
    size.append(len(vec))
  if len(list(set(size))) != 1:
    print "size not equal"
  for id in range(0, size[0]):
    max = nestvec[0][id]
    for vecid in range(1, len(nestvec)):
      if nestvec[vecid][id] > max:
        max = nestvec[vecid][id]
    result.append(max)
  return result


#if subtime, get the latest number
def gettm(path):
  filter = path[-10:]
  filepath = ""
  files = []
  vec = []
  dir = ""
  if filter.find("pubtime") != -1:
    filepath = path
  elif filter.find("subtime") != -1:
    dir = path[:-7]
    files = os.listdir(dir)
  if filepath:
    vec = readsinglefile(filepath)
  if files:
    tmp = []
    for file in files:
      if file.find("subtime") == -1:
        continue
      tmp.append(readsinglefile(dir + file))
    if len(tmp) == 1:
      vec = tmp[0]
    else:
      vec = getlatestdata(tmp)
  return vec
      

def getmaxdiff(path, vec):
  subtm = gettm(path + "subtime")
  pubtm = gettm(path + "pubtime")
  maxdiff = 0
  mindiff = 0
  maxid = 0
  minid = 0
  print "[%d %d]" % (len(subtm), len(pubtm))
  for id in range(0, 1000):
    diff = subtm[id] - pubtm[id]
    if diff > maxdiff:
      maxdiff = diff
      maxid = id
    if mindiff == 0:
      mindiff = diff
    elif mindiff > diff:
      mindiff = diff
      minid = id
  maxdiff = 0
  mindiff = 0
  for id in range(0, 1000):
    if id == maxid or id == minid:
      continue
    diff = subtm[id] - pubtm[id]
    if diff > maxdiff:
      maxdiff = diff
    if mindiff == 0:
      mindiff = diff
    elif mindiff > diff:
      mindiff = diff
    vec.append(diff)

if __name__ == '__main__':
  global diff1cli
  global diff5cli
  global diff10cli
  global DIRPATH
  getmaxdiff(DIRPATH + "1cli/", diff1cli)
  getmaxdiff(DIRPATH + "5cli/", diff5cli)
  getmaxdiff(DIRPATH + "10cli/", diff10cli)
  drawpic(diff1cli, '1client')
  drawpic(diff5cli, '5client')
  drawpic(diff10cli, '10client')