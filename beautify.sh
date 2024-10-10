make clean -C build || true
rm -r build/CMakeFiles || true
clang-format-11 --verbose -i $(find . -name "*.hpp" -o -name "*.cpp" -o -name "*.inl")
