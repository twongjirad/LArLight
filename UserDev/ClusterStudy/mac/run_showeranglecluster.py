import sys
from ROOT import *
gSystem.Load("libClusterStudy")
from ROOT import larlight as fmwk

ana_proc = fmwk.ana_processor()
ana_proc.set_io_mode(fmwk.storage_manager.BOTH)
ana_proc.add_input_file(sys.argv[1])
ana_proc.set_input_rootdir("scanner")
ana_proc.set_output_file("out.root")
ana_proc.add_process(fmwk.ShowerAngleCluster())

ana_proc.run()
