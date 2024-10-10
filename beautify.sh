# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "clang-format could not be found, please install it."
    exit 1
fi

# Get the clang-format version
CLANG_FORMAT_VERSION=$(clang-format --version)

# # Check if the version is 14.x.x
# if [[ "$CLANG_FORMAT_VERSION" != *"14."* ]]; then
#     echo "Error: clang-format version 14.x.x is required. Found: $CLANG_FORMAT_VERSION"
#     exit 1
# fi

make clean -C build || true
rm -r build/CMakeFiles || true
clang-format --verbose -i $(find . -name "*.hpp" -o -name "*.cpp" -o -name "*.inl")
