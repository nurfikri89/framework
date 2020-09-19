import os
import subprocess
import collections
import SampleDict

# REMEMBER TO SOURCE CRAB3 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#
# https://twiki.cern.ch/twiki/bin/view/CMS/DBS3APIInstructions
# https://github.com/dmwm/DBS/blob/master/Client/src/python/dbs/apis/dbsClient.py
# 
from dbs.apis.dbsClient import DbsApi 

dbs = DbsApi('https://cmsweb.cern.ch/dbs/prod/global/DBSReader')

#
# Make the samples dictionary. Grab from SampleDict.py
#
samples = collections.OrderedDict()
samples.update(SampleDict.samplesData18)
samples.update(SampleDict.samplesMC18)

for sample in samples:
  shortName    = sample
  dataset      = samples[sample]
  print "Saving path to files for sample = ", dataset
  #
  # This spits out a list of dictionary. Each element of the list
  # is a single file of the dataset
  #
  fileDictList = dbs.listFiles(dataset=dataset, detail=0)
  fout = "./NanoAODv7/%s.txt" %(shortName)
  fo = open(fout, "w")
  for fileDict in fileDictList:
    fileNameFull = fileDict["logical_file_name"]
    XROOTD = "root://xrootd-cms.infn.it/"
    fo.write(XROOTD+fileNameFull+'\n')
  fo.close()

