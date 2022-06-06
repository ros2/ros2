#!/usr/bin/env ruby


require "yaml"

ros2 = YAML.load_file "ros2.repos"
spaceros = YAML.load_file "spaceros.repos"


spaceros["repositories"].each do |repo, data|
  ros2["repositories"][repo] = data
end

# Create a new hash so values can be inserted in sort-order.
repositories = Hash.new
ros2["repositories"].keys.sort.each do |repo|
  repositories[repo] = ros2["repositories"][repo]
end
ros2["repositories"] = repositories


File.write("ros2.repos", YAML.dump(ros2))
