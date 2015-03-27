#!/usr/bin/env python3

import argparse
import os

parser = argparse.ArgumentParser(description='Generate dockerfile')
parser.add_argument('template', help='The template file')
parser.add_argument('output', help='The output file')

args = parser.parse_args()

with open(args.template, 'r') as fh:
    temp = fh.read()


substitution_dict = {}
substitution_dict['uid'] = os.geteuid()

content = temp % substitution_dict

print("Outputting to %s " % args.output)
for l in content.splitlines():
    print('> %s' % l)

with open(args.output, 'w') as fh:
    fh.write(content)
