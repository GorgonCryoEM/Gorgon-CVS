#!/usr/bin/python
# Copyright (C) 2005-2008 Washington University in St Louis, Baylor College of Medicine.  All rights reserved
# Author:  Mike Marsh (michael.marsh@bcm.edu)
# Class:  StructurePrediction
# Class Description: Class that represents all of the secels predicted to exist based on primary sequence.
#                    More info in: correspondence-doc.txt
#

from Helix import Helix
from Coil import Coil
from Strand import Strand
from Chain import Chain

class StructurePrediction:  #results of secondary-structure prediction
  def __init__(self, filename):
    secelIndex=0
    self.secelDict={}
    self.params=None
    self.comments=None

    lines=open(filename).readlines()
    chain=Chain(str.strip(lines[0]))

    # loop pre-conditions
    # i is the next char in the predictionStr
    predictionsStr=lines[1]
    current='-'
    start=1
    helixCount=0
    strandCount=0
    coilCount=0
    for i,index in zip(predictionsStr,range(1,len(predictionsStr)+1)):

      prev=current
      current=i

      if prev != current:
	stop=index-1
	print '%s: %s-%s' %(prev,start,stop)

	if prev=='H':
	  helixCount=helixCount+1
	  label='H' + str(helixCount)
	  secel = Helix(chain,label,start,stop)
	  #chain.secel_list.append(secel)

	elif prev=='E':
	  strandCount=strandCount+1
	  label='E' + str(strandCount)
	  secel = Strand(chain,label,start,stop)
	  #chain.secel_list.append(secel)

	elif prev=='-':
	  coilCount=coilCount+1
	  label='C' + str(coilCount)
	  secel = Coil(chain,label,start,stop)
	  #chain.secel_list.append(secel)

	else:
	  errString="got %s when rexpecting 'H','E', or '-'" %prev
	  raise ValueError(errString)
	start = index
	self.secelDict[secelIndex]=secel
	secelIndex = secelIndex+1
	
    print chain.to_pdb()