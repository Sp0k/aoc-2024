# frozen_string_literal: true

def build_disk(disk_map)
  file_counter = 0
  disk = []

  disk_map.chars.each_with_index do |char, index|
    length = char.to_i
    if index.even?
      disk.concat([file_counter] * length) # Add file blocks
      file_counter += 1
    else
      disk.concat(['.'] * length) # Add free space
    end
  end

  disk
end

def compact_disk(disk)
  # Traverse the disk from right to left
  (disk.length - 1).downto(0) do |i|
    next if disk[i] == '.'

    (0...i).each do |j|
      if disk[j] == '.'
        disk[j] = disk[i]
        disk[i] = '.'
        break
      end
    end
    print '*'
  end

  disk
end

def calculate_checksum(disk)
  checksum = 0

  disk.each_with_index do |block, index|
    next if block == '.'

    checksum += index * block.to_i
  end

  checksum
end

# Read input
file_name = ARGV
unless file_name.length == 1
  puts 'Please add your input file'
  return
end

file_path = "../resources/#{file_name[0]}"
disk_map = File.read(file_path).strip

# Process the disk
disk = build_disk(disk_map)
compacted_disk = compact_disk(disk)
checksum = calculate_checksum(compacted_disk)

# Output the result
puts
puts "The resulting filesystem checksum is #{checksum}"
