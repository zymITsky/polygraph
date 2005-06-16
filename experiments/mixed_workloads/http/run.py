#!/usr/bin/env python

import sys
sys.path.append('../../')
import evaluate
import config

dynamic_workload = {
    'fname': 'httpnoise',
    'pickle': config.workloadsdir + 'http_noise.pickle',
    'numeval': 0,
}

static_workloads = [
    {
        'fname': 'apache', 
        'pickle': config.workloadsdir + 'apache.pickle', 
        'numeval': 1000,
        'numtrain': 5
    },
    {
        'fname': 'atphttpd', 
        'pickle': config.workloadsdir + 'atphttpd.pickle', 
        'numeval': 1000,
        'numtrain': 5
    }
]

import sys
starttrial=0
trials=5
if len(sys.argv) > 1:
        starttrial=int(sys.argv[1])
        trials = starttrial+1

evaluate.bigeval(
	sig_names=['BayesAndTree', 'LCSeqTree', 'Bayes2'],
	training_streams=config.traces[80]['training'],
	fpos_eval_streams=config.traces[80]['eval'],
	fpos_eval_count='5000000',
	dynamic_workload=dynamic_workload,
	static_workloads=static_workloads,
	dynamic_range=[0,1,3] + range(5,21,5)+[30, 50],
	trials=5
)
