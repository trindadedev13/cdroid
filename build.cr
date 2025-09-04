require "option_parser"

def run(*cmd)
  res = system *cmd
  puts "Failed to run #{cmd}" if !res
end

def delete(f)
  if Dir.exists?(f)
    d = Dir.new f
    d.children.each do |child|
      delete child
    end
  elsif File.exists?(f)
    File.delete f
  end
end

def cleanup
  delete "build/" if Dir.exists?("build")
  delete "example/build/" if Dir.exists?("example/build")
end

op_build = false
op_fmt = false
op_prepare = false
op_debug = false
op_ex = false

option_parser = OptionParser.parse do |parser|
  parser.banner = "CDroid 0.1.0 Build Program"

  parser.on "-b", "--build", "Builds the library" do
    op_build = true
  end

  parser.on "-fmt", "--format", "Format all files" do
    op_fmt = true
  end

  parser.on "-p", "--prepare", "Prepare android structure" do
    op_prepare = true
  end

  parser.on "-d", "--debug", "Build debug" do
    op_debug = true
  end

  parser.on "-e", "--example", "Builds example" do
    op_ex = true
  end

  parser.on "-c", "--clean", "Cleanup all before build" do
    cleanup
  end

  parser.on "-h", "--help", "Displays help" do
    puts parser
  end
end

if op_fmt
  folders = [
    "src",
    "include/cdroid",
    "include/cdroid/internal",
    "android/app/src/main/java/cdroid/app",
    "example/src",
  ]
  exts = [".c", ".h", ".java"]
  folders.each do |fo|
    exts.each do |ext|
      Dir.glob("#{fo}/*#{ext}") do |f|
        puts "Formated #{f}."
        run "clang-format -i \"#{f}\""
      end
    end
  end

  # exit 0
end

NDK_DIR          = ENV["ANDROID_NDK"] || ENV["ANDROID_NDK_HOME"]
ANDROID_PLATFORM = 26
ABIS             = ["arm64-v8a", "armeabi-v7a"]

def build(src, build, abi, is_debug)
  run(
    "cmake -B #{build} -S #{src} " \
    "-DCMAKE_TOOLCHAIN_FILE=#{NDK_DIR}/build/cmake/android.toolchain.cmake " \
    "-DANDROID_ABI=#{abi} " \
    "-DANDROID_PLATFORM=#{ANDROID_PLATFORM} " \
    "-DCMAKE_BUILD_TYPE=#{is_debug ? "Debug" : "Release"} "
  )
  run "cmake --build #{build}"
end

if op_build
  ABIS.each do |abi|
    if op_ex
      b = "example/build/#{abi}"
      build("example", b, abi, op_debug)
    else
      b = "build/#{abi}"
      build(".", b, abi, op_debug)
    end
  end
end

if op_prepare
  ABIS.each do |abi|
    if op_ex
      src = "example/build/#{abi}/libcdroid_main.so"
      dest = "android/app/src/main/jniLibs/#{abi}"
      Dir.mkdir_p(dest)
      File.copy(src, "#{dest}/libcdroid_main.so")
      puts "File #{src} copied to #{dest}/libcdroid_main.so."

      # copy the subdir build too
      src = "example/build/#{abi}/cdroid_build/libcdroid.so"
      dest = "android/app/src/main/jniLibs/#{abi}"
      Dir.mkdir_p(dest)
      File.copy(src, "#{dest}/libcdroid.so")
      puts "File #{src} copied to #{dest}/libcdroid.so."
    else
      src = "build/#{abi}/libcdroid.so"
      dest = "android/app/src/main/jniLibs/#{abi}"
      Dir.mkdir_p(dest)
      File.copy(src, "#{dest}/libcdroid.so")
      puts "File #{src} copied to #{dest}/libcdroid.so."
    end
  end
end
