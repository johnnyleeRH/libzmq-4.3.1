#pull-push draw pic
#result
# [388 10032]  -- 4k
# [740 4610]   -- 40k
# [6235 21037] -- 400k
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
DIRPATH = "/home/lrhcmp/cmpshare/zmq4.3.1/libzmq-4.3.1/example/drawpic/delay/ipc/"

PUSHTM = ""
PULLTM = ""
pulltm = []
pushtm = []
difftm4k = []
difftm40k = []
difftm400k = []
gmin = 0
gmax = 0

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
  plt.xlabel('pull-push sample cnt')
  plt.ylabel('us')
  x = range(0, len(vec))
  plt.plot(x, vec, color='red', label=labelstr)
  # plt.plot(x, difftm40k, color='blue', label='40k')
  # plt.plot(x, difftm400k, color='yellow', label='400k')
  plt.legend(loc='upper right')
  plt.savefig("/home/lrhcmp/cmpshare/zmq4.3.1/libzmq-4.3.1/example/drawpic/pullput%s.png" % labelstr)
  plt.close()

def gettm(path, vec):
  fread = open(path, "r")
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

def getmaxdiff(diffvec):
  global PUSHTM
  global PULLTM
  global gmin
  global gmax
  global pushtm
  global pulltm
  pushtm = []
  pulltm = []
  # print DIRPATH + PUSHTM
  gettm(DIRPATH + PUSHTM, pushtm)
  gettm(DIRPATH + PULLTM, pulltm)
  maxdiff = 0
  mindiff = 0
  maxid = 0
  minid = 0
  for id in range(0, 1000):
    diff = pulltm[id] - pushtm[id]
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
    diff = pulltm[id] - pushtm[id]
    if diff > maxdiff:
      maxdiff = diff
    if mindiff == 0:
      mindiff = diff
    elif mindiff > diff:
      mindiff = diff
    diffvec.append(diff)
  # print "haha %d %d" % (mindiff, maxdiff)
  if gmax < maxdiff:
    gmax = maxdiff
  if gmin > mindiff:
    gmin = mindiff

if __name__ == '__main__':
  global PUSHTM
  global PULLTM
  PUSHTM = "4k/pushtime"
  PULLTM = "4k/pulltime"
  getmaxdiff(difftm4k)
  PUSHTM = "40k/pushtime"
  PULLTM = "40k/pulltime"
  getmaxdiff(difftm40k)
  PUSHTM = "400k/pushtime"
  PULLTM = "400k/pulltime"
  getmaxdiff(difftm400k)
  drawpic(difftm4k, '4k')
  drawpic(difftm40k, '40k')
  drawpic(difftm400k, '400k')