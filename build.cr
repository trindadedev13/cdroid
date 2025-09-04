require "option_parser"

def run(*cmd)
  res = system *cmd
  puts "Failed to run #{cmd}" if !res
end

op_build = false
op_fmt = false
op_prepare = false

option_parser = OptionParser.parse do |parser|
  parser.banner = "CDroid 0.1.0 Build Program"

  parser.on "-b", "--build", "Builds the library" do
    op_build = true
  end

  parser.on "-fmt", "--format", "Format all files" do
    op_fmt = true
  end

  parser.on "-p", "--Prepare", "Prepare android structure" do
    op_prepare = true
  end

  parser.on "-h", "--help", "Displays help" do
    puts parser
  end
end

if op_fmt
  folders = [
    "src",
    "include/cdroid/internal",
    "android/app/src/main/java/cdroid/app"
  ]
  exts = [ ".c", ".h", ".java" ]
  folders.each do |fo|
    exts.each do |ext|
      Dir.glob("#{fo}/*#{ext}") do |f|
        puts "Formated #{f}."
        run "clang-format -i --style=GNU \"#{f}\""
      end
    end
  end
  
  # exit 0
end

NDK_DIR = ENV["ANDROID_NDK"] || ENV["ANDROID_NDK_HOME"]
ANDROID_PLATFORM = 26
ABIS = [ "arm64-v8a", "armeabi-v7a", "x86_64", "x86" ]

if op_build
  ABIS.each do |abi|
    b = "build/#{abi}"
    run (
      "cmake -B #{b} -S . " \
      "-DCMAKE_TOOLCHAIN_FILE=#{NDK_DIR}/build/cmake/android.toolchain.cmake " \
      "-DANDROID_ABI=#{abi} " \
      "-DANDROID_PLATFORM=#{ANDROID_PLATFORM} " \
      "-DCMAKE_BUILD_TYPE=Release "
    )
    run "cmake --build #{b}"
  end
end

if op_prepare
  ABIS.each do |abi|
    src = "build/#{abi}/libcdroid.so"
    dest = "android/app/src/main/jniLibs/#{abi}/"
    Dir.mkdir_p(dest)
    File.copy(src, "#{dest}/libcdroid.so")
    puts "File #{src} copied to #{dest}/libcdroid.so."
  end
end