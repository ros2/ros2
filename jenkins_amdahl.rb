#!/usr/bin/env ruby
# nokogiri on ubuntu needs "apt-get install ruby-nokogiri"
# or you can get it from rubygems
require 'nokogiri'
require 'open-uri'
require 'time'

if ARGV.size < 2
  puts "usage: jenkins_amdahl.rb JOB NUMBER"
  puts "  example: jenkins_amdahl.rb ci_windows 1206"
  exit(1)
end

uri = "http://ci.ros2.org/job/#{ARGV[0]}/#{ARGV[1]}/consoleFull"
page = Nokogiri::HTML(open(uri))
console = page.css("pre[class='console-output']")
sections = [ ]
t = nil
console.text.lines do |line|
  if line.include?("# BEGIN SUBSECTION:")
    name = line.slice((line.index("# BEGIN SUB") + 20)..-1)
    sections.push({ "type" => "subsection", "name" => name, "t" => t })
  elsif line.include?("+++ Building '")
    name = line.slice((line.index("+++ Building '") + 14)..-4)
    sections.push({ "type" => "build", "name" => name, "t" => t })
  elsif line.include?("+++ Testing '")
    name = line.slice((line.index("+++ Testing '") + 13)..-4)
    sections.push({ "type" => "test", "name" => name, "t" => t })
  else
    t = Time.parse(line.split(' ')[0])
  end
end
sections.push({'name'=>"end", 't'=>t})

(0..sections.length-2).each do |i|
  s = sections[i]
  type = s['type']
  s_next = sections[(i+1)..-1].find{|x| x['type'] == s['type']}
  s_next = sections[i+1] if not s_next
  s['dt'] = s_next['t'] - s['t']
end
sections.pop
sections.sort!{ |x,y| y['dt'] <=> x['dt'] }

def print_table(label, sections)
  puts "\n#{label.upcase}S (slowest 10, in seconds)"
  puts "============================================="
  items = sections.select{|s| s['type'] == label}
  items[0..9].each do |item|
    puts "#{item['dt'].to_i.to_s.rjust(6)} #{item['name']}"
  end
end

print_table('subsection', sections)
print_table('build', sections)
print_table('test', sections)

