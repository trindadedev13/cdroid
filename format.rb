require "fileutils"

def run(cmd)
  success = system(cmd)
  abort("Failed to run: #{cmd}") unless success
end

if ARGV.length < 1
  puts "Usage: ruby format.rb <base_dir>"
  exit(1)
end

base_dir = File.expand_path(ARGV[0])
extensions = ["c", "h", "cpp", "hpp", "java"]

extensions.each do |ext|
  Dir.glob(File.join(base_dir, "**", "*.#{ext}")).each do |file|
    next if file.split(File::SEPARATOR).include?("build")
    next if file.split(File::SEPARATOR).include?("extern")

    puts "Formatted: " + file
    run("clang-format -i \"#{file}\"")
  end
end