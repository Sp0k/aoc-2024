# frozen_string_literal: false

def generate_combinations(size)
  ['+', '*', '||'].repeated_permutation(size).to_a
end

def calculate_combinations(goal, integers)
  sections = integers.size - 1
  combinations = generate_combinations(sections)

  combinations.each do |ops|
    sum = integers[0] # Start with the first integer
    integers[1..].each_with_index do |num, index|
      if ops[index] == '+'
        sum += num
      elsif ops[index] == '*'
        sum *= num
      elsif ops[index] == '||'
        new_sum = sum.to_s
        new_sum += num.to_s
        sum = new_sum.to_i
      end
    end

    # Check if the current combination achieves the goal
    return true if sum == goal
  end

  false # Return false if no combinations match the goal
end

# Read file input
file_name = ARGV

unless file_name.length == 1
  puts 'Please include the input file'
  return
end

file_path = "../resources/#{file_name[0]}"
input_file = File.read(file_path).split("\n")

# Initialize total calibration result
sum = 0

# Process each line
input_file.each do |line|
  integers = line.scan(/\b\d+\b/).map(&:to_i)
  goal = integers.shift # First number is the goal

  # Increment sum if the goal can be achieved
  sum += goal if calculate_combinations(goal, integers)
end

puts "The total calibration result is #{sum}"

