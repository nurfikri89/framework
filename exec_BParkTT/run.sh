filename=example_ttbar_2lep
maxEvents=50000
maxNFiles=5
sample=MC18_TT_2L

./${filename} --sample ${sample} --nEvents ${maxEvents} --nFiles ${maxNFiles}
