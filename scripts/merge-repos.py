#!/usr/bin/env python3

import yaml
import argparse

parser = argparse.ArgumentParser(description='Merge YAML repository files.')
parser.add_argument('ros2_repos', help='The ROS2 repo YAML file.')
parser.add_argument('spaceros_repos', help='The SpaceROS repo YAML file.')
parser.add_argument('-o', '--output', default=None, help='Output file, will default to overwriting the ros2 repo')
args = parser.parse_args()

# Defalt to overwriting the ros2_repos file if not specified
output_file = args.output if args.output else args.ros2_file

# Load YAML repos files
with open(args.ros2_repos, 'r') as ros2_file:
    ros2 = yaml.safe_load(ros2_file)

with open(args.spaceros_repos, 'r') as spaceros_file:
    spaceros = yaml.safe_load(spaceros_file)

# Merge repos
for repo, data in spaceros['repositories'].items():
    ros2['repositories'][repo] = data

# Sort repositories and create a new ordered dictionary
sorted_repositories = {repo: ros2['repositories'][repo] for repo in sorted(ros2['repositories'].keys())}
ros2['repositories'] = sorted_repositories

# Write the updated YAML back to file
with open(output_file, 'w') as ros2_file:
    yaml.dump(ros2, ros2_file, default_flow_style=False, explicit_start=True)
