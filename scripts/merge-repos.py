#!/usr/bin/env python3

import yaml

# Load YAML repos files
with open('ros2.repos', 'r') as ros2_file:
    ros2 = yaml.safe_load(ros2_file)

with open('spaceros.repos', 'r') as spaceros_file:
    spaceros = yaml.safe_load(spaceros_file)

# Merge repos
for repo, data in spaceros['repositories'].items():
    ros2['repositories'][repo] = data

# Sort repositories and create a new ordered dictionary
sorted_repositories = {repo: ros2['repositories'][repo] for repo in sorted(ros2['repositories'].keys())}
ros2['repositories'] = sorted_repositories

# Write the updated YAML back to file
with open('ros2.repos', 'w') as ros2_file:
    yaml.dump(ros2, ros2_file, default_flow_style=False, explicit_start=True)
