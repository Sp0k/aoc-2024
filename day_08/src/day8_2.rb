# frozen_string_literal: false

require 'set'

# Get file name
file_name = ARGV
unless file_name.length == 1
  puts 'Please add the input file'
  return
end

# Create file path
file_path = "../resources/#{file_name[0]}"

# Open the file
map = File.readlines(file_path, chomp: true)

# Get the antenna's positions on the map
m = map.length
n = map[0].length
positions = Hash.new { |hash, key| hash[key] = [] }

(0...m).each do |i|
  (0...n).each do |j|
    next if map[i][j] == '.'

    positions[map[i][j]] << [i, j]
  end
end

# Find all the antinodes
antinodes = Set.new
positions.each_value do |freq_positions|
  freq_positions.each do |(x1, y1)|
    freq_positions.each do |(x2, y2)|
      next if [x1, y1] == [x2, y2]

      dx = x2 - x1
      dy = y2 - y1
      antinodes.add([x2, y2])

      new_x = x2 + dx
      new_y = y2 + dy
      while (new_x >= 0 && new_x < m) && (new_y >= 0 && new_y < n)
        antinodes.add([new_x, new_y])
        new_x += dx
        new_y += dy
      end
    end
  end
end

# Output
puts "There are #{antinodes.size} locations within the bounds of the map!"
